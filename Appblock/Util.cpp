#include "Util.h"
#include <filesystem>
#include <sddl.h>

using namespace std;
using json = nlohmann::json;

string ProcessIdToName(DWORD processId)
{
    std::string ret;
    HANDLE handle = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        processId /* This is the PID, you can find one from windows task manager */
    );
    if (handle)
    {
        DWORD buffSize = 1024;
        CHAR buffer[1024];
        if (QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
        {
            ret = buffer;
        }
        else
        {
            printf("Error GetModuleBaseNameA : %lu", GetLastError());
        }
        CloseHandle(handle);
    }
    else
    {
        printf("Error OpenProcess : %lu", GetLastError());
    }
    return ret;
}
ostream& operator<<(ostream& os, REFGUID guid) {

    os.fill('0');
    os << std::uppercase;
    os.width(8);
    os << std::hex << guid.Data1 << '-';

    os.width(4);
    os << std::hex << guid.Data2 << '-';

    os.width(4);
    os << std::hex << guid.Data3 << '-';

    os.width(2);
    os << std::hex 
	<< static_cast<short>(guid.Data4[0]);

    os.width(2);
    os << static_cast<short>(guid.Data4[1]);
    os << '-';

    os.width(2);
    os << static_cast<short>(guid.Data4[2]);
    os.width(2);
    os << static_cast<short>(guid.Data4[3]);
    os.width(2);
    os << static_cast<short>(guid.Data4[4]);
    os.width(2);
    os << static_cast<short>(guid.Data4[5]);
    os.width(2);
    os << static_cast<short>(guid.Data4[6]);
    os.width(2);
	os << static_cast<short>(guid.Data4[7]);
    os << std::nouppercase;
    return os;
}
void DumpHex(void* data, size_t size) {
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i) {
        printf("%02X ", ((unsigned char*)data)[i]);
        if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
            ascii[i % 16] = ((unsigned char*)data)[i];
        }
        else {
            ascii[i % 16] = '.';
        }
        if ((i + 1) % 8 == 0 || i + 1 == size) {
            printf(" ");
            if ((i + 1) % 16 == 0) {
                printf("|  %s \n", ascii);
            }
            else if (i + 1 == size) {
                ascii[(i + 1) % 16] = '\0';
                if ((i + 1) % 16 <= 8) {
                    printf(" ");
                }
                for (j = (i + 1) % 16; j < 16; ++j) {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
}

void SaveJsonToFile(string filePath, json& J) {
    std::ofstream ofs(filePath, std::ofstream::out);
    ofs << J.dump(3) << std::endl;
}
json LoadJsonFromFile(std::string filePath) {
    std::ifstream file(filePath);
    json j = NULL; 
    if (file.good()) {
        j = json::parse(file,
            /* callback */ nullptr,
            /* allow exceptions */ true,
            /* skip_comments */ true);
    }
    return j;
}

int GUIDStringToGUIDWString(wstring& ws, const string& s)
{
    std::wstring wsTmp(s.begin(), s.end());

    ws = wsTmp;

    return 0;
}
char* IPNumber2IPAddress(unsigned int ip)
{
    static char ipo[24];

    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    int n = sprintf(ipo, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
    // printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);

    return ipo;
}
char* GUIDToString(REFGUID guid) {


    static char lguid[36];
    sprintf(lguid, "%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	if ( !IsEqualGUID(guid, GUID()) && !IsEqualGUID(guid, GUID_NULL)) {

    sprintf(lguid, "%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    }
    return lguid;
}
string wstr2stru8(wstring src) {
    return std::filesystem::path(src).generic_u8string();
}
wstring str2wstr(string src) {
   
    std::wstring dst(src.length(), L' '); // Make room for characters
    // Copy string to wstring.
    std::copy(src.begin(), src.end(), dst.begin());
    return dst;
}
vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

#pragma region TypeConversion
string UINT8ToString(UINT8 dataIn) {
    return  to_string(dataIn);
}
string UINT16ToString(UINT16 dataIn) {
    return  to_string(dataIn);
}
string UINT32ToString(UINT32 dataIn) {
    return  to_string(dataIn);
}
string UINT64ToString(UINT64* dataIn) {
    return  to_string(*dataIn);
}
string INT8ToString(INT8 dataIn) {
    return  to_string(dataIn);
}
string INT16ToString(INT16 dataIn) {
    return  to_string(dataIn);
}
string INT32ToString(INT32 dataIn) {
    return  to_string(dataIn);
}
string INT64ToString(INT64* dataIn) {
    return  to_string(*dataIn);
}
string FLOAT32ToString(FLOAT dataIn) {
    return  to_string(dataIn);
}
string DOUBLE64ToString(DOUBLE* dataIn) {
    return  to_string(*dataIn);
}
string SIDToString(SID* dataIn) {
    LPWSTR sSid = nullptr;
    string dataOut;
    if (ConvertSidToStringSid(dataIn, &sSid))
    {
        dataOut = wstr2stru8(sSid);
    }

    return dataOut;
}
#pragma endregion

