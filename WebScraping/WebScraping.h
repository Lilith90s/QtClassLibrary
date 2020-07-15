#pragma once

#include "webscraping_global.h"
#include <QObject>
/*∏Ë«˙–≈œ¢*/
struct SongInfo
{
	QString name;
	QString athor;
	QString hash;
};
class WEBSCRAPING_EXPORT WebScraping : public QObject
{
	Q_OBJECT
public:
	WebScraping();
public slots:
	QList<SongInfo> findSongs(QString song_name);

	bool downloadSong(SongInfo &song_info,QString download_path = "./");

protected:
	QJsonObject getReply(QUrl url);
	QByteArray getSongData(QUrl url);
};
