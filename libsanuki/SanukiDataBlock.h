// SanukiDataBlock.h
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

#ifndef LIBSANUKI_SanukiDataBlock_H
#define LIBSANUKI_SanukiDataBlock_H

#include <string>
#include <vector>
#include <list>
#include <inttypes.h>

#include <boost/shared_ptr.hpp>

namespace LibSanuki {

	/// ひとつのメッセージを表すデータブロックです。
	typedef std::string SanukiDataBlock;
	/// データブロックのshared_ptrです
	typedef boost::shared_ptr<SanukiDataBlock> SanukiDataBlockSharedPtr;
	/// データブロックの配列です。
	typedef std::vector<SanukiDataBlockSharedPtr> SanukiDataBlockVector;
	/// データブロックのリストです。
	typedef std::list<SanukiDataBlockSharedPtr> SanukiDataBlockList;

}; // namespase LibSanuki

#endif // LIBSANUKI_SanukiDataBlock_H
