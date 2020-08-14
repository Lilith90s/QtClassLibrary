#include "WYYScraping.h"
#include "CaculatePowerThread.h"

#include <string>
#include <QDebug>
#include <qfile.h>
#include <QUrlQuery>
#include <QEventLoop>
#include <QJsonArray>
#include <QByteArray>
#include <QJsonObject>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <cryptopp/integer.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#define PARAM_TEST "8I7lV3VtFZApQtug5Ud6b7e9Tor44t1KDqVMdTVzJ2HIX3OICwKP4Px3Vr9XKvnLzAW2lLcD/uWl6eHvEAliYwmROnLF1cfZfhbQuxVGgfGuCnkd7Ao/oPMEptrCpK05m2TZ4XoybJWIQ6sqm4em1X59lM5wP80iq3VOjktvkXCCiB2QNUPyExqx9X4BRPNeSOd6wCGh8myY2N6RFiVb8piSsxCqehe8pMBt0gT6aBA0feWwfDoqLuJkTmfQpesA3LBzlX0QcnapQCGL9zetWyPEqfWwCfStjHkkybSfRpY="
#define ENCSECKEY_TEST "a363ebf3dd50f0c74b5b2c48ec2b4196890db40aaed9ad16f7f31fe7b3324604061bea442e09410a0f49dfaff6774e67f2d158e7d4c24d4de9161c1fdd16d12f66b61e3e2e1dcaa1c7e53817a813571f5b3d12764e2441818fea16731788e904f4f07c052f2740904b9081f5d2a214fe23eb0ae6ef2fe73b186351d19cb9772f"
using namespace CryptoPP;

CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH + 1] = "0CoJUm6Qyw8W8jud";
CryptoPP::byte key_test[CryptoPP::AES::DEFAULT_KEYLENGTH + 1] = "e3dqSctgw6bd4Icv";
CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE + 1] = "0102030405060708";

QList<SongInfo> WYYScraping::findSongs(QString song_name)
{
	//song_name = QString::fromLocal8Bit("千山万水");
	QList<SongInfo> song_infos;
	QByteArray msg = QString(R"({"hlpretag":"<span class=\"s-fc7\">","hlposttag":"</span>","s":"%1","type":"1","offset":"0","total":"true","limit":"30","csrf_token":""})").arg(song_name).toStdString().c_str();
	//qDebug() << msg;
	QByteArray encText = aesEncrypt(msg.toStdString(),(char*)key,(char*)iv).c_str();
	//qDebug() << "encText = " << encText;
	QByteArray random_key = generate_random_string(16);
	std::string str_random_key = random_key.toStdString();
	encText = aesEncrypt(encText.toStdString(), "mYPaD0qtCw6V1Axt",(char*)iv).c_str();
	//qDebug() << "encText = " << encText;
	QByteArray encSecKey = rsaEncrypt("mYPaD0qtCw6V1Axt", "010001", "00e0b509f6259df8642dbc35662901477df22677ec152b5ff68ace615bb7b725152b3ab17a876aea8a5aa76d2e417629ec4ee34" \
		"1f56135fccf695280104e0312ecbda92557c93870114af6c9d05c4f7f0c3685b7a46bee255932575cce10b424d813cfe4875d3e" \
		"82047b97ddef52741d546b8e289dc6935b3ece0462db0a22b8e7");
	//qDebug() << "encSecKey = " << encSecKey;

	QUrlQuery item;
	item.addQueryItem("params", encText);
	item.addQueryItem("encSecKey", encSecKey);
	
	QUrl url("https://music.163.com/weapi/cloudsearch/get/web?csrf_token=");
	//url.setQuery(item);
	//qDebug() << url;
	//encText = "eKjzrcc0ha9NK32WLk5aWbtw3vVASSGWL1Sido%2FWzppCltge18%2B7TGZPU9Pf1CD13fAEFH%2B%2BckvBLcxhIwnUrKbxjAIYnidURNYLVmDDF7hQHf0yNa2mTXf%2BJJp5ndm6OlFO7oOAq%2Fs8LQDi2KLtVtEdFFvNcnEqJN9xG9%2BYtXAikXKzSWiAeT5GgSnJdxxYoHONohNAncIdzP2Wiyk7wSMCXZqY98S3mx7xNBe83iz5tsZB4j9VvGV2E0vt9BPRp5IENksBKwuKy7OEdb%2FrOfjcLgnmcMkMlmGWmAIVU3g%3D";
	//encSecKey = "c8476759e575b608bd17563dfd5d63c271a504df54130d6352c71e3d3c45ebacc99082587eb5e3c4fb6b9b93a2bd4ddbce439fdc8f076e865ac85120b6f090aad030a63361ea5e50b0472fc5a7fa26d76284a24631ac29c875f9cc3237eaa3fd656c08a890f0e6f259eb31e5f1638bcd15e0a8eb242e1b881a199278db5bb14c";

	QString params = QString("params=%1&encSecKey=%2").arg(encText.toPercentEncoding().toStdString().c_str(),encSecKey.toPercentEncoding().toStdString().c_str());
	//qDebug() << params;
	auto res = this->post(url,params.toStdString().c_str());
	if (res.contains("result"))
	{
		QJsonObject result_object = res["result"].toObject();
		if (result_object.contains("songs"))
		{
			QJsonArray songs_array = result_object["songs"].toArray();
			for (auto &song:songs_array)
			{
				SongInfo song_info;
				QJsonObject song_object = song.toObject();
				if (song_object.contains("name"))
				{
					 song_info.name = song_object.value("name").toString();
					 song_info.hash = QString::number(song_object.value("id").toInt());
					 QJsonArray author_array = song_object.value("ar").toArray();
					 for (auto &author_object :author_array)
					 {
						 QString author = author_object.toObject().value("name").toString();
						 if (author_array.size() == 0)
						 {
							 
							 song_info.athor = author;
						 }
						 else
						 {
							 song_info.athor += "/" + author;
						 }
					 }
					 song_infos.append(song_info);
				}
			}
		}
	}

	return song_infos;
}

bool WYYScraping::downloadSong(SongInfo &song_info)
{

	return false;
}

CryptoPP::Integer WYYScraping::toIntString(QString hex)
{
	QMap<QChar, int> ascii = {
		{'0',0 },{'1',1 },{'2',2 },{'3',3 },{'4',4 },
		{'5',5 },{'6',6 },{'7',7 },{'8',8 },{'9',9 },
		{'a',10},{'b',11},{'c',12},{'d',13},{'e',14},
		{'f',15}
	};
	CryptoPP::Integer sum = 0;
	int length = hex.size();
	for (int i = length -1; i >= 0; i--)
	{
		
		QChar c = hex.at(i).toLower();
		CryptoPP::Integer number(ascii[c]);
		CryptoPP::Integer width = pow(16, length - 1 - i);
		sum = sum + number * width;
		//qDebug() << CryptoPP::IntToString<CryptoPP::Integer>(sum).c_str();
	}
	return sum;
}

CryptoPP::Integer WYYScraping::pow(int a , unsigned long e)
{
	CryptoPP::Integer sum = 1;
	for (CryptoPP::Integer i = 0; i < e; i++)
	{
		sum = sum * a;
	}
	return sum;
}

QJsonObject WYYScraping::post(QUrl url, QByteArray param)
{
	QSslConfiguration config;
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	auto request = QNetworkRequest(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
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
	manager->post(request,param);
	loop.exec();
	return json;
}

QByteArray WYYScraping::generate_random_string(int length)
{
	QByteArray string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	QByteArray random;
	for (int i = 0;i<length ;i++)
	{
		random += string[qrand() % string.size()];
	}
	return random;
}

QByteArray WYYScraping::aesEncrypt(QString msg, CryptoPP::byte* key)
{
	std::string cipherText;
	// ase加密明文长度必须是16的倍数，不足的使用对应的字符串进行填充
	int padding = 16 - (msg.size() % 16);
	// msg += "12313123123";
	for (size_t i = 0; i < padding; i++)
	{
		msg += char(padding);
	}
	//msg += std::string(padding, char(padding));
	// 用来进行加密或者解密的初始向量（必须是16位）
	// CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE+1] = "0102030405060708";

	std::string msg_cstr = msg.toStdString();  // 存储加密后的数据
	// 进行AES加密  
	
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(msg_cstr.c_str()), msg_cstr.length() + 1);
	stfEncryptor.MessageEnd();
	
	

	
	// 转换
	//std::string cipherTextHex;
	//
	//for (int i = 0; i < cipherText.size(); i++)
	//{
	//	char ch[3] = { 0 };
	//	sprintf_s(ch, "%02x", static_cast<CryptoPP::byte>(cipherText[i]));
	//	cipherTextHex += ch;
	//}
	QByteArray ret = msg_cstr.c_str();
	
	return ret.toBase64();
}

std::string WYYScraping::aesEncrypt(const std::string& str_in, const std::string& key, const std::string& iv)
{
	std::string str_out;
	
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption((CryptoPP::byte*)(key.c_str()), key.length(), (CryptoPP::byte*)(iv.c_str()));

	CryptoPP::StringSource encryptor(str_in, true,
		new CryptoPP::StreamTransformationFilter(encryption,
			new CryptoPP::Base64Encoder(
				new CryptoPP::StringSink(str_out),
				false // do not append a newline
			)
		)
	);
	return str_out;
}

QByteArray WYYScraping::rsaEncrypt(const std::string text, const std::string pubkey, const std::string modulus)
{
	// 随机字符串逆序排列
	std::string reserve_string;
	for (int i = text.size() - 1; i >= 0; i--)
	{
		reserve_string.push_back(text[i]);
	}
	
	QByteArray byte = reserve_string.c_str();
	bool ok;
	std::string text_byte = byte.toHex().toStdString() ;
	std::string pubkey_byte = QByteArray(pubkey.c_str()).toHex().toStdString();
	std::string modulus_byte = QByteArray(modulus.c_str()).toHex().toStdString();
	// qDebug() << text_byte.c_str();
	// qDebug() << QByteArray(modulus.c_str()).toHex();
	CryptoPP::Integer text_int = toIntString(byte.toHex());
	CryptoPP::Integer pubkey_int("65537");
	CryptoPP::Integer modulus_int = toIntString(modulus.c_str());

	// 存放运算结果
	/* 计算原理a*b%c == (a%c*b%c)%c */
	/* a^11 == a^2^0 * a^2^1 * a^2^3 == a^1 * a^2 * a^8  */
	CryptoPP::Integer sec_key_int = 1;
	text_int %= modulus_int;
	while (pubkey_int > 0)
	{
		if (pubkey_int % 2 ==1)
		{
			sec_key_int = (sec_key_int*text_int) % modulus_int;
		}
		text_int = text_int * text_int%modulus_int;
		pubkey_int /= 2;
	}
	// 转换成十六进制
	std::string str_sec_key = CryptoPP::IntToString<CryptoPP::Integer>(sec_key_int,16).c_str();
	QByteArray byte_sec_key = str_sec_key.c_str();
	// 不满256位补0
	int length = 256 - byte_sec_key.size();
	for (size_t i = 0; i < length; i++)
	{
		byte_sec_key = '0' + byte_sec_key;
	}
	return byte_sec_key;
}
