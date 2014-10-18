#ifndef single_historical_bar_select_hpp
#define single_historical_bar_select_hpp

// boost components
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

// twsapi
#include "utilities/type/all.hpp"
#include "utilities/define.hpp"
#include "utilities/settings/settings.hpp"
#include "recordset/tableContractRecordSet2/tableContractRecordSet2.hpp"
#include "recordset/tableHistoricalBarRecordset2/tableHistoricalBarRecordset2.hpp"

// this function is performing a standard instrument
// request in the dataBase to retrive the time series for a 
// given instrument between two dates
// the function returns a pointer to avoid unnecessary copy of the time series
thOth::timeSeries<thOth::bar> singleHistoricalBarSelect(
	const IB::dataBase::contractRecord & contract_,
	const thOth::dateTime & startDate_,
	const thOth::dateTime & endDate_);

#endif