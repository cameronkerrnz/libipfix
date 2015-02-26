/*
$$LIC$$
 */
/*
**     ipfix_col_jsonfile.c - IPFIX collector functions for jsonlines
**
**     Copyright Cameron Kerr, Fraunhofer FOKUS
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <inttypes.h>
#include <arpa/inet.h>

#include "mlog.h"
#include "misc.h"
#include "ipfix.h"
#include "ipfix_col.h"
#include "ipfix_col_jsonlines.h"
#include "json_out.h"

/*------ defines ---------------------------------------------------------*/

/*------ structs ---------------------------------------------------------*/

typedef struct ipfix_export_data_jsonlines
{
    char *json_filename;
    FILE *json_file;
} ipfixe_data_jsonlines_t;

/*------ globals ---------------------------------------------------------*/

/*----- revision id ------------------------------------------------------*/

/*----- globals ----------------------------------------------------------*/

/*----- static funcs -----------------------------------------------------*/

int ipfix_export_drecord_jsonlines( ipfixs_node_t      *s,
                                   ipfixt_node_t      *t,
                                   ipfix_datarecord_t *d,
                                   void               *arg )
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = (ipfixe_data_jsonlines_t*)arg;
    char             *func = "export_drecord_jsonlines";
    int              i;

    if ( !data->json_filename ) {
        return -1;
    }

    /* Write data set to a file as JSON. One JSON document per line.
     */

    if (strcmp(data->json_filename, "-") == 0) {
        data->json_file = stdout;
    } else {
        if ( data->json_filename && data->json_file == NULL ) {
            data->json_file = fopen(data->json_filename, "a");
            if (data->json_file == NULL) {
                mlogf( 0, "[%s] opening file '%s' for appending failed: %s\n",
                       func, data->json_filename, strerror(errno));
            }
        }
    }

    fprintf(data->json_file, "{\"ipfix_template_id\":\"%d\"", t->ipfixt->tid);

    /* TODO The first attribute should be the template number.
     */

    for ( i=0; i<t->ipfixt->nfields; i++ ) {
        if ( t->ipfixt->fields[i].elem->ft->eno == 0 
             && t->ipfixt->fields[i].elem->ft->ftype == 0xD2 ) {
             continue; /* D2 == 210, paddingOctets */
        }

        /* The attribute names come from trusted data, not from the protocol
         */

        fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);

        switch (t->ipfixt->fields[i].elem->ft->coding) {
            case IPFIX_CODING_UINT:
                switch (d->lens[i]) {
                    case 1:
                        fprintf(data->json_file, "%u", *((uint8_t *) (d->addrs[i])) );
                        break;
                    case 2:
                        fprintf(data->json_file, "%u", *((uint16_t *) (d->addrs[i])) );
                        break;
                    case 4:
                        fprintf(data->json_file, "%u", *((uint32_t *) (d->addrs[i])) );
                        break;
                    case 8:
                        fprintf(data->json_file, "%"PRIu64, *((uint64_t *) (d->addrs[i])) );
                        break;
                    default:
                        mlogf(1, "[%s] JSON emmission of type UINT (%d bytes) is NOT IMPLEMENTED (%s).\n", func, d->lens[i], t->ipfixt->fields[i].elem->ft->name);
                        fprintf(data->json_file, "null");
                }
                break;
            case IPFIX_CODING_INT:
                switch (d->lens[i]) {
                    case 1:
                        fprintf(data->json_file, "%d", *((int8_t *) (d->addrs[i])) );
                        break;
                    case 2:
                        fprintf(data->json_file, "%d", *((int16_t *) (d->addrs[i])) );
                        break;
                    case 4:
                        fprintf(data->json_file, "%d", *((int32_t *) (d->addrs[i])) );
                        break;
                    case 8:
                        fprintf(data->json_file, "%"PRId64, *((uint64_t *) (d->addrs[i])) );
                        break;
                    default:
                        mlogf(1, "[%s] JSON emmission of type INT (%d bytes) is NOT IMPLEMENTED (%s).\n", func, d->lens[i], t->ipfixt->fields[i].elem->ft->name);
                        fprintf(data->json_file, "null");
                }
                break;
            case IPFIX_CODING_FLOAT:
                mlogf(1, "[%s] JSON emmission of type FLOAT not complete yet (%s).\n", func, t->ipfixt->fields[i].elem->ft->name);
                fprintf(data->json_file, "null");
                break;
            case IPFIX_CODING_IPADDR:
                {
                    char addrbuf[INET6_ADDRSTRLEN];

                    ipfix_snprint_ipaddr(addrbuf, INET6_ADDRSTRLEN, d->addrs[i], d->lens[i]);

                    fprintf(data->json_file, "\"%s\"", addrbuf);
                }
                break;
            case IPFIX_CODING_NTP:
                json_render_NTP_timestamp_to_FILE(data->json_file, d->addrs[i], d->lens[i]);
                break;
            case IPFIX_CODING_STRING:
                // don't forget JSON is meant to be UTF-8; IPFIX/Netscaler is ....?
                json_render_string_to_FILE(data->json_file, (const char *) d->addrs[i], d->lens[i]);  
                break;
            case IPFIX_CODING_BYTES:
                json_render_bytes_as_hexpairs_to_FILE(data->json_file, d->addrs[i], d->lens[i]);  
                break;
            default:
                mlogf(1, "[%s] JSON emmission of type %d not currently supported (%s).\n",
                      func, t->ipfixt->fields[i].elem->ft->coding, t->ipfixt->fields[i].elem->ft->name);
                fprintf(data->json_file, "null");
        }
    }

    fprintf(data->json_file, "}\n");

    if (data->json_file) {
        /* TODO: Need to be able to have a more performant flushing policy */
        fflush(data->json_file);
    }
#endif
    return 0;
}

int ipfix_export_init_jsonlines( char *jsonfile, void **arg )
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data;

    if ( (data=calloc( 1, sizeof(ipfixe_data_jsonlines_t))) ==NULL)
        return -1;

    data->json_filename = jsonfile;
    data->json_file = NULL;

    *arg = (void**)data;
#endif
    return 0;
}

void ipfix_export_reload_jsonlines( void *arg )
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = (ipfixe_data_jsonlines_t*)arg;

    if (data->json_file != NULL && data->json_file != stdout) {
        fclose(data->json_file);
        data->json_file = NULL;
        /* It will get reopened when it next receives data */
    }
#endif
}

void ipfix_export_cleanup_jsonlines( void *arg )
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = arg;

    if ( data ) {
        if (data->json_file != NULL && data->json_file != stdout) {
            fclose(data->json_file);
            data->json_file = NULL;
        }

        free(data);
    }
#endif
}


/*----- export funcs -----------------------------------------------------*/

int ipfix_col_init_jsonlinesexport( char *jsonfile )
{
#ifdef JSONLINESSUPPORT
    void *data;

    if ( ipfix_export_init_jsonlines(jsonfile, &data) <0 ) {
        return -1;
    }

    if ( (g_colinfo=calloc( 1, sizeof(ipfix_col_info_t))) ==NULL) {
        ipfix_export_cleanup_jsonlines( data );
        return -1;
    }

    g_colinfo->export_drecord   = ipfix_export_drecord_jsonlines;
    g_colinfo->export_cleanup   = ipfix_export_cleanup_jsonlines;
    g_colinfo->export_reload    = ipfix_export_reload_jsonlines;
    g_colinfo->data = data;

    return ipfix_col_register_export( g_colinfo );
#endif
    errno = ENODEV;
    return -1;
}

void ipfix_col_stop_jsonlinesexport(void)
{
#ifdef JSONLINESSUPPORT
    /* currently the same as a reload */
    ipfix_export_reload_jsonlines(g_colinfo->data);
#endif
}

void ipfix_col_reload_jsonlinesexport(void)
{
#ifdef JSONLINESSUPPORT
    ipfix_export_reload_jsonlines(g_colinfo->data);
#endif
}

