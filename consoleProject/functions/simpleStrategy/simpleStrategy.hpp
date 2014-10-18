#ifndef tws_simple_strategy
#define tws_simple_strategy

#include <thread>
#include <memory>

#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

// thOth components
#include <thOth/time/DateTime.hpp>

// twsapi
#include "request/historicalRequestClient/historicalRequestClient.hpp"
#include "recordset/functions/singleHistoricalBarSelect/singleHistoricalBarSelect.hpp"

// this function is meant to test a simple signal strategy over a time series
void simpleStrategy(const IB::dataBase::contractRecord & contract_,
				    const thOth::dateTime & startDate_,
				    const thOth::dateTime & endDate_,
					bool deletionPolicy_ = false);

#endif