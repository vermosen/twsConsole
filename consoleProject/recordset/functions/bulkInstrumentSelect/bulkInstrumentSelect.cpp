#include "recordset/functions/bulkInstrumentSelect/bulkInstrumentSelect.hpp"

void bulkInstrumentSelect(IB::dataBase::tableContractRecordset::iterator & beg_,
					      IB::dataBase::tableContractRecordset::iterator & end_) {

	TWS_LOG_V(													// log
		std::string("bulk request of all the contracts"), 0)

	// recordset`& query
	IB::dataBase::tableContractRecordset rs(					// table contract recordset
		IB::settings::instance().connection());

	std::string selectQuery(									// query to run
		"SELECT * FROM table_contract");

	if (rs.selectQ(selectQuery)) {								// query succeeded ?
		
		beg_ = rs.begin();
		end_ = rs.end  ();
		
	}
};