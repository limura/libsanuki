/// SocketDescriptor
/// WinsockとBSD Socketを同じように扱うためのwrapper
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

	/// 初期化します
	const bool Initialize(int addressFamily, int type, int protocol);

	/// 有効な値を持っているかどうかを確認します
	const bool IsValid() const;

	/// Non Blocking Mode にします
	const bool SetNonBlocking();

	/// Blocking Mode にします
	const bool SetBlocking();

	/// 対象に接続を開始します
	const bool ConnectTo(IPEndPoint &endPoint);

	/// 読み込み用のイベントハンドラを登録します
	const bool AddReadEventHandler(EventManager &manager, EventFunctor &functor);

	/// 書き込み用のイベントハンドラを登録します
	const bool AddWriteEventHandler(EventManager &manager, EventFunctor &functor);

	/// すでに接続済みかどうかを取得します。
	const bool IsConnected() const;

#ifdef _WIN32
	const SOCKET GetSocket();
#else
	const int GetSocket();
#endif
};

}; // namespase LibSanuki

#endif // LIBSANUKI_?_H
