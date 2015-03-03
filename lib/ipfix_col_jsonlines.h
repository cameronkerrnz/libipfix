/*
 * ipfix_col_jsonlines.h - Private API for the JSONLINES mode
 *
 * Copyright Cameron Kerr
 */

#ifndef IPFIX_COL_JSONLINES_H
#define IPFIX_COL_JSONLINES_H

#ifdef __cplusplus
extern "C" {
#endif

int ipfix_export_drecord_jsonlines(
    ipfixs_node_t *s,            /* <  Parsed message */
    ipfixt_node_t *t,            /* <  Relevant template information for this data record */
    ipfix_datarecord_t *d,       /* <  Data record to be emitted */
    void *arg,                   /* <> jsonlines state */
    ipfix_input_t *source        /* <  Potential IP address information. May be NULL */      
    );
int ipfix_export_newsrc_jsonlines( ipfixs_node_t *s, void *arg );

void ipfix_export_reload_jsonlines(void *arg);
void ipfix_export_cleanup_jsonlinesexport( void *arg );
int  ipfix_export_init_jsonlinesexport(char *jsonfile, void **data );

#ifdef __cplusplus
}
#endif
#endif
