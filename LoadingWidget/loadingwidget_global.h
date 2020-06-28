#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOADINGWIDGET_LIB)
#  define LOADINGWIDGET_EXPORT Q_DECL_EXPORT
# else
#  define LOADINGWIDGET_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOADINGWIDGET_EXPORT
#endif
