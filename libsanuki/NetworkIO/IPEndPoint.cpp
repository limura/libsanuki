/// IPEndPoint.cpp
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

#include "IPEndPoint.h"
#include "SocketDescriptor.h"

namespace LibSanuki {

/**
 @brief �R���X�g���N�^
 */
IPEndPoint::IPEndPoint(){
}

IPEndPoint::IPEndPoint(char *address){
	//�Ƃ肠����inet_atoi()�̂݁B
	inet_atoi(address); //�����ǂ��������H����
}

IPEndPoint::IPEndPoint(const IPEndPoint &other){
	memcpy(&m_Storage, &other.m_Storage, sizeof(m_Storage));
}

IPEndPoint::~IPEndPoint(){
}

const bool IPEndPoint::Initialize(char *address){
XXXX
}

/// DNS�ɂ�閼�O�������s���܂��B
static const bool IPEndPoint::Lookup(EventManager &eventManager, ::boost::function<void(IPEndPoint, bool)> &LookupResultReciver){
	// �Ƃ肠�����͎������܂���
	// XXX not implemented yet.
	return false;
}

/// �ڑ����J�n���܂�
const bool IPEndPoint::Connect(SocketDescriptor &descriptor){
	return connect(descriptor.GetSocket(), (struct sockaddr*)&m_Storage, sizeof(m_Storage)) == 0;
}

}; // namespase LibSanuki


