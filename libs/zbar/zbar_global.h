#ifndef ZBARLIB_GLOBAL_H
#define ZBARLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZBARLIB_LIBRARY)
#  define ZBARLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZBARLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ZBARLIB_GLOBAL_H
