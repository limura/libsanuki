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

#ifndef LIBSANUKI_SanukiLogger_H
#define LIBSANUKI_SanukiLogger_H

#include <string>
#include <map>
#include <set>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace LibSanuki {

class RemoteService;

class SanukiLogger {
public:
	typedef enum {
		LOG_ERROR,
		LOG_INFO,
		LOG_DEBUG,
		LOG_WARN,
	} LogType;
private:
	typedef std::set<LogType> LogTypeSet;
	/// �����ɐݒ肳��Ă���Log�^�C�v�͏o�͂���܂���B
	LogTypeSet m_DisableLogType;

	typedef std::map<std::string, FILE *> FileName2FILEMap;
	FileName2FILEMap m_FileName2FILEMap;
	typedef std::set<FILE *> FileSet;
	FileSet m_FileSet;
	typedef std::set<RemoteService> RemoteServiceSet;
	RemoteServiceSet m_RemoteServiceSet;

	/// �V���O���g���Ȃ̂ŃR���X�g���N�^�� private �ł��B
	SanukiLogger();
	/// �V���O���g���Ȃ̂ŃR���X�g���N�^�� private �ł��B
	SanukiLogger(SanukiLogger &);
public:
	/// �f�X�g���N�^
	~SanukiLogger();

	/// Logger �̃V���O���g�� object ���擾���܂��B
	static SanukiLogger &GetInstance();

	/// �w�肵�����O�^�C�v���o�͂��Ȃ��悤�ɂ��܂�
	const bool Disable(const LogType type);

	/// �w�肵�����O�^�C�v���o�͂���悤�ɂ��܂�
	const bool Enable(const LogType type);

	/// ���O���t�@�C���ցu���v�o�͂���悤�ɂ��܂��B
	const bool AddLogOutput(char *filePath);
	/// ���O���w�肵���o�͐�ւ��o�͂���悤�ɂ��܂��B
	const bool AddLogOutput(FILE *fp);
	/// �t�@�C���ւƏo�͂��Ă������O������߂܂�
	const bool DelLogOutput(char *filePath);
	/// �w�肳�ꂽ�o�͐�ɏo�͂��Ă��郍�O������߂܂��B
	const bool DelLogOutput(FILE *fp);

	/// �w�肳�ꂽ�T�[�r�X�ɑ΂��ă��O���o�͂���悤�ɐݒ肵�܂��B
	const bool AddLogOutput(RemoteService remote);
	/// �w�肳�ꂽ�T�[�r�X�ɑ΂��ă��O���o�͂����悤�ɂ��Ă������̂�����߂܂��B
	const bool DelLogOutput(RemoteService remote);

	/// ��������t�H�[�}�b�g���܂��B
	std::string Format(const char *fmt, ...);
	/// ��������t�H�[�}�b�g���܂��B
	std::string Format(const wchar_t *fmt, ...);
	// �t�H�[�}�b�g���ꂽ��������󂯎��܂�
	//std::string Format(std::ostream &ostream);

	/// ���O���o�͂��܂��B
	void PutLog(const LogType type, std::string log, char *funcName, char *file, int line);
};

/// LOG_DEBUG �^�C�v�Ń��O���o�͂��܂��B
#define LOG_DEBUG(a) ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_DEBUG, ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)
/// LOG_INFO  �^�C�v�Ń��O���o�͂��܂��B
#define LOG_INFO(a)  ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_INFO,  ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)
/// LOG_ERROR �^�C�v�Ń��O���o�͂��܂��B
#define LOG_ERROR(a) ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_ERROR, ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)
/// LOG_WARN  �^�C�v�Ń��O���o�͂��܂��B
#define LOG_WARN(a)  ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_WARN,  ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)

}; // namespase LibSanuki

#endif // LIBSANUKI_SanukiLogger_H
