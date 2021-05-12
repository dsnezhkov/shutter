#pragma once

#include <windows.h>
#include <string>

//
// Interface for nci.dll.
//

namespace common::network
{

class Nci
{
	HMODULE m_dllHandle;

	using nciGetConnectionNameFunc = DWORD(__stdcall*)(const GUID*, wchar_t*, DWORD, DWORD*);
	using nciSetConnectionNameFunc = DWORD(__stdcall*)(const GUID*, const wchar_t*);

	nciGetConnectionNameFunc m_nciGetConnectionName;
	nciSetConnectionNameFunc m_nciSetConnectionName;

public:

	Nci();
	~Nci();

	Nci(Nci&&) = delete;
	Nci& operator=(Nci&&) = delete;

	std::wstring getConnectionName(const GUID& guid) const;
	void setConnectionName(const GUID& guid, const wchar_t* newName) const;
};

}
