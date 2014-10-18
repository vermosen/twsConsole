#include "functions/historyFileCreation/historyFileCreation.hpp"

// this procedure aims at creating the history file of a
// given contract
void historyFileCreation(
	const IB::dataBase::contractRecord & contract_,
	const thOth::dateTime & startDate_,
	const thOth::dateTime & endDate_) {

	// step 1: initialization
	std::cout
		<< std::endl
		<< "History File Creation"
		<< std::endl
		<< "---------------------"
		<< std::endl
		<< std::endl;

	boost::timer tt;											// set a timer
	
	std::cout													// console message
		<< "creating history file for contract: "
		<< contract_.second.summary.symbol
		<< std::endl
		<< std::endl;

	// step 2: call request function
	thOth::timeSeries<thOth::bar> data 
		= singleHistoricalBarSelect(contract_, startDate_, endDate_);

	// step 3: creates a csv file containing the data
	std::string csvPath(										// csv path
		std::string("C://Temp/")
			.append(contract_.second.summary.symbol)
			.append("_")
			.append("bars")
			.append(".csv"));

	thOth::utilities::csvBuilder csv(csvPath, true);			// csv file, overwrite
	
	csv.allocate(												// pre-allocate memory to avoid multiple resizing
		static_cast<thOth::size>(data.size()) + 1, 7);

	csv.add(std::string("bar start"), 1, 1);					// column titles
	csv.add(std::string("bar end"  ), 1, 2);
	csv.add(std::string("open"     ), 1, 3);
	csv.add(std::string("close"    ), 1, 4);
	csv.add(std::string("high"     ), 1, 5);
	csv.add(std::string("low"      ), 1, 6);
	csv.add(std::string("volume"   ), 1, 7);

	// TODO: create a populate method to fill up the csv directly from a recordset
	long i = 0;	for (thOth::timeSeries<thOth::bar>::const_iterator It
		= data.cbegin(); It != data.cend(); It++, i++) {
	
		csv.add(boost::lexical_cast<std::string>(
			It->first.ExcelDate()), i + 2, 1);

		csv.add(boost::lexical_cast<std::string>(
			thOth::dateTime::advance(
				It->first, It->second.length()).ExcelDate()), i + 2, 2);
		
		csv.add(It->second.open  (), i + 2, 3);
		csv.add(It->second.close(), i + 2, 4);
		csv.add(It->second.high(), i + 2, 5);
		csv.add(It->second.low(), i + 2, 6);
		csv.add(It->second.volume(), i + 2, 7);
		
	}
	
	TWS_LOG_V(													// log
		std::string("history file created in ")
		.append(boost::lexical_cast<std::string>(tt.elapsed()))
		.append(" seconds"), 0)

};