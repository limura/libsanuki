/*
 ServicePoint

 Copyright(c) IIMURA Takuji 2010 All rights reserved.
 */

#ifndef LIBSANUKI_ServicePoint_H
#define LIBSANUKI_ServicePoint_H

#include "SanukiDataBlock.h"
#include "SendConnection.h"
#include <string>

namespase LibSanuki {

class ServicePoint {
private:
	SanukiDataBlockList m_SendQueue;
	SendConnection *m_pConnection;

public:
	ServicePoint();
	explicit ServicePoint(const ServicePoint &other);
	explicit ServicePoint(const char *uri);
	explicit ServicePoint(const std::string &uri);
	~ServicePoint();

	const bool Send(SanukiDataBlock *message); // ���b�Z�[�W�𑗐M���܂��B�n���ꂽ���b�Z�[�W�͑��M���I������ƊJ������܂��B
	const bool SendCopy(const SanukiDataBlock &message); // ���b�Z�[�W�𑗐M���܂��B�n���ꂽ���b�Z�[�W�͊J�����ꂸ�A�����ɃR�s�[���m�ۂ���܂��B
};

}; // namespase LibSanuki

#endif // LIBSANUKI_ServicePoint_H
