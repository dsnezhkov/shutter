#include "stdafx.h"
#include "registrymonitor.h"
#include <libcommon/error.h>

namespace common::registry
{

RegistryMonitor::RegistryMonitor(RegistryMonitorArguments &&args)
	: m_args(std::move(args))
{
	m_event = CreateEventW(nullptr, TRUE, FALSE, nullptr);

	if (nullptr == m_event)
	{
		THROW_ERROR("Could not create event for registry key monitoring");
	}
}

RegistryMonitor::~RegistryMonitor()
{
	RegCloseKey(m_args.key);
	CloseHandle(m_event);
}

HANDLE RegistryMonitor::queueSingleEvent()
{
	if (m_hasRequestedNotification)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(m_event, 0))
		{
			return m_event;
		}
	}

	DWORD filter = 0;

	for (const auto &flag : m_args.events)
	{
		switch (flag)
		{
			case RegistryEventFlag::SubkeyChange:
			{
				filter |= REG_NOTIFY_CHANGE_NAME;
				break;
			}
			case RegistryEventFlag::ValueChange:
			{
				filter |= REG_NOTIFY_CHANGE_LAST_SET;
				break;
			}
			default:
			{
				THROW_ERROR("Invalid event flag");
			}
		}
	}

	const auto status = RegNotifyChangeKeyValue(m_args.key, m_args.monitorTree, filter, m_event, TRUE);

	if (ERROR_SUCCESS != status)
	{
		THROW_WINDOWS_ERROR(status, "Activate registry monitoring");
	}

	m_hasRequestedNotification = true;

	return m_event;
}

}
