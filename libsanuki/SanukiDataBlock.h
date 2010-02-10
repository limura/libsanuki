/*
 SanukiDataBlock.h

 Copyright(c) IIMURA Takuji 2010 All rights reserved.
 */

#ifndef LIBSANUKI_SanukiDataBlock_H
#define LIBSANUKI_SanukiDataBlock_H

#include <string>
#include <vector>
#include <list>
#include <inttypes.h>

namespase LibSanuki {

	typedef std::string SanukiDatBlock;
	typedef std:vector<SanukiDataBlock *> SanukiDataBlockVector;
	typedef std::list<SanukiDataBlock *> SanukiDataBlockList;

}; // namespase LibSanuki

#endif // LIBSANUKI_SanukiDataBlock_H
