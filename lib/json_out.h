#ifndef __JSON_OUT_H
# define __JSON_OUT_H

#include <stdio.h>

/* Assumes that the input is UTF-8 */

extern void json_render_string_to_FILE(FILE *out, const char *s, int len);

/* JSON doesn't have a data representation for arbitrary bytes, so I'll use a hexdump sort
 * of notation like  XX XX XX XX  YY YY YY YY  ZZ ZZ ZZ ZZ  with a space between each
 * byte and a double-space between each 32-bit word. */

extern void json_render_bytes_as_hexpairs_to_FILE(FILE *out, const void *s /* bytes */, int len);

/* eg. 2015-02-19T01:15:58.938Z */

extern void json_render_NTP_timestamp_to_FILE(FILE *json_file, const void *addr, int len);

#endif /* __JSON_OUT_H */

