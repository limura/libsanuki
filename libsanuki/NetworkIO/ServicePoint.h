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

	const bool Send(SanukiDataBlock *message); // メッセージを送信します。渡されたメッセージは送信が終了すると開放されます。
	const bool SendCopy(const SanukiDataBlock &message); // メッセージを送信します。渡されたメッセージは開放されず、内部にコピーが確保されます。
};

}; // namespase LibSanuki

#endif // LIBSANUKI_ServicePoint_H
