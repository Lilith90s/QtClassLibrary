#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(WEBSCRAPING_LIB)
#  define WEBSCRAPING_EXPORT Q_DECL_EXPORT
# else
#  define WEBSCRAPING_EXPORT Q_DECL_IMPORT
# endif
#else
# define WEBSCRAPING_EXPORT
#endif
