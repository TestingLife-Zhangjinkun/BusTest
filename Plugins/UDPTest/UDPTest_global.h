#ifndef UDPTEST_GLOBAL_H
#define UDPTEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UDPTEST_LIBRARY)
#  define UDPTEST_EXPORT Q_DECL_EXPORT
#else
#  define UDPTEST_EXPORT Q_DECL_IMPORT
#endif

#endif // UDPTEST_GLOBAL_H
