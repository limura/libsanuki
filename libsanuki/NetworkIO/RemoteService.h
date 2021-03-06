/**
 * RemoteService
 */
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

#ifndef LIBSANUKI_RemoteService_H
#define LIBSANUKI_RemoteService_H

#include "SanukiDataBlock.h"
#include "SendConnection.h"
#include "EventManager.h"
#include <string>

namespace LibSanuki {

class ServicePoint;

class RemoteService {
private:
	/// メッセージの送信時に利用するEventManager
	EventManager &m_EventManager;
	/// 指定されたURI
	const std::string m_Uri;
	/// 送信中のデータのリスト
	SanukiDataBlockList m_SendQueue;
	/// 利用中のコネクション
	SendConnection *m_pConnection;

	/// 送信を開始します。
	const bool _InvokeSend(SanukiDataBlockSharedPtr &message);

	/// 接続に失敗したときのイベントハンドラです
	void _ConnectError(SendConnection *);

public:
	/// コピーコンストラクタ
	//explicit RemoteService(const ServicePoint &other);
	/// コンストラクタ
	explicit RemoteService(EventManager &manager, const char *uri);
	/// コンストラクタ
	explicit RemoteService(EventManager &manager, const std::string &uri);
	/// デストラクタ
	~RemoteService();

	/// メッセージを送信します。渡されたメッセージはServicePoint側でもリファレンスし、送信が終わると開放します。
	const bool Send(SanukiDataBlockSharedPtr &message);
	/// メッセージを送信します。渡されたメッセージはServicePoint内部にはコピーが確保されます。
	const bool SendCopy(const SanukiDataBlock &message);

	/// 比較演算子(==)
	const bool operator==(const RemoteService &other) const;
	/// 比較演算子(!=)
	const bool operator!=(const RemoteService &other) const;
	/// 比較演算子(<)
	const bool operator<(const RemoteService &other) const;
};

}; // namespase LibSanuki

#endif // LIBSANUKI_RemoteService_H
