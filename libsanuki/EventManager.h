/// EventManager
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

#ifndef LIBSANUKI_EventManager_H
#define LIBSANUKI_EventManager_H

#include <inttypes.h>

// libevent を使います
#include <event.h>
#include <boost/function.hpp>

namespace LibSanuki {

typedef int SocketDescriptor;
typedef boost::function::function<const bool(SanukiDataBlock *)> ReciveEventFunctor;
typedef boost::function::function<const bool(SendConnection *)> SendEventFunctor;
typedef boost::function::function<const bool()> TimerEventFunctor;
typedef uint32_t EventDesctiptor;

class EventManager {
private:
	struct event_base *m_pEventBase;
	struct EventData {
		struct event m_Event;

	};
	typedef std::map<EventDescriptor, struct event> EventMap;
	EventMap m_EventMap;
public:
	EventManager();
	~EventManager();

	const bool Initialize();

	/// そのときに送受信できるものについての I/O を行います。
	const bool Dispatch();
	/// そのとき処理できるもののうち、一個のみを処理して返ります。
	const bool DispatchOnce();
	/// 送受信やタイマイベントのためのループに入ります。処理すべき対象がなくなるまで返りません。
	const bool DispatchAll();

	/// 読み込み用にイベントハンドラを指定します
	const EventDescriptor SetReadEventHandler(const SocketDescriptor descriptor, ReciveEventFunctor &functor);
	/// 書き込み用にイベントハンドラを指定します
	const EventDescriptor SetWriteEventFunctor(const SocketDescriptor descriptor, SendEventFunctor &functor);
	/// 時間がたったときに呼び出されるイベントハンドラを指定します
	const EventDescriptor SetTimerEventFunctor(const uint32_t timeoutMillisecond, TimerEventFunctor &functor);

	/// Set*EventFunctor　で設定したイベントハンドラを取り除きます。
	const bool CanselEvent(const EventDescriptor descriptor);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_EventManager_H
