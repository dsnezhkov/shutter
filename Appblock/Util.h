#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <wtypes.h>
#include <string_view>
#include <clocale>
#include <cwchar>
#include <cassert>
#include <nlohmann/json.hpp>


std::string ProcessIdToName(DWORD processId);
std::ostream& operator<<(std::ostream& os, REFGUID guid);
int GUIDStringToGUIDWString(std::wstring& ws, const std::string& s);
void DumpHex(void* data, size_t size);
void SaveJsonToFile(std::string filePath, nlohmann::json& J);
nlohmann::json LoadJsonFromFile(std::string filePath);
char* IPNumber2IPAddress(unsigned int ip);
char* GUIDToString(REFGUID guid);
std::vector<std::string> split(const std::string& s, char delim);
std::string wstr2stru8(std::wstring src);
std::wstring str2wstr(std::string src);
std::string UINT8ToString(UINT8 dataIn);
std::string UINT16ToString(UINT16 dataIn);
std::string UINT32ToString(UINT32 dataIn);
std::string UINT64ToString(UINT64* dataIn);
std::string INT8ToString(INT8 dataIn);
std::string INT16ToString(INT16 dataIn);
std::string INT32ToString(INT32 dataIn);
std::string INT64ToString(INT64* dataIn);
std::string FLOAT32ToString(FLOAT dataIn);
std::string DOUBLE64ToString(DOUBLE* dataIn);
std::string SIDToString(SID* dataIn);
#endif
