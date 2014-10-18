#ifndef validate_contract_with_dialog_hpp
#define validate_contract_with_dialog_hpp

// stl headers
#include <string>
#include <utility>
#include <iostream>

// boost components
#include <boost/lexical_cast.hpp>

// twsapi
#include <Contract.h>
#include "utilities/type/all.hpp"
#include "utilities/define.hpp"
#include "utilities/settings/settings.hpp"
#include "recordset/tableContractRecordset/tableContractRecordset.hpp"
#include "recordset/functions/singleInstrumentSelect/singleInstrumentSelect.hpp"

// opens a dialog with the user and returns
// the uniquely defined contract in the dataBase
IB::dataBase::contractRecord
validateContractWithDialog(std::string contractCode);

#endif