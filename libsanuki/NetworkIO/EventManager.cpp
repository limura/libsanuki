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

#include "EventManager.h"
#include "SocketDescriptor.h"

extern "C" {

/// libevent 用のイベントハンドラ
static void libeventEventHandler(int fd, short ev, void *arg){
	LibSanuki::EventManager::EventData *data = reinterpret_cast<LibSanuki::EventManager::EventData *>(arg);
	if(data != NULL && data->m_pManager != NULL){
		data->m_pManager->EventHandler(data, ev);
	}
}
/// libevent 用のDNS lookup用のイベントハンドラ
static void DNSHandler(int result, char type, int count, int ttl, void *addresses, void *arg){
	LibSanuki::EventManager::DNSLookupData *data = reinterpret_cast<LibSanuki::EventManager::DNSLookupData *>(arg);
	if(data != NULL && data->m_pManager != NULL){
		data->m_pManager->DNSLookupEventHandler(data, result, type, count, ttl, addresses);
	}
}

};

namespace LibSanuki {

/**
 @brief コンストラクタ
 */
EventManager::EventManager()
: m_pEventBase(NULL)
, m_NowDescriptorNum(0)
{
	m_EventSet.clear();
}

/**
 @brief デストラクタ
 */
EventManager::~EventManager(){
	EventSet::iterator i = m_EventSet.begin();
	for(; i != m_EventSet.end(); i++){
		event_del(&(*i)->m_Event);
		delete *i;
	}
	m_EventSet.clear();
}

/// 新しいEventDataを m_EventSet に登録し、それを返します。
EventManager::EventData *EventManager::_CreateNewEventData(){
	struct EventData *data = new EventData();
	if(data == NULL){
		return NULL;
	}
	std::pair<EventSet::iterator, bool> result = m_EventSet.insert(data);
	if(result.second == false){
		delete data;
		return NULL;
	}
	data->m_pManager = this;
	data->m_ReadFunctor = 0;
	data->m_WriteFunctor = 0;
	data->m_TimeoutFunctor = 0;
	return data;
}

/// 登録されたイベントを解除します
const bool EventManager::_DeleteEventData(struct EventData *data){
	if(data == NULL){
		return false;
	}
	EventSet::iterator i = m_EventSet.find(data);
	if(i != m_EventSet.end()){
		event_del(&data->m_Event);
		m_EventSet.erase(data);
		delete data;
		return true;
	}
	delete data;
	return false;
}


EventManager::DNSLookupData *EventManager::_CreateNewDNSLookupData(){
	struct DNSLookupData *data = new DNSLookupData();
	if(data == NULL){
		return NULL;
	}
	std::pair<DNSLookupSet::iterator, bool> result = m_LookupSet.insert(data);
	if(result.second == false){
		delete data;
		return NULL;
	}
	data->m_bNeedFallbackIPv4 = false;
	data->m_Functor = 0;
	data->m_pManager = this;
	data->m_ResolvingName = "";
	return data;
}
const bool EventManager::_DeleteDNSLookupData(EventManager::DNSLookupData *data){
	if(data != NULL){
		m_LookupSet.erase(data);
		delete data;
		return true;
	}
	return false;
}


/// 初期化します。falseを返した場合は初期化に失敗しています。
const bool EventManager::Initialize(){
	m_pEventBase = event_init();
	if(m_pEventBase == NULL){
		return false;
	}
	return true;
}

/// そのときに送受信できるものについての I/O を行います。
const bool EventManager::Dispatch(){
	switch(event_loop(EVLOOP_NONBLOCK)){
		case 0: // success
		case 1: // no events ware registerd
			return true;
		case -1: // error
		default:
			return false;
	}
	return false;
}
/// そのとき処理できるもののうち、一個のみを処理して返ります。
const bool EventManager::DispatchOnce(){
	switch(event_loop(EVLOOP_NONBLOCK | EVLOOP_ONCE)){
		case 0: // success
		case 1: // no events ware registerd
			return true;
		case -1: // error
		default:
			return false;
	}
	return false;
}
/// 送受信やタイマイベントのためのループに入ります。処理すべき対象がなくなるまで返りません。
const bool EventManager::DispatchAll(){
	event_dispatch();
	return false;
}

/// 読み込み用にイベントハンドラを指定します
const EventDescriptor EventManager::SetReadEventHandler(
SocketDescriptor descriptor
, EventFunctor &readFunctor
, EventFunctor &timeoutFunctor
, uint32_t timeoutMillisecond){
	EventData *data = _CreateNewEventData();
	if(data == NULL){
		return NULL;
	}
	data->m_ReadFunctor = readFunctor;
	data->m_TimeoutFunctor = timeoutFunctor;
	event_base_set(m_pEventBase, &data->m_Event);
	event_set(&data->m_Event, descriptor.GetSocket(), EV_READ, libeventEventHandler, data);
	if(timeoutMillisecond > 0){
		struct timeval tv;
		tv.tv_sec = timeoutMillisecond / 1000;
		tv.tv_usec = (timeoutMillisecond % 1000) * 1000;;
		event_add(&data->m_Event, &tv);
	}else{
		event_add(&data->m_Event, NULL);
	}
	return data;
}

/// 書き込み用にイベントハンドラを指定します
const EventDescriptor EventManager::SetWriteEventFunctor(
SocketDescriptor descriptor
, EventFunctor &writeFunctor
, EventFunctor &timeoutFunctor
, uint32_t timeoutMillisecond){
	EventData *data = _CreateNewEventData();
	if(data == NULL){
		return NULL;
	}
	data->m_WriteFunctor = writeFunctor;
	data->m_TimeoutFunctor = timeoutFunctor;
	event_base_set(m_pEventBase, &data->m_Event);
	event_set(&data->m_Event, descriptor.GetSocket(), EV_WRITE, libeventEventHandler, data);
	if(timeoutMillisecond > 0){
		struct timeval tv;
		tv.tv_sec = timeoutMillisecond / 1000;
		tv.tv_usec = (timeoutMillisecond % 1000) * 1000;;
		event_add(&data->m_Event, &tv);
	}else{
		event_add(&data->m_Event, NULL);
	}
	return data;
}

/// 読み込み、書き込み両用にイベントハンドラを指定します
const EventDescriptor EventManager::SetReadWriteEventFunctor(
SocketDescriptor descriptor
, EventFunctor &readFunctor
, EventFunctor &writeFunctor
, EventFunctor &timeoutFunctor
, uint32_t timeoutMillisecond){
	EventData *data = _CreateNewEventData();
	if(data == NULL){
		return NULL;
	}
	data->m_ReadFunctor = readFunctor;
	data->m_WriteFunctor = writeFunctor;
	data->m_TimeoutFunctor = timeoutFunctor;
	event_base_set(m_pEventBase, &data->m_Event);
	event_set(&data->m_Event, descriptor.GetSocket(), EV_WRITE, libeventEventHandler, data);
	if(timeoutMillisecond > 0){
		struct timeval tv;
		tv.tv_sec = timeoutMillisecond / 1000;
		tv.tv_usec = (timeoutMillisecond % 1000) * 1000;;
		event_add(&data->m_Event, &tv);
	}else{
		event_add(&data->m_Event, NULL);
	}
	return data;
}

/// 時間がたったときに呼び出されるイベントハンドラを指定します
const EventDescriptor EventManager::SetTimerEventFunctor(const uint32_t timeoutMillisecond, EventFunctor &functor){
	EventData *data = _CreateNewEventData();
	if(data == NULL){
		return NULL;
	}
	data->m_TimeoutFunctor = functor;
	event_base_set(m_pEventBase, &data->m_Event);
	evtimer_set(&data->m_Event, libeventEventHandler, data);
	struct timeval tv;
	tv.tv_sec = timeoutMillisecond / 1000;
	tv.tv_usec = (timeoutMillisecond % 1000) * 1000;
	event_add(&data->m_Event, &tv);
	return data;
}

/// Set*EventFunctor　で設定したイベントハンドラを取り除きます。
const bool EventManager::CanselEvent(EventDescriptor descriptor){
	return _DeleteEventData(reinterpret_cast<EventData *>(descriptor));
}

/// 何らかのイベントが発生したときに呼び出されるイベントハンドラです
void EventManager::EventHandler(EventData *data, short ev){
	if(data == NULL || m_EventSet.find(data) == m_EventSet.end()){
		// NULLか登録がなくなっていれば何もしなくてよい
		return;
	}
	// それぞれイベントハンドラを呼び出して、
	if(ev & EV_READ && data->m_ReadFunctor != 0){
		data->m_ReadFunctor();
	}
	if(ev & EV_WRITE && data->m_WriteFunctor != 0){
		data->m_WriteFunctor();
	}
	if(ev & EV_TIMEOUT && data->m_TimeoutFunctor != 0){
		data->m_TimeoutFunctor();
	}
	// 登録を削除
	_DeleteEventData(data);
}

/// IPv4アドレスのみで名前解決を行います
const EventDescriptor EventManager::StartIPv4Lookup(
const char *name, DNSLookupFunctor &functor){
	DNSLookupData *data = _CreateNewDNSLookupData();
	if(data == NULL){
		return NULL;
	}
	data->m_bNeedFallbackIPv4 = false;
	data->m_Functor = functor;

	evdns_resolve_ipv4(name, 0, DNSHandler, data);

	return data;
}
/// IPv6アドレスのみで名前解決を行います
const EventDescriptor EventManager::StartIPv6Lookup(const char *name, DNSLookupFunctor &functor){
	DNSLookupData *data = _CreateNewDNSLookupData();
	if(data == NULL){
		return NULL;
	}
	data->m_bNeedFallbackIPv4 = false;
	data->m_Functor = functor;

	evdns_resolve_ipv6(name, 0, DNSHandler, data);

	return data;
}

/// 名前解決を行います
const EventDescriptor EventManager::StartDNSLookup(const char *name, DNSLookupFunctor &functor){
	DNSLookupData *data = _CreateNewDNSLookupData();
	if(data == NULL){
		return NULL;
	}
	data->m_bNeedFallbackIPv4 = true;
	data->m_Functor = functor;

	evdns_resolve_ipv6(name, 0, DNSHandler, data);

	return data;
}

/// DNS lookup でのイベントが発生したときに呼び出されるイベントハンドラです
void EventManager::DNSLookupEventHandler(
DNSLookupData *data, int result, char type, int count, int ttl, void *addresses){
	if(m_LookupSet.find(data) == m_LookupSet.end()){
		// 既にテーブルになければ呼び出す必要はない
		return;
	}
	if(data->m_Functor == 0){
		// functor がなければ、何もする必要はない
		_DeleteDNSLookupData(data);
		return;
	}
	if(result != DNS_ERR_NONE){
		data->m_Functor(::std::vector<IPEndPoint>(), false);
		_DeleteDNSLookupData(data);
		return;
	}
	switch(type){
		case DNS_IPv4_A:
			{
				::std::vector<IPEndPoint> ipVector;
				uint32_t *pui32 = reinterpret_cast<uint32_t *>(addresses);
				for(int i = 0; i < count; i++){
					ipVector.push_back(IPEndPoint(pui32[i]));
				}
				data->m_Functor(ipVector, true);
			}
			break;
		case DNS_PTR:
			data->m_Functor(::std::vector<IPEndPoint>(), false);
			break;
		case DNS_IPv6_AAAA:
			{
				if(count <= 0 && data->m_bNeedFallbackIPv4 == true){
					evdns_resolve_ipv4(data->m_ResolvingName.c_str(), 0, DNSHandler, data);
					return;
				}

				::std::vector<IPEndPoint> ipVector;
				struct in6_addr *paddr = reinterpret_cast<struct in6_addr *>(addresses);
				for(int i = 0; i < count; i++){
					ipVector.push_back(IPEndPoint(paddr[i]));
				}
				data->m_Functor(ipVector, true);
			}
			break;
		default:
			data->m_Functor(::std::vector<IPEndPoint>(), false);
			break;
	}
	_DeleteDNSLookupData(data);
}


}; // namespase LibSanuki


