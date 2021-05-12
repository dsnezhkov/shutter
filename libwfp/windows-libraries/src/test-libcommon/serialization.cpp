#include "pch.h"
#include "libcommon/string.h"
#include "libcommon/serialization/serializer.h"
#include "libcommon/serialization/deserializer.h"
#include "CppUnitTest.h"
#include <string>
#include <cstdint>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{

template<>
std::wstring ToString<uint16_t>(const uint16_t &i)
{
	return std::to_wstring(i);
}

template<>
std::wstring ToString<GUID>(const GUID &guid)
{
	return common::string::FormatGuid(guid);
}

}

namespace testlibcommon
{

TEST_CLASS(TestLibCommonSerialization)
{
public:

	TEST_METHOD(SerializeAndDeserialize)
	{
		//
		// Compose
		//

		::common::serialization::Serializer s;

		s << (uint8_t)8;
		s << (uint16_t)16;
		s << (uint32_t)32;

		GUID guid =
		{
			1,
			2,
			3,
			{ 4, 5, 6, 7, 8, 9, 'A', 'B' }
		};

		s << guid;

		std::wstring str(L"meh");

		s << str.c_str();
		s << str;

		std::vector<std::wstring> sa;

		sa.push_back(L"foo");
		sa.push_back(L"bar");

		s << sa;

		//
		// Decompose
		//

		auto blob = s.blob();

		::common::serialization::Deserializer d(&blob[0], blob.size());

		Assert::AreEqual((uint8_t)8, d.decode<uint8_t>());
		Assert::AreEqual((uint16_t)16, d.decode<uint16_t>());
		Assert::AreEqual((uint32_t)32, d.decode<uint32_t>());
		Assert::AreEqual(guid, d.decode<GUID>());
		Assert::AreEqual(str, d.decode<std::wstring>());
		Assert::AreEqual(str, d.decode<std::wstring>());

		std::vector<std::wstring> readSa;
		d >> readSa;

		for (size_t i = 0; i < sa.size(); ++i)
		{
			Assert::AreEqual(sa[i], readSa[i], L"string arrays differ");
		}
	}

	TEST_METHOD(DeserializeWrongTypeFails)
	{
		::common::serialization::Serializer s;

		s << (uint8_t)8;

		auto blob = s.blob();

		::common::serialization::Deserializer d(&blob[0], blob.size());

		Assert::ExpectException<std::runtime_error>([&d]() { d.decode<uint16_t>(); });
	}

	TEST_METHOD(DeserializingExcessivelyFails)
	{
		::common::serialization::Serializer s;

		s << (uint8_t)8;

		auto blob = s.blob();

		::common::serialization::Deserializer d(&blob[0], blob.size());

		d.decode<uint8_t>();

		Assert::ExpectException<std::runtime_error>([&d]() { d.decode<uint8_t>(); });
	}

	TEST_METHOD(CanHandleEmptyString)
	{
		::common::serialization::Serializer s;

		s << L"first";
		s << L"";
		s << L"third";

		auto blob = s.blob();

		::common::serialization::Deserializer d(&blob[0], blob.size());

		Assert::AreEqual(L"first", d.decode<std::wstring>().c_str());
		Assert::AreEqual(L"", d.decode<std::wstring>().c_str());
		Assert::AreEqual(L"third", d.decode<std::wstring>().c_str());
	}

	TEST_METHOD(CanHandleEmptyStringInArray)
	{
		::common::serialization::Serializer s;

		std::vector<std::wstring> sa;

		sa.push_back(L"first");
		sa.push_back(L"");
		sa.push_back(L"third");

		s << sa;

		auto blob = s.blob();

		::common::serialization::Deserializer d(&blob[0], blob.size());

		std::vector<std::wstring> readSa;
		d >> readSa;

		for (size_t i = 0; i < sa.size(); ++i)
		{
			Assert::AreEqual(sa[i], readSa[i], L"string arrays differ");
		}
	}

};

}
