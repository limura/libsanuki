/// TCPSendConnection
/*
Copyright (c) 2010 IIMURA Takuji. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
$Id$
*/

#include "TCPSendConnection.h"

#include <functional>
#include <boost/bind.hpp>

namespace LibSanuki {

/**
 @brief コンストラクタ
 */
TCPSendConnection::TCPSendConnection(EventManager &eventManager)
: m_EventManager(eventManager)
, m_Socket()
, m_ErrorFunctor(0)
{
}

TCPSendConnection::~TCPSendConnection(){
}

void TCPSendConnection::_ConnectEventHandler(){
	// ここに来たら、とりあえず接続はできたこととする
	if(_IsSendQueueAlive() == false){
		return;
	}
	m_EventManager.SetWriteEventFunctor(
		m_Socket
		, ::boost::bind(&TCPSendConnection::_WriteEventHandler, this)
		, 0);
}
void TCPSendConnection::_ConnectTimeoutEventHandler(){
	if(m_ErrorFunctor != 0){
		m_ErrorFunctor(this);
	}
}
void TCPSendConnection::_WriteEventHandler(){

}


const bool TCPSendConnection::Initialize(
const std::string &uri, SendConnection::ConnectionErrorFunctor functor){
	m_ErrorFunctor = functor;
	if(m_Socket.IsConnected() == true){
		// すでに接続されている
		return true;
	}

	std::string::size_type pos = uri.find_first_of(':');
	if(pos == std::string::npos){
		return false;
	}
	std::string addr = uri.substr(pos);
	IPEndPoint endPoint(addr.c_str());

	if(m_Socket.Initialize(AF_INET, SOCK_STREAM, 0) == false){
		return false;
	}

	if(m_Socket.SetNonBlocking() == false){
		return false;
	}
	if(endPoint.Connect(m_Socket) == false){
		return false;
	}
	m_EventManager.SetWriteEventFunctor(
		m_Socket
		, boost::bind(&TCPSendConnection::_ConnectEventHandler, this)
		, boost::bind(&TCPSendConnection::_ConnectTimeoutEventHandler, this)
		, 5 * 1000);
	return true;
}

const bool TCPSendConnection::SendBlock(SanukiDataBlock *data){
	return false;
}

}; // namespase LibSanuki


