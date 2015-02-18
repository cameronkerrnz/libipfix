#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

/* len includes the trailing NUL byte (like snprintf) */

void json_render_string_to_FILE(FILE *out, const char *s /* utf-8 */, int len)
{
    /* See json.org for the spec. The real spec gives some further instruction
     * with regard to codepoints above the Unicode BMP.
     * http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf */

    int offset;

    if (len > 0) len -= 1; /* Should never be less, but we wouldn't want it to wrap around */

    fputc('"', out);

    for (offset = 0; offset < len; offset++)
    {
        switch(s[offset])
        {
            case '"':
                fprintf(out, "\\\"");
                break;
            case '\\':
                fprintf(out, "\\\\");
                break;
            case '/':
                fprintf(out, "\\/");
                break;
            case '\b':
                fprintf(out, "\\b");
                break;
            case '\f': /* really!? but not bell, not vertical tab and not NUL */
                fprintf(out, "\\f");
                break;
            case '\n':
                fprintf(out, "\\n");
                break;
            case '\r':
                fprintf(out, "\\r");
                break;
            case '\t':
                fprintf(out, "\\t");
                break;
            default:
                if(s[offset] < ' ') /* ie. control character, in ASCII */
                {
                    fprintf(out, "\\u%04X", s[offset]);
                }
                else if ( (s[offset] >= ' ') && (s[offset] < 127) )
                {
                    fputc(s[offset], out);
                }
                else if (    ((192 <= s[offset]) && (s[offset] <= 193))
                          || ((245 <= s[offset]) && (s[offset] <= 255)) )
                {
                    /* Illegal UTF-8 bytes. Replace with REPLACEMENT CHARACTER */
                    fprintf(out, "\\uFFFD");
                }
                else
                {
                    fputc(s[offset], out);
                }
        }
    }

    fputc('"', out);
}

/* JSON doesn't have a data representation for arbitrary bytes, so I'll use a hexdump sort
 * of notation like  XX XX XX XX  YY YY YY YY  ZZ ZZ ZZ ZZ  with a space between each
 * byte and a double-space between each 32-bit word. */

void json_render_bytes_as_hexpairs_to_FILE(FILE *json_file, const void *s /* bytes */, int len)
{
    const uint8_t *b = s;
    int offset;

    fputc('"', json_file);

    for (offset = 0; offset < len; offset++)
    {
        fprintf(json_file, "%02X%s", b[offset], (offset==0)?"":" ");
        if ((offset % 4) == 3) fputc(' ', json_file);
    }
    
    fputc('"', json_file);
}

/* JSON doesn't have a format for date/time representation, but ElasticSearch does,
 * so we'll use that (RFC3306)
 *
 * Credit for the NTP conversion: Willy Kuo
 * http://waitingkuo.blogspot.co.nz/2012/06/conversion-between-ntp-time-and-unix.html
 */

struct ntp_time_t {
    uint32_t seconds;
    uint32_t fraction;
};
         
// Okay.... somewhere 'unix' is being defined as a token and leads to a syntax error
// So I renamed it unixtime for now.
//
static void convert_ntp_time_into_unix_time(const struct ntp_time_t *ntp, struct timeval *unixtime)
{
    unixtime->tv_sec = ntp->seconds - 0x83AA7E80; /* the seconds from Jan 1, 1900 to Jan 1, 1970 */
    unixtime->tv_usec = (uint32_t)( (double)ntp->fraction * 1.0e6 / (double)(1LL<<32) );
    return;
}

// ElasticSearch would also take milliseconds from the Epoch... but I'd prefer
// something more general.
//
void json_render_NTP_timestamp_to_FILE(FILE *json_file, const void *addr, int len)
{
    struct ntp_time_t ntp;
    struct timeval unixtime;
    struct tm unixtime_utc_tm;
    char datetimebuf[25];

    ntp.seconds = (*((uint64_t *)addr)) >> 32;
    ntp.fraction = (*((uint64_t *)addr)) & 0xFFFFFFFF;

    convert_ntp_time_into_unix_time(&ntp, &unixtime);

    gmtime_r(&unixtime.tv_sec, &unixtime_utc_tm);

    strftime(datetimebuf, sizeof datetimebuf, "%FT%T", &unixtime_utc_tm);

    fprintf(json_file, "\"%s.%03ldZ\"", datetimebuf, unixtime.tv_usec / 1000);
}

