/**
 * SendConnection
 * ���M���邽�߂̃R�l�N�V���� abstract class
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

#ifndef LIBSANUKI_SendConnection_H
#define LIBSANUKI_SendConnection_H

#include "SanukiDataBlock.h"
#include <string>

namespace LibSanuki {

class SendConnection {
public:
	virtual ~SendConnection();
	virtual const bool Initialize(const std::string &uri) = 0;

	virtual const bool SendBlock(SanukiDataBlock *data) = 0; // �f�[�^�𑗐M���܂��B���M�����s�����ꍇ�ɂ� false ��Ԃ��܂��Bdata�͑��M���ꂽ�f�[�^�������k�݂܂��B���M�̏I���̓f�[�^�̃T�C�Y�Ŕ��f���Ă��������B
};

}; // namespase LibSanuki

#endif // LIBSANUKI_SendConnection_H
