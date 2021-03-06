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

/* Constant size 1977-09-06T01:02:03.004Z */
#define JSON_MESSAGE_TIMESTAMP_SIZE 25
#define JSON_MESSAGE_TIMESTAMP_ATTRIBUTE_NAME "ipfix_timestamp"

typedef struct ipfix_export_data_jsonlines
{
    char *json_filename;
    FILE *json_file;
    char message_timestamp_str[JSON_MESSAGE_TIMESTAMP_SIZE];
    int json_record_unknown_sets;
    ipfix_template_source_t template_source;
} ipfixe_data_jsonlines_t;

/*------ globals ---------------------------------------------------------*/

/*----- revision id ------------------------------------------------------*/

/*----- globals ----------------------------------------------------------*/

/*----- static funcs -----------------------------------------------------*/

int _jsonlines_ensure_open(const char *func, ipfixe_data_jsonlines_t *data)
{
    if (strcmp(data->json_filename, "-") == 0) {
        data->json_file = stdout;
    } else {
        if ( data->json_filename && data->json_file == NULL ) {
            data->json_file = fopen(data->json_filename, "a");
            if (data->json_file == NULL) {
                mlogf( 0, "[%s] opening file '%s' for appending failed: %s\n",
                       func, data->json_filename, strerror(errno));
                return -1;
            }
        }
    }
    return 0;
}

static void _jsonlines_after_message(ipfixe_data_jsonlines_t *data)
{
    if (data->json_file) {
        /* TODO: Need to be able to have a more performant flushing policy */
        fflush(data->json_file);
    }
}

int ipfix_export_drecord_jsonlines( ipfixs_node_t      *s,
                                   ipfixt_node_t      *t,
                                   ipfix_datarecord_t *d,
                                   void               *arg,
                                   ipfix_input_t      *source )
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = (ipfixe_data_jsonlines_t*)arg;
    char             *func = "export_drecord_jsonlines";
    int              i;
    char             exporter_ip[INET6_ADDRSTRLEN];

    if ( !data->json_filename ) {
        return -1;
    }

    /* Write data set to a file as JSON. One JSON document per line.
     */

    if (_jsonlines_ensure_open(func, data) < 0)
    {
        return -1;
    }

    fprintf(data->json_file, "{\"" JSON_MESSAGE_TIMESTAMP_ATTRIBUTE_NAME "\":\"%s\"",
        data->message_timestamp_str);

    if (source != NULL && source->type == IPFIX_INPUT_IPCON
            && source->u.ipcon.addr->sa_family == AF_INET)
    {
        inet_ntop( AF_INET, & ((struct sockaddr_in *)(source->u.ipcon.addr))->sin_addr.s_addr,
            exporter_ip, INET6_ADDRSTRLEN);
        fprintf(data->json_file, ", \"ipfix_exporter_ip\":\"%s\"", exporter_ip);
    }
    else if (source != NULL && source->type == IPFIX_INPUT_IPCON
            && source->u.ipcon.addr->sa_family == AF_INET6)
    {
        inet_ntop( AF_INET6, & ((struct sockaddr_in6 *)(source->u.ipcon.addr))->sin6_addr,
            exporter_ip, INET6_ADDRSTRLEN);
        fprintf(data->json_file, ", \"ipfix_exporter_ip\":\"%s\"", exporter_ip);
    }
    else
    {
        fprintf(data->json_file, ", \"ipfix_exporter_ip\":null");
    }

    fprintf(data->json_file, ", \"ipfix_template_id\":\"%d\"", t->ipfixt->tid);

    fprintf(data->json_file, ", \"ipfix_template_source\":\"%s\"", data->template_source ? "fallback" : "protocol");

    /* TODO The first attribute should be the template number.
     */

    for ( i=0; i<t->ipfixt->nfields; i++ ) {

        if ( t->ipfixt->fields[i].elem->ft->eno == 0 
             && t->ipfixt->fields[i].elem->ft->ftype == 0xD2 ) {
             continue; /* D2 == 210, paddingOctets */
        }

        /*
         * The attribute names come from trusted data, not from the protocol.
         * We print out the header in each case, as we might wish to ignore the
         * attribute based on the value (eg. a string "") 
         */

        switch (t->ipfixt->fields[i].elem->ft->coding) {
            case IPFIX_CODING_UINT:
                fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
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
                fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
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
                fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
                mlogf(1, "[%s] JSON emmission of type FLOAT not complete yet (%s).\n", func, t->ipfixt->fields[i].elem->ft->name);
                fprintf(data->json_file, "null");
                break;
            case IPFIX_CODING_IPADDR:
                fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
                {
                    char addrbuf[INET6_ADDRSTRLEN];

                    ipfix_snprint_ipaddr(addrbuf, INET6_ADDRSTRLEN, d->addrs[i], d->lens[i]);

                    fprintf(data->json_file, "\"%s\"", addrbuf);
                }
                break;
            case IPFIX_CODING_NTP:
                fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
                json_render_NTP_timestamp_to_FILE(data->json_file, d->addrs[i], d->lens[i]);
                break;
            case IPFIX_CODING_STRING:
                if ((d->lens[i] > 0) && ((const char *)(d->addrs[i]))[0] != '\0')
                {
                    fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
                    // don't forget JSON is meant to be UTF-8; IPFIX/Netscaler is ....?
                    json_render_string_to_FILE(data->json_file, (const char *) d->addrs[i], d->lens[i]);  
                }
                break;
            case IPFIX_CODING_BYTES:
                if (d->lens[i] > 0)
                {
                    fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
                    json_render_bytes_as_hexpairs_to_FILE(data->json_file, d->addrs[i], d->lens[i]);  
                }
                break;
            default:
                fprintf(data->json_file, ", \"%s\":", t->ipfixt->fields[i].elem->ft->name);
                mlogf(1, "[%s] JSON emmission of type %d not currently supported (%s).\n",
                      func, t->ipfixt->fields[i].elem->ft->coding, t->ipfixt->fields[i].elem->ft->name);
                fprintf(data->json_file, "null");
        }
    }

    fprintf(data->json_file, "}\n");

    _jsonlines_after_message(data);
#endif
    return 0;
}

int ipfix_export_newsource_jsonlines( ipfixs_node_t *s, void *arg )
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = (ipfixe_data_jsonlines_t*)arg;

    if (_jsonlines_ensure_open(__FUNCTION__, data) < 0)
    {
        return -1;
    }

    /* "ipfix_collector_notify":"newsource"  */

    fprintf(data->json_file, 
            "{ \"" JSON_MESSAGE_TIMESTAMP_ATTRIBUTE_NAME "\":\"%s\""
            ", \"ipfix_collector_notice\":\"newsource\""
            ", \"summary\":\"new source seen %s/%lu\""
            ", \"ipfix_exporter_ip\":\"%s\""
            ", \"observationDomainId\":%lu"
            "}\n",
            data->message_timestamp_str,
            ipfix_col_input_get_ident( s->input ), (u_long)s->odid,
            ipfix_col_input_get_ident( s->input ), (u_long)s->odid );

    _jsonlines_after_message(data);

#endif
    return 0;
}

int ipfix_export_notify_no_template_for_set_jsonlines(
    int template_id,
    ipfixs_node_t * source,
    const uint8_t * set_start,
    size_t set_len,
    void * arg)
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = (ipfixe_data_jsonlines_t*)arg;

    if (_jsonlines_ensure_open(__FUNCTION__, data) < 0)
    {
        return -1;
    }
    
    fprintf(data->json_file, 
            "{ \"" JSON_MESSAGE_TIMESTAMP_ATTRIBUTE_NAME "\":\"%s\""
            ", \"ipfix_collector_notice\":\"no_template_for_set\""
            ", \"ipfix_template_id\":\"%d\""
            ", \"ipfix_exporter_ip\":\"%s\""
            ", \"summary\":\"no template for %d, skip data set\"",
            data->message_timestamp_str,
            template_id,
            ipfix_col_input_get_ident( source->input ),
            template_id);
            
    if (data->json_record_unknown_sets)
    {
        fprintf(data->json_file, ", \"set_bytes\":");
        json_render_bytes_as_hexpairs_to_FILE(data->json_file, set_start, set_len);
    }

    fprintf(data->json_file,
            "}\n");

    _jsonlines_after_message(data);
#endif
    return 0;
}

int ipfix_export_newmsg_jsonlines(ipfixs_node_t * s, ipfix_hdr_t * hdr, void * arg)
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = (ipfixe_data_jsonlines_t*)arg;

    time_t         message_time;
    struct timeval timestamp_tv;
    struct tm      timestamp_tm;

    (void) s;

    if ( hdr->version == IPFIX_VERSION_NF9 )
    {
        message_time = hdr->u.nf9.unixtime;
    }
    else
    {
        message_time = hdr->u.ipfix.exporttime;
    }

    memset(&timestamp_tv, 0, sizeof(timestamp_tv));

    timestamp_tv.tv_sec = message_time;
    timestamp_tv.tv_usec = 0;

    gmtime_r(&timestamp_tv.tv_sec, &timestamp_tm);

    strftime(data->message_timestamp_str, JSON_MESSAGE_TIMESTAMP_SIZE,
        "%Y-%m-%dT%H:%M:%SZ", &timestamp_tm);
#endif
    return 0;
}

void ipfix_export_template_source_jsonlines(int template_id, ipfix_template_source_t source, void * arg)
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data = (ipfixe_data_jsonlines_t*)arg;

    fprintf(stderr, "Template source is %s for template ID %d\n",
        (source == IPFIX_TEMPLATE_SOURCE_PROTOCOL) ? "protocol" : "fallback", template_id);

    data->template_source = source;
#endif
}
    
    
int ipfix_export_init_jsonlines( char *jsonfile, int json_record_unknown_sets, void **arg )
{
#ifdef JSONLINESSUPPORT
    ipfixe_data_jsonlines_t *data;

    if ( (data=calloc( 1, sizeof(ipfixe_data_jsonlines_t))) ==NULL)
        return -1;

    data->json_filename = jsonfile;
    data->json_file = NULL;
    data->json_record_unknown_sets = json_record_unknown_sets;

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

int ipfix_col_init_jsonlinesexport(
    char *jsonfile,
    int json_record_unknown_sets)
{
#ifdef JSONLINESSUPPORT
    void *data;

    if ( ipfix_export_init_jsonlines(jsonfile, json_record_unknown_sets, &data) <0 ) {
        return -1;
    }

    if ( (g_colinfo=calloc( 1, sizeof(ipfix_col_info_t))) ==NULL) {
        ipfix_export_cleanup_jsonlines( data );
        return -1;
    }

    g_colinfo->export_drecord                    = ipfix_export_drecord_jsonlines;
    g_colinfo->export_cleanup                    = ipfix_export_cleanup_jsonlines;
    g_colinfo->export_reload                     = ipfix_export_reload_jsonlines;
    g_colinfo->export_newsource                  = ipfix_export_newsource_jsonlines;
    g_colinfo->export_notify_no_template_for_set = ipfix_export_notify_no_template_for_set_jsonlines;
    g_colinfo->export_newmsg                     = ipfix_export_newmsg_jsonlines;
    g_colinfo->export_template_source            = ipfix_export_template_source_jsonlines;

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

