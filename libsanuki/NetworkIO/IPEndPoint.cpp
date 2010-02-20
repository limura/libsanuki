/// IPEndPoint.cpp
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

#include "IPEndPoint.h"
#include "SocketDescriptor.h"

#ifdef _WIN32
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

namespace LibSanuki {

/**
 @brief コンストラクタ
 */
IPEndPoint::IPEndPoint(){
}

IPEndPoint::IPEndPoint(const char *address){
	Initialize(address);
}

IPEndPoint::IPEndPoint(const IPEndPoint &other){
	memcpy(&m_Storage, &other.m_Storage, sizeof(m_Storage));
}

IPEndPoint::~IPEndPoint(){
}

const bool IPEndPoint::Initialize(const char *address){
	if(address == NULL){
		return false;
	}
	std::string url(address);
	std::string host = url.substr(0, url.find_first_of(':'));
	std::string portStr = url.substr(url.find_first_of(':'));
	if(host.size() <= 0 || portStr.size() <= 0){
		return false;
	}
	int port = atoi(portStr.c_str());
	memset(&m_Storage, 0, sizeof(m_Storage));
#ifdef _WIN32
	//WSAStringToAddress(host.c_str(), AF_INET6, 
#else
	unsigned char buf[sizeof(struct in6_addr)];
	if(inet_pton(AF_INET6, address, buf) == 1){
		struct sockaddr_in6 *p = (struct sockaddr_in6 *)&m_Storage;
		memcpy(&p->sin6_addr, buf, sizeof(p->sin6_addr));
		p->sin6_family = AF_INET6;
		p->sin6_port = htons(port);
		//p->sin6_flowinfo;
		//p->sin6_scope_id;
	}else if(inet_pton(AF_INET, address, buf) == 1){
		struct sockaddr_in *p = (struct sockaddr_in *)&m_Storage;
		memcpy(&p->sin_addr, buf, sizeof(p->sin_addr));
		p->sin_family = AF_INET;
		p->sin_port = htons(port);
	}else{
		return false;
	}
	return true;
#endif
}

/// DNSによる名前解決を行います。
const bool IPEndPoint::Lookup(EventManager &eventManager, ::boost::function<void(IPEndPoint, bool)> LookupResultReciver){
	// とりあえずは実装しません
	// XXX not implemented yet.
	return false;
}

/// 接続を開始します
const bool IPEndPoint::Connect(SocketDescriptor &descriptor){
	if(connect(descriptor.GetSocket(), (struct sockaddr*)&m_Storage, sizeof(m_Storage)) != 0){
		// XXX != 0 でいいのかは不明
		return false;
	}

}

}; // namespase LibSanuki


