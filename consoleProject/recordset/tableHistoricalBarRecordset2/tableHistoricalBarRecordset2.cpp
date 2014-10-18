#include "recordset/tableHistoricalBarRecordset2/tableHistoricalBarRecordset2.hpp"

namespace IB {

	namespace dataBase {
	
		//barRecord::barRecord(
		//	recordId id,
		//	const thOth::timeSeries<thOth::bar> & bars,
		//	const std::string & exchange) 
		//	: id_(id), bars_(bars), exchange_(exchange) {};
		//
		//barRecord::barRecord(const barRecord & rec)
		//	: id_(rec.id_), bars_(rec.bars_), exchange_(rec.exchange_) {};

		tableHistoricalBarRecordset2::tableHistoricalBarRecordset2(MYSQL * connection) 
			: recordset2(connection) {};

		tableHistoricalBarRecordset2 & tableHistoricalBarRecordset2::operator=(const tableHistoricalBarRecordset2 & o) {

			if (this != &o) {
			
				recordset2::operator=(o);						// call the parent class =
				records_ = o.records_  ;						// copy local stuff

			}

			return *this;
		
		}

		bool tableHistoricalBarRecordset2::selectStr(const std::string & selectStr) {
		
			mysql_query(												// query to run
				connection_,
				selectStr.c_str());

			reception_ = mysql_store_result(connection_);
		
			if (!reception_)											// sql statement failed
				throw selectQueryExceptionSelectFailed();

			if (reception_->row_count == 0)								// no record
				throw selectQueryExceptionNoSelection();

			MYSQL_ROW row;

			//recordId barId = 1;										// in case the id is not part of the 
																		// request we generate a key

			std::string exchange;
			recordId instrumentId;										// the id of the record to insert

			while (row = mysql_fetch_row(reception_)) {					// loop over the results
				
				
				thOth::dateTime startDate; thOth::dateTime endDate;		// mandatory bar components
				thOth::real open; thOth::real close; thOth::real low;
				thOth::real high; thOth::size volume;
				
				for (unsigned long i = 0;								// loop over the fields
					i < reception_->field_count; i++) {	

					std::string field(reception_->fields[i].name);

					if (std::string(reception_->fields[i].name)
						== "CONTRACT_ID" && row[i] != NULL)
						instrumentId = boost::lexical_cast<recordId>(row[i]);

					else if (std::string(reception_->fields[i].name)		// we don't need the bar
						== "BAR_ID" && row[i] != NULL) {}

					else if (std::string(reception_->fields[i].name)
						== "BAR_START" && row[i] != NULL)
						startDate = convertDateTime_sql(std::string(row[i]));

					else if (std::string(reception_->fields[i].name)
						== "BAR_END" && row[i] != NULL)
						endDate = convertDateTime_sql(std::string(row[i]));

					else if (std::string(reception_->fields[i].name)
						== "OPEN" && row[i] != NULL)
						open = boost::lexical_cast<thOth::real>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CLOSE" && row[i] != NULL)
						close = boost::lexical_cast<thOth::real>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "HIGH" && row[i] != NULL)
						high = boost::lexical_cast<thOth::real>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "LOW" && row[i] != NULL)
						low = boost::lexical_cast<thOth::real>(row[i]);
					
					else if (std::string(reception_->fields[i].name)
						== "VOLUME" && row[i] != NULL)
						volume = boost::lexical_cast<thOth::size>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "EXCHANGE" && row[i] != NULL)
						exchange = boost::lexical_cast<std::string>(row[i]);

					else

						throw selectQueryExceptionUnknownField();

				}

				records_.insert(
					std::pair<thOth::dateTime, thOth::bar>(
						startDate, thOth::bar(
							open, close, high,
							low, thOth::period(
								thOth::second, 30), volume)));

			}

			return true;

		};

		bool tableHistoricalBarRecordset2::insert(
			const std::pair<recordId, ContractDetails> & ct, 
			const thOth::timeSeries<thOth::bar> & recs) {

			std::string fieldStr, valueStr;								// the two fields to build together

			// TODO: need to iterate over the ts
			for (thOth::timeSeries<thOth::bar>::const_iterator It = recs.cbegin(); It != recs.cend(); It++) {

				fieldStr.append("CONTRACT_ID,");						// contract id
				INSERT_SQL_NUM(valueStr, ct.first)
					valueStr.append(",");

				fieldStr.append("BAR_START,");							// barStart
				INSERT_SQL_DATE(valueStr, It->first)
					valueStr.append(",");

				fieldStr.append("BAR_END,");							// barEnd
				INSERT_SQL_DATE(valueStr, thOth::dateTime::advance(It->first, It->second.length()))
					valueStr.append(",");

				fieldStr.append("OPEN,");								// open
				INSERT_SQL_NUM(valueStr, It->second.open())
					valueStr.append(",");

				fieldStr.append("CLOSE,");								// close
				INSERT_SQL_NUM(valueStr, It->second.close())
					valueStr.append(",");

				fieldStr.append("HIGH,");								// close
				INSERT_SQL_NUM(valueStr, It->second.high())
					valueStr.append(",");

				fieldStr.append("LOW,");								// close
				INSERT_SQL_NUM(valueStr, It->second.low())
					valueStr.append(",");

				fieldStr.append("VOLUME,");								// volume
				INSERT_SQL_NUM(valueStr, It->second.volume())
					valueStr.append(",");

				fieldStr.append("EXCHANGE");							// exchange
				INSERT_SQL_STR(valueStr, ct.second.summary.exchange)

					std::string insertStatement("INSERT INTO table_historical_bar (");

				insertStatement
					.append(fieldStr)
					.append(") VALUES (")
					.append(valueStr)
					.append(")");

				if (mysql_query(connection_, insertStatement.c_str()) != 0)	// throw on an error
					throw std::exception(mysql_error(connection_));

				fieldStr.clear(), valueStr.clear();							

			}
			

			return true;												// return true otherwise

		}

		bool tableHistoricalBarRecordset2::deleteStr(const std::string & deleteStr) {
		
			if (mysql_query(connection_, deleteStr.c_str()) != 0) {		// throw on an error

				std::string tt(mysql_error(connection_));
				throw std::exception(mysql_error(connection_));

			}

			// todo: error management
			return true;
		
		}
	}
}