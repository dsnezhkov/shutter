#include "stdafx.h"
#include "nci.h"
#include <libcommon/error.h>
#include <libcommon/filesystem.h>
#include <filesystem>

namespace common::network
{

Nci::Nci()
{
	const auto systemDir = common::fs::GetKnownFolderPath(
		FOLDERID_System,
		KF_FLAG_DEFAULT,
		nullptr
	);
	const auto nciPath = std::filesystem::path(systemDir).append(L"nci.dll");

	m_dllHandle = LoadLibraryW(nciPath.c_str());

	if (nullptr == m_dllHandle)
	{
		THROW_WINDOWS_ERROR(GetLastError(), "Load nci.dll");
	}

	m_nciGetConnectionName = reinterpret_cast<nciGetConnectionNameFunc>(
		GetProcAddress(m_dllHandle, "NciGetConnectionName"));

	if (nullptr == m_nciGetConnectionName)
	{
		FreeLibrary(m_dllHandle);
		THROW_ERROR("Failed to obtain pointer to NciGetConnectionName");
	}

	m_nciSetConnectionName = reinterpret_cast<nciSetConnectionNameFunc>(
		GetProcAddress(m_dllHandle, "NciSetConnectionName"));

	if (nullptr == m_nciSetConnectionName)
	{
		FreeLibrary(m_dllHandle);
		THROW_ERROR("Failed to obtain pointer to NciSetConnectionName");
	}
}

Nci::~Nci()
{
	FreeLibrary(m_dllHandle);
}

std::wstring Nci::getConnectionName(const GUID& guid) const
{
	DWORD nameLen = 0; // including L'\0'

	if (0 != m_nciGetConnectionName(&guid, nullptr, 0, &nameLen))
	{
		THROW_ERROR("NciGetConnectionName() failed");
	}

	std::vector<wchar_t> buffer;
	buffer.resize(nameLen / sizeof(wchar_t));

	if (0 != m_nciGetConnectionName(&guid, &buffer[0], nameLen, nullptr))
	{
		THROW_ERROR("NciGetConnectionName() failed");
	}

	return buffer.data();
}

void Nci::setConnectionName(const GUID& guid, const wchar_t* newName) const
{
	if (0 != m_nciSetConnectionName(&guid, newName))
	{
		THROW_ERROR("NciSetConnectionName() failed");
	}
}

}
