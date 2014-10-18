#include "functions/simpleStrategy/simpleStrategy.hpp"

void simpleStrategy(
	const std::pair<IB::dataBase::recordId, IB::ContractDetails> & contract_,
	const thOth::dateTime & startDate_,
	const thOth::dateTime & endDate_,
	bool deletionPolicy_) {
	
	// step 1: initialization
	boost::timer tt;											// set a timer

	std::cout
		<< "simple strategy test"
		<< std::endl
		<< "--------------------"
		<< std::endl
		<< std::endl;

	// step 2: call request function
	thOth::timeSeries<thOth::bar> d								// the data, assuming there is no hole
		= singleHistoricalBarSelect(contract_, startDate_, endDate_);

	TWS_LOG_V(													// log
		std::string("simple strategy test completed in ")
		.append(boost::lexical_cast<std::string>(tt.elapsed()))
		.append(" seconds."), 0)

};