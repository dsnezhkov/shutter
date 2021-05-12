#include "stdafx.h"
#include "consoletracesink.h"
#include <iostream>

namespace common::trace
{

void ConsoleTraceSink::trace(const wchar_t *sender, const wchar_t *message)
{
	//
	// There won't be much gain in locking since we don't control wcout anyway.
	//
	std::wcout << sender << L": " << message << std::endl;
}

}
