/*
** mlog.h - export declarations for mlog funcs
**
** Copyright Fraunhofer FOKUS
**
** $Id: mlog.h 22 2008-08-12 08:34:40Z tor $
**
** Remarks: This is experimental code!
**
*/
#ifndef _MLOG_H
#define _MLOG_H

#ifdef   __cplusplus
extern "C" {
#endif

extern void errorf ( char fmt[], ... ) __attribute__ ((format (printf, 1, 2)));
extern void debugf ( char fmt[], ... ) __attribute__ ((format (printf, 1, 2)));
extern void mlogf  ( int verbosity,
              char fmt[], ... ) __attribute__ ((format (printf, 2, 3)));
extern int  mlog_open  ( char *logfile, char *prefix );
extern void mlog_close ( void );
extern void mlog_set_vlevel( int vlevel );
extern int  mlog_get_vlevel();

#ifdef   __cplusplus
}
#endif
#endif 
