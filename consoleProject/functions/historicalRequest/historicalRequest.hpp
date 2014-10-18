#ifndef tws_function_historical_request
#define tws_function_historical_request

#include <functional>
#include <chrono>

// boost components
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#include <boost/thread.hpp>

// thOth components
#include <thOth/time/DateTime.hpp>

// twsapi
#include "request/historicalRequestClient/historicalRequestClient.hpp"
#include "recordset/tableHistoricalBarRecordset2/tableHistoricalBarRecordset2.hpp"
#include "recordset/functions/singleHistoricalBarInsert/singleHistoricalBarInsert.hpp"

// this procedure is meant to request 
// missing historical data about a given contract
void historicalRequest(IB::dataBase::contractRecord contract_,
					   const thOth::dateTime & startDate,
					   const thOth::dateTime & endDate,
					   bool deletionPolicy);
#endif