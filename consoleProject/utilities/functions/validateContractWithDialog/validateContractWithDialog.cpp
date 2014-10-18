#include "utilities/functions/validateContractWithDialog/validateContractWithDialog.hpp"

IB::dataBase::contractRecord 
validateContractWithDialog(std::string contractCode) {

	for (;;) {															// infinite loop

		try {

			if (contractCode.empty()) {									// if string is empty, manual managment

				std::cout
					<< "please provide some contract code : "
					<< std::endl;

				std::cin >> contractCode;								// user response

			}

			return singleInstrumentSelect(contractCode);

		} catch (IB::dataBase::selectQueryExceptionNoSelection & ex) {	// no corresponding contract 

			TWS_LOG_V(std::string("given code has no \
				corresponding contract in the database"), 0)

			std::cout													// message
				<< " unknown code: "
				<< contractCode
				<< ", please try again."
				<< std::endl;

			contractCode.clear();										// new attempt

		}
		catch (std::exception & ex) {

			TWS_LOG_V(std::string("an error occured in convertContractWithDialog function: ")
				.append(ex.what()), 0)

				throw ex;

		}
		catch (...) {

			throw std::exception("an unknown error occured in convertContractWithDialog function");

		}
	}

};