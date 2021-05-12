#include "Appblock.h"

using namespace WFPManager;
using namespace common::logging;

int main(int argc, char** argv)
{

    const char* current_locale = setlocale(LC_ALL, "en_US");

    //UNREFERENCED_PARAMETER(argc);
    //UNREFERENCED_PARAMETER(argv);

    cxxopts::Options options("AppBlock", "Block by condition");
    options.positional_help("[--list | --add | --remove]");

    bool debug;
    cxxopts::ParseResult result; 
    cxxopts::ParseResult posresult; 

    try {

        options.add_options("general")
			("h,help", "Print usage")
			("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
			("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
			;
        options.add_options("action")
            ("list", "list", cxxopts::value<bool>()->default_value("false"))
            ("add", "add", cxxopts::value<bool>()->default_value("false"))
            ("remove", "remove", cxxopts::value<bool>()->default_value("false"))
            ;
        options.add_options("qualifier")
			("filter", "list:filter GUID | add:filter file path", cxxopts::value<std::string>()->implicit_value(""))
			("layer", "layer", cxxopts::value<std::string>()->implicit_value(""))
			("sublayer", "sublayer", cxxopts::value<std::string>()->implicit_value(""))
			("session", "session", cxxopts::value<std::string>()->implicit_value(""))
			("provider", "provider", cxxopts::value<std::string>()->implicit_value(""))
			("context", "context", cxxopts::value<std::string>()->implicit_value(""))
			("event", "event", cxxopts::value<bool>()->default_value("false"))
            ;
        options.add_options("result")
			("output", "output", cxxopts::value<std::string>()->implicit_value("out.json"))
            ;
	}catch (cxxopts::OptionException oe) {
        std::cout << oe.what() << std::endl;
        return 1;
    }catch (std::exception& e) {
        std::cout << "Apb ex: " << e.what() << std::endl;
        return 1;
    }catch (...) {
        std::cout << "unknown exception" << std::endl;
        return 1;
    }


	auto wfpMgr = new WFPSessionManager();
    wfpMgr->Engine();

    try {
        options.parse_positional("{list, add, remove}");
		result = options.parse(argc, argv);

        // general options
        if (result.count("help")) {
            std::vector <std::string> help_groups({ "general", "action", "qualifier", "result" });
            std::cout << options.help(help_groups) << std::endl;
            return 0;
        }
        if (result.count("debug")) {
            debug = result["debug"].as<bool>();
            std::cout << debug << std::endl;
        }
        if (result.count("verbose")) {
            debug = result["verbose"].as<bool>();
            std::cout << result.count("verbose") << debug << std::endl;
        }

        // Actions
        if (result.count("list")) {
            if (result["list"].as<bool>()) {
                std::cout << "Action: list" << std::endl;

                // list options
                if (result.count("filter")) {
                    std::string filter = result["filter"].as<std::string>();
                    wfpMgr->ListFilter(filter);
                }
                if (result.count("layer")) {
                    std::string layer = result["layer"].as<std::string>();
                    wfpMgr->ListLayer(layer);
                }
                if (result.count("sublayer")) {
                    std::string sublayer = result["sublayer"].as<std::string>();
                    wfpMgr->ListSublayer(sublayer);
                }
                if (result.count("session")) {
                    std::string session = result["session"].as<std::string>();
                    wfpMgr->ListSession(session);
                }
                if (result.count("provider")) {
                    std::string provider = result["provider"].as<std::string>();
                    wfpMgr->ListProvider(provider);
                }
                if (result.count("context")) {
                    std::string context = result["context"].as<std::string>();
                    wfpMgr->ListProviderContext(context);
                }
                if (result.count("event")) {
                    // bool event = result["event"].as<bool>();
                    wfpMgr->ListEvent();
                }
                // Save output
                nlohmann::json jCollection = wfpMgr->GetJsonCollection();
                if (result.count("output")) {
                    // std::cout << "result.count('output'): " << result.count("output") << std::endl;
                    std::string filePath = result["output"].as<std::string>();
                    SaveJsonToFile(filePath, jCollection);
                }
                else {
                    std::cout << jCollection.dump(3) << std::endl;
                }
            }
        }
        else{
            if (result.count("add")) {
                if (result["add"].as<bool>()) {
                    std::cout << "Action: add" << std::endl;

                    // list options
                    if (result.count("filter")) {
                        std::string filterFile = result["filter"].as<std::string>();
                        nlohmann::json jCollection = LoadJsonFromFile(filterFile);
                        if (jCollection != NULL) {
                            // std::cout << jCollection.dump(3) << std::endl;
                            bool ok = wfpMgr->AddFilter(jCollection);
                        } 
                        else {
                            std::cerr << "filter file not read" << std::endl;
                        }
                    }

                    return 0;
                }
            }
            else {
				if (result.count("remove")) {
					if (result["remove"].as<bool>()) {
						std::cout << "Action: remove" << std::endl;
						return 0;
					}
                }
                else {
                    std::cerr << "Invalid action specified" << std::endl;
                    std::vector <std::string> help_groups({ "action" });
					std::cout << options.help(help_groups) << std::endl;
					return 1;
                }
            }
        } 

  


    }
    catch (cxxopts::OptionException oe) {
        std::cout << "Apb options" << oe.what() << std::endl;
        return 1;
    }
    catch (std::exception& e) {
        std::cout << "Apb ex: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cout << "unknown exception" << std::endl;
        return 1;
    }

    return 0;
}