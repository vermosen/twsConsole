#include "recordset/functions/singleInstrumentSelect/singleInstrumentSelect.hpp"

IB::dataBase::contractRecord  singleInstrumentSelect(
	const std::string & contractCode) {

	// recordset`& query
	IB::dataBase::tableContractRecordset contractRs(			// table contract recordset
		IB::settings::instance().connection());

	std::string selectQuery(									// query to run
		"SELECT * FROM table_contract WHERE contract_symbol = '");
		selectQuery.append(contractCode);
		selectQuery.append("'");

	TWS_LOG_V(std::string("running query: ")					// log
		.append(selectQuery), 0)

	if (!contractRs.selectQ(selectQuery))						// query succeeded ?
		throw std::exception("instrument request failed");	

	if (contractRs.size() == 0)									// symbol found ?
		throw std::exception("symbol not found");

	if (contractRs.size() > 1)									// unique ?
		throw std::exception("different symbols found");

	return *contractRs.cbegin();

};