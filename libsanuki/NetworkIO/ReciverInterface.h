// ReciverInterface
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

#ifndef LIBSANUKI_ReciverInterface_H　
#define LIBSANUKI_ReciverInterface_H

#include <inttypes.h>
#include <sys/types.h>

#include "SanukiDataBlock.h"

namespace LibSanuki {

// 外部からの入力に対するインタフェースのabstract classです。
class ReciverInterface {
public:
	// コンストラクタ
	virtual ReciverInterface();
	// デストラクタ
	virtual ~ReciverInterface();

	// 入力を処理します。入力されたデータをデータブロックのリストにして返却します。
	// @returns 処理にエラーがあった時のみ false を返します。
	// @note データブロックは読み込み終わったデータブロックのみが返却され、
	// 読み込み途中のものは ReciverInterface が保持します。
	//virtual const bool Input(const char *data, const size_t size, SanukiDataBlockVector &out_dataList);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_ReciverInterface_H
