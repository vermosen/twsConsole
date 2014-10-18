/*
 * 
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#include <thOth/time/DateTime.hpp>									// thOth components
#include <utilities/factory/all.hpp>

#include "contract.h"												// TWS library
#include "functions/all.hpp"										// test functions
#include "utilities/type/all.hpp"
#include "utilities/settings/settings.hpp"							// additional 
#include "utilities/define.hpp"
#include "utilities/functions/validateContractWithDialog/validateContractWithDialog.hpp"
#include "utilities/functions/convertDateWithDialog/convertDateWithDialog.hpp"

// This procedure can be started manually (empty argv)
// or automatically by passing some argument through one
// of the following options:
//     - verbose: defines the level of verbosity
//     - host   : define the TWS server adress
//     - port   : define the TWS server port
//     - log    : overload the default log path
//     - test   : automatically start selected test
int main(int argc, char** argv) {

	try {

		static ObjectHandler::EnumTypeRegistry enumTypeRegistry;	// registry
		
		IB::utilities::registerAllFactories();						// register the factories

		bool end = false; int test = 0;								// indicators
		std::string opt1, opt2, opt3;								// optional arguments
		bool erase = false;											// deletion policy

		IB::settings::instance().logPath(							// set the log path
			std::string(LOGPATH)
				.append("TwsApiServerTest")
				.append("_")
				.append(boost::posix_time::to_iso_string(
					boost::posix_time::second_clock::local_time()))
				.append("_")
				.append(".csv"));

		TWS_LOG_V(std::string("starting TwsApiTest"), 0)			// log

		for (int i = 1; i < argc; i++) {							// deals with optional arguments
			
			std::string arg(argv[i]);								// current std::string

			if (arg.substr(1, 7) == "verbose") {					// expects -verbose=n
				
				std::string str(arg.substr(9, arg.length() - 9));	// the value
				IB::settings::instance().verbosity(					// set the verbosity
					boost::lexical_cast<int>(str));
				TWS_LOG_V(std::string("sets verbosity to ")			// log
					.append(str), 1)

			};

			if (arg.substr(1, 4) == "host") {						// expects -host=xxx.xx.x.xxx

				std::string str(arg.substr(6, arg.length() - 6));	// the value
				IB::settings::instance().ibHost(str);				// set the host
				TWS_LOG_V(std::string("sets host to ")				// log
					.append(str), 1)

			};

			if (arg.substr(1, 4) == "port") {						// expects -port=xxxx

				std::string str(arg.substr(6, arg.length() - 6));	// the value
				IB::settings::instance().ibPort(					// set the port
					boost::lexical_cast<int>(str));
				TWS_LOG_V(std::string("sets port to ")				// log
					.append(str), 1)

			};

			if (arg.substr(1, 3) == "log") {						// expects -log=C:/bla

				std::string str(arg.substr(5, arg.length() - 5));	// the value
				IB::settings::instance().logPath(str);				// set the log path
				TWS_LOG_V(std::string("sets log path to ")			// log
					.append(str), 1)

			};

			if (arg.substr(1, 4) == "test") {						// expects -test=n
			
				std::string str(arg.substr(6, arg.length() - 6));	// the value
				test = boost::lexical_cast<int>(str);				// runs the selected test automatically	
				TWS_LOG_V(std::string("enforcing test ")			// log
					.append(str), 1)
				end = true;											// for later use: only one attempt

			}

			if (arg.substr(1, 5) == "erase") {						// expects -erase=true

				std::string str(arg.substr(7, arg.length() - 7));	// the value
				if (str == "true") erase = true;					// set erase to true
				TWS_LOG_V(std::string("set erase policy to ")		// log
					.append(str), 1)


			}

			if (arg.substr(1, 4) == "opt1") {						// expects -opt1=toto

				std::string str(arg.substr(6, arg.length() - 6));	// the value
				opt1 = str;											// set the opt1 value
				TWS_LOG_V(std::string("sets opt1 value to ")		// log
					.append(str), 1)

			}

			if (arg.substr(1, 4) == "opt2") {						// expects -opt1=toto

				std::string str(arg.substr(6, arg.length() - 6));	// the value
				opt2 = str;											// set the opt2 value
				TWS_LOG_V(std::string("sets opt2 value to ")		// log
					.append(str), 1)

			}

			if (arg.substr(1, 4) == "opt3") {						// expects -opt1=toto

				std::string str(arg.substr(6, arg.length() - 6));	// the value
				opt3 = str;											// set the opt2 value
				TWS_LOG_V(std::string("sets opt3 value to ")		// log
					.append(str), 1)

			}

		}
																	
		do {														// manual selection - loop over the choices
		
			int res = test;											// for manual definition

			if (test == 0) {
			
				std::cout											// message
					<< std::endl
					<< "Please select an activity: "
					<< std::endl
					<< "1 - static data request"
					<< std::endl
					<< "2 - historical data request"
					<< std::endl
					<< "3 - historical bulk request"
					<< std::endl
					<< "4 - history file creation"
					<< std::endl
					<< "5 - simple strategy"
					<< std::endl
					<< "6 - multi-threading test"
					<< std::endl
					<< "7 - csv writing test"
					<< std::endl
					<< "8 - debug test"
					<< std::endl
					<< "0 - exit"
					<< std::endl;

				std::cin >> res;									// user defined test
			
				TWS_LOG_V(std::string("manual selection ")			// log
					.append(boost::lexical_cast<std::string>(res)), 0)

			}
			
			switch (res) {											// switch over the tests available
			
				case 1:

					TWS_LOG_V(										// log
						std::string("starting static data request"), 0)

						if (opt1.empty()) {
						
							std::cout << "Please provide some contract code:" << std::endl;
							std::cin >> opt1;
						
						}

					staticDataRequest(opt1, erase);
					
					break;

				case 2:

					{
						TWS_LOG_V(									// log
							std::string("starting historical request"), 0)

						IB::dataBase::contractRecord ct_ = validateContractWithDialog(opt1);
						thOth::dateTime start_ = convertDateWithDialog("start date", opt2);
						thOth::dateTime end_ = convertDateWithDialog("end date", opt3);

						historicalRequest(ct_, start_, end_, erase);// launches historical request process
					
					}

					break;				

				case 3:

					{
						TWS_LOG_V(									// log
							std::string("starting historical bulk request"), 0)

						thOth::dateTime start_ = convertDateWithDialog("start date", opt2);
						thOth::dateTime end_ = convertDateWithDialog("end date", opt3);

						bulkImport(start_, end_, erase);			// launches bulk request process (opt1 ignored) 
					
					}

					break;

				case 4:

					{
						TWS_LOG_V(									// log
							std::string("starting history file creation"), 0)

							IB::dataBase::contractRecord ct_ = validateContractWithDialog(opt1);
						thOth::dateTime start_ = convertDateWithDialog("start date", opt2);
						thOth::dateTime end_ = convertDateWithDialog("end date", opt3);

						historyFileCreation(ct_, start_, end_);		// launches file creation procedure
				
					}
						
					break;

				case 5:

					{
						TWS_LOG_V(									// log
							std::string("starting simple strategy computation"), 0)

						IB::dataBase::contractRecord ct_ = validateContractWithDialog(opt1);
						thOth::dateTime start_ = convertDateWithDialog("start date", opt2);
						thOth::dateTime end_ = convertDateWithDialog("end date", opt3);

						simpleStrategy(ct_, start_, end_, erase);	// launches historical request process

					}

					break;

				case 6:

					TWS_LOG_V(										// log
						std::string("starting multi-threaded settings test"), 0)

						multiThreadedSetting();						// launches multi-threading
					break;

				case 7:

					TWS_LOG_V(										// log
						std::string("starting multi-threaded csv builder test"), 0)

					multiThreadedCsvBuilder();						// launches multi-threaded csv writing test
					
					break;

				case 8:

					TWS_LOG_V(										// log
						std::string("starting debug test"), 0)

					debug();										// launches debug test
					
					break;

				case 0:

					TWS_LOG_V(std::string("manual exit"), 0)		// log
					end = true;										// stop the server
					break;

				default:											// unknown, invalid

					TWS_LOG_V(										// log
						std::string("invalid selection"), 0)

					std::cout
						<< "invalid selection, please try again"
						<< std::endl;

					break;
			
			}
		
		} while (end == false);										// loop until exit

	} catch (std::exception & e) {									// exception management
			
		std::string mess("an error occured: ");
			mess.append(e.what());

		TWS_LOG_V(mess, 0)											// message
		std::cout << mess << std::endl;

	} catch (...) {													// unknown error
	
		std::string mess("an unknown error occured...");

		TWS_LOG_V(mess, 0)											// message
			std::cout << mess << std::endl;

	}

	if (IB::settings::instance().verbosity() > 0) {					// exit

		TWS_LOG_V(std::string("end of TwsApiTest"), 0)
		system("pause");

	}
}

