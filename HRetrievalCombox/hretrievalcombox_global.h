#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HRETRIEVALCOMBOX_LIB)
#  define HRETRIEVALCOMBOX_EXPORT Q_DECL_EXPORT
# else
#  define HRETRIEVALCOMBOX_EXPORT Q_DECL_IMPORT
# endif
#else
# define HRETRIEVALCOMBOX_EXPORT
#endif
