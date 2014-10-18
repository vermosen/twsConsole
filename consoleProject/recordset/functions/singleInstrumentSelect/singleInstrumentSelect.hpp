#ifndef single_instrument_select_hpp
#define single_instrument_select_hpp

// stl headers
#include <string>

// boost components
#include <boost/lexical_cast.hpp>

// twsapi
#include <Contract.h>
#include "utilities/type/all.hpp"
#include "utilities/define.hpp"
#include "utilities/settings/settings.hpp"
#include "recordset/tableContractRecordset/tableContractRecordset.hpp"

// this function is performing a standard instrument
// request in the dataBase to retrive a given instrument code
IB::dataBase::contractRecord singleInstrumentSelect(
	const std::string & contractCode);

#endif