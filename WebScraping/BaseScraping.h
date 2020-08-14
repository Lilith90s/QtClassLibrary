#pragma once

#include "webscraping_global.h"
#include <QObject>
/*歌曲信息*/
struct SongInfo
{
	QString name;
	QString athor;
	QString hash;
};
/*下载路径配置*/
struct DownloadPath
{
	QString music_path = "./";
	QString image_path = "./";
	QString lyric_path = "./";
	DownloadPath& operator =(const DownloadPath &rhs);
};

class WEBSCRAPING_EXPORT BaseScraping : public QObject
{
	Q_OBJECT
public:
	BaseScraping();
	virtual ~BaseScraping();
public slots:
	virtual QList<SongInfo> findSongs(QString song_name) = 0;

	virtual bool downloadSong(SongInfo &song_info) = 0;

	void setMusicPath(DownloadPath& path);

	DownloadPath getMusicPath();
protected:

	// 使用get的方式获取reply
	QJsonObject getReply(QUrl url);
	// 使用post的方式，可携带数据
	QJsonObject postReply(QUrl url, QByteArray param);
	// 使用get的方式获取data
	QByteArray getData(QUrl url);

	QString toStandardFormat(QString &lrc);  // 歌词标准化

	
private:
	DownloadPath path_data;
};

