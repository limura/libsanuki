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
#include <string>

namespace LibSanuki {

class RemoteService {
private:
	/// �w�肳�ꂽURI
	const std::string m_Uri;
	/// ���M���̃f�[�^�̃��X�g
	SanukiDataBlockList m_SendQueue;
	/// ���p���̃R�l�N�V����
	SendConnection *m_pConnection;

public:
	RemoteService();
	explicit RemoteService(const ServicePoint &other);
	explicit RemoteService(const char *uri);
	explicit RemoteService(const std::string &uri);
	~RemoteService();

	/// ���b�Z�[�W�𑗐M���܂��B�n���ꂽ���b�Z�[�W��ServicePoint�̊Ǘ��ƂȂ�A���M���I������ƊJ������܂��B
	const bool Send(SanukiDataBlock *message);
	/// ���b�Z�[�W�𑗐M���܂��B�n���ꂽ���b�Z�[�W�͊J�����ꂸ�AServicePoint�����ɂ̓R�s�[���m�ۂ���܂��B
	const bool SendCopy(const SanukiDataBlock &message);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_RemoteService_H
