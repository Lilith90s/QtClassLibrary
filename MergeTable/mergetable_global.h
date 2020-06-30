#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MERGETABLE_LIB)
#  define MERGETABLE_EXPORT Q_DECL_EXPORT
# else
#  define MERGETABLE_EXPORT Q_DECL_IMPORT
# endif
#else
# define MERGETABLE_EXPORT
#endif
