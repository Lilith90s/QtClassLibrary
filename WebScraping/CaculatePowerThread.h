#pragma once
#include <QThread>
#include <cryptopp/integer.h>
/*���߳��н���������*/
using CryptoPP::Integer;
class CaculatePowerThread :
	public QThread
{
	Q_OBJECT
public:
	CaculatePowerThread(Integer i, size_t p, int sequence);

	void run() override;

	Integer getResult();

signals:
	void caculateFinished(Integer data,int sequence);	

private:
	Integer base;
	size_t p;
	Integer result;
	int sequence;
};

