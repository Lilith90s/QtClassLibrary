#include "CaculatePowerThread.h"
#include <QDebug>
CaculatePowerThread::CaculatePowerThread(Integer i, size_t p, int sequence)
{
	this->base = i;
	this->p = p;
	this->sequence = sequence;
}

void CaculatePowerThread::run()
{
	Integer pow = 1;
	for (CryptoPP::Integer i = 0; i < p; i++)
	{
		//qDebug() << CryptoPP::IntToString<CryptoPP::Integer>(i).c_str();
		pow = pow * base;
	}
	result = pow;
	//qDebug() << CryptoPP::IntToString<CryptoPP::Integer>(result).c_str();
	emit caculateFinished(result,sequence);
}

Integer CaculatePowerThread::getResult()
{
	return this->result;
}
