/**
 * ServicePoint
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

#ifndef LIBSANUKI_ServicePoint_H
#define LIBSANUKI_ServicePoint_H

#include "SanukiDataBlock.h"
#include "SendConnection.h"
#include <string>

namespace LibSanuki {

class ServicePoint {
private:
	SanukiDataBlockList m_SendQueue;
	SendConnection *m_pConnection;

public:
	ServicePoint();
	explicit ServicePoint(const ServicePoint &other);
	explicit ServicePoint(const char *uri);
	explicit ServicePoint(const std::string &uri);
	~ServicePoint();

	const bool Send(SanukiDataBlock *message); // メッセージを送信します。渡されたメッセージは送信が終了すると開放されます。
	const bool SendCopy(const SanukiDataBlock &message); // メッセージを送信します。渡されたメッセージは開放されず、内部にコピーが確保されます。
};

}; // namespase LibSanuki

#endif // LIBSANUKI_ServicePoint_H
