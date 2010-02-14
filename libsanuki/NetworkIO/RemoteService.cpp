/// RemoteService
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

#include "RemoteService.h"
#include "EventManager.h"
#include "SanukiLogger.h"

namespace LibSanuki {

#if 0
/// �R�s�[�R���X�g���N�^
/// @note ���Mqueue����ۂ̐ڑ��ɂ��Ă̓R�s�[����܂���B
RemoteService::RemoteService(const RemoteService &other)
: m_EventManager(other.m_EventManager)
, m_Uri(other.m_Uri)
, m_pConnection(NULL)
{
	m_SendQueue.clear();
}
#endif

/// �R���X�g���N�^
RemoteService::RemoteService(EventManager &eventManager, const char *uri)
: m_EventManager(eventManager)
, m_Uri(uri)
, m_pConnection(NULL)
{
	m_SendQueue.clear();
}

/// �R���X�g���N�^
RemoteService::RemoteService(EventManager &eventManager, const std::string &uri)
: m_EventManager(eventManager)
, m_Uri(uri)
, m_pConnection(NULL)
{
	m_SendQueue.clear();
}

/// �f�X�g���N�^
RemoteService::~RemoteService(){
	if(m_pConnection != NULL){
		delete m_pConnection;
	}
	m_pConnection = NULL;

	SanukiDataBlockList::iterator i = m_SendQueue.begin();
	for(; i != m_SendQueue.end(); i++){
		if(*i != NULL){
			delete *i;
		}
	}
	m_SendQueue.clear();
}

/// ���M���J�n���܂��B
void RemoteService::_InvokeSend(){
	// XXXXXXX not implemented yet.
	LOG_DEBUG((L"�܂���������Ă��܂���B"));
}

/// ���b�Z�[�W�𑗐M���܂��B�n���ꂽ���b�Z�[�W��ServicePoint�̊Ǘ��ƂȂ�A���M���I������ƊJ������܂��B
const bool RemoteService::Send(SanukiDataBlock *message){
	if(message == NULL){
		return false;
	}
	m_SendQueue.push_back(message);
	_InvokeSend();
	return true;
}
/// ���b�Z�[�W�𑗐M���܂��B�n���ꂽ���b�Z�[�W�͊J�����ꂸ�AServicePoint�����ɂ̓R�s�[���m�ۂ���܂��B
const bool RemoteService::SendCopy(const SanukiDataBlock &message){
	SanukiDataBlock *block = new SanukiDataBlock(message);
	if(block == NULL){
		return false;
	}
	m_SendQueue.push_back(block);
	_InvokeSend();
	return true;
}

/// ��r���Z�q(==)
const bool RemoteService::operator==(const RemoteService &other) const{
	return m_Uri == other.m_Uri;
}
/// ��r���Z�q(!=)
const bool RemoteService::operator!=(const RemoteService &other) const{
	return m_Uri != other.m_Uri;
}
/// ��r���Z�q(<)
const bool RemoteService::operator<(const RemoteService &other) const{
	return m_Uri < other.m_Uri;
}


}; // namespase LibSanuki


