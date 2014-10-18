#ifndef bulk_instrument_select_hpp
#define bulk_instrument_select_hpp

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

// this function is performing a standard
// request to retrieve all the elements in the database
void bulkInstrumentSelect(IB::dataBase::tableContractRecordset::iterator & beg_,
						  IB::dataBase::tableContractRecordset::iterator & end_);

#endif