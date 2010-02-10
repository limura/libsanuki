/*
 SendConnection

 ���M���邽�߂̃R�l�N�V���� abstract class

 Copyright(c) IIMURA Takuji 2010 All rights reserved.
 */

#ifndef LIBSANUKI_SendConnection_H
#define LIBSANUKI_SendConnection_H

#include "SanukiDataBlock.h"
#include <string>

namespase LibSanuki {

class SendConnection {
public:
	virtual ~SendConnection();
	virtual const bool Initialize(const std::string &uri) = 0;

	virtual const bool SendBlock(SanukiDataBlock *data) = 0; // �f�[�^�𑗐M���܂��B���M�����s�����ꍇ�ɂ� false ��Ԃ��܂��Bdata�͑��M���ꂽ�f�[�^�������k�݂܂��B���M�̏I���̓f�[�^�̃T�C�Y�Ŕ��f���Ă��������B
};

}; // namespase LibSanuki

#endif // LIBSANUKI_SendConnection_H
