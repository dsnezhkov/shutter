#pragma once

#include <vector>
#include <windows.h>

namespace common::registry
{

enum class RegistryEventFlag
{
	SubkeyChange,
	ValueChange
};

struct RegistryMonitorArguments
{
	HKEY key;
	std::vector<RegistryEventFlag> events;
	bool monitorTree;
};

class RegistryMonitor
{
public:

	RegistryMonitor(RegistryMonitorArguments &&args);
	~RegistryMonitor();

	RegistryMonitor(const RegistryMonitor &rhs) = delete;
	RegistryMonitor &operator=(const RegistryMonitor &rhs) = delete;

	//
	// Due to the way the registry API works, you have to rearm the monitor
	// for each event you want to receive :-(
	//
	// This method returns a wait handle.
	// The handle should never be freed in calling code.
	//
	HANDLE queueSingleEvent();

private:

	RegistryMonitorArguments m_args;
	HANDLE m_event;

	bool m_hasRequestedNotification = false;
};

}
