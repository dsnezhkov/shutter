#pragma once
#include <libwfp/filterengine.h>
#include <libwfp/buildervalidation.h>
#include <libwfp/sublayerbuilder.h>
#include <libwfp/objectinstaller.h>
#include <libwfp/conditionbuilder.h>
#include <libwfp/conditions/conditionapplication.h>
#include <libwfp/conditions/conditionportrange.h>
#include <libwfp/conditions/comparison.h>
#include <libwfp/filterbuilder.h>
#include <libwfp/objectexplorer.h>
#include <libwfp/objectenumerator.h>
#include <libwfp/objectdeleter.h>
#include <libwfp/objectinstaller.h>
#include <libwfp/ipaddress.h>
#include <libcommon/logging/logsink.h>

#include <cxxopts.hpp>

#include <iostream>
#include <memory>
#include <exception>
#include <typeinfo>
#include <stdexcept>

#include "Util.h"
#include "MgmtGUIDs.h"
#include "WFPSessionManager.h"
