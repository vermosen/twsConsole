#include "functions/bulkStaticDataRequest/bulkStaticDataRequest.hpp"

void bulkStaticDataRequest(const std::string & code,
					       bool deletionPolicy) {
	
	boost::timer tt;											// timer

	// step 1: initialization
	std::cout
		<< "bulk static data request"
		<< std::endl
		<< "------------------------"
		<< std::endl
		<< std::endl;

	// step 2: import csv file


	// step 3: check for previous insert
	std::vector<IB::Contract> contracts;

	while (true) {													// iterate on the strings
	
		std::string code("toto");

		// check wether the contract is in the database
		// TODO: replace with bulkInstrumentSelect function
		try {
		
			IB::dataBase::contractRecord rs = singleInstrumentSelect(code);
		
			if (deletionPolicy = true) {							// insert only if deletion policy is set to true
			
				IB::Contract ct;

				ct.symbol = code;
				ct.exchange = "SMART";
				ct.primaryExchange = "NYSE";
				ct.secType = "STK";

				contracts.push_back(ct);
			
			}

		} catch (IB::dataBase::selectQueryExceptionNoSelection) {		// no contract, insert in any case
		
			IB::Contract ct;

			ct.symbol = code;
			ct.exchange = "SMART";
			ct.primaryExchange = "NYSE";
			ct.secType = "STK";

			contracts.push_back(ct);
		
		} catch (std::exception & ex) {					// other exception, throw
		
			throw ex;
		
		}
	}

	// step 4: request static data
	for (std::vector<IB::Contract>::const_iterator It = contracts.cbegin(); It != contract.cend(); It++) {
	
		for (unsigned int attempt = 1;; attempt++) {				// loop over attemps

			if (IB::settings::instance().verbosity() > 0)

				TWS_LOG_V(std::string("attempt number ")			// log
				.append(boost::lexical_cast<std::string>(attempt))
				.append(" out of ")
				.append(boost::lexical_cast<std::string>(MAX_ATTEMPT)), 0)

				client.connect(
				IB::settings::instance().ibHost().c_str(),
				IB::settings::instance().ibPort());					// TODO: test if we have to provide connection id here

			while (client.isConnected()) client.processMessages();

			if (attempt > MAX_ATTEMPT)								// max attemps reached
				throw std::exception("failed to connect after max attempts");

			if (client.endOfData()) {								// download succedded

				TWS_LOG_V(std::string("download successful"), 0)	// log	
					break;

			}
			else {

				TWS_LOG_V(std::string("sleeping ")					// log
					.append(boost::lexical_cast<std::string>(SLEEP_TIME))
					.append(" seconds before next attempt"), 0)

					boost::this_thread::sleep_for(						// sleep for 100 ms
					boost::chrono::milliseconds(SLEEP_TIME));

			}

		}															// end of for loop

		TWS_LOG_V(													// partially log the contract details
			std::string("contract details: (symbol) ")
			.append(client.contract().symbol)
			.append(", (secType) ")
			.append(client.contract().secType)
			.append(", (currency) ")
			.append(client.contract().currency)
			.append(", (primary exchange) ")
			.append(client.contract().primaryExchange)
			.append(", (bondType) ")
			.append(client.contractDetails().bondType)
			.append(", (callable) ")
			.append(boost::lexical_cast<std::string>(client.contractDetails().callable))
			.append(", (category) ")
			.append(client.contractDetails().category)
			.append(", (contractMonth) ")
			.append(client.contractDetails().contractMonth)
			.append("..."), 1)

			// step 3: insert into the database
			TWS_LOG_V(													// log
			std::string("attempt to insert contract details"), 0)

			MYSQL * connect =
			IB::settings::instance().connection();

		// recordset`& query
		IB::dataBase::tableContractRecordset rs(connect);			// table contract recordset

		if (!rs.insert(client.contractDetails()))					// tries to insert 
			TWS_LOG_V(std::string("insert failed"), 0)
		
	}
	
	TWS_LOG_V(													// log
		std::string("bulk static data request completed in ")
			.append(boost::lexical_cast<std::string>(tt.elapsed()))
			.append(" seconds"), 0)

};