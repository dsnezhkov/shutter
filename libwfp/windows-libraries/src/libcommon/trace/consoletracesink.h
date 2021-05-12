#pragma once

#include "itracesink.h"

namespace common::trace
{

struct ConsoleTraceSink : public ITraceSink
{
	void trace(const wchar_t *sender, const wchar_t *message) override;
};

}
