#include "WFPSessionManager.h"
#include <sddl.h>


using namespace WFPManager;
using json = nlohmann::json;


#pragma region WFPInitAndUtil
void WFPSessionManager::Engine() {
    // Our session will last for the maximum duration
    // engine = wfp::FilterEngine::DynamicSession(UINT32_MAX);
    engine = wfp::FilterEngine::DynamicSession();
}
nlohmann::json WFPSessionManager::GetJsonCollection() {
    return this->J;
}
#pragma endregion

#pragma region Sessions
void WFPSessionManager::ListSession(std::string sessionIn) {
    GUID sessionInGUID = GUID_NULL;

    if (!sessionIn.empty()) {
        std::cout << "Session is specified" << std::endl;
        std::wstring sessionGUIDwstring;

        GUIDStringToGUIDWString(sessionGUIDwstring, sessionIn);
        try {
            sessionInGUID = common::Guid::FromString(sessionGUIDwstring);
        }
        catch (std::exception e) {
            std::cout << "Unable to parse GUID: " << e.what() << std::endl;
            return;
        }
    }

    // session collector
    json jSessions = json::array();

    bool ok = wfp::ObjectEnumerator::Sessions(*this->engine, [&sessionInGUID, &jSessions, this](const FWPM_SESSION0& session)
	{
		json jSession;

        if (sessionInGUID == GUID_NULL) {
            ProcessSession(session, jSession);
			jSessions.push_back(jSession);
        }
        else {
            if (IsEqualGUID(session.sessionKey, sessionInGUID)) {
                ProcessSession(session, jSession);
                jSessions.push_back(jSession);
            }
        }

		return true;
	});
	// std::cout << jSessions.dump(3) << std::endl;
    this->J["Sessions"] = jSessions;
}
void WFPSessionManager::ProcessSession(const FWPM_SESSION0& session, nlohmann::json& jSession) {

    jSession["SessionPID"] = "0";
    jSession["SessionProcessName"] = "None";

    jSession["SessionUsername"] = wstr2stru8(session.username);
    jSession["SessionKey"] = GUIDToString(session.sessionKey);
    jSession["SessionSID"] = SIDToString(session.sid);
    jSession["SessionKernelMode"] = (session.kernelMode == 0 ? "0" : "1");

    if (!session.kernelMode) {
        jSession["SessionPID"] = session.processId;
        jSession["SessionProcessName"] = ProcessIdToName(session.processId);
    }
    jSession["SessionWaitTime"] = (session.txnWaitTimeoutInMSec / 60 / 60);
}
#pragma endregion

#pragma region Filters
void WFPSessionManager::ListFilter(std::string filterIn) {
    GUID filterInGUID = GUID_NULL;

    if (!filterIn.empty()) {
        std::wstring filterGUIDwstring;

        GUIDStringToGUIDWString(filterGUIDwstring, filterIn);
        try {
			filterInGUID = common::Guid::FromString(filterGUIDwstring);
        }
        catch (std::exception e) {
            std::cout << "Unable to parse GUID: " << e.what() << std::endl;
            return;
        }
    }

    // filter collector
    json jFilters = json::array();
    bool ok = wfp::ObjectEnumerator::Filters(*engine, [&filterInGUID, &jFilters, this](const FWPM_FILTER0& filter)
	{
		json jFilter;

		if (filterInGUID == GUID_NULL) {
			// std::cout << "GUID Null, Processing all: " << filterInGUID << std::endl;
			ProcessFilter(filter, jFilter);
			jFilters.push_back(jFilter);
		}
		else {
			if (IsEqualGUID(filter.filterKey, filterInGUID)) {
				// std::cout << "Equal to: " << filter.filterKey << " Processing GUID: " << filterInGUID << std::endl;
				ProcessFilter(filter, jFilter);
		        jFilters.push_back(jFilter);
			}
		}
		return true;
	});

    this->J["Filters"] = jFilters;

}
void WFPSessionManager::ProcessFilter(const FWPM_FILTER0& filter, nlohmann::json& J) {

	// Structured filter record
	std::unique_ptr<FilterRecord> filterRecord(new FilterRecord);

    try {

        // Filter Key
        filterRecord->FilterKey = filter.filterKey;
        J["FilterKey"] = GUIDToString(filter.filterKey);
        // Filter Id
        filterRecord->FilterID = filter.filterId;
        J["FilterID"] = std::to_string(filter.filterId);
        // Filter Name
        filterRecord->FilterName = filter.displayData.name;
		J["FilterName"] = wstr2stru8(filterRecord->FilterName);
        // Filter Description
        if (filter.displayData.description != NULL) {
            filterRecord->FilterDesc = filter.displayData.description;
            J["FilterDesc"] = wstr2stru8(filterRecord->FilterDesc);
        }
        else {
            filterRecord->FilterDesc = L"None";
            J["FilterDesc"] = "None";
        }

        // Filter Action
        switch (filter.action.type) {
        case  FWP_ACTION_BLOCK: filterRecord->ActionType = "FWP_ACTION_BLOCK"; break;
        case  FWP_ACTION_PERMIT: filterRecord->ActionType = "FWP_ACTION_PERMIT"; break;
        case  FWP_ACTION_CALLOUT_TERMINATING: filterRecord->ActionType = "FWP_ACTION_CALLOUT_TERMINATING"; break;
        case  FWP_ACTION_CALLOUT_INSPECTION: filterRecord->ActionType = "FWP_ACTION_CALLOUT_INSPECTION"; break;
        case  FWP_ACTION_CALLOUT_UNKNOWN: filterRecord->ActionType = "FWP_ACTION_CALLOUT_UNKNOWN"; break;
        case  FWP_ACTION_CONTINUE: filterRecord->ActionType = "FWP_ACTION_CONTINUE"; break;
        case  FWP_ACTION_NONE: filterRecord->ActionType = "FWP_ACTION_NONE"; break;
        case  FWP_ACTION_NONE_NO_MATCH: filterRecord->ActionType = "FWP_ACTION_NONE_NO_MATCH"; break;
        case  FWP_ACTION_BITMAP_INDEX_SET: filterRecord->ActionType = "FWP_ACTION_BITMAP_INDEX_SET"; break;
        default: filterRecord->ActionType = "NOT IMPLEMENTED";
        }
        J["FilterAction"] = filterRecord->ActionType;


        // Filter Layer
        filterRecord->FilterRecordLayerIn.LayerKey = filter.layerKey;
        J["FilterLayer"]["LayerKey"] = GUIDToString(filterRecord->FilterRecordLayerIn.LayerKey);

        // Filter Layer explanation help
        // fwpm_layer_desc_t* layer_desc = new (fwpm_layer_desc_t);
        //bool ok = print_fwpm_layer_desc_guidance(filterRecord->FilterRecordLayerIn.LayerKey, layer_desc);

        std::unique_ptr<fwpm_layer_desc_t> layer_desc(new fwpm_layer_desc_t);
        bool ok = getLayerGuidance(filterRecord->FilterRecordLayerIn.LayerKey, layer_desc);

        if (ok && !IsEqualGUID(layer_desc->guid, GUID_NULL)) {
            filterRecord->FilterRecordLayerIn.LayerMsg = std::string(layer_desc->msg);
            J["FilterLayer"]["LayerMsg"] = filterRecord->FilterRecordLayerIn.LayerMsg;
        }

        // Filter Provider
        filterRecord->FilterRecordProviderIn.ProviderKey = filter.providerKey;
        // Some EDRs send us on a wild good chase, don't do it :) 
        if (0x0000000000000000 != filterRecord->FilterRecordProviderIn.ProviderKey && !IsEqualGUID(*filterRecord->FilterRecordProviderIn.ProviderKey, GUID()) && !IsEqualGUID(filterRecord->FilterRecordProviderIn.ProviderContextKey, GUID_NULL)) {
		    J["FilterProvider"]["ProviderKey"] = GUIDToString(*filterRecord->FilterRecordProviderIn.ProviderKey);
        }
        else {
            J["FilterProvider"]["ProviderKey"] = "None";
        }

        if (!IsEqualGUID(filterRecord->FilterRecordProviderIn.ProviderContextKey, GUID())
            && !IsEqualGUID(filterRecord->FilterRecordProviderIn.ProviderContextKey, GUID_NULL)) {
            filterRecord->FilterRecordProviderIn.ProviderContextKey = filter.providerContextKey;
            J["FilterProvider"]["ProviderContextKey"] = GUIDToString(filterRecord->FilterRecordProviderIn.ProviderContextKey);
        }
        else {
            J["FilterProvider"]["ProviderContextKey"] = "None";
        }

        // Filter Provider Details as it applies to Filter
        ok = wfp::ObjectExplorer::GetProvider(*engine, *filterRecord->FilterRecordProviderIn.ProviderKey, [&filterRecord](const FWPM_PROVIDER0& provider)
            {
                if (!IsEqualGUID(provider.providerKey, GUID()) && !IsEqualGUID(provider.providerKey, GUID_NULL) ) {

                    //std::wcout << L"Provider Name: " << provider.displayData.name << std::endl;
                    filterRecord->FilterRecordProviderIn.ProviderName = provider.displayData.name;
                    if (provider.serviceName != nullptr) {
                        //std::wcout << L"Provider Service: " << provider.serviceName << std::endl;
                        filterRecord->FilterRecordProviderIn.ProviderService = provider.serviceName;
                    }
                }
                return true;
            });
		J["FilterProvider"]["ProviderName"] = wstr2stru8(filterRecord->FilterRecordProviderIn.ProviderName);
		J["FilterProvider"]["ProviderServiceName"] = wstr2stru8(filterRecord->FilterRecordProviderIn.ProviderService);


        

        //std::cout << "Filter Conditions:" << std::endl;

        for (int ix = 0; ix < (int)filter.numFilterConditions; ix++)
        {
            std::unique_ptr<FilterCondition> filterConditionIn(new FilterCondition);

            filterConditionIn->FieldKey = filter.filterCondition[ix].fieldKey;
            J["FilterConditions"][ix]["ConditionKey"] = GUIDToString(filterConditionIn->FieldKey);

            // Filter Condition explanation help 
            fwpm_condition_desc_t* condition_desc = new (fwpm_condition_desc_t);
            bool ok = print_fwpm_condition_desc_guidance(filter.filterCondition[ix].fieldKey, condition_desc);
            if (ok && !IsEqualGUID(condition_desc->guid, GUID_NULL)) {
                filterConditionIn->ConditonName = std::string(condition_desc->msg);
                J["FilterConditions"][ix]["ConditionName"] = filterConditionIn->ConditonName;
                filterConditionIn->ConditionDesc = std::string(condition_desc->desc);
                J["FilterConditions"][ix]["ConditionDesc"] = filterConditionIn->ConditionDesc;
            }

            switch (filter.filterCondition[ix].matchType)
            {
            case FWP_MATCH_EQUAL: filterConditionIn->MatchType = "EQUAL"; break;
            case FWP_MATCH_GREATER: filterConditionIn->MatchType = "GREATER"; break;
            case FWP_MATCH_LESS: filterConditionIn->MatchType = "LESS"; break;
            case FWP_MATCH_GREATER_OR_EQUAL: filterConditionIn->MatchType = "GREATER_OR_EQUAL"; break;
            case FWP_MATCH_LESS_OR_EQUAL: filterConditionIn->MatchType = "LESS_OR_EQUAL"; break;
            case FWP_MATCH_RANGE: filterConditionIn->MatchType = "RANGE"; break;
            case FWP_MATCH_FLAGS_ALL_SET: filterConditionIn->MatchType = "FLAGS_ALL_SET"; break;
            case FWP_MATCH_FLAGS_ANY_SET: filterConditionIn->MatchType = "FLAGS_ANY_SET"; break;
            case FWP_MATCH_FLAGS_NONE_SET: filterConditionIn->MatchType = "FLAGS_NONE_SET"; break;
            case FWP_MATCH_EQUAL_CASE_INSENSITIVE: filterConditionIn->MatchType = "EQUAL_CASE_INSENSEITIVE"; break;
            case FWP_MATCH_NOT_EQUAL: filterConditionIn->MatchType = "NOT_EQUAL"; break;
            case FWP_MATCH_PREFIX: filterConditionIn->MatchType = "MATCH_PREFIX"; break;
            case FWP_MATCH_NOT_PREFIX: filterConditionIn->MatchType = "MATCH_NOT_PREFIX"; break;
            case FWP_MATCH_TYPE_MAX: filterConditionIn->MatchType = "MATCH_TYPE_MAX"; break;
            default: filterConditionIn->MatchType = "UNKNOWN"; break;
            }

            J["FilterConditions"][ix]["ConditionMatchType"] = filterConditionIn->MatchType;
            J["FilterConditions"][ix]["ConditionDataType"] = filterConditionIn->DataType;

            FWP_CONDITION_VALUE0 value = (filter.filterCondition[ix]).conditionValue;
            switch (value.type)
            {
            case FWP_EMPTY:
                filterConditionIn->DataType = "FWP_EMPTY";
                filterConditionIn->DataValue = "";
                break;
            case FWP_UINT8:
            {
                //printf("%u", value.uint8);
                filterConditionIn->DataType = "FWP_UINT8";
                filterConditionIn->DataValue = UINT8ToString(value.uint8);

            }
            break;
            case FWP_UINT16:
            {
                // printf("V: %u", value.uint16);
                filterConditionIn->DataType = "FWP_UINT16";
                filterConditionIn->DataValue = UINT16ToString(value.uint16);
            }
            break;
            case FWP_UINT32:
            {
                // printf("V: %lu", value.uint32);
                filterConditionIn->DataType = "FWP_UINT32";
                filterConditionIn->DataValue = UINT32ToString(value.uint32);
            }
            break;
            case FWP_UINT64:
            {
                // printf("V: ll%u", value.uint64);
                filterConditionIn->DataType = "FWP_UINT64";
                filterConditionIn->DataValue = UINT64ToString(value.uint64);
            }
            break;
            case FWP_INT8:
            {
                // printf("V: %d", value.int8);
                filterConditionIn->DataType = "FWP_INT8";
                filterConditionIn->DataValue = INT8ToString(value.int8);
            }
            break;
            case FWP_INT16:
            {
                // std::cout << std::hex << value.int16;
                filterConditionIn->DataType = "FWP_INT16";
                filterConditionIn->DataValue = INT16ToString(value.int16);
            }
                break;
            case FWP_INT32:
            {
                // std::cout << std::hex << value.int32;
                filterConditionIn->DataType = "FWP_INT32";
                filterConditionIn->DataValue = INT32ToString(value.int32);
            }
                break;
            case FWP_INT64:
            {
                // std::cout << std::hex << value.int64;
                filterConditionIn->DataType = "FWP_INT64";
                filterConditionIn->DataValue = INT64ToString(value.int64);
            }
                break;
            case FWP_FLOAT:
            {
                // std::cout << value.float32;
                filterConditionIn->DataType = "FWP_FLOAT";
                filterConditionIn->DataValue = FLOAT32ToString(value.float32);
            }
			    break;
            case FWP_DOUBLE:
            {
                // std::cout << value.double64;
                filterConditionIn->DataType = "FWP_DOUBLE";
                filterConditionIn->DataValue = DOUBLE64ToString(value.double64);
            }
			    break;
            case FWP_SID:
            {
                filterConditionIn->DataType = "FWP_SID";
                filterConditionIn->DataValue = SIDToString(value.sid);
            }
			    break;
            case FWP_BYTE_ARRAY16_TYPE:
            {
                filterConditionIn->DataType = "FWP_BYTE_ARRAY16_TYPE";

                wfp::IpAddress ipv6 = wfp::IpAddress::IpAddress(
                    *value.byteArray16
                );
                filterConditionIn->DataValue = wstr2stru8(ipv6.toString());
            }
            break;
            case FWP_BYTE_BLOB_TYPE:
            {
                filterConditionIn->DataType = "FWP_BYTE_BLOB_TYPE";
                if (value.byteBlob != nullptr && value.byteBlob->size != 0) {
                    //wprintf(L"%ls", (wchar_t*)value.byteBlob->data);
                    filterConditionIn->DataValue = wstr2stru8((wchar_t*)value.byteBlob->data);
                }
            }
			break;
            case FWP_V4_ADDR_MASK:
            {
                filterConditionIn->DataType = "FWP_V4_ADDR_MASK";
                
                std::stringstream ss;
                //ss << value.v4AddrMask->addr;

                unsigned char oct[4] = { 0,0,0,0 };
                for (int i = 0; i < 4; i++)
                {
                    oct[i] = (value.v4AddrMask->addr >> (i * 8)) & 0xFF;
                }
                ss << oct[3] << "." << oct[2] << "." << oct[1] << "." << oct[0];

                //ss << value.v4AddrMask->mask;
                UINT8 prefix = 0;
                for(int i = 0 ; prefix < 32; i++)
                {
                    if ((ntohl(value.v4AddrMask->mask) & ((UINT32)1 << (31 - i))) == 0)
                    {
                        break;
                    }
                    prefix++;
                }
                ss << " /" << prefix;
                filterConditionIn->DataValue = ss.str();

            }
            break;
            case FWP_V6_ADDR_MASK:
            {
                filterConditionIn->DataType = "FWP_V6_ADDR_MASK";
                std::stringstream ss;
                
                wfp::IpAddress ipv6 = wfp::IpAddress::IpAddress(*(value.v6AddrMask->addr));
                //std::wcout << "V: " << ipv6.toString();
                ss << wstr2stru8(ipv6.toString());
                filterConditionIn->DataValue = ss.str();
            }
            break;
            case FWP_RANGE_TYPE:
            {
                filterConditionIn->DataType = "FWP_RANGE_TYPE";
                std::stringstream ss;
                //std::cout << " l: " << (FWP_CONDITION_VALUE0*)&(value.rangeValue)->valueLow;
                switch (value.rangeValue->valueLow.type) {

                case FWP_UINT8: {
                    ss << " (FWP_UINT8) " << value.rangeValue->valueLow.uint8
                        << "-" << value.rangeValue->valueHigh.uint8;
                }break;
                case FWP_UINT16: {
                    ss << " (FWP_UINT16) " << value.rangeValue->valueLow.uint16
                        << "-" << value.rangeValue->valueHigh.uint16;
                }break;
                case FWP_UINT32: {
                    ss << " (FWP_UINT32) " << IPNumber2IPAddress(value.rangeValue->valueLow.uint32)
                        << "-" << IPNumber2IPAddress(value.rangeValue->valueHigh.uint32);
                }break;
                case FWP_UINT64: {
                    ss << " (FWP_UINT64) " << *value.rangeValue->valueLow.uint64
                        << "-" << *value.rangeValue->valueHigh.uint64;
                }break;
                case FWP_INT8: {
                    ss << " (FWP_INT8) " << value.rangeValue->valueLow.int8
                        << "-" << value.rangeValue->valueHigh.int8;
                }break;
                case FWP_INT16: {
                    ss << " (FWP_INT16) " << value.rangeValue->valueLow.int16
                        << "-" << value.rangeValue->valueHigh.int16;
                }break;
                case FWP_INT32: {
                    ss << " (FWP_INT32) " << value.rangeValue->valueLow.int32
                        << "-" << value.rangeValue->valueHigh.int32;
                }break;
                case FWP_INT64: {
                    ss << " (FWP_INT64) " << *value.rangeValue->valueLow.int64
                        << "-" << *value.rangeValue->valueHigh.int64;
                }break;
                case FWP_FLOAT: {
                    ss << " (FWP_FLOAT) " << value.rangeValue->valueLow.float32
                        << "-" << value.rangeValue->valueHigh.float32;
                }break;
                case FWP_DOUBLE: {
                    ss << " (FWP_DOUBLE) " << value.rangeValue->valueLow.double64
                        << "-" << value.rangeValue->valueHigh.double64;
                }break;
                case FWP_BYTE_ARRAY16_TYPE: {
                    // This comes in reversed (Network byte order?)
                    wfp::IpAddress ipL = wfp::IpAddress::IpAddress( *value.rangeValue->valueLow.byteArray16 );
                    wfp::IpAddress ipH = wfp::IpAddress::IpAddress( *value.rangeValue->valueHigh.byteArray16 );
                    ss << " (FWP_BYTE_ARRAY16_TYPE) " << wstr2stru8(ipL.toString()) << "-" << wstr2stru8(ipH.toString());
                }break;
                case FWP_BYTE_BLOB_TYPE: {
                    ss << " (FWP_BYTE_BLOB_TYPE) " << value.rangeValue->valueLow.byteBlob
                        << "-" << value.rangeValue->valueHigh.byteBlob;
                }break;
                case FWP_SID: {
                    ss << " (FWP_SID) " << value.rangeValue->valueLow.sid
                        << "-" << value.rangeValue->valueHigh.sid;
                }break;
                case FWP_SECURITY_DESCRIPTOR_TYPE: {
                    ss << " (FWP_SECURITY_DESCRIPTOR_TYPE) " << value.rangeValue->valueLow.sd
                        << "-" << value.rangeValue->valueHigh.sd;
                }break;
                case FWP_TOKEN_INFORMATION_TYPE: {
                    ss << " (FWP_TOKEN_INFORMATION_TYPE) " << value.rangeValue->valueLow.tokenInformation
                        << " - " << value.rangeValue->valueHigh.tokenInformation;
                }break;
                case FWP_TOKEN_ACCESS_INFORMATION_TYPE: {
                    ss << " (FWP_TOKEN_ACCESS_INFORMATION_TYPE) " << value.rangeValue->valueLow.tokenAccessInformation
                        << " - " << value.rangeValue->valueHigh.tokenAccessInformation;
                }break;
                case FWP_UNICODE_STRING_TYPE: {
                    ss << " (FWP_UNICODE_STRING_TYPE) " << value.rangeValue->valueLow.unicodeString
                        << " - " << value.rangeValue->valueHigh.unicodeString;
                }break;
                case FWP_BYTE_ARRAY6_TYPE: {
                    ss << " (FWP_BYTE_ARRAY6_TYPE) " << value.rangeValue->valueLow.byteArray6
                        << " - " << value.rangeValue->valueLow.byteArray6;
                }break;
                case FWP_V4_ADDR_MASK: {
                    ss << " (FWP_V4_ADDR_MASK) " << value.rangeValue->valueLow.uint32
                        << " - " << value.rangeValue->valueHigh.uint32;
                }break;
                case FWP_V6_ADDR_MASK: { 
                    ss << " (FWP_V6_ADDR_MASK) " << "FWP_V6_ADDR_MASK Not Implemented";
                }break;
                default: ss << " unknown";
                }
                filterConditionIn->DataType = ss.str();
            }
			break;
            case FWP_TOKEN_INFORMATION_TYPE:
                filterConditionIn->DataType = "FWP_TOKEN_INFORMATION_TYPE";
                filterConditionIn->DataValue = "FWP_TOKEN_INFORMATION_TYPE";
                break;
            case  FWP_TOKEN_ACCESS_INFORMATION_TYPE:
            {
                std::stringstream ss;
                filterConditionIn->DataType = "FWP_TOKEN_ACCESS_INFORMATION_TYPE";
                //value.tokenAccessInformation->size;
                auto ntk = (TOKEN_ACCESS_INFORMATION*)(void*)value.tokenAccessInformation->data;
                ss << "Token Type: " << ntk->TokenType;
                filterConditionIn->DataValue = ss.str();
            }
                break;
            case  FWP_SINGLE_DATA_TYPE_MAX:
                filterConditionIn->DataType = "FWP_SINGLE_DATA_TYPE_MAX";
                filterConditionIn->DataValue = "FWP_SINGLE_DATA_TYPE_MAX";
                break;
            case  FWP_SECURITY_DESCRIPTOR_TYPE:
            {
                filterConditionIn->DataType = "FWP_SECURITY_DESCRIPTOR_TYPE";
                char* Sddl = (char*)malloc(value.sd->size);

                if (Sddl != NULL) {

                    if (ConvertSecurityDescriptorToStringSecurityDescriptorA(
                        value.sd->data,
                        SDDL_REVISION_1,
                        OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION |
                        DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION,
                        &Sddl, 0) == TRUE) {

                        filterConditionIn->DataValue = Sddl;
                    }
                }
            }
                break;
            default:
                filterConditionIn->DataType = "UNSUPPORTED";
                filterConditionIn->DataValue = "Unsupported type: " + std::to_string(value.type);
                // printf("%d (unsupported)", value.type);
                break;
            }
            J["FilterConditions"][ix]["ConditionDataType"] = filterConditionIn->DataType;
            J["FilterConditions"][ix]["ConditionDataValue"] = filterConditionIn->DataValue;
        }
		// std::cout << J.dump(4) << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unknown exception\n";
    }
}
#pragma endregion

#pragma region Providers
void WFPSessionManager::ListProvider(std::string providerIn) {
    GUID providerInGUID = GUID_NULL;

    if (!providerIn.empty()) {
        std::wstring providerGUIDwstring;

        GUIDStringToGUIDWString(providerGUIDwstring, providerIn);
        try {
            providerInGUID = common::Guid::FromString(providerGUIDwstring);
        }
        catch (std::exception e) {
            std::cout << "Unable to parse GUID: " << e.what() << std::endl;
            return;
        }
    }

    // provider collector
    json jProviders = json::array();

    bool ok = wfp::ObjectEnumerator::Providers(*this->engine, [&providerInGUID, &jProviders, this](const FWPM_PROVIDER0& provider)
	{
		json jProvider;

		if (providerInGUID == GUID_NULL) {
			ProcessProvider(provider, jProvider);
			jProviders.push_back(jProvider);
		}
		else {
			if (IsEqualGUID(provider.providerKey, providerInGUID)) {
				ProcessProvider(provider, jProvider);
				jProviders.push_back(jProvider);
			}
		}
		return true;
	});
    // std::cout << jProviders.dump(3) << std::endl;
    this->J["Providers"] = jProviders;
}
void WFPSessionManager::ProcessProvider(const FWPM_PROVIDER0& provider, nlohmann::json& jProvider) {

    jProvider["ProviderData"] = "None";
    jProvider["ProviderDataSz"] = 0;
    jProvider["ProviderName"] = wstr2stru8(provider.displayData.name);
    if (provider.displayData.description != nullptr) {
        jProvider["ProviderDescription"] = wstr2stru8(provider.displayData.description);
    }
    jProvider["ProviderKey"] = GUIDToString(provider.providerKey);
    jProvider["ProviderFlags"] = provider.flags;
    if (provider.serviceName != NULL) {
        jProvider["ProviderServiceName"] = wstr2stru8(provider.serviceName);
    }
    else {
        jProvider["ProviderServiceName"] = "None";
    }
	if (provider.providerData.size != 0) {
        jProvider["ProviderDataSz"] = provider.providerData.size;

        std::stringstream ss;
        for (unsigned int i = 0; i < provider.providerData.size; ++i)
            ss << std::hex << (int)provider.providerData.data[i];

        jProvider["ProviderData"] = ss.str();
	}

    //std::cout << jProvider.dump(3) << std::endl;
    
}
#pragma endregion

#pragma region Context
void WFPSessionManager::ListProviderContext(std::string contextIn) {
    GUID contextInGUID = GUID_NULL;

    if (!contextIn.empty()) {
        std::wstring contextGUIDwstring;

        GUIDStringToGUIDWString(contextGUIDwstring, contextIn);
        try {
            contextInGUID = common::Guid::FromString(contextGUIDwstring);
        }
        catch (std::exception e) {
            std::cout << "Unable to parse GUID: " << e.what() << std::endl;
            return;
        }
    }

    // provider context collector
    json jContexts = json::array();

    bool ok = wfp::ObjectEnumerator::ProviderContexts(*this->engine, [&contextInGUID, &jContexts, this](const FWPM_PROVIDER_CONTEXT0& context)
        {
            json jContext;

            if (contextInGUID == GUID_NULL) {
                ProcessProviderContext(context, jContext);
                jContexts.push_back(jContext);
            }
            else {
                if (IsEqualGUID(context.providerContextKey, contextInGUID)) {
                    ProcessProviderContext(context, jContext);
                    jContexts.push_back(jContext);
                }
            }
            return true;
        });
    // std::cout << jProviders.dump(3) << std::endl;
    this->J["ProviderContexts"] = jContexts;
}
void WFPSessionManager::ProcessProviderContext(const FWPM_PROVIDER_CONTEXT0& context, nlohmann::json& jContext) {

    jContext["ContextName"] = wstr2stru8(context.displayData.name);
    jContext["ContextKey"] = GUIDToString(context.providerContextKey);
    jContext["ContextID"] = context.providerContextId;
    jContext["ContextFlags"] = context.flags;
    if (context.displayData.description != nullptr) {
        jContext["ContextDescription"] = wstr2stru8(context.displayData.description);
    }
    else {
        jContext["ContextDescription"] = "None";
    }

    if (0x0000000000000000 != context.providerKey && !IsEqualGUID(*context.providerKey, GUID()) 
            && !IsEqualGUID(context.providerContextKey, GUID_NULL)) {
        jContext["Provider"]["ProviderKey"] = GUIDToString(*context.providerKey);

        json jProvider;
        bool ok = wfp::ObjectExplorer::GetProvider(*engine, *context.providerKey, [&jProvider](const FWPM_PROVIDER0& provider)
            {
                jProvider["ProviderName"] = wstr2stru8(provider.displayData.name);
                jProvider["ProviderKey"] = GUIDToString(provider.providerKey);
                if (provider.serviceName != NULL) {
                    jProvider["ProviderServiceName"] = wstr2stru8(provider.serviceName);
                }
                else {
                    jProvider["ProviderServiceName"] = "None";
                }
                return true;
            });

        jContext["Provider"] = jProvider;

    }
    else {
        jContext["Provider"]["ProviderKey"] = GUIDToString(GUID_NULL);
    }
}
#pragma endregion

#pragma region Sublayer
void WFPSessionManager::ListSublayer(std::string sublayerIn) {
    GUID sublayerInGUID = GUID_NULL;

    if (!sublayerIn.empty()) {
        std::wstring sublayerGUIDwstring;

        GUIDStringToGUIDWString(sublayerGUIDwstring, sublayerIn);
        try {
            sublayerInGUID = common::Guid::FromString(sublayerGUIDwstring);
        }
        catch (std::exception e) {
            std::cout << "Unable to parse GUID: " << e.what() << std::endl;
            return;
        }
    }

    // sublayer collector
    json jSublayers = json::array();

    bool ok = wfp::ObjectEnumerator::Sublayers(*engine, [&sublayerInGUID, &jSublayers, this](const FWPM_SUBLAYER0& sublayer)
        {
            json jSublayer;

            if (sublayerInGUID == GUID_NULL) {
                ProcessSublayer(sublayer, jSublayer);
                jSublayers.push_back(jSublayer);
            }
            else {
                if (IsEqualGUID(sublayer.subLayerKey, sublayerInGUID)) {
                    ProcessSublayer(sublayer, jSublayer);
                    jSublayers.push_back(jSublayer);
                }
            }
            return true;
        });
    // std::cout << jSublayers.dump(3) << std::endl;
    this->J["Sublayers"] = jSublayers;
}
void WFPSessionManager::ProcessSublayer(const FWPM_SUBLAYER0& sublayer, nlohmann::json& jSublayer) {

    jSublayer["SublayerDataSz"] = 0;
    jSublayer["SublayerName"] = wstr2stru8(sublayer.displayData.name);
    jSublayer["SublayerKey"] = GUIDToString(sublayer.subLayerKey);
    jSublayer["SublayerWeight"] = sublayer.weight;

    if (sublayer.flags == FWPM_SUBLAYER_FLAG_PERSISTENT) {
        jSublayer["SublayerFlags"] = "Persistent";
    }
    else {
        jSublayer["SublayerFlags"] = "Ephemeral";
    }

    if (sublayer.providerKey != nullptr) {
        jSublayer["SublayerProviderKey"] = GUIDToString(*sublayer.providerKey);

        // provider collector
        json jProvider;
        bool ok = wfp::ObjectExplorer::GetProvider(*engine, *sublayer.providerKey, [&jProvider](const FWPM_PROVIDER0& provider)
            {
                jProvider["ProviderName"] = wstr2stru8(provider.displayData.name);
                jProvider["ProviderKey"] = GUIDToString(provider.providerKey);
                jProvider["ProviderFlags"] = provider.flags;
                if (provider.serviceName != NULL) {
                    jProvider["ProviderServiceName"] = wstr2stru8(provider.serviceName);
                }
                else {
                    jProvider["ProviderServiceName"] = "None";
                }
                return true;
            });

        jSublayer["Provider"] = jProvider;
    }

    std::unique_ptr<fwpm_sublayer_desc_t> sublayer_desc(new fwpm_sublayer_desc_t);
    getSublayerGuidance(sublayer.subLayerKey, sublayer_desc);

    if (!IsEqualGUID(sublayer_desc->guid, GUID_NULL)) {
        jSublayer["SublayerGuidance"]["Message"] = sublayer_desc->msg;
        jSublayer["SublayerGuidance"]["Description"] = sublayer_desc->desc;
    }
    else {
        jSublayer["SublayerGuidance"]["Message"] = "None";
        jSublayer["SublayerGuidance"]["Description"] = "None";
    }

}
#pragma endregion

#pragma region  Layer
void WFPSessionManager::ListLayer(std::string layerIn) {
    GUID layerInGUID = GUID_NULL;

    if (!layerIn.empty()) {
        std::wstring layerGUIDwstring;

        GUIDStringToGUIDWString(layerGUIDwstring, layerIn);
        try {
            layerInGUID = common::Guid::FromString(layerGUIDwstring);
        }
        catch (std::exception e) {
            std::cout << "Unable to parse GUID: " << e.what() << std::endl;
            return;
        }
    }

    // layer collector
    json jLayers = json::array();

    bool ok = wfp::ObjectEnumerator::Layers(*engine, [&layerInGUID, &jLayers, this](const FWPM_LAYER0& layer)
        {
            json jLayer;

            if (layerInGUID == GUID_NULL) {
                ProcessLayer(layer, jLayer);
                jLayers.push_back(jLayer);
            }
            else {
                if (IsEqualGUID(layer.layerKey, layerInGUID)) {
                    ProcessLayer(layer, jLayer);
                    jLayers.push_back(jLayer);
                }
            }
            return true;
        });
    // std::cout << jLayers.dump(3) << std::endl;
    this->J["Layers"] = jLayers;
}
void WFPSessionManager::ProcessLayer(const FWPM_LAYER0& layer, nlohmann::json& jLayer) {

    jLayer["LayerName"] = wstr2stru8(layer.displayData.name);
    jLayer["LayerKey"] = GUIDToString(layer.layerKey);
    jLayer["LayerID"] = layer.layerId;
    jLayer["LayerDefaultSublayerKey"] = "None";

    if (layer.defaultSubLayerKey != GUID_NULL) {
        jLayer["LayerDefaultSublayerKey"] = GUIDToString(layer.defaultSubLayerKey);

        // sublayer collector
        json jSublayer;
        bool ok = wfp::ObjectExplorer::GetSublayer(*engine, layer.defaultSubLayerKey, [&jSublayer](const FWPM_SUBLAYER0& sublayer)
            {

                if (sublayer.displayData.name != NULL) {
                    jSublayer["SublayerName"] = wstr2stru8(sublayer.displayData.name);
                }
                else {
                    jSublayer["SublayerName"] = "None";
                }
                return true;
            });

        jLayer["Sublayer"] = jSublayer;
    }

    std::unique_ptr<fwpm_layer_desc_t> layer_desc(new fwpm_layer_desc_t);
    bool ok = getLayerGuidance(layer.layerKey, layer_desc);

    if (ok && !IsEqualGUID(layer_desc->guid, GUID_NULL)) {
        jLayer["LayerGuidance"]["Message"] = layer_desc->msg;
        jLayer["LayerGuidance"]["Description"] = layer_desc->desc;
    }
    else {
        jLayer["LayerGuidance"]["Message"] = "None";
        jLayer["LayerGuidance"]["Description"] = "None";
    }

}
#pragma endregion

#pragma region  Event
void WFPSessionManager::ListEvent() {


	//bool ok = wfp::ObjectEnumerator::Events(*engine, [this](const FWPM_NET_EVENT0& event)
	//{

	//	std::cout << "Type: " << event.type  << std::endl;
	//	bool ok = wfp::ObjectExplorer::GetFilter(*engine, event.classifyDrop->filterId, [](const FWPM_FILTER0& filter)
	//		{
	//			std::cout << "\tFilter: " << wstr2stru8(filter.displayData.name) << std::endl;
	//			return true;
	//		});
	//	ok = wfp::ObjectExplorer::GetLayer(*engine, event.classifyDrop->layerId, [](const FWPM_LAYER0& layer)
	//		{
	//			std::cout << "\tLayer: " << wstr2stru8(layer.displayData.name) << std::endl;
	//			return true;
	//		});
	//	//DumpHex(event.header.appId.data, event.header.appId.size);

	//	return true;
	//});


    FWP_VALUE val;
    val.type = FWP_UINT32;
    val.uint32 = 1;


    std::shared_ptr<wfp::FilterEngine> engine2 = wfp::FilterEngine::StandardSession();

    unsigned long code = FwpmEngineSetOption0(engine2.get()->session(), FWPM_ENGINE_COLLECT_NET_EVENTS, &val);

    if (code ==  ERROR_SUCCESS)
    {
		std::cerr << "Options set" << std::endl;
		auto monitor = wfp::ObjectMonitor(this->engine);
		monitor.monitorEvents( [](const FWPM_NET_EVENT1& event) 
		{
		    std::cerr << "in monitoring" << std::endl;
			std::cout <<  event.classifyDrop->filterId << std::endl;
		});
    }
    else {
        std::cerr << "Error: " << std::hex << code << std::endl;
    }

}
#pragma endregion

#pragma region AddFilter

bool WFPSessionManager::AddFilter(nlohmann::json& J) {
    bool status = false;
    FilterAddIn filterAddIn; 
    // std::vector<FilterConditionIn> filterConditionsIn;
    GUID filterKey;


    // Meta
    if (J.contains("Meta") && J["Meta"].contains("SubLayerName") && !J["Meta"]["SubLayerName"].is_null()) {
        filterAddIn.subLayerName = J["Meta"]["SubLayerName"].get<std::string>();
        // std::cout << "SubLayerName: " << filterAddIn.subLayerName << std::endl;
    }
    else {
        std::cerr << "SubLayerName directive not found or empty" << std::endl;
        return status;
    }
    
    if (J.contains("Meta") && J["Meta"].contains("SubLayerWeight") && !J["Meta"]["SubLayerWeight"].is_null()) {

        if (J["Meta"]["SubLayerWeight"].is_number_unsigned()) {
            filterAddIn.subLayerWeight = J["Meta"]["SubLayerWeight"].get<unsigned int>();
            // std::cout << "SubLayerWeight: " << filterAddIn.subLayerWeight << std::endl;
        }
        else {
            std::cerr << "SubLayerWeight directive expects number" << std::endl;
            return status;
        }
    }
    else {
        filterAddIn.subLayerWeight = static_cast <unsigned int> (wfp::FilterBuilder::WeightClass::Max);
        std::cout << "SubLayerWeight directive not found or empty. Defaulting to Max" << std::endl;
    }

    GUID subLayerGUID = CreateSublayer(filterAddIn);

    if (IsEqualGUID(subLayerGUID, GUID_NULL)) {
            std::cerr << "SubLayer was not created" << std::endl;
            return status;
    }

    // Filters
    if (J.contains("Filters") && !J["Filters"].is_null()) {

        for (auto& filter : J["Filters"].items()) {

            // std::cout << "Processing filter: " << filter.key() <<  std::endl;

            if (filter.value().contains("FilterAction") && !filter.value()["FilterAction"].is_null()) {
                // std::cout << "fitler action" << std::endl;
                filterAddIn.filterAction = filter.value()["FilterAction"];
                if (filterAddIn.filterAction.compare("FWP_ACTION_BLOCK") == 0) {
					filterAddIn.filterAction = "FWP_ACTION_BLOCK";
                }
                else {
                    if (filterAddIn.filterAction.compare("FWP_ACTION_PERMIT") == 0) {
                        filterAddIn.filterAction = "FWP_ACTION_PERMIT";
                    }
                    else {
                        std::cerr << "Filter Action incorrect, valid (BLOCK|PERMIT) : " << filterAddIn.filterAction << std::endl;
                        return status;
                    }
                }
            } else {
                std::cerr << "FilterAction directive not found or empty" << std::endl;
                return status;
            }

            if (filter.value().contains("FilterType") && !filter.value()["FilterType"].is_null()) {
                filterAddIn.filterType = filter.value()["FilterType"];
            } else {
                // std::cout << "fitler type" << std::endl;
                std::cerr << "FilterAction directive not found or empty" << std::endl;
                return status;
            }

            if (filter.value().contains("FilterKey") && !filter.value()["FilterKey"].is_null()) {
                filterAddIn.filterKey = filter.value()["FilterKey"];
                // std::cout << "fitler key" << std::endl;
            } else {
                std::cerr << "FilterKey directive not found or empty" << std::endl;
                return status;
            }

            if (filter.value().contains("FilterName") && !filter.value()["FilterName"].is_null()) {
                filterAddIn.filterName = filter.value()["FilterName"];
                // std::cout << "fitler name" << std::endl;
            } else {
                std::cerr << "FilterName directive not found or empty" << std::endl;
                return status;
            }

            if (filter.value().contains("FilterDesc") && !filter.value()["FilterDesc"].is_null()) {
                filterAddIn.filterDesc = filter.value()["FilterDesc"];
                // std::cout << "fitler desc" << std::endl;
            } else {
                std::cout << "FilterDesc directive not found or empty. Defaulting to filter name" << std::endl;
                filterAddIn.filterDesc = filterAddIn.filterName;
            }

            if (filter.value().contains("FilterLayerName") && !filter.value()["FilterLayerName"].is_null()) {
                // std::cout << "fitler layer name" << std::endl;
                filterAddIn.filterLayerName = filter.value()["FilterLayerName"];
            } else {
                std::cerr << "FilterLayerName directive not found or empty" << std::endl;
                return status;
            }

            if (filter.value().contains("FilterLayerWeight") && !filter.value()["FilterLayerWeight"].is_null()) {
                filterAddIn.filterLayerWeight = filter.value()["FilterLayerWeight"].get<unsigned int>();
                // std::cout << "fitler layer weight" << std::endl;
            } else {
                std::cout << "FilterLayerWeight directive not found or empty. Defaulting to max" << std::endl;
                filterAddIn.filterLayerWeight = MAXUINT16;
            }

            // Filter conditions
            if (filter.value().contains("FilterConditions") && !filter.value()["FilterConditions"].is_null()) {

                for (auto& filterCondition : filter.value()["FilterConditions"].items()) {

                    FilterConditionIn filterConditionIn;
					if (filterCondition.value().contains("DataValue") && !filterCondition.value()["DataValue"].is_null()) {
                        // TODO: if app file  - check if it exists
						 filterConditionIn.DataValue = filterCondition.value()["DataValue"];
                        // std::cout << "fitler conditions - datavalue" << std::endl;
					} else {
						std::cerr << "FilterCondition - DataValue directive not found or empty" << std::endl;
						return status;
					}

					if (filterCondition.value().contains("DataType") && !filterCondition.value()["DataType"].is_null()) {
                        // std::cout << "fitler conditions - datatype" << std::endl;
						 filterConditionIn.DataType = filterCondition.value()["DataType"];
					} else {
						std::cerr << "FilterCondition - DataType directive not found or empty" << std::endl;
						return status;
					}

					if (filterCondition.value().contains("MatchType") && !filterCondition.value()["MatchType"].is_null()) {
						 filterConditionIn.MatchType = filterCondition.value()["MatchType"];
                        // std::cout << "fitler conditions - matchtype" << std::endl;
					} else {
						std::cerr << "FilterCondition - MatchType directive not found or empty" << std::endl;
						return status;
					}

                    filterAddIn.filterConditionsIn.push_back(filterConditionIn);
                }

                filterKey = CreateFilter(filterAddIn, subLayerGUID);

                if (IsEqualGUID(filterKey, GUID_NULL)) {
                    std::cerr << "Filter GUID key is bad: " << filterKey << std::endl;
                    std::cerr << "Maybe check if the CONDITION and the FILTER are added to correct LAYER, and that the LAYER you are adding it to is designed to accept them." << std::endl;
                    return status;
                }
                filterAddIn.filterConditionsIn.clear();
            }
            else {
                std::cerr << "FilterConditions directive not found or empty" << std::endl;
                return status;
            }
        }

        Sleep(INFINITE);
    } else {
        std::cerr << "Filters directive not found or empty" << std::endl;
        return status;
    }

    return status;
}
#pragma endregion

GUID WFPSessionManager::CreateSublayer(FilterAddIn& filterAddIn) {
    GUID sublayerGuid;
	wfp::SublayerBuilder sublayer(wfp::BuilderValidation::OnlyCritical);
    sublayer
        .name(str2wstr(filterAddIn.subLayerName))
        .weight(static_cast<UINT16>(filterAddIn.subLayerWeight));

    try {
        wfp::ObjectInstaller::AddSublayer(*this->engine, sublayer, &sublayerGuid);
    }
	catch ( common::error::WindowsException e) { 
		std::cout << "CreateSublayer exception: " <<  "Code: " <<  e.errorCode() <<  " Msg: " << common::error::FormatWindowsError(e.errorCode()) << std::endl;
		return GUID_NULL;
	}
    catch (...) {
        std::cerr << "unknown exception" << std::endl;
        return GUID_NULL;
    }

    return sublayerGuid;
}
GUID WFPSessionManager::CreateFilter(FilterAddIn& filterAddIn, GUID subLayerGUID){

    std::wstring FilterGUIDWstr;
    static GUID FilterKey;

    GUIDStringToGUIDWString(FilterGUIDWstr, filterAddIn.filterKey);
    try {
        FilterKey = common::Guid::FromString(FilterGUIDWstr);
    }
    catch (std::exception e) {
        std::cerr << "Unable to parse GUID: " << e.what() << std::endl;
        return GUID_NULL;
    }

    std::unique_ptr<fwpm_layer_desc_t> layer_desc(new fwpm_layer_desc_t);
    bool ok = getLayerGuidance(filterAddIn.filterLayerName, layer_desc);

    if (!ok && IsEqualGUID(layer_desc->guid, GUID_NULL)) {
		std::cerr << "Layer GUID cannot be identified: " << filterAddIn.filterLayerName << std::endl;
		return GUID_NULL;
    }


    // Conditions are checked against the specified layer
    // To verify that they're compatible
    wfp::ConditionBuilder conditions(layer_desc->guid);

    for (auto& filterCondition : filterAddIn.filterConditionsIn) {

        // Match on filter type.
        std::string filterTypeApp = "APP";
        if (filterTypeApp.compare(filterAddIn.filterType) == 0) {

            if (filterCondition.DataType.compare("PATH") == 0) {

                // check if path exists
                std::ifstream appFile(filterCondition.DataValue);
                if (appFile.fail()) {
                    std::cerr << "Check condition, app file not found: " << filterCondition.DataValue << std::endl;
                    return GUID_NULL;
                }

				try {
        
                    std::wcout << str2wstr(filterCondition.DataValue) << std::endl;
					conditions.add_condition(
						std::make_unique<wfp::conditions::ConditionApplication>( str2wstr(filterCondition.DataValue)));
				}
				catch ( common::error::WindowsException e) { 
					std::cout << "Add condition exception: " <<  "Code: " <<  e.errorCode() <<  " Msg: " << common::error::FormatWindowsError(e.errorCode()) << std::endl;
					return GUID_NULL;
				}
				catch (std::exception& e) {
					std::cerr << "excption: " << e.what() <<  std::endl;
					return GUID_NULL;
				}
				catch (...) {
					std::cerr << "unknown exception" <<   std::endl;
					return GUID_NULL;
				}
            }
			
            if (filterCondition.DataType.compare("IPADDR") == 0) {

                try {
                    // const wfp::IpAddress ipaddr = wfp::IpAddress(L"0:0:0:0:0:FFFF:ACD9:0924");
                    // const wfp::IpAddress ipaddr = wfp::IpAddress(L"172.217.9.36");

                    if (filterCondition.MatchType.compare("EQUAL") == 0) {
                        conditions.add_condition(
                            wfp::conditions::ConditionIp::Remote(wfp::IpAddress(str2wstr(filterCondition.DataValue)), wfp::conditions::CompareEq()));
                    }else if (filterCondition.MatchType.compare("NEQUAL") == 0 ) {
                        conditions.add_condition(
                            wfp::conditions::ConditionIp::Remote(wfp::IpAddress(str2wstr(filterCondition.DataValue)), wfp::conditions::CompareNeq()));
                    } else {
						std::cerr << "Add condition exception: Match type is unsupported (valid: EQUAL, NEQUAL): " << filterCondition.MatchType << std::endl;
						return GUID_NULL;
                    }
                }
                catch (common::error::WindowsException e) {
                    std::cerr << "Add condition exception: " << "Code: " << e.errorCode() << " Msg: " << common::error::FormatWindowsError(e.errorCode()) << std::endl;
                    return GUID_NULL;
                }
                catch (...) {
                    std::cerr << "unknown exception" << std::endl;
                    return GUID_NULL;
                }
            }

            if (filterCondition.DataType.compare("IPNET") == 0) {

                try {
                    // "52.114.128.43/16"

                    // split CIDR string into vector or net and prefix, then build the network part
                    std::vector<std::string> ipAddrV = split(filterCondition.DataValue, '/');

                    uint8_t prefix = unsigned(std::stoi(ipAddrV.back(), nullptr, 0));

                    const wfp::IpNetwork ipNet = wfp::IpNetwork(
                        wfp::IpAddress( str2wstr(ipAddrV.front())), prefix );

                    //std::wcout << "Ipnetwork: " << ipNet.toString() << std::endl;


                    if (filterCondition.MatchType.compare("EQUAL") == 0) {
                        conditions.add_condition(
                            wfp::conditions::ConditionIp::Remote(ipNet, wfp::conditions::CompareEq()));
                    }
                    else if (filterCondition.MatchType.compare("NEQUAL") == 0) {
                        conditions.add_condition(
                            wfp::conditions::ConditionIp::Remote(wfp::IpAddress(str2wstr(filterCondition.DataValue)), wfp::conditions::CompareNeq()));
                    }
                    else {
                        std::cerr << "Add condition exception: Match type is unsupported (valid: EQUAL, NEQUAL): " << filterCondition.MatchType << std::endl;
                        return GUID_NULL;
                    }
                }
                catch (common::error::WindowsException e) {
                    std::cerr << "Add condition exception: " << "Code: " << e.errorCode() << " Msg: " << common::error::FormatWindowsError(e.errorCode()) << std::endl;
                    return GUID_NULL;
                }
                catch (...) {
                    std::cerr << "unknown exception" << std::endl;
                    return GUID_NULL;
                }
            }

        }
        else {
			std::cerr << "Unsupported filter cond type: " << filterAddIn.filterType << std::endl;
			return GUID_NULL;
        }
    }

    
    
    // Match remote ports outside given range
    /* conditions.add_condition(wfp::conditions::ConditionPortRange::Remote(\
        0, 1023, wfp::conditions::CompareNeq()));
    */

    wfp::FilterBuilder filter(wfp::BuilderValidation::OnlyCritical);

	std::stringstream ss;
    ss << "\nInstalling Filter: "  << filterAddIn.filterName << std::endl;
    ss << "+ Key: " << std::setw(32) << FilterKey << std::endl;
    ss << "+ In Layer: " << layer_desc->guid << "(" << layer_desc->msg << ")";

    std::cout << ss.str() << std::endl;

    filter
        .key(FilterKey)
        .name(str2wstr(filterAddIn.filterName))
        .description(str2wstr(filterAddIn.filterDesc))
        .layer(layer_desc->guid)
        .sublayer(subLayerGUID)
        .weight(filterAddIn.filterLayerWeight); // todo

    if (filterAddIn.filterAction.compare("FWP_ACTION_BLOCK") == 0) {
        filter.block();
    }
    else {
        filter.permit();
    }
  
	try {
		wfp::ObjectInstaller::AddFilter(*engine, filter, conditions);
	}
	catch ( common::error::WindowsException e) { 
		std::cerr << "AddFilter exception: " <<  "Code: " <<  e.errorCode() <<  " Msg: " << common::error::FormatWindowsError(e.errorCode()) << std::endl;
		return GUID_NULL;
	}
	catch (...) {
		std::cerr << "unknown exception" << std::endl;
		return GUID_NULL;
	}

    /*ok = (wfp::ObjectExplorer::GetFilter(*engine, FilterKey, [&](const FWPM_FILTER0& filter)
        {
            return 0 == wcscmp(filter.displayData.name, str2wstr(filterAddIn.filterKey));
        }));

    */
    return FilterKey;
}
