#pragma once

namespace common::trace
{

struct ITraceSink
{
	virtual ~ITraceSink() = 0
	{
	}

	virtual void trace(const wchar_t *sender, const wchar_t *message) = 0;
};

}
