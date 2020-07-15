#include "WebScraping.h"
#include <QDebug>
#include <qfile.h>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

WebScraping::WebScraping()
{

}

QList<SongInfo> WebScraping::findSongs(QString song_name)
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

bool WebScraping::downloadSong(SongInfo &song_info, QString download_path /*= "./"*/)
{
	if (!download_path.endsWith('/'))
	{
		download_path += '/';
	}
	QString url_path = QString("https://wwwapi.kugou.com/yy/index.php?r=play/getdata&callback=jQuery19104844152583738923_1580266512987&hash=%1&album_id=&dfid=2SSV0x4LWcsx0iylej1F6w7P&mid=44328d3dc4bfce21cf2b95cf9e76b968&platid=4&_=1580266512988").arg(song_info.hash);
	QUrl url(url_path);
	QJsonObject json = getReply(url);
	if (json.contains("data"))
	{
		QJsonObject data_object = json.value("data").toObject();
		if (data_object.contains("play_backup_url"))
		{
			auto download_url = data_object.value("play_backup_url").toString();
			QByteArray data = getSongData(download_url);
			QFile f(download_path+song_info.name+".mp3");
			if (f.open(QIODevice::WriteOnly))
			{
				f.write(data);
				f.close();
				return true;
			}	
		}
	}
	return false;
}

QJsonObject WebScraping::getReply(QUrl url)
{
	QSslConfiguration config;
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	auto request = QNetworkRequest(url);
	request.setSslConfiguration(config);
	auto manager = new QNetworkAccessManager;
	QJsonObject json;
	QEventLoop loop;
	connect(manager, &QNetworkAccessManager::finished, &loop, [&](QNetworkReply* reply) {
		auto data = reply->readAll();
		if (data.size() >= 2)
		{
			auto standard_data = data.mid(data.indexOf('(') + 1, data.lastIndexOf(')') - data.indexOf('(') - 1);

			QJsonParseError parser_error;
			json = QJsonDocument::fromJson(standard_data, &parser_error).object();
			if (!(parser_error.error == QJsonParseError::NoError))
			{
				qDebug() << parser_error.errorString();
				json;
			}
		}
		reply->deleteLater();
		loop.exit();
	});
	manager->get(request);
	loop.exec();

	return json;
}

QByteArray WebScraping::getSongData(QUrl url)
{
	auto request = QNetworkRequest(url);
	auto manager = new QNetworkAccessManager;
	QByteArray data;
	QEventLoop loop;
	connect(manager, &QNetworkAccessManager::finished, &loop, [&](QNetworkReply* reply) {
		data = reply->readAll();
		reply->deleteLater();
		loop.exit();
	});
	manager->get(request);
	loop.exec();
	return data;
}
