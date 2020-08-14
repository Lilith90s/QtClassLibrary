#pragma once
#include "BaseScraping.h"
#include <QObject>
#include <cryptopp/aes.h>
#include <cryptopp/rsa.h>
#include <cryptopp/modes.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>

class WYYScraping :
	public BaseScraping
{
	Q_OBJECT
public:

	QList<SongInfo> findSongs(QString song_name);

	bool downloadSong(SongInfo &song_info);

	// 将16进制字符串转换成int型字符串
	static CryptoPP::Integer toIntString(QString hex);

	// 计算Integer的次方数
	static CryptoPP::Integer pow(int a,unsigned long e);

protected:
	QJsonObject post(QUrl url,QByteArray param);
private:
	// 生成密钥
	QByteArray generate_random_string(int length);

	QByteArray aesEncrypt(QString msg, CryptoPP::byte* key);

	std::string aesEncrypt(const std::string& str_in, const std::string& key, const std::string& iv);

	QByteArray rsaEncrypt(const std::string text,const std::string pubkey,const std::string modulus);
};

