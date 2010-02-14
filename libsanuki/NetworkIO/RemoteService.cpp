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
/// コピーコンストラクタ
/// @note 送信queueや実際の接続についてはコピーされません。
RemoteService::RemoteService(const RemoteService &other)
: m_EventManager(other.m_EventManager)
, m_Uri(other.m_Uri)
, m_pConnection(NULL)
{
	m_SendQueue.clear();
}
#endif

/// コンストラクタ
RemoteService::RemoteService(EventManager &eventManager, const char *uri)
: m_EventManager(eventManager)
, m_Uri(uri)
, m_pConnection(NULL)
{
	m_SendQueue.clear();
}

/// コンストラクタ
RemoteService::RemoteService(EventManager &eventManager, const std::string &uri)
: m_EventManager(eventManager)
, m_Uri(uri)
, m_pConnection(NULL)
{
	m_SendQueue.clear();
}

/// デストラクタ
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

/// 送信を開始します。
void RemoteService::_InvokeSend(){
	// XXXXXXX not implemented yet.
	LOG_DEBUG((L"まだ実装されていません。"));
}

/// メッセージを送信します。渡されたメッセージはServicePointの管理となり、送信が終了すると開放されます。
const bool RemoteService::Send(SanukiDataBlock *message){
	if(message == NULL){
		return false;
	}
	m_SendQueue.push_back(message);
	_InvokeSend();
	return true;
}
/// メッセージを送信します。渡されたメッセージは開放されず、ServicePoint内部にはコピーが確保されます。
const bool RemoteService::SendCopy(const SanukiDataBlock &message){
	SanukiDataBlock *block = new SanukiDataBlock(message);
	if(block == NULL){
		return false;
	}
	m_SendQueue.push_back(block);
	_InvokeSend();
	return true;
}

/// 比較演算子(==)
const bool RemoteService::operator==(const RemoteService &other) const{
	return m_Uri == other.m_Uri;
}
/// 比較演算子(!=)
const bool RemoteService::operator!=(const RemoteService &other) const{
	return m_Uri != other.m_Uri;
}
/// 比較演算子(<)
const bool RemoteService::operator<(const RemoteService &other) const{
	return m_Uri < other.m_Uri;
}


}; // namespase LibSanuki


