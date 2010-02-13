/// SanukiLogger
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

#include "SanukiLogger.h"
#include "NetworkIO/RemoteService.h"
#include "SanukiDateTime.h"
#include <wchar.h>

namespace LibSanuki {

/**
 @brief �R���X�g���N�^
 */
SanukiLogger::SanukiLogger(){
	m_DisableLogType.clear();
	m_FileName2FILEMap.clear();
	m_FileSet.clear();
	m_RemoteServiceSet.clear();

	m_FileSet.insert(stderr);
}

SanukiLogger::~SanukiLogger(){
}

/// Logger �̃V���O���g�� object ���擾���܂��B
SanukiLogger &SanukiLogger::GetInstance(){
	// ���������C�̂Ȃ��V���O���g���̎���
	static SanukiLogger logger;
	return logger;
}

/// �w�肵�����O�^�C�v���o�͂��Ȃ��悤�ɂ��܂�
const bool SanukiLogger::Disable(const LogType type){
	m_DisableLogType.insert(type);
	return true;
}

/// �w�肵�����O�^�C�v���o�͂���悤�ɂ��܂�
const bool SanukiLogger::Enable(const LogType type){
	m_DisableLogType.erase(type);
	return true;
}

/// ���O���t�@�C���ցu���v�o�͂���悤�ɂ��܂��B
const bool SanukiLogger::AddLogOutput(char *filePath){
	if(filePath == NULL){
		return false;
	}
#ifdef _WIN32
	FILE *fp = NULL;
	if(fopen_s(&fp, filePath, "wb") != 0){
		return false;
	}
#else
	FILE *fp = fopen(filePath, "w");
#endif
	if(fp == NULL){
		return false;
	}
	m_FileName2FILEMap[filePath] = fp;
	return true;
}

/// �t�@�C���ւƏo�͂��Ă������O������߂܂�
const bool SanukiLogger::DelLogOutput(char *filePath){
	FileName2FILEMap::iterator i = m_FileName2FILEMap.find(filePath);
	if(i != m_FileName2FILEMap.end()){
		m_FileName2FILEMap.erase(i);
		return true;
	}
	return false;
}

/// ���O���w�肵���o�͐�ւ��o�͂���悤�ɂ��܂��B
const bool SanukiLogger::AddLogOutput(FILE *fp){
	if(fp == NULL){
		return false;
	}
	std::pair<FileSet::iterator, bool> result = m_FileSet.insert(fp);
	return result.second;
}

/// �w�肳�ꂽ�o�͐�ɏo�͂��Ă��郍�O������߂܂��B
const bool SanukiLogger::DelLogOutput(FILE *fp){
	FileSet::iterator i = m_FileSet.find(fp);
	if(i != m_FileSet.end()){
		m_FileSet.erase(i);
		return true;
	}
	return false;
}

/// �w�肳�ꂽ�T�[�r�X�ɑ΂��ă��O���o�͂���悤�ɐݒ肵�܂��B
const bool SanukiLogger::AddLogOutput(RemoteService remote){
	std::pair<RemoteServiceSet::iterator, bool> result = m_RemoteServiceSet.insert(remote);
	return result.second;
}

/// �w�肳�ꂽ�T�[�r�X�ɑ΂��ă��O���o�͂����悤�ɂ��Ă������̂�����߂܂��B
const bool SanukiLogger::DelLogOutput(RemoteService remote){
	RemoteServiceSet::iterator i = m_RemoteServiceSet.find(remote);
	if(i != m_RemoteServiceSet.end()){
		m_RemoteServiceSet.erase(remote);
		return true;
	}
	return false;
}

/// ��������t�H�[�}�b�g���܂��B
std::string SanukiLogger::Format(const char *fmt, ...){
	char buffer[4096];
	va_list ap;
	va_start(ap, fmt);
#ifdef _WIN32
	vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer), fmt, ap);
#else
	vsnprintf(buffer, sizeof(buffer), fmt, ap);
#endif
	va_end(ap);
	return std::string(buffer);
}

/// ��������t�H�[�}�b�g���܂��B
std::string SanukiLogger::Format(const wchar_t *fmt, ...){
	wchar_t wBuffer[2047];
	va_list ap;
	va_start(ap, fmt);
	vswprintf(wBuffer, sizeof(wBuffer), fmt, ap);
	va_end(ap);

	char cBuffer[4096];
#ifdef _WIN32
	size_t converted;
	wcstombs_s(&converted, cBuffer, sizeof(cBuffer), wBuffer, sizeof(cBuffer));
#else
	wcstombs(cBuffer, wBuffer, sizeof(cBuffer));
#endif
	return std::string(cBuffer);
}

/// �t�H�[�}�b�g���ꂽ��������󂯎��܂�
std::string SanukiLogger::Format(std::stringstream &ostream){
	return ostream.str();
}

/// ���O���o�͂��܂��B
void SanukiLogger::PutLog(const LogType type, std::string log, char *funcName, char *file, int line){
	char *LogTypeName = "UNKNOWN";
	switch(type){
		case LOG_ERROR:
			LogTypeName = "ERROR";
			break;
		case LOG_WARN:
			LogTypeName = "WARN";
			break;
		case LOG_DEBUG:
			LogTypeName = "DEBUG";
			break;
		case LOG_INFO:
			LogTypeName = "INFO";
			break;
		default:
			LogTypeName = "UNKNOWN";
			break;
	}
#ifdef _WIN32
	file = strrchr(funcName, '\\');
#else
	file = strrchr(funcName, '/');
#endif
	char buffer[4096+512];
#ifdef _WIN32
	sprintf_s(
#else
	snprintf(
#endif
		buffer, sizeof(buffer), "%s %s %s %s:%d %s"
					, SanukiDateTime::NowTime().FormatedString().c_str()
					, LogTypeName
					, funcName != NULL ? funcName : "UNKNOWN"
					, file
					, line
					, log.c_str());
	{
		FileName2FILEMap::iterator i = m_FileName2FILEMap.begin();
		for(; i != m_FileName2FILEMap.end(); i++){
			if(i->second != NULL){
				fputs(buffer, i->second);
			}
		}
	}
	{
		FileSet::iterator i = m_FileSet.begin();
		for(; i != m_FileSet.end(); i++){
			if(*i != NULL){
				fputs(buffer, *i);
			}
		}
	}
	{
		RemoteServiceSet::iterator i = m_RemoteServiceSet.begin();
		for(; i != m_RemoteServiceSet.end(); i++){
			i->SendCopy(SanukiDataBlock(buffer));
		}
	}
}

}; // namespase LibSanuki


