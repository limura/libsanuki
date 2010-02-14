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
	/// ここに設定されているLogタイプは出力されません。
	LogTypeSet m_DisableLogType;

	typedef std::map<std::string, FILE *> FileName2FILEMap;
	FileName2FILEMap m_FileName2FILEMap;
	typedef std::set<FILE *> FileSet;
	FileSet m_FileSet;
	typedef std::set<RemoteService> RemoteServiceSet;
	RemoteServiceSet m_RemoteServiceSet;

	/// シングルトンなのでコンストラクタは private です。
	SanukiLogger();
	/// シングルトンなのでコンストラクタは private です。
	SanukiLogger(SanukiLogger &);
public:
	/// デストラクタ
	~SanukiLogger();

	/// Logger のシングルトン object を取得します。
	static SanukiLogger &GetInstance();

	/// 指定したログタイプを出力しないようにします
	const bool Disable(const LogType type);

	/// 指定したログタイプを出力するようにします
	const bool Enable(const LogType type);

	/// ログをファイルへ「も」出力するようにします。
	const bool AddLogOutput(char *filePath);
	/// ログを指定した出力先へも出力するようにします。
	const bool AddLogOutput(FILE *fp);
	/// ファイルへと出力していたログを取りやめます
	const bool DelLogOutput(char *filePath);
	/// 指定された出力先に出力しているログを取りやめます。
	const bool DelLogOutput(FILE *fp);

	/// 指定されたサービスに対してログを出力するように設定します。
	const bool AddLogOutput(RemoteService remote);
	/// 指定されたサービスに対してログを出力されるようにしていたものを取りやめます。
	const bool DelLogOutput(RemoteService remote);

	/// 文字列をフォーマットします。
	std::string Format(const char *fmt, ...);
	/// 文字列をフォーマットします。
	std::string Format(const wchar_t *fmt, ...);
	// フォーマットされた文字列を受け取ります
	//std::string Format(std::ostream &ostream);

	/// ログを出力します。
	void PutLog(const LogType type, std::string log, char *funcName, char *file, int line);
};

/// LOG_DEBUG タイプでログを出力します。
#define LOG_DEBUG(a) ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_DEBUG, ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)
/// LOG_INFO  タイプでログを出力します。
#define LOG_INFO(a)  ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_INFO,  ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)
/// LOG_ERROR タイプでログを出力します。
#define LOG_ERROR(a) ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_ERROR, ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)
/// LOG_WARN  タイプでログを出力します。
#define LOG_WARN(a)  ::LibSanuki::SanukiLogger::GetInstance().PutLog(::LibSanuki::SanukiLogger::LOG_WARN,  ::LibSanuki::SanukiLogger::GetInstance().Format a, __FUNCTION__, __FILE__, __LINE__)

}; // namespase LibSanuki

#endif // LIBSANUKI_SanukiLogger_H
