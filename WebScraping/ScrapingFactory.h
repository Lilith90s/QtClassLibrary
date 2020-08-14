#pragma once
#include "webscraping_global.h"
#include "KGScraping.h"
#include "WYYScraping.h"

class WEBSCRAPING_EXPORT ScrapingFactory
{
public:
	enum ScrapingType {
		KuGou,
		WangYiYun,
	};
	BaseScraping* createScraping(ScrapingType type);
};


