#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HDATETIMELINEEDIT_LIB)
#  define HDATETIMELINEEDIT_EXPORT Q_DECL_EXPORT
# else
#  define HDATETIMELINEEDIT_EXPORT Q_DECL_IMPORT
# endif
#else
# define HDATETIMELINEEDIT_EXPORT
#endif
