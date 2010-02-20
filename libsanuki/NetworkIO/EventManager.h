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

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <inttypes.h>

#include <event.h>
#include <evdns.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <vector>

namespace LibSanuki {

class IPEndPoint;

typedef boost::function<void()> EventFunctor;
typedef ::boost::function<void(std::vector<IPEndPoint>, bool)> DNSLookupFunctor;
typedef void *EventDescriptor;

class SocketDescriptor;

class EventManager {
private:
	struct event_base *m_pEventBase;
public:
	/// �����ŗ��p���邽�߂̍\���̂ł��B�O������̓A�N�Z�X���Ȃ��ł�������
	struct EventData {
		EventManager *m_pManager;
		struct event m_Event;
		EventFunctor m_ReadFunctor;
		EventFunctor m_WriteFunctor;
		EventFunctor m_TimeoutFunctor;
		EventDescriptor m_Descriptor;
	};
	/// �����Ŏg�p���邽�߂̍\���̂ł��B�O������̓A�N�Z�X���Ȃ��ł�������
	struct DNSLookupData{
		EventManager *m_pManager;
		DNSLookupFunctor m_Functor;
		bool m_bNeedFallbackIPv4; //!< IPv6 �Ŗ��O�����Ɏ��s������AIPv4�ň����Ȃ����ׂ������w�肵�܂�
		std::string m_ResolvingName; //!< �������̖��O
	};
private:
	/// �R�s�[�R���X�g���N�^�͊J������܂���B(����������܂���)
	EventManager(const EventManager &other);

	typedef std::set<EventData *> EventSet;
	EventSet m_EventSet;
	uint32_t m_NowDescriptorNum;
	typedef std::set<DNSLookupData *> DNSLookupSet;
	DNSLookupSet m_LookupSet;

	EventData *_CreateNewEventData();
	const bool _DeleteEventData(struct EventData *data);

	DNSLookupData *_CreateNewDNSLookupData();
	const bool _DeleteDNSLookupData(DNSLookupData *data);

public:
	EventManager();
	~EventManager();

	const bool Initialize();

	static EventFunctor GetNullFunctor();

	/// ���̂Ƃ��ɑ���M�ł�����̂ɂ��Ă� I/O ���s���܂��B
	const bool Dispatch();
	/// ���̂Ƃ������ł�����̂̂����A��݂̂��������ĕԂ�܂��B
	const bool DispatchOnce();
	/// ����M��^�C�}�C�x���g�̂��߂̃��[�v�ɓ���܂��B�������ׂ��Ώۂ��Ȃ��Ȃ�܂ŕԂ�܂���B
	const bool DispatchAll();

	/// �ǂݍ��ݗp�ɃC�x���g�n���h�����w�肵�܂�
	const EventDescriptor SetReadEventHandler(SocketDescriptor descriptor, EventFunctor &readFunctor, EventFunctor &timeoutFunctor, uint32_t timeoutMillisecond = 0);
	/// �������ݗp�ɃC�x���g�n���h�����w�肵�܂�
	const EventDescriptor SetWriteEventFunctor(SocketDescriptor descriptor, EventFunctor &writeFunctor, EventFunctor &timeoutFunctor, uint32_t timeoutMillisecond = 0);
	/// �ǂݍ��݁A�������ݗ��p�ɃC�x���g�n���h�����w�肵�܂�
	const EventDescriptor SetReadWriteEventFunctor(SocketDescriptor descriptor, EventFunctor &readFunctor, EventFunctor &writeFunctor, EventFunctor &timeoutFunctor, uint32_t timeoutMillisecond = 0);
	/// ���Ԃ��������Ƃ��ɌĂяo�����C�x���g�n���h�����w�肵�܂�
	const EventDescriptor SetTimerEventFunctor(const uint32_t timeoutMillisecond, EventFunctor &functor);

	/// IPv4�A�h���X�݂̂Ŗ��O�������s���܂�
	const EventDescriptor StartIPv4Lookup(const char *name, DNSLookupFunctor &functor);
	/// IPv6�A�h���X�݂̂Ŗ��O�������s���܂�
	const EventDescriptor StartIPv6Lookup(const char *name, DNSLookupFunctor &functor);
	/// ���O�������s���܂�
	const EventDescriptor StartDNSLookup(const char *name, DNSLookupFunctor &functor);

	/// Set*EventFunctor�@�Őݒ肵���C�x���g�n���h������菜���܂��B
	const bool CanselEvent(EventDescriptor descriptor);

	/// �Ȃ�炩�̃C�x���g�����������Ƃ��ɌĂяo�����C�x���g�n���h���ł�
	void EventHandler(EventData *data, short ev);

	/// DNS lookup �ł̃C�x���g�����������Ƃ��ɌĂяo�����C�x���g�n���h���ł�
	void DNSLookupEventHandler(DNSLookupData *data, int result, char type, int count, int ttl, void *addresses);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_EventManager_H
