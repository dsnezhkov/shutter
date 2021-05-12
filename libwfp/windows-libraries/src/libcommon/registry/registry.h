#pragma once

#include "registrykey.h"
#include "registrymonitor.h"
#include <memory>
#include <string>
#include <vector>
#include <windows.h>

namespace common::registry
{

enum class RegistryView
{
	Default,
	Force64,
	Force32
};

class Registry
{
public:

	Registry() = delete;

	static std::unique_ptr<RegistryKey> CreateKey
	(
		HKEY key,
		const std::wstring &subkey,
		RegistryView view = RegistryView::Default
	);

	static std::unique_ptr<RegistryKey> OpenKey
	(
		HKEY key,
		const std::wstring &subkey,
		bool writeAccess = false,
		RegistryView view = RegistryView::Default
	);

	static void DeleteKey
	(
		HKEY key,
		const std::wstring &subkey,
		RegistryView view = RegistryView::Default
	);

	//
	// Delete everything below the specified subkey, but not the subkey itself.
	//
	static void DeleteTree
	(
		HKEY key,
		const std::wstring &subkey,
		RegistryView view = RegistryView::Default
	);

	static std::unique_ptr<RegistryMonitor> MonitorKey
	(
		HKEY key,
		const std::wstring &subkey,
		const std::vector<RegistryEventFlag> &events,
		bool monitorTree = false,
		RegistryView view = RegistryView::Default
	);

	static void MoveKey
	(
		HKEY sourceKey,
		const std::wstring &sourceSubkey,
		HKEY destinationKey,
		const std::wstring &destinationSubkey,
		RegistryView view = RegistryView::Default
	);
};

}
