/*
 SendConnection

 送信するためのコネクション abstract class

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

	virtual const bool SendBlock(SanukiDataBlock *data) = 0; // データを送信します。送信が失敗した場合には false を返します。dataは送信されたデータ分だけ縮みます。送信の終了はデータのサイズで判断してください。
};

}; // namespase LibSanuki

#endif // LIBSANUKI_SendConnection_H
