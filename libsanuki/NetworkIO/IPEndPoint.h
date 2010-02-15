/// IPEndPoint.h
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

#ifndef LIBSANUKI_IPEndPoint_H
#define LIBSANUKI_IPEndPoint_H

#include <boost/function/function.hpp>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <net/inet.h>
#include <sys/types.h>
#endif

namespace LibSanuki {

class SocketDescriptor;

class IPEndPoint {
private:
	struct sockaddr_storage m_Storage;
public:
	IPEndPoint();
	explicit IPEndPoint(char *address);
	explicit IPEndPoint(const IPEndPoint &other);
	~IPEndPoint();

	/// ���������܂�
	const bool Initialize(char *address);

	/// DNS�ɂ�閼�O�������s���܂��B
	static const cool Lookup(EventManager &eventManager, ::boost::function<void(IPEndPoint, bool)> &LookupResultReciver);

	/// �ڑ����J�n���܂�
	const bool Connect(SocketDescriptor &descriptor, ::boost::function<void(bool)> &connectEventHandler);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_IPEndPoint_H
