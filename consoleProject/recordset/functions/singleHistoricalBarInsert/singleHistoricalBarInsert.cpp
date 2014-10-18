#include "recordset/functions/singleHistoricalBarInsert/singleHistoricalBarInsert.hpp"

void singleHistoricalBarInsert(
	const IB::dataBase::contractRecord & contract_,
	IB::dataBase::tableHistoricalBarRecordset2 & barRs_,
	thOth::dateTime dt_,
	bool policy_) {

	// step 0: set the client
	TWS_LOG_V(std::string("requesting IB data for date: ")	// log
		.append(boost::lexical_cast<std::string>(dt_.date())), 0)

	IB::historicalRequestClient client(						// creates a new client 
		contract_.second.summary,							// contract 
		dt_ + boost::gregorian::days(1),					// TODO: set to end of day
		IB::barSize::thirtySeconds,							// minimum bar size TODO: turn those as function parameters
		1, IB::dataDuration::day,							// period length and type
		IB::dataType::trade);								// data type

	TWS_LOG_V("connecting to the server", 1)				// log

	// step 1: data request
	for (int attempt = 0;; attempt++) {						// loop over attempts

		if (attempt > MAX_ATTEMPT)							// max attemps reached
			throw std::exception("failed to connect after max attempts");

		TWS_LOG_V(std::string("connection attempt number ")	// log
			.append(boost::lexical_cast<std::string>(attempt))
			.append(" out of ")
			.append(boost::lexical_cast<std::string>(MAX_ATTEMPT)), 0)

		client.connect(										// client is connecting
			IB::settings::instance().ibHost().c_str(),
			IB::settings::instance().ibPort());

		while (client.isConnected())						// TODO: turn into asynchronous mode
			client.processMessages();

		if (client.endOfData()) {							// download succedded

			// log
			TWS_LOG_V(std::string("download successful on attempt number ")
				.append(boost::lexical_cast<std::string>(attempt))
				.append(". Trying to store data in the database"), 0)

			std::cout										// information
				<< "successfully dowloaded data for contract "
				<< contract_.second.summary.symbol
				<< " on the date of "
				<< boost::lexical_cast<std::string>(dt_.date())
				<< std::endl;

			break;

		} else {

			int sleep = 100;

			TWS_LOG_V(std::string("sleeping ")				// log
				.append(boost::lexical_cast<std::string>(sleep))
				.append(" milli-seconds before next attempt "), 1)

			std::this_thread::sleep_for(					// sleep for some extra time
				std::chrono::milliseconds(sleep));

		}
	}

	// step 2: check for previous import: contract Id * dateframe * exchange
	std::string selectQuery;
	selectQuery.append("SELECT * FROM table_historical_bar WHERE (contract_ID = ");
	INSERT_SQL_NUM(selectQuery, contract_.first)
		selectQuery.append(" AND exchange = ");
	INSERT_SQL_STR(selectQuery, contract_.second.summary.exchange)
		selectQuery.append(" AND bar_start >= ");
	INSERT_SQL_DATE(selectQuery, client.cbegin()->first)
		selectQuery.append(" AND bar_end <= ");
	INSERT_SQL_DATE(selectQuery, thOth::dateTime::advance(
		client.crbegin()->first, client.crbegin()->second.length()))
		selectQuery.append(")");

	TWS_LOG_V(std::string("new query to launch: ")			// log
		.append(selectQuery), 1)

	try {

		if (barRs_.selectStr(selectQuery) == true) {			// if it doens't throw, there are item to delete

			if (policy_ == true) {

				TWS_LOG_V("previous import found, deleting existing data", 1)

				std::string deleteQuery;					// delete query
				deleteQuery.append("DELETE FROM TABLE_HISTORICAL_BAR WHERE (CONTRACT_ID = ");
				INSERT_SQL_NUM(deleteQuery, contract_.first)
					deleteQuery.append(" AND EXCHANGE = ");
				INSERT_SQL_STR(deleteQuery, contract_.second.summary.exchange)
					deleteQuery.append(" AND BAR_START >= ");
				INSERT_SQL_DATE(deleteQuery, client.cbegin()->first)
					deleteQuery.append(" AND BAR_END <= ");
				INSERT_SQL_DATE(deleteQuery, thOth::dateTime::advance(
					client.crbegin()->first, client.crbegin()->second.length()))
					deleteQuery.append(")");

				barRs_.deleteStr(deleteQuery);				// run the delete statement

			} else {

				client.clear();								// clear the data

			}
		}
	} catch (IB::dataBase::selectQueryExceptionNoSelection &) {

		// nothing to erase, go to the next step
		TWS_LOG_V("selectQueryExceptionNoSelection raised, \
				   continuing current procedure", 1)

	} catch (std::exception & ex) {

		throw ex;											// any other mistake -> throw

	}

	// step 3: copy data into the recordset
	barRs_.insert(contract_, thOth::timeSeries<thOth::bar>(client.cbegin(), client.cend()));

	// data summary
	TWS_LOG_V(std::string("")								// log
		.append(boost::lexical_cast<std::string>(barRs_.size()))
		.append(" new data inserted for contract ")
		.append(contract_.second.summary.symbol)
		.append(" and for date ")
		.append(boost::lexical_cast<std::string>(dt_.date())), 1)

}