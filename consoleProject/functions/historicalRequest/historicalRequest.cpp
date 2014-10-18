#include "functions/historicalRequest/historicalRequest.hpp"

void historicalRequest(IB::dataBase::contractRecord contract_,
					   const thOth::dateTime & startDate_,
					   const thOth::dateTime & endDate_,
					   bool deletionPolicy_) {

	boost::timer tt;											// set a timer
	
	// step 1: initialization
	std::cout
		<< "historical Request Test"
		<< std::endl
		<< "-----------------------"
		<< std::endl
		<< std::endl;	

	TWS_LOG_V(													// log
		std::string("contract provided: ")
			.append(contract_.second.summary.symbol), 0)

	TWS_LOG_V(													// log
		std::string("contract details: ")
			.append(contract_.second.summary.symbol)
			.append(", ")
			.append(contract_.second.summary.secType)
			.append(", ")
			.append(contract_.second.summary.exchange)
			.append(", ")
			.append(contract_.second.summary.currency)
			.append(", ")
			.append(contract_.second.summary.primaryExchange), 0);

	MYSQL * connect =											// use the default connection
		IB::settings::instance().connection();

	IB::dataBase::tableHistoricalBarRecordset2 barRs(connect);	// bar recordset
	IB::ContractDetails ct = contract_.second;					// copy the contract
	contract_.second.summary.exchange = "SMART";				// setting exchange to SMART
	
	thOth::dateTime dt = startDate_;							// date copy

	// step 3: loop over the dates
	do {

		singleHistoricalBarInsert(
			contract_, barRs,									// insert single contract_, do not throw
			dt, deletionPolicy_);

		boost::this_thread::sleep_for(							// sleep time necessary between two requests
			boost::chrono::milliseconds(SLEEP_TIME_H));
	
		dt += boost::gregorian::days(1);						// add 1 day we need to ensure it increases
																// TODO: increment business days instead
	} while (dt <= endDate_);

	TWS_LOG_V(													// log
		std::string("historical data download test completed in ")
			.append(boost::lexical_cast<std::string>(tt.elapsed()))
			.append(" seconds."), 0)

};