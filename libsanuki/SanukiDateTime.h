/// SanukiDateTime
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

#ifndef LIBSANUKI_SanukiDateTime_H
#define LIBSANUKI_SanukiDateTime_H

#include <inttypes.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <time.h>
#include <string>

namespace LibSanuki {

class SanukiDateTime {
private:
	/// 時間を保存しておきます
	struct timeval m_Tv;

	/// 現在時刻を設定します
	void _SetNowTime();
public:
	/// コンストラクタ
	SanukiDateTime();
	/// デストラクタ
	~SanukiDateTime();

	/// 現在の時間を取得します。
	static SanukiDateTime NowTime();

	/// フォーマットされた文字列を取得します
	std::string FormatedString();

	/// 比較演算子(==)
	const bool operator==(const SanukiDateTime &other) const;
	/// 比較演算子(!=)
	const bool operator!=(const SanukiDateTime &other) const;
	/// 比較演算子(<)
	const bool operator<(const SanukiDateTime &other) const;
	/// 比較演算子(>)
	const bool operator>(const SanukiDateTime &other) const;
	/// 比較演算子(<=)
	const bool operator<=(const SanukiDateTime &other) const;
	/// 比較演算子(>=)
	const bool operator>=(const SanukiDateTime &other) const;

	/// 加算演算子。ミリ秒単位で時間を加えます
	const SanukiDateTime &operator+(const uint32_t millisecond);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_SanukiDateTime_H
