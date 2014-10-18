#include "utilities/functions/convertDateWithDialog/convertDateWithDialog.hpp"

// date conversion dialog
thOth::dateTime convertDateWithDialog(
	const std::string & dateName,
	std::string dtStr) {

	for(;;) {													// infinite loop

		try {

			if (dtStr.empty()) {								// if string is empty, manual managment

				std::cout										// message
					<< "Please provide some "
					<< dateName
					<< " (MM/dd/yyyy):"
					<< std::endl;

				std::cin >> dtStr;								// user response

			}

			return thOth::dateTime(								// no exception raised
				boost::lexical_cast<unsigned short>(dtStr.substr(6, 4)),
				boost::lexical_cast<int>(dtStr.substr(0, 2)),
				boost::lexical_cast<int>(dtStr.substr(3, 2)));				

		}
		catch (boost::bad_lexical_cast & ex) {					// error 

			TWS_LOG_V(std::string("bad lexical cast exception: ")
				.append(ex.what()), 0)

			std::cout											// message
				<< dateName
				<< " conversion impossible, Please try again."
				<< std::endl;

			dtStr.clear();										// new attempt

		}
		catch (std::exception & ex) {							// TODO: manage dateTime creation exceptions

			TWS_LOG_V(std::string("an error occured in main: ")
				.append(ex.what()), 0)

				throw ex;

		}
		catch (...) {

			throw std::exception("an unknown error occured in main");

		}
	}
}