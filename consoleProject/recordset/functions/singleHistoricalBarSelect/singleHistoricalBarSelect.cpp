#include "recordset/functions/singleHistoricalBarSelect/singleHistoricalBarSelect.hpp"

thOth::timeSeries<thOth::bar> singleHistoricalBarSelect(
	const IB::dataBase::contractRecord & contract_,
	const thOth::dateTime & startDate_,
	const thOth::dateTime & endDate_) {

	thOth::timeSeries<thOth::bar> returndata;

	// step 1: initialize connection
	IB::dataBase::tableHistoricalBarRecordset2 rs(
		IB::settings::instance().connection());

	// step 2: building the query
	std::string query;
	query.append("SELECT * FROM table_historical_bar WHERE (contract_ID = ");
	INSERT_SQL_NUM(query, contract_.first)
		query.append(" AND bar_start >= ");
	INSERT_SQL_DATE(query, startDate_)
		query.append(" AND bar_end <= ");
	INSERT_SQL_DATE(query, endDate_)
		query.append(")");

	rs.selectStr(query);											// run the query

	for (IB::dataBase::tableHistoricalBarRecordset2::const_iterator It
		= rs.cbegin(); It != rs.cend(); It++)

		returndata.insert(*It);

	return returndata;

};