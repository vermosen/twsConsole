#ifndef single_historical_bar_insert_hpp
#define single_historical_bar_insert_hpp

//#include <functional>
#include <thread>

// boost components
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

// thOth components
#include <thOth/time/DateTime.hpp>
#include <thOth/bar/bar.hpp>

// twsapi
#include "request/historicalRequestClient/historicalRequestClient.hpp"
#include "recordset/tableContractRecordset/tableContractRecordset.hpp"
#include "recordset/tableHistoricalBarRecordset2/tableHistoricalBarRecordset2.hpp"

// single date insert function
void singleHistoricalBarInsert(
	const IB::dataBase::contractRecord & contract_,
	IB::dataBase::tableHistoricalBarRecordset2 & barRs_,
	thOth::dateTime dt_,
	bool policy_);

#endif