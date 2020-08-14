#include "KGScraping.h"
#include <QDebug>
#include <qfile.h>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>



KGScraping::KGScraping()
{

}
QList<SongInfo> KGScraping::findSongs(QString song_name)
{
	QUrl url("http://songsearch.kugou.com/song_search_v2?callback=jQuery191034642999175022426_1489023388639&keyword="+song_name);
	QList<SongInfo> song_infos;
	QJsonObject json = getReply(url);
	if (json.contains("data"))
	{
		QJsonObject data_object = json.value("data").toObject();
		if (data_object.contains("lists"))
		{
			QJsonArray lists_array = data_object.value("lists").toArray();
			for (size_t i = 0, length = lists_array.size(); i < length; i++)
			{
				SongInfo song_info;
				QJsonObject song_object = lists_array.at(i).toObject();
				song_info.name = song_object["FileName"].toString().remove("</em>").remove("<em>");
				song_info.hash = song_object["FileHash"].toString();

				song_infos.append(song_info);
			}
		}
	}

	return song_infos;
}

bool KGScraping::downloadSong(SongInfo &song_info)
{
	
	QString url_path = QString("https://wwwapi.kugou.com/yy/index.php?r=play/getdata&callback=jQuery19104844152583738923_1580266512987&hash=%1&album_id=&dfid=2SSV0x4LWcsx0iylej1F6w7P&mid=44328d3dc4bfce21cf2b95cf9e76b968&platid=4&_=1580266512988").arg(song_info.hash);
	QUrl url(url_path);
	QJsonObject json = getReply(url);
	if (json.contains("data"))
	{
		QJsonObject data_object = json.value("data").toObject();
		// ¸èÇú
		if (data_object.contains("play_backup_url"))
		{
			
			qDebug() << QString::fromLocal8Bit("ÏÂÔØ¸èÇúÂ·¾¶ : ") << getMusicPath().music_path;
			auto download_url = data_object.value("play_backup_url").toString();
			qDebug() << download_url;
			QByteArray data = getData(download_url);
			QFile f(getMusicPath().music_path+song_info.name+".mp3");
			if (f.open(QIODevice::WriteOnly))
			{
				f.write(data);
				f.close();
			}	
		}
		// ¸è´Ê
		if (data_object.contains("lyrics"))
		{
			qDebug() << QString::fromLocal8Bit("ÏÂÔØ¸è´ÊÂ·¾¶ : ") << getMusicPath().lyric_path;
			QString lyrics = data_object.value("lyrics").toString();
			// ¸ñÊ½»¯
			QString standard_lyrics = toStandardFormat(lyrics);
			QFile f(getMusicPath().lyric_path + song_info.name + ".lrc");
			if (f.open(QIODevice::WriteOnly))
			{
				f.write(standard_lyrics.toStdString().c_str());
				f.close();
			}
		}

		// ±³¾°Í¼Æ¬
		if (data_object.contains("img"))
		{
			qDebug() << QString::fromLocal8Bit("ÏÂÔØÍ¼Æ¬Â·¾¶ : ") << getMusicPath().image_path;
			QString img_url = data_object.value("img").toString();
			qDebug() << img_url;
			QString img_format(img_url.split(".").last());
			QByteArray img_data = getData(img_url);
			QFile f(getMusicPath().image_path + song_info.name + "." + img_format);
			if (f.open(QIODevice::WriteOnly))
			{
				f.write(img_data);
				f.close();
			}
		}
		return true;
	}
	
	return false;
}




