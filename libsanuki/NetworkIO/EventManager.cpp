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

extern "C" {

/// libevent �p�̓ǂݍ��ݗp�C�x���g�n���h��
static void ReadHandler(int fd, short event, void *arg){
	LibSanuki::EventManager::EventData *data = reinterpret_cast<LibSanuki::EventManager::EventData *>(arg);
	if(data != NULL && data->m_pManager != NULL){
		data->m_pManager->EventHandler(data);
	}
}
/// libevent �p�̏����o���p�C�x���g�n���h��
static void WriteHandler(int fd, short event, void *arg){
	LibSanuki::EventManager::EventData *data = reinterpret_cast<LibSanuki::EventManager::EventData *>(arg);
	if(data != NULL && data->m_pManager != NULL){
		data->m_pManager->EventHandler(data);
	}
}
/// libevent �p�̃^�C�}�p�C�x���g�n���h��
static void TimerHandler(int fd, short event, void *arg){
	LibSanuki::EventManager::EventData *data = reinterpret_cast<LibSanuki::EventManager::EventData *>(arg);
	if(data != NULL && data->m_pManager != NULL){
		data->m_pManager->EventHandler(data);
	}
}
};

namespace LibSanuki {

/**
 @brief �R���X�g���N�^
 */
EventManager::EventManager()
: m_pEventBase(NULL)
, m_NowDescriptorNum(0)
{
	m_EventSet.clear();
}

/**
 @brief �f�X�g���N�^
 */
EventManager::~EventManager(){
	EventSet::iterator i = m_EventSet.begin();
	for(; i != m_EventSet.end(); i++){
		event_del(&(*i)->m_Event);
		delete *i;
	}
	m_EventSet.clear();
}

/// �V����EventData�� m_EventSet �ɓo�^���A�����Ԃ��܂��B
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
	data->m_Functor = 0;
	return data;
}

/// �o�^���ꂽ�C�x���g���������܂�
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

/// ���������܂��Bfalse��Ԃ����ꍇ�͏������Ɏ��s���Ă��܂��B
const bool EventManager::Initialize(){
	m_pEventBase = event_init();
	if(m_pEventBase == NULL){
		return false;
	}
	return true;
}

/// ���̂Ƃ��ɑ���M�ł�����̂ɂ��Ă� I/O ���s���܂��B
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
/// ���̂Ƃ������ł�����̂̂����A��݂̂��������ĕԂ�܂��B
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
/// ����M��^�C�}�C�x���g�̂��߂̃��[�v�ɓ���܂��B�������ׂ��Ώۂ��Ȃ��Ȃ�܂ŕԂ�܂���B
const bool EventManager::DispatchAll(){
	event_dispatch();
	return false;
}

/// �ǂݍ��ݗp�ɃC�x���g�n���h�����w�肵�܂�
const EventDescriptor EventManager::SetReadEventHandler(const SocketDescriptor descriptor, EventFunctor &functor){
	EventData *data = _CreateNewEventData();
	if(data == NULL){
		return NULL;
	}
	data->m_Functor = functor;
	event_base_set(m_pEventBase, &data->m_Event);
	event_set(&data->m_Event, descriptor, EV_READ, ReadHandler, data);
	event_add(&data->m_Event, NULL);
	return data;
}

/// �������ݗp�ɃC�x���g�n���h�����w�肵�܂�
const EventDescriptor EventManager::SetWriteEventFunctor(const SocketDescriptor descriptor, EventFunctor &functor){
	EventData *data = _CreateNewEventData();
	if(data == NULL){
		return NULL;
	}
	data->m_Functor = functor;
	event_base_set(m_pEventBase, &data->m_Event);
	event_set(&data->m_Event, descriptor, EV_WRITE, WriteHandler, data);
	event_add(&data->m_Event, NULL);
	return data;
}

/// ���Ԃ��������Ƃ��ɌĂяo�����C�x���g�n���h�����w�肵�܂�
const EventDescriptor EventManager::SetTimerEventFunctor(const uint32_t timeoutMillisecond, EventFunctor &functor){
	EventData *data = _CreateNewEventData();
	if(data == NULL){
		return NULL;
	}
	data->m_Functor = functor;
	event_base_set(m_pEventBase, &data->m_Event);
	evtimer_set(&data->m_Event, TimerHandler, data);
	struct timeval tv;
	tv.tv_sec = timeoutMillisecond / 1000;
	tv.tv_usec = (timeoutMillisecond % 1000) * 1000;
	event_add(&data->m_Event, &tv);
	return data;
}

/// Set*EventFunctor�@�Őݒ肵���C�x���g�n���h������菜���܂��B
const bool EventManager::CanselEvent(EventDescriptor descriptor){
	return _DeleteEventData(reinterpret_cast<EventData *>(descriptor));
}

/// ���炩�̃C�x���g�����������Ƃ��ɌĂяo�����C�x���g�n���h���ł�
void EventManager::EventHandler(EventData *data){
	if(data != NULL){
		if(data->m_Functor != 0){
			data->m_Functor();
		}
		_DeleteEventData(data);
	}
}

}; // namespase LibSanuki


