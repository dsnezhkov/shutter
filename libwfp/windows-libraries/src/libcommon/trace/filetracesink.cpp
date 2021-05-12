#include "stdafx.h"
#include "filetracesink.h"
#include "libcommon/filesystem.h"
#include "libcommon/string.h"
#include "libcommon/error.h"
#include <filesystem>

namespace common::trace
{

FileTraceSink::FileTraceSink(const std::wstring &file)
{
	const auto path = std::filesystem::path(file).parent_path();

	common::fs::Mkdir(path);

	m_file = CreateFileW(file.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == m_file)
	{
		const auto error = GetLastError();
		const auto msg = std::string("Failed to create trace file: ").append(common::string::ToAnsi(file));

		THROW_WINDOWS_ERROR(error, msg.c_str());
	}
}

FileTraceSink::~FileTraceSink()
{
	CloseHandle(m_file);
}

void FileTraceSink::trace(const wchar_t *sender, const wchar_t *message)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	auto msg = std::wstring(sender).append(L": ").append(message).append(L"\xd\xa");
	auto encoded = common::string::ToAnsi(msg);

	DWORD bytesWritten;

	if (FALSE == WriteFile(m_file, encoded.c_str(), static_cast<DWORD>(encoded.size()), &bytesWritten, nullptr))
	{
		THROW_WINDOWS_ERROR(GetLastError(), "Failed to write trace event to disk");
	}
}

}
