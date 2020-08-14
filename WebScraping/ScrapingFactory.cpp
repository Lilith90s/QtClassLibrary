#include "ScrapingFactory.h"

BaseScraping* ScrapingFactory::createScraping(ScrapingType type)
{
	switch (type)
	{
	case ScrapingFactory::KuGou:
		return new KGScraping;

	case ScrapingFactory::WangYiYun:

		return new WYYScraping;
	default:
		return nullptr;
		break;
	}
}
