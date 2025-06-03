#ifndef PINUI_DLL_GLOBAL_H
#define PINUI_DLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PINUI_DLL_LIBRARY)
#define PINUI_DLL_EXPORT Q_DECL_EXPORT
#else
#define PINUI_DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // PINUI_DLL_GLOBAL_H
