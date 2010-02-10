/*
 StreamReciver

 TCP �ł� Reciver

 Copyright(c) IIMURA Takuji 2010 All rights reserved.
 */

#ifndef LIBSANUKI_StreamReciver_H
#define LIBSANUKI_StreamReciver_H

#include "ReciverInterface.h

namespase LibSanuki {

class StreamReciver : public ReciverInterface {
private:
	std::string m_Buffer; // �ǂݍ��ݒ��̃o�b�t�@
	size_t m_LeftSize; // �c��̓ǂݍ��ݗ�
public:
	StreamReciver();
	~StreamReciver();

	const bool Input(const char *data, const size_t size, SanukiDataBlockVector &out_dataList);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_StreamReciver_H
