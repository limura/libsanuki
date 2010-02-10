/*
 dummy inttypes.h

 Copyright(c) IIMURA Takuji 2010 All rights reserved.
 */

#ifndef LIBSANUKI_inttypes_H
#define LIBSANUKI_inttypes_H

#ifdef _WIN32
#include <windows.h>

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef INT16 int16_t;
typedef UINT16 uint16_t;
typedef INT32 int32_t;
typedef UINT32 uint32_t;
typedef INT64 int64_t;
typedef UINT64 uint64_t;

#endif // _WIN32

#endif // LIBSANUKI_inttypes_H
