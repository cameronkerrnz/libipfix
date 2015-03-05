/*
$$LIC$$
 */
/*
** ipfix_col.h - export declarations of ipfix collector funcs
**
** Copyright Fraunhofer FOKUS
**
** $Id: ipfix_col.h 166 2010-02-23 10:15:04Z csc $
**
*/
#ifndef IPFIX_COL_H
#define IPFIX_COL_H

#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ipfix.h>
#ifdef DBSUPPORT
#include <ipfix_db.h>
#endif
#ifdef JSONLINESSUPPORT
# include <ipfix_jsonlines.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DFLT_MYSQL_HOST      "localhost"
#define DFLT_MYSQL_DBNAME    "ipfix"
#define DFLT_MYSQL_USER      "ipfix"
#define DFLT_MYSQL_PASSWORD  "ipfix"

#define MAXTEMPLIDENT        240

typedef enum {
    IPFIX_INPUT_FILE, IPFIX_INPUT_IPCON
} ipfix_input_type_t;

typedef struct ipfix_input {
    ipfix_input_type_t      type;
    union {
        struct {
            struct sockaddr *addr;           /* exporter addess */
            socklen_t       addrlen;         /* exporter address length */
        } ipcon;
        struct {
            char            *name;           /* filename */
        } file;
    } u;
} ipfix_input_t;

typedef struct ipfixt_node
{
    struct ipfixt_node   *next;
    time_t               expire_time;
    ipfix_template_t     *ipfixt;
    char                 ident[MAXTEMPLIDENT];
#ifdef DBSUPPORT
    char                 tablename[MAXTABLENAMELEN+1]; /* make this dynamic */
    unsigned             template_id;      /* id from template table (hack) */
    unsigned             message_snr;      /* last ipfix message snr (hack) */
#endif
} ipfixt_node_t;

typedef struct ipfixs_node
{
    struct ipfixs_node   *next;
    uint32_t             odid;                        /* observation domain */
    ipfix_input_t        *input;                     /* ipfix input details */
    ipfixt_node_t        *templates;                   /* list of templates */
    char                 fname[PATH_MAX+1];
    FILE                 *fp;
    unsigned int         last_seqno;
#ifdef DBSUPPORT
    unsigned int         last_msgid;                      /* ugh! move this */
    unsigned int         last_message_snr;
    unsigned int         exporterid;
#endif
} ipfixs_node_t;

typedef struct ipfixi_node
{
    struct ipfixe_node      *next;
    ipfix_input_t           *input;          /* ipfix input details */
    struct ipfixs_node      *ods;            /* list of observation domains */
} ipfixi_node_t;

typedef struct ipfix_col_info
{
    int (*export_newsource)(ipfixs_node_t*,void*);
    int (*export_newmsg)(ipfixs_node_t*,ipfix_hdr_t*,void*);
    int (*export_trecord)(ipfixs_node_t*,ipfixt_node_t*,void*);
    int (*export_dset)(ipfixt_node_t*,const uint8_t*,size_t,void*);
    int (*export_drecord)(ipfixs_node_t*,ipfixt_node_t*,
                          ipfix_datarecord_t*,void*,ipfix_input_t*);
    int (*export_rawmsg)(ipfixs_node_t *source, const uint8_t* data, size_t len, void *arg);
    int (*export_notify_no_template_for_set)(int,ipfixs_node_t*,const uint8_t*,size_t,void*);
    void (*export_cleanup)(void*);
    void (*export_reload)(void*);
    void *data;
} ipfix_col_info_t;

extern ipfix_col_info_t   *g_colinfo;

typedef struct ipfix_col_info_node
{
    struct ipfix_col_info_node *next;
    struct ipfix_col_info      *elem;

} ipfixe_node_t;

typedef void* ipfix_col_t;

void ipfix_col_init( void );
int  ipfix_col_init_fileexport( char *datadir );
void ipfix_col_stop_fileexport( void );
int  ipfix_col_init_mysqlexport( char *host, char *user, char *pw, char *name );
void ipfix_col_stop_mysqlexport( void );
int  ipfix_col_init_jsonlinesexport( char *jsonfile, int json_record_unknown_sets );
void ipfix_col_stop_jsonlinesexport( void );
void ipfix_col_reload_jsonlinesexport( void );
int  ipfix_col_register_export( ipfix_col_info_t *colinfo );
int  ipfix_col_cancel_export( ipfix_col_info_t *colinfo );
int  ipfix_col_listen( int *nfds, int **fds, ipfix_proto_t protocol, 
                       int port, int family, int maxcon );
int  ipfix_col_start_msglog( FILE *fpout ); 
void ipfix_col_stop_msglog( void ); 
int  ipfix_col_close( int fd );
void ipfix_col_cleanup( void );
void ipfix_col_reload( void );

/* internal, experimental */
int  ipfix_parse_hdr( const uint8_t *buf, size_t buflen, ipfix_hdr_t *hdr );
int  ipfix_parse_raw_msg( ipfixs_node_t *source, ipfixe_node_t  *g_exporter,
                      const uint8_t *msg, size_t nbytes );
int  ipfix_parse_msg( ipfix_input_t *input, ipfixs_node_t **sources, 
                      const uint8_t *msg, size_t nbytes );
int  ipfix_get_template_ident( ipfix_template_t *t, char *buf, size_t buflen );
int  ipfix_col_listen_ssl( ipfix_col_t **handle, ipfix_proto_t protocol, 
                           int port, int family, int maxcon,
                           ipfix_ssl_opts_t *ssl_opts );
int  ipfix_col_close_ssl( ipfix_col_t *handle );


const char *ipfix_col_input_get_ident( ipfix_input_t *input );

#ifdef DBSUPPORT
# include <ipfix_col_db.h>
#endif
#ifdef JSONLINESSUPPORT
# include <ipfix_col_jsonlines.h>
#endif

#ifdef __cplusplus
}
#endif
#endif
