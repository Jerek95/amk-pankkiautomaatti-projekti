#ifndef RESTAPI_DLL_GLOBAL_H
#define RESTAPI_DLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RESTAPI_DLL_LIBRARY)
#define RESTAPI_DLL_EXPORT Q_DECL_EXPORT
#else
#define RESTAPI_DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // RESTAPI_DLL_GLOBAL_H
