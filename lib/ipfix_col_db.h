/*
$$LIC$$
 */
/*
** ipfix_col.h - export declarations of ipfix collector funcs
**
** Copyright Fraunhofer FOKUS
**
** $Id: ipfix_col_db.h 23 2008-08-14 11:30:44Z tor $
**
*/
#ifndef IPFIX_COL_DB_H
#define IPFIX_COL_DB_H

#ifdef __cplusplus
extern "C" {
#endif

int  ipfix_export_newsrc_db( ipfixs_node_t *s, void *arg ) ;
int  ipfix_export_newmsg_db( ipfixs_node_t *s, ipfix_hdr_t *hdr, void *arg );
int  ipfix_export_trecord_db( ipfixs_node_t *s, ipfixt_node_t *t, void *arg );
int  ipfix_export_drecord_db( ipfixs_node_t *s, ipfixt_node_t *t,
                              ipfix_datarecord_t *d, void *arg,
                              ipfix_input_t      *source );
int  ipfix_export_drecord_jsonfile( ipfixs_node_t *s, ipfixt_node_t *t,
                                     ipfix_datarecord_t *d, void *arg );
void ipfix_export_cleanup_db( void *arg );
int  ipfix_export_init_db( char *dbhost, char *dbuser,
                           char *dbpw, char *dbname, 
                           void **data );

#ifdef __cplusplus
}
#endif
#endif
