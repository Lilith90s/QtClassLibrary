#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GANNTVIEW_LIB)
#  define GANNTVIEW_EXPORT Q_DECL_EXPORT
# else
#  define GANNTVIEW_EXPORT Q_DECL_IMPORT
# endif
#else
# define GANNTVIEW_EXPORT
#endif
