#pragma once

#include "BaseScraping.h"
#include <QObject>

/*�ṷ*/
class KGScraping : public BaseScraping
{
	Q_OBJECT
public:
	KGScraping();
public slots:
	QList<SongInfo> findSongs(QString song_name);

	bool downloadSong(SongInfo &song_info);


};
