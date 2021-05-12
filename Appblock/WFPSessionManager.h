#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>

#include <libwfp/filterengine.h>
#include <libwfp/buildervalidation.h>
#include <libwfp/sublayerbuilder.h>
#include <libwfp/objectinstaller.h>
#include <libwfp/conditionbuilder.h>
#include <libwfp/conditions/conditionapplication.h>
#include <libwfp/conditions/conditionportrange.h>
#include <libwfp/conditions/comparison.h>
#include <libwfp/conditions/conditionip.h>
#include <libwfp/filterbuilder.h>
#include <libwfp/objectexplorer.h>
#include <libwfp/objectenumerator.h>
#include <libwfp/objectdeleter.h>
#include <libwfp/objectinstaller.h>
#include <libwfp/objectmonitor.h>
#include <libwfp/ipaddress.h>
#include <libcommon/guid.h>
#include <libcommon/error.h>

#include <nlohmann/json.hpp>
#include "Util.h"
#include "MgmtGUIDs.h"

namespace WFPManager {

	enum class FWTypes {
		NET_FW_PROFILE2_DOMAIN = 1,
		NET_FW_PROFILE2_PRIVATE = 2,
		NET_FW_PROFILE2_PUBLIC = 4,

	};

	typedef struct _FilterCondition {
		GUID FieldKey;
		std::string MatchType;
		std::string DataType;
		std::string ConditonName;
		std::string ConditionDesc;
		std::string DataValue;
	} FilterCondition;

	typedef struct _FilterRecordLayer {
		GUID LayerKey;
		std::string LayerMsg;
		std::string LayerDesc;
	} FilterRecordLayer;

	typedef struct _FilterRecordProvider {
		GUID *ProviderKey;
		GUID ProviderContextKey;
		FWP_BYTE_BLOB ProviderData;
		std::wstring ProviderName;
		std::wstring ProviderService;
	} FilterRecordProvider;

	typedef struct _FilterRecord {
		std::string ActionType;
		GUID FilterKey;
		UINT64 FilterID;
		std::wstring FilterName;
		std::wstring FilterDesc;
		FilterRecordLayer FilterRecordLayerIn;
		FilterRecordProvider FilterRecordProviderIn;
	} FilterRecord;

#pragma region AddFilter
	typedef struct _FilterConditionIn {
		std::string MatchType;
		std::string DataType;
		std::string DataValue;
	} FilterConditionIn;

	typedef struct _FilterAddIn {
		std::string subLayerName;
		unsigned int subLayerWeight;
		std::string filterAction;
		std::string filterType;
		std::string filterKey;
		std::string filterName;
		std::string filterDesc;
		std::string filterLayerName;
		unsigned int filterLayerWeight;
		std::vector<FilterConditionIn> filterConditionsIn;
	} FilterAddIn;
#pragma endregion



	class WFPSessionManager
	{
	private:
		nlohmann::json J;
		std::shared_ptr<wfp::FilterEngine> engine;
		void ProcessFilter(const FWPM_FILTER0& filter, nlohmann::json& J);
		void ProcessSession(const FWPM_SESSION0& session, nlohmann::json& J);
		void ProcessProvider(const FWPM_PROVIDER0& provider, nlohmann::json& J);
		void ProcessProviderContext(const FWPM_PROVIDER_CONTEXT0& context, nlohmann::json& J);
		void ProcessSublayer(const FWPM_SUBLAYER0& sublayer, nlohmann::json& J);
		void ProcessLayer(const FWPM_LAYER0& sublayer, nlohmann::json& J);
	public:
		void Engine();
		void ListSession(std::string sessionIn);
		void ListFilter(std::string filterIn);
		void ListProvider(std::string providerIn);
		void ListProviderContext(std::string contextIn);
		void ListSublayer(std::string sublayerIn);
		void ListLayer(std::string layerIn);
		void ListEvent();
		bool AddFilter(nlohmann::json& J);
		GUID CreateFilter(FilterAddIn& filterAddIn, GUID subLayerGUID);
		GUID CreateSublayer(FilterAddIn& filterAddIn);
		nlohmann::json GetJsonCollection();
	};
}

