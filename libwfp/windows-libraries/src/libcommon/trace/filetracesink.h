#pragma once

#include "itracesink.h"
#include <string>
#include <mutex>
#include <windows.h>

namespace common::trace
{

class FileTraceSink : public ITraceSink
{
public:

	FileTraceSink(const std::wstring &file);
	~FileTraceSink();

	void trace(const wchar_t *sender, const wchar_t *message) override;

private:

	HANDLE m_file;
	std::mutex m_mutex;
};

}
