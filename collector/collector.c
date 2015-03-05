/*
$$LIC$$
 */
/*
 *    collector.c - example ipfix collector
 *
 *    Copyright Fraunhofer FOKUS
 *
 *    $Date: 2007/02/28 10:33:47 $
 *
 *    $Revision: 1.12 $
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <libgen.h>
#include <stdarg.h>
#include <fcntl.h>
#include <netdb.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif
#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif
#include <ipfix.h>
#ifdef DBSUPPORT
#include "ipfix_db.h"
#endif
#ifdef JSONLINESSUPPORT
# include "ipfix_jsonlines.h"
#endif
#include "ipfix_col.h"
#include "ipfix_def_fokus.h"
#include "ipfix_fields_fokus.h"
#include "ipfix_def_netscaler.h"
#include "ipfix_fields_netscaler.h"
#include "ipfix_reverse_fields_netscaler.h"

#include "mlog.h"
#include "mpoll.h"

/*------ defines ---------------------------------------------------------*/

#define CAFILE          "rootcert.pem"
#define CADIR           NULL
#define KEYFILE         "server.pem"
#define CERTFILE        "server.pem"

/*------ stuctures -------------------------------------------------------*/

typedef struct ipfix_collector_opts
{
    char           progname[30];
    int            debug;        /* some debug output */
    char           *logfile;

    char           *datadir;
    int            dbexport;     /* flag        */
    char           *dbuser;      /* db username */
    char           *dbpw;        /* db password */
    char           *dbpw_filename; /* db password from file */
    char           *dbname;      /* db name     */
    char           *dbhost;      /* hostname    */

    int            jsonexport;   /* flag        */
    char           *jsonfile;    /* filename    */
    int            json_record_unknown_sets; /* boolean */

    int            udp;          /* support udp clients  */
    int            tcp;          /* support tcp packets  */
    int            sctp;         /* support sctp clients */
    int            ssl;          /* ipfix over TLS/SSL   */
    char           *cafile;
    char           *cadir;
    char           *keyfile;     /* private key */
    char           *certfile;    /* certificate */
    int            port;         /* port number */
    int            maxcon;       /* backlog parameter for listen(2) */
    int            family;       /* AF_UNSPEC, _INET, _INET6 */

} ipfix_col_opts_t;

/*------ globals ---------------------------------------------------------*/

ipfix_col_opts_t  par;
int               verbose_level = 0;
int               *tcp_s=NULL, ntcp_s=0;       /* socket */
int               *udp_s=NULL, nudp_s=0;
int               *sctp_s=NULL, nsctp_s=0;
ipfix_col_t       *scol=NULL;

/*------ prototypes ------------------------------------------------------*/

/*------ static funcs ----------------------------------------------------*/

static void usage( char *taskname)
{
    const char helptxt[] =
        "[options]\n\n"
        "options:\n"
        "  -h                          this help\n"
        "  -4                          accept connections via AF_INET socket\n"
        "  -6                          accept connections via AF_INET6 socket\n"
        "  -o <datadir>                store files of collected data in this dir\n"
        "  -p <portno>                 listen on this port (default=4739)\n"
        "  -s                          support SCTP clients\n"
        "  -t                          support TCP clients\n"
        "  -u                          support UDP clients\n"
        "  -v                          increase verbose level\n"
#ifdef JSONLINESSUPPORT
        "jsonlines options:\n"
        "  --json                      export JSON to a file; one JSON doc/line\n"
        "  --jsonfile <filename>       file to append to, or '-' for stdout\n"
        "  --json-record-unknown-sets         include bytes of sets dropped due to no template\n"
#endif
#ifdef DBSUPPORT
#ifdef HAVE_GETOPT_LONG
        "db options:\n"
        "  --db                        export into database\n"
        "  --dbhost <hostname>         db host\n"
        "  --dbname <database>         db name\n"
        "  --dbuser <user>             db user\n"
        "  --dbpw   <password>         db password\n"
        "  --dbpw-filename <filename>  db password from first line of file\n"
#else
        "  -d                          export into database\n"
#endif
#ifdef SSLSUPPORT
        "ssl options:\n"
        "  --ssl                       expect tls/ssl clients\n"
        "  --key    <file>             private key file to use\n"
        "  --cert   <file>             certificate file to use\n"
        "  --cafile <file>             file of CAs\n"
        "  --cadir  <dir>              directory of CAs\n"
#endif
#endif
        "\n";

    fprintf( stderr, "\nipfix collector (%s %s)\n",
             "$Revision: 1.12 $", __DATE__ );

    fprintf( stderr,"\nusage: %s %sexample: %s -stu -vv -o . \n\n",
             taskname, helptxt, taskname );

}/*usage*/

void exit_func ( int retval )
{
    int i;

    if ( par.tcp && tcp_s ) {
        for( i=0; i<ntcp_s; i++ ) {
            ipfix_col_close( tcp_s[i] );
        }
        free( tcp_s );
    }
    if ( par.udp && udp_s ) {
        for( i=0; i<nudp_s; i++ ) {
            ipfix_col_close( udp_s[i] );
        }
        free( udp_s );
    }
    if ( par.sctp && sctp_s ) {
        for( i=0; i<nsctp_s; i++ ) {
            ipfix_col_close( sctp_s[i] );
        }
        free( sctp_s );
    }
    if ( par.ssl && scol ) {
        ipfix_col_close_ssl( scol );
    }

    if ( par.datadir ) ipfix_col_stop_fileexport();
#ifdef DBSUPPORT
    if ( par.dbexport ) ipfix_col_stop_mysqlexport();
#endif
#ifdef JSONLINESSUPPORT
    if ( par.jsonexport ) ipfix_col_stop_jsonlinesexport();
#endif
    (void) ipfix_col_stop_msglog();
    ipfix_col_cleanup();
    ipfix_cleanup();
    mlog_close();
    exit( retval );
}

void sig_func( int signo )
{
    if ( verbose_level )
        fprintf( stderr, "\n[%s] got signo %d, bye.\n\n", par.progname, signo );

    exit_func( 1 );
}

void sig_hup( int signo )
{
    if ( verbose_level )
        fprintf( stderr, "\n[%s] got SIGHUP, giving collectors a chance to react\n", par.progname );

#ifdef JSONLINESSUPPORT
    ipfix_col_reload_jsonlinesexport();
#endif
}

int do_collect()
{
    int      i, retval = -1;
    ipfix_ssl_opts_t opts;

    if ( par.ssl ) {
        opts.cafile  = par.cafile;
        opts.cadir   = par.cadir;
        opts.keyfile = par.keyfile;
        opts.certfile= par.certfile;
    }

    /** activate file export
     */
    if ( par.datadir )
        (void) ipfix_col_init_fileexport( par.datadir );

#ifdef DBSUPPORT
    if ( par.dbexport ) {
        if ( ipfix_col_init_mysqlexport( par.dbhost, par.dbuser,
                                         par.dbpw, par.dbname ) <0 ) {
            mlogf( 0, "[%s] cannot connect to database\n", par.progname );
            return -1;
        }
    }
#endif
#ifdef JSONLINESSUPPORT
    if ( par.jsonexport ) {
        if ( ipfix_col_init_jsonlinesexport( par.jsonfile,
                                             par.json_record_unknown_sets ) < 0 ) {
            mlogf( 0, "[%s] cannot use jsonlines (WHY?)\n", par.progname );
            return -1;
        }
    }
#endif

    /** open ipfix collector port(s)
     */
    if ( par.tcp ) {
        if ( par.ssl ) {
            if ( ipfix_col_listen_ssl( &scol, IPFIX_PROTO_TCP, 
                                       par.port, par.family, par.maxcon,
                                       &opts ) <0 ) {
                fprintf( stderr, "ipfix_listen_ssl(tcp) failed: %s\n",
                         strerror(errno) );
                return -1;
            }
        }
        else if ( ipfix_col_listen( &ntcp_s, &tcp_s, IPFIX_PROTO_TCP, 
                               par.port, par.family, par.maxcon ) <0 ) {
            fprintf( stderr, "ipfix_listen(tcp) failed: %s\n",
                     strerror(errno) );
            return -1;
        }
    }

    if ( par.udp ) {
        if ( par.ssl ) {
            if ( ipfix_col_listen_ssl( &scol, IPFIX_PROTO_UDP,
                                       par.port, par.family, 0, &opts ) <0 ) {
                fprintf( stderr, "ipfix_listen_ssl(udp) failed: %s\n",
                         strerror(errno) );
                return -1;
            }
        }
        else if ( ipfix_col_listen( &nudp_s, &udp_s, IPFIX_PROTO_UDP,
                                    par.port, par.family, 0 ) <0 ) {
            fprintf( stderr, "ipfix_listen(udp) failed: %s\n",
                     strerror(errno) );
            goto end;
        }
    }

    if ( par.sctp ) {
        if ( ipfix_col_listen( &nsctp_s, &sctp_s, IPFIX_PROTO_SCTP,
                               par.port, par.family, par.maxcon ) <0 ) {
            fprintf( stderr, "ipfix_listen(sctp) failed: %s\n",
                     strerror(errno) );
            goto end;
        }
    }

    /** event loop
     */
    for (;;)
    {
        if ( mpoll_loop( 10 ) <0 )
            break;

    } /* forever */

 end:
    if ( par.tcp && tcp_s ) {
        for( i=0; i<ntcp_s; i++ )
            ipfix_col_close( tcp_s[i] );
    }
    if ( par.udp && udp_s ) {
        for( i=0; i<nudp_s; i++ )
            ipfix_col_close( udp_s[i] );
    }
    if ( par.sctp && sctp_s ) {
        for( i=0; i<nsctp_s; i++ )
            ipfix_col_close( sctp_s[i] );
    }
    return retval;
}

static int read_password_from_file(const char *dbpw_filename, char **dbpw)
{
    /* FIXME: note that this will leak memory because dbpw in the caller is
     * a pointer to constant string (Text area), but if we set it here
     * it is a pointer to heap memory, so the caller wouldn't readily know
     * if it should be freed or not. In reality, this shouldn't be much of
     * an issue as it the password will remain in memory for the duration
     * of the program (which is in itself less ideal). */

    FILE *dbpw_file;
    char password[50];
    int retval;

    dbpw_file = fopen(dbpw_filename, "r");
    if (dbpw_file == NULL) {
        return -1;
    }

    if (fgets(password, sizeof password, dbpw_file) == NULL) {
        password[0] = '\0';
        *dbpw = NULL;
        retval = -1;
    } else {
        if (password[strlen(password)-1] == '\n') {
            password[strlen(password)-1] = '\0';
        }
        *dbpw = strdup(password);
        retval = 0;
    }
    
    fclose(dbpw_file);
    return retval;
}

int main (int argc, char *argv[])
{
    char          arg;          /* short options: character */
    int           loptidx=0;    /* long options: arg==0 and index */
    char          opt[] = "64stuhl:p:vo:";
#ifdef HAVE_GETOPT_LONG
    struct option lopt[] = { 
        { "db", 0, 0, 0},
        { "dbhost", 1, 0, 0},
        { "dbname", 1, 0, 0},
        { "dbuser", 1, 0, 0},
        { "dbpw", 1, 0, 0},
        { "dbpw-filename", 1, 0, 0},
        { "ssl", 0, 0, 0},
        { "key", 1, 0, 0},
        { "cert", 1, 0, 0},
        { "cafile", 1, 0, 0},
        { "cadir", 1, 0, 0},
        { "help", 0, 0, 0},
        { "json", 0, 0, 0},
        { "jsonfile", 1, 0, 0},
        { "json-record-unknown-sets", 0, 0, 0},
        { 0, 0, 0, 0 } 
    };
#endif

    /** set default options
     */
    par.tcp            =  0;
    par.udp            =  0;
    par.sctp           =  0;
    par.ssl            =  0;
    par.cafile         =  CAFILE;
    par.cadir          =  CADIR;
    par.keyfile        =  KEYFILE;
    par.certfile       =  CERTFILE;
    par.port           =  0;
    par.family         =  AF_UNSPEC;
    par.logfile        =  NULL;
    par.maxcon         =  10;
    par.datadir        =  NULL;
    par.dbexport       =  0;
    par.dbhost         =  DFLT_MYSQL_HOST;
    par.dbname         =  DFLT_MYSQL_DBNAME;
    par.dbuser         =  DFLT_MYSQL_USER;
    par.dbpw           =  DFLT_MYSQL_PASSWORD;
    par.dbpw_filename  =  NULL;
    par.jsonexport     =  0;
    par.jsonfile       =  "-";
    par.json_record_unknown_sets = 0;

    snprintf( par.progname, sizeof(par.progname), "%s", basename( argv[0]) );

    /* --- command line parsing ---
     */
#ifdef HAVE_GETOPT_LONG
    while ((arg=getopt_long( argc, argv, opt, lopt, &loptidx)) >=0 )
#else
    while( (arg=getopt( argc, argv, opt )) != EOF )
#endif
    {
        switch (arg) 
        {
          case 0: 
              switch (loptidx) {
                case 0: /* db */
                    par.dbexport = 1;
                    break;
                case 1: /* dbhost */
                    par.dbhost = optarg;
                    break;
                case 2: /* dbname */
                    par.dbname = optarg;
                    break;
                case 3: /* dbuser */
                    par.dbuser = optarg;
                    break;
                case 4: /* dbpw */
                    par.dbpw = optarg;
                    break;
                case 5: /* dbpw-filename */
                    par.dbpw_filename = optarg;
                    break;
                case 6: /* ssl */
                    par.ssl = 1;
                    break;
                case 7: /* key */
                    par.keyfile = optarg;
                    break;
                case 8: /* cert */
                    par.certfile = optarg;
                    break;
                case 9: /* cafile */
                    par.cafile = optarg;
                    break;
                case 10: /* cadir */
                    par.cadir = optarg;
                    break;
                case 11: /* help */
                    usage(par.progname);
                    exit(1);
                case 12: /* json */
                    par.jsonexport = 1;
                    break;
                case 13: /* jsonfile */
                    par.jsonfile = optarg;
                    break;
                case 14: /* json-record-unknown-sets */
                    par.json_record_unknown_sets = 1;
                    break;
              }
              break;

          case '4':
#ifdef INET6
              par.family = (par.family==AF_INET6)? AF_UNSPEC : AF_INET;
              break;

          case '6':
              par.family = (par.family==AF_INET)? AF_UNSPEC : AF_INET6;
#endif
              break;

          case 'd':
              par.dbexport = 1;
              break;

          case 'l':
              par.logfile = optarg;
              break;

          case 's':
              par.sctp ++;
              break;

          case 't':
              par.tcp ++;
              break;

          case 'u':
              par.udp ++;
              break;

          case 'o':
              par.datadir = optarg;
              if ( access( optarg, W_OK|X_OK ) <0 ) {
                  fprintf( stderr, "cannot access dir '%s': %s!\n",
                           optarg, strerror(errno) );
                  exit(1);
              }
              break;

          case 'p':
              if ((par.port=atoi(optarg)) <0)
              {
                  fprintf( stderr, "Invalid -p argument!\n" );
                  exit(1);
              }
              break;

          case 'v':
              verbose_level ++;
              break;

          case 'h':
          default:
              usage(par.progname);
              exit(1);
        }
    }

    if ( !par.udp && !par.tcp && !par.sctp )
        par.tcp++;

    if ( !par.dbexport && !par.datadir && !par.jsonexport ) {
        fprintf( stderr, "info: message dump, no data storage.\n" );
        fflush( stderr );
    }
    if ( par.dbexport ) {
        if ( (strcmp(par.dbpw, DFLT_MYSQL_PASSWORD) != 0 && par.dbpw_filename != NULL) ) {
            fprintf( stderr, "error: don't specify both --dbpw and --dbpw-filename.\n" );
            exit(1);
        } else if (par.dbpw_filename != NULL ) {
            if (read_password_from_file(par.dbpw_filename, &par.dbpw) < 0) {
                fprintf( stderr, "error: could not read database password from file '%s': %s\n",
                    par.dbpw_filename, strerror(errno) );
                exit(1);
            }
        }
    }

    if ( par.port==0 ) {
        par.port = par.ssl?IPFIX_TLS_PORTNO:IPFIX_PORTNO;
    }

    /** init loggin
     */
    mlog_set_vlevel( verbose_level );
    if ( par.logfile )
        (void) mlog_open( par.logfile, NULL );
    if ( (!par.dbexport && !par.datadir)
         || (verbose_level >2) )
        (void) ipfix_col_start_msglog( stderr );

    mlogf( 1, "[%s] listen on port %d, write to %s ...\n",
           par.progname, par.port,
           par.dbexport?"database":par.datadir?"files":"stdout" );

    if ( par.jsonexport ) {
        mlogf(1, "[%s] data goes to file %s as one JSON document per line\n",
              par.progname, par.jsonfile);
    }

    /** init ipfix lib
     */
    if ( ipfix_init() <0 ) {
        fprintf( stderr, "ipfix_init() failed: %s\n", strerror(errno) );
        exit(1);
    }
    if ( ipfix_add_vendor_information_elements( ipfix_ft_fokus ) <0 ) {
        fprintf( stderr, "ipfix_add_vendor_information_elements() failed adding Fokus types: %s\n", strerror(errno) );
        exit(1);
    }
    if ( ipfix_add_vendor_information_elements( ipfix_ft_netscaler ) <0 ) {
        fprintf( stderr, "ipfix_add_vendor_information_elements() failed adding Netscaler types: %s\n", strerror(errno) );
        exit(1);
    }
    if ( ipfix_add_vendor_information_elements( ipfix_reverse_ft_netscaler ) <0 ) {
        fprintf( stderr, "ipfix_add_vendor_information_elements() failed adding Netscaler reverse types: %s\n", strerror(errno) );
        exit(1);
    }


    /** signal handler
    signal( SIGSEGV, sig_func );
     */
    signal( SIGKILL, sig_func );
    signal( SIGTERM, sig_func );
    signal( SIGINT,  sig_func );

    signal( SIGHUP,  sig_hup );

    /** do the work
     */
    if ( do_collect() <0 )
        exit_func(1);

    exit_func(0);
    return 0;
}
