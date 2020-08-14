#include "BaseScraping.h"
#include <QDebug>
#include <qfile.h>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

DownloadPath& DownloadPath::operator=(const DownloadPath &rhs)
{
	this->image_path = rhs.image_path;
	if (!this->image_path.endsWith('/') && !this->image_path.endsWith('\\'))
	{
		this->image_path.append('/');
	}
	this->lyric_path = rhs.lyric_path;
	if (!this->lyric_path.endsWith('/') && !this->lyric_path.endsWith('\\'))
	{
		this->lyric_path.append('/');
	}
	this->music_path = rhs.music_path;
	if (!this->music_path.endsWith('/') && !this->music_path.endsWith('\\'))
	{
		this->music_path.append('/');
	}
	return *this;
}

BaseScraping::BaseScraping()
{

}

BaseScraping::~BaseScraping()
{

}

void BaseScraping::setMusicPath(DownloadPath& path)
{
	path_data = path;
}

DownloadPath BaseScraping::getMusicPath()
{
	return path_data;
}

QJsonObject BaseScraping::getReply(QUrl url)
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

QJsonObject BaseScraping::postReply(QUrl url, QByteArray param)
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
			QJsonParseError parser_error;
			json = QJsonDocument::fromJson(data, &parser_error).object();
			if (!(parser_error.error == QJsonParseError::NoError))
			{
				qDebug() << parser_error.errorString();
				json;
			}
		}
		reply->deleteLater();
		loop.exit();
	});
	manager->post(request, param);
	loop.exec();

	return json;
}


QByteArray BaseScraping::getData(QUrl url)
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

QString BaseScraping::toStandardFormat(QString &lrc)
{
	auto lyrics_list = lrc.split("\n");
	if (lyrics_list.size() > 10)
	{
		// 酷狗需要去除前10个
		for (size_t i = 0, length = 10; i < length; i++)
		{
			lyrics_list.removeFirst();
		}
	}
	return lyrics_list.join("\n");
}

