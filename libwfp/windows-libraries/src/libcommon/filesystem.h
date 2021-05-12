#pragma once

#include <string>
#include <windows.h>
#include <shlobj.h>

namespace common::fs
{

void Mkdir(const std::wstring &path);

std::wstring GetKnownFolderPath(REFKNOWNFOLDERID folderId, DWORD flags, HANDLE userToken);

class ScopedNativeFileSystem
{
public:

	ScopedNativeFileSystem();
	~ScopedNativeFileSystem();

	ScopedNativeFileSystem(const ScopedNativeFileSystem &) = delete;
	ScopedNativeFileSystem &operator=(const ScopedNativeFileSystem &) = delete;

private:

	PVOID m_context;
};

}
