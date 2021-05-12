#pragma once

#include "itracesink.h"
#include <string>
#include <cstdint>

#ifdef _DEBUG
#define TRACING_ENABLED 1
#else
#define TRACING_ENABLED 0
#endif

namespace common::trace
{

class Trace
{
public:

	static void DoTrace(const wchar_t *sender, const wchar_t *message);

	static void RegisterSink(ITraceSink *sink);

	static bool HasSink();

private:

	static const uint32_t TAG_VALUE = 0xCAFEBABE;

	static ITraceSink *Sink();

	static std::wstring SinkKey();
};

}
