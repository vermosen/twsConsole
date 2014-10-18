#ifndef tws_function_history_file_creation
#define tws_function_history_file_creation

#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

// thOth components
#include <thOth/time/DateTime.hpp>
#include <thOth/utilities/csvBuilder.hpp>

// twsapi
#include "utilities/type/all.hpp"
#include "utilities/settings/settings.hpp"
#include "utilities/define.hpp"
#include "recordset/functions/singleHistoricalBarSelect/singleHistoricalBarSelect.hpp"

// this procedure creates a csv file with the requested informations
void historyFileCreation(
	const IB::dataBase::contractRecord & contract_,
	const thOth::dateTime & startDate_,
	const thOth::dateTime & endDate_);

#endif