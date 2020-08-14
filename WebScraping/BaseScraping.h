#pragma once

#include "webscraping_global.h"
#include <QObject>
/*������Ϣ*/
struct SongInfo
{
	QString name;
	QString athor;
	QString hash;
};
/*����·������*/
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

	// ʹ��get�ķ�ʽ��ȡreply
	QJsonObject getReply(QUrl url);
	// ʹ��post�ķ�ʽ����Я������
	QJsonObject postReply(QUrl url, QByteArray param);
	// ʹ��get�ķ�ʽ��ȡdata
	QByteArray getData(QUrl url);

	QString toStandardFormat(QString &lrc);  // ��ʱ�׼��

	
private:
	DownloadPath path_data;
};

