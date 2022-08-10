#ifndef UARTTEST_GLOBAL_H
#define UARTTEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UARTTEST_LIBRARY)
#  define UARTTEST_EXPORT Q_DECL_EXPORT
#else
#  define UARTTEST_EXPORT Q_DECL_IMPORT
#endif

#endif // UARTTEST_GLOBAL_H
