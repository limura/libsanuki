/// SocketDescriptor
/// Winsock��BSD Socket�𓯂��悤�Ɉ������߂�wrapper
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

#ifndef LIBSANUKI_SocketDescriptor_H
#define LIBSANUKI_SocketDescriptor_H

#include "IPEndPoint.h"
#include "EventManager.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <net/inet.h>
#include <sys/types.h>
#endif

namespace LibSanuki {

class SocketDescriptor {
private:
#ifdef _WIN32
	SOCKET m_Socket;
#else
	int m_Socket;
#endif
public:
	SocketDescriptor();
	~SocketDescriptor();

	/// ���������܂�
	const bool Initialize(int addressFamily, int type, int protocol);

	/// �L���Ȓl�������Ă��邩�ǂ������m�F���܂�
	const bool IsValid() const;

	/// Non Blocking Mode �ɂ��܂�
	const bool SetNonBlocking();

	/// Blocking Mode �ɂ��܂�
	const bool SetBlocking();

	/// �Ώۂɐڑ����J�n���܂�
	const bool ConnectTo(IPEndPoint &endPoint);

	/// �ǂݍ��ݗp�̃C�x���g�n���h����o�^���܂�
	const bool AddReadEventHandler(EventManager &manager, EventFunctor &functor);

	/// �������ݗp�̃C�x���g�n���h����o�^���܂�
	const bool AddWriteEventHandler(EventManager &manager, EventFunctor &functor);

	/// ���łɐڑ��ς݂��ǂ������擾���܂��B
	const bool IsConnected() const;

#ifdef _WIN32
	const SOCKET GetSocket();
#else
	const int GetSocket();
#endif
};

}; // namespase LibSanuki

#endif // LIBSANUKI_?_H
