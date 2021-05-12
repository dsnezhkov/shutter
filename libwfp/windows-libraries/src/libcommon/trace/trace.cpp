#include "stdafx.h"
#include "trace.h"
#include <sstream>
#include <wchar.h>
#include <windows.h>

namespace common::trace
{

typedef struct tag_SinkBucket
{
	uint32_t tag;
	ITraceSink *sink;
}
SinkBucket;

//static
void Trace::DoTrace(const wchar_t *sender, const wchar_t *message)
{
#if TRACING_ENABLED == 1

	auto activeSink = Sink();

	if (nullptr == activeSink)
	{
		return;
	}

	activeSink->trace(sender, message);

#else

	UNREFERENCED_PARAMETER(sender);
	UNREFERENCED_PARAMETER(message);

#endif
}

//static
void Trace::RegisterSink(ITraceSink *sink)
{
#if TRACING_ENABLED == 1

	auto bucket = new SinkBucket { TAG_VALUE, sink };

	SetEnvironmentVariableW
	(
		SinkKey().c_str(),
		std::to_wstring((unsigned long long)bucket).c_str()
	);

#else

	UNREFERENCED_PARAMETER(sink);

#endif
}

//static
bool Trace::HasSink()
{
#if TRACING_ENABLED == 1

	return nullptr != Sink();

#else

	return false;

#endif
}

//static
ITraceSink *Trace::Sink()
{
	//
	// Always read the instance from global storage.
	// This way, it becomes possible to redirect trace messages at any time.
	//

	wchar_t bucketLocation[128];

	if (0 == GetEnvironmentVariableW(SinkKey().c_str(), bucketLocation, _countof(bucketLocation)))
	{
		return nullptr;
	}

	auto bucket = (SinkBucket *)wcstoull(bucketLocation, nullptr, 10);

	try
	{
		if (bucket->tag != TAG_VALUE)
		{
			return nullptr;
		}
	}
	catch (...)
	{
		return nullptr;
	}

	return bucket->sink;
}

//static
std::wstring Trace::SinkKey()
{
	std::wstringstream ss;

	ss << L"LIBCOMMON_TRACE_SINK_" << GetCurrentProcessId();

	return ss.str();
}

}
