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

#include "SanukiDateTime.h"

#include <stdio.h>
#include <time.h>

namespace LibSanuki {

/**
 @brief ÉRÉìÉXÉgÉâÉNÉ^
 */
SanukiDateTime::SanukiDateTime(){
	_SetNowTime();
}

SanukiDateTime::~SanukiDateTime(){
}

void SanukiDateTime::_SetNowTime(){
#ifdef _WIN32
#define EPOCHFILETIME (116444736000000000i64)
    FILETIME        tagFileTime;
    LARGE_INTEGER   largeInt;
    __int64         val64;

	GetSystemTimeAsFileTime(&tagFileTime);

	largeInt.LowPart  = tagFileTime.dwLowDateTime;
	largeInt.HighPart = tagFileTime.dwHighDateTime;
	val64 = largeInt.QuadPart;
	val64 = val64 - EPOCHFILETIME;
	val64 = val64 / 10;
	m_Tv.tv_sec  = (long)(val64 / 1000000);
	m_Tv.tv_usec = (long)(val64 % 1000000);
#else
	gettimeofday(&m_Tv, NULL);
#endif
}

/// åªç›ÇÃéûä‘ÇéÊìæÇµÇ‹Ç∑ÅB
SanukiDateTime SanukiDateTime::NowTime(){
	return SanukiDateTime();
}

/// ÉtÉHÅ[É}ÉbÉgÇ≥ÇÍÇΩï∂éöóÒÇéÊìæÇµÇ‹Ç∑
std::string SanukiDateTime::FormatedString(){
	struct tm result;
#ifdef _WIN32
	localtime_s(&result, reinterpret_cast<const time_t *>(&m_Tv.tv_sec));
#else
	localtime_r(&m_Tv.tv_sec, &result);
#endif
	char buffer[256];
#ifdef _WIN32
	_snprintf_s(buffer, sizeof(buffer), sizeof(buffer)
#else
	snprintf(buffer, sizeof(buffer)
#endif
		, "%04d/%02d/%02d %02d:%02d:%02d.%06ld"
		, result.tm_year + 1900
		, result.tm_mon + 1
		, result.tm_mday
		, result.tm_hour
		, result.tm_min
		, result.tm_sec
		, m_Tv.tv_usec);
	return std::string(buffer);
}

/// î‰ärââéZéq(==)
const bool SanukiDateTime::operator==(const SanukiDateTime &other) const{
	return m_Tv.tv_sec == other.m_Tv.tv_sec
		&& m_Tv.tv_usec == other.m_Tv.tv_usec;
}
/// î‰ärââéZéq(!=)
const bool SanukiDateTime::operator!=(const SanukiDateTime &other) const{
	return m_Tv.tv_sec != other.m_Tv.tv_sec
		|| m_Tv.tv_usec != other.m_Tv.tv_usec;
}
/// î‰ärââéZéq(<)
const bool SanukiDateTime::operator<(const SanukiDateTime &other) const{
	if(m_Tv.tv_sec < other.m_Tv.tv_sec){
		return true;
	}
	if(m_Tv.tv_sec > other.m_Tv.tv_sec){
		return false;
	}
	return m_Tv.tv_usec < other.m_Tv.tv_usec;
}
/// î‰ärââéZéq(>)
const bool SanukiDateTime::operator>(const SanukiDateTime &other) const{
	if(m_Tv.tv_sec > other.m_Tv.tv_sec){
		return true;
	}
	if(m_Tv.tv_sec < other.m_Tv.tv_sec){
		return false;
	}
	return m_Tv.tv_usec > other.m_Tv.tv_usec;
}
/// î‰ärââéZéq(<=)
const bool SanukiDateTime::operator<=(const SanukiDateTime &other) const{
	if(m_Tv.tv_sec < other.m_Tv.tv_sec){
		return true;
	}
	if(m_Tv.tv_sec > other.m_Tv.tv_sec){
		return false;
	}
	return m_Tv.tv_usec <= other.m_Tv.tv_usec;
}
/// î‰ärââéZéq(>=)
const bool SanukiDateTime::operator>=(const SanukiDateTime &other) const{
	if(m_Tv.tv_sec > other.m_Tv.tv_sec){
		return true;
	}
	if(m_Tv.tv_sec < other.m_Tv.tv_sec){
		return false;
	}
	return m_Tv.tv_usec >= other.m_Tv.tv_usec;
}

const SanukiDateTime &SanukiDateTime::operator+(const uint32_t millisecond){
	while((m_Tv.tv_usec + (millisecond % 1000) * 1000) > 1000000){
		m_Tv.tv_sec++;
		m_Tv.tv_usec -= 10000000;
	}
	m_Tv.tv_sec += millisecond / 1000;
	m_Tv.tv_usec += (millisecond % 1000) * 1000;

	return *this;
}


}; // namespase LibSanuki


