#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SELECTCOMBOBOX_LIB)
#  define SELECTCOMBOBOX_EXPORT Q_DECL_EXPORT
# else
#  define SELECTCOMBOBOX_EXPORT Q_DECL_IMPORT
# endif
#else
# define SELECTCOMBOBOX_EXPORT
#endif
