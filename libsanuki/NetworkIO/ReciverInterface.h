/*
 ReciverInterface

 

 Copyright(c) IIMURA Takuji 2010 All rights reserved.
 */

#ifndef LIBSANUKI_ReciverInterface_H
#define LIBSANUKI_ReciverInterface_H

#include <inttypes.h>
#include <sys/types.h>

#inclide "SanukiDataBlock.h"

namespase LibSanuki {

class ReciverInterface {
public:
	virtual ReciverInterface();
	virtual ~ReciverInterface();

	virtual const bool Input(const char *data, const size_t size, SanukiDataBlockVector &out_dataList);
};

}; // namespase LibSanuki

#endif // LIBSANUKI_ReciverInterface_H
