/*
 TCPSendConnection

 Copyright(c) IIMURA Takuji 2010 All rights reserved.
 */

#ifndef LIBSANUKI_TCPSendConnection_H
#define LIBSANUKI_TCPSendConnection_H

#include "SendConnection.h"

namespase LibSanuki {

class TCPSendConnection : public SendConnection {
private:
	int m_Socket;
public:
	TCPSendConnection();
	~TCPSendConnection();

	const bool Initialize(const std::string &uri);
	const bool SendBlock(SanukiSendBlock *data);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_TCPSendConnection_H
