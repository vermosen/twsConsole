#include "functions/bulkImport/bulkImport.hpp"

void bulkImport(const thOth::dateTime & startDate,
				const thOth::dateTime & endDate,
				bool deletionPolicy) {

	// step 0: variable intialization
	boost::timer tt;											// set a timer

	// step 1: initialization
	std::cout
		<< "bulk import test"
		<< std::endl
		<< "----------------"
		<< std::endl
		<< std::endl;
	
	// recordset`& query
	IB::dataBase::tableContractRecordset2 contractRs(
		IB::settings::instance().connection());					// table contract recordset

	std::string selectQuery(									// query to run
		"SELECT * FROM table_contract");

	TWS_LOG_V(std::string("running query: ")					// log
		.append(selectQuery), 0)

	if (!contractRs.selectStr(selectQuery))						// query succeeded ?
		throw std::exception("instrument request failed");

	if (contractRs.size() == 0)									// symbol found ?
		throw std::exception("no symbol found");

	TWS_LOG_V(													// log
		std::string("")
		.append(boost::lexical_cast<std::string>(contractRs.size()))
		.append(" contracts found"), 0);

	IB::dataBase::tableHistoricalBarRecordset2 barRs(
		IB::settings::instance().connection());					// bar recordset

	// loop over the contracts
	for (std::map<IB::dataBase::recordId, IB::ContractDetails>::iterator It
		= contractRs.begin(); It != contractRs.end(); It++) {
	
		It->second.summary.exchange = "SMART";					// sets exchange to SMART

		thOth::dateTime dt = startDate;							// local copy

		// loop over the dates
		do {

			singleHistoricalBarInsert(
				*It, barRs, dt,									// insert single contract, do not throw
				deletionPolicy);

			std::this_thread::sleep_for(						// sleep time necessary between two requests
				std::chrono::milliseconds(SLEEP_TIME_H));

			dt += boost::gregorian::days(1);					// add 1 day

		} while (dt <= endDate);
	}

	TWS_LOG_V(													// log
		std::string("bulk data download completed in ")
		.append(boost::lexical_cast<std::string>(tt.elapsed()))
		.append(" seconds."), 0)

};