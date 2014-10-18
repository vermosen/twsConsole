#include "recordset/tableContractRecordset/tableContractRecordset.hpp"

namespace IB {

	namespace dataBase {
	
		tableContractRecordset::tableContractRecordset(MYSQL * connection) 
			: recordset(connection) {};

		tableContractRecordset::tableContractRecordset(const tableContractRecordset & o) {
		
			records_ = o.records_;
		
		};

		tableContractRecordset::~tableContractRecordset() {};

		tableContractRecordset & tableContractRecordset::operator=(const tableContractRecordset & o) {
		
			if (this != &o) {
				
				recordset::operator=(o);						// call the parent class =
				records_ = o.records_  ;						// copy local stuff

			}

			return *this;
		
		}

		bool tableContractRecordset::selectQ(const std::string & selectStr) {
		
			// log
			TWS_LOG_V(std::string("running contract table select query: ")
				.append(selectStr), 1)

			mysql_query(												// query to run
				connection_,
				selectStr.c_str());

			reception_ = mysql_store_result(connection_);				// store the results
		
			if (!reception_)											// sql statement failed
				return false;

			if (reception_->row_count == 0)								// no record
				return false;

			MYSQL_ROW row;
			recordId id = 1;											// in case the db id is not part of the 
																		// request, automatically generate one

			while (row = mysql_fetch_row(reception_)) {					// loop over the results
																		// !! check how it iterates !!
				// contract details might be partial 
				// depending of the original request
				ContractDetails contract;								// the current contract				

				for (unsigned long i = 0; i < reception_->field_count; i++) {

					if (std::string(reception_->fields[i].name)      
						== "CONTRACT_ID" && row[i] != NULL)
						id = boost::lexical_cast<recordId>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_IBID" && row[i] != NULL)
						contract.summary.conId = boost::lexical_cast<long>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_SYMBOL" && row[i] != NULL)
						contract.summary.symbol  = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_SECTYPE" && row[i] != NULL)
						contract.summary.secType = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_EXPIRY" && row[i] != NULL)
						contract.summary.expiry  = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_STRIKE" && row[i] != NULL)
						contract.summary.strike  = boost::lexical_cast<double>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_RIGHT" && row[i] != NULL) {

						// temporary variable
						unsigned int j = boost::lexical_cast<unsigned int>(row[i]);

						(j == 1 ? contract.summary.right = "P" :
							(j == 2 ? contract.summary.right = "C" :
							contract.summary.right = ""));

					}

					else if (std::string(reception_->fields[i].name) 
						== "CONTRACT_MULTIPLIER" && row[i] != NULL)
						contract.summary.multiplier = std::string(row[i]);

					else if (std::string(reception_->fields[i].name) 
						== "CONTRACT_PRIMARY_EXCHANGE" && row[i] != NULL)
						contract.summary.primaryExchange = std::string(row[i]);

					else if (std::string(reception_->fields[i].name) 
						== "CONTRACT_CURRENCY" && row[i] != NULL)
						contract.summary.currency = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_TRADING_CLASS" && row[i] != NULL)
						contract.summary.tradingClass = std::string(row[i]);

					// might be the cusip plus another identifier
					// strategy: first insert cusip only in bond.cusip
					// then complete if this is the only identifier
					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_CUSIP" && row[i] != NULL)
						contract.cusip = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_ISIN" && row[i] != NULL) {

						contract.summary.secId = std::string(row[i]);
						contract.summary.secIdType = "ISIN";

					}
						
					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_SEDOL" && row[i] != NULL) {

						contract.summary.secId = std::string(row[i]);
						contract.summary.secIdType = "SEDOL";

					}

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_RIC" && row[i] != NULL) {

						contract.summary.secId = std::string(row[i]);
						contract.summary.secIdType = "RIC";

					}

					// other fields
					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_MARKET_NAME" && row[i] != NULL)
						contract.marketName = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_MINTICK" && row[i] != NULL)
						contract.minTick = boost::lexical_cast<double>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_ORDERTYPES" && row[i] != NULL)
						contract.orderTypes = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_VALID_EXCHANGES" && row[i] != NULL)
						contract.validExchanges = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_PRICE_MAGNIFIER" && row[i] != NULL)
						contract.priceMagnifier = boost::lexical_cast<long>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_UNDERLYING_CONTRACT_ID" && row[i] != NULL)
						contract.underConId = boost::lexical_cast<long>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_LONG_NAME" && row[i] != NULL)
						contract.longName = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_MONTH" && row[i] != NULL)
						contract.contractMonth = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_INDUSTRY" && row[i] != NULL)
						contract.industry = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_CATEGORY" && row[i] != NULL)
						contract.category = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_SUBCATEGORY" && row[i] != NULL)
						contract.subcategory = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_TIMEZONE_ID" && row[i] != NULL)
						contract.timeZoneId = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_TRADINGHOURS" && row[i] != NULL)
						contract.tradingHours = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_LIQUIDHOURS" && row[i] != NULL)
						contract.liquidHours = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_EVRULE" && row[i] != NULL)
						contract.evRule = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_EVRULE_MULTIPLIER" && row[i] != NULL)
						contract.evMultiplier = boost::lexical_cast<long>(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_RATINGS" && row[i] != NULL)
						contract.ratings = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_DESCRIPTION" && row[i] != NULL)
						contract.descAppend = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_TYPE" && row[i] != NULL)
						contract.bondType = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_COUPONTYPE" && row[i] != NULL)
						contract.couponType = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_CALLABLE" && row[i] != NULL)
						(std::string(row[i]) == "1" ? 
							contract.callable = true : 
							contract.callable = false);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_PUTABLE" && row[i] != NULL)
						(std::string(row[i]) == "1" ? 
							contract.putable = true : 
							contract.putable = false);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_COUPON" && row[i] != NULL)
						contract.couponType = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_CONVERTIBLE" && row[i] != NULL)
						(std::string(row[i]) == "1" ?
						contract.convertible = true :
						contract.convertible = false);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_MATURITY" && row[i] != NULL)
						contract.maturity = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_ISSUEDATE" && row[i] != NULL)
						contract.issueDate = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_NEXTOPTIONDATE" && row[i] != NULL)
						contract.nextOptionDate = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_NEXTOPTIONTYPE" && row[i] != NULL)
						contract.nextOptionType = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_NEXTOPTIONTYPE" && row[i] != NULL)
						contract.nextOptionType = std::string(row[i]);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_NEXTOPTIONPARTIAL" && row[i] != NULL)
						(std::string(row[i]) == "1" ?
						contract.nextOptionPartial = true :
						contract.nextOptionPartial = false);

					else if (std::string(reception_->fields[i].name)
						== "CONTRACT_DETAILS_BOND_NOTE" && row[i] != NULL)
						contract.notes = std::string(row[i]);

					else
						std::exception("unknown field provided");

				}

				// in case the cusip has been copied
				if (contract.summary.secType == "" && contract.cusip != "") {
				
					contract.summary.secId = contract.cusip;
					contract.summary.secIdType = "CUSIP";
				
				}
				
				// TODO: check for minimum structure requirements
				records_.insert(										// finally insert the contract details in the map
					std::pair<recordId, ContractDetails>(
					boost::lexical_cast<recordId>(id), contract));

				id++;													// in case there is no id included

			}
						
			return true;

		};

		bool tableContractRecordset::insert(const ContractDetails & details) {

			std::string fieldStr, valueStr;								// the two fields to build together
			
			if (details.summary.secIdType == "SIN") {					// first manage the identifiers

				fieldStr.append("CONTRACT_ISIN,");
				INSERT_SQL_STR(valueStr, details.summary.secId)
				valueStr.append(",");
			
				if (details.cusip != "") {
				
					fieldStr.append("CONTRACT_CUSIP,");
					INSERT_SQL_STR(valueStr, details.cusip)
					valueStr.append(",");

				}

			} else 

			if (details.summary.secIdType == "CUSIP") {					// case is CUSIP

				fieldStr.append("CONTRACT_CUSIP,");
				INSERT_SQL_STR(valueStr, details.summary.secId)
				valueStr.append(",");

			} else

			if (details.summary.secIdType == "SEDOL") {					// case is SEDOL

				fieldStr.append("CONTRACT_SEDOL,");
				INSERT_SQL_STR(valueStr, details.summary.secId)
				valueStr.append(",");

				if (details.cusip != "") {

					fieldStr.append("CONTRACT_CUSIP,");
					INSERT_SQL_STR(valueStr, details.cusip)
					valueStr.append(",");

				}

			} else

			if (details.summary.secIdType == "RIC") {					// case is RIC

				fieldStr.append("CONTRACT_RIC,");
				INSERT_SQL_STR(valueStr, details.summary.secId)
				valueStr.append(",");

				if (details.cusip != "") {

					fieldStr.append("CONTRACT_CUSIP,");
					INSERT_SQL_STR(valueStr, details.cusip)
					valueStr.append(",");

				}
			} else {													// in case nothng provided but the cusip is provided
				
				if (details.cusip != "") {

					fieldStr.append("CONTRACT_CUSIP,");
					INSERT_SQL_STR(valueStr, details.cusip)
					valueStr.append(",");

				}
			}

			if (details.summary.conId != 0) {							// isin provided

				fieldStr.append("CONTRACT_IBID,");
				INSERT_SQL_NUM(valueStr, details.summary.conId)
				valueStr.append(",");

			}

			if (details.summary.symbol != "") {						// symbol provided

				fieldStr.append("CONTRACT_SYMBOL,");
				INSERT_SQL_STR(valueStr, details.summary.symbol)
				valueStr.append(",");

			}

			if (details.summary.secType != "") {					// sectype provided

				fieldStr.append("CONTRACT_SECTYPE,");
				INSERT_SQL_STR(valueStr, details.summary.secType)
				valueStr.append(",");

			}

			if (details.summary.expiry != "") {						// sectype provided

				fieldStr.append("CONTRACT_EXPIRY,");
				INSERT_SQL_STR(valueStr, details.summary.expiry)
				valueStr.append(",");

			}

			if (details.summary.strike != 0.0) {					// strike provided

				fieldStr.append("CONTRACT_STRIKE,");
				INSERT_SQL_NUM(valueStr, details.summary.strike)
				valueStr.append(",");

			}

			if (details.summary.right != "") {						// right provided

				fieldStr.append("CONTRACT_RIGHT,");

				std::string val("0");								// convert into unsigned int
				if (details.summary.right == "P"   ) val = "1";		// default to 0
				if (details.summary.right == "PUT" ) val = "1";
				if (details.summary.right == "C"   ) val = "2";
				if (details.summary.right == "CALL") val = "2";

				valueStr
					.append(val)
					.append("',");

			}

			if (details.summary.multiplier != "") {					// multiplier

				fieldStr.append("CONTRACT_MULTIPLIER,");
				INSERT_SQL_STR(valueStr, details.summary.multiplier)
				valueStr.append(",");

			}

			if (details.summary.primaryExchange != "") {			// primary exchange

				fieldStr.append("CONTRACT_PRIMARY_EXCHANGE,");
				INSERT_SQL_STR(valueStr, details.summary.primaryExchange)
				valueStr.append(",");

			}

			if (details.summary.currency != "") {					// currency

				fieldStr.append("CONTRACT_CURRENCY,");
				INSERT_SQL_STR(valueStr, details.summary.currency)
				valueStr.append(",");

			}
			
			if (details.summary.tradingClass != "") {				// trading class

				fieldStr.append("CONTRACT_TRADING_CLASS,");
				INSERT_SQL_STR(valueStr, details.summary.tradingClass)
				valueStr.append(",");

			}

			if (details.marketName != "") {							// market name

				fieldStr.append("CONTRACT_DETAILS_MARKET_NAME,");
				INSERT_SQL_STR(valueStr, details.marketName)
				valueStr.append(",");

			}

			if (details.minTick != 0.0) {							// market name

				fieldStr.append("CONTRACT_DETAILS_MINTICK,");
				INSERT_SQL_NUM(valueStr, details.minTick)
				valueStr.append(",");

			}
			
			if (details.orderTypes != "") {							// order type string (long)

				fieldStr.append("CONTRACT_DETAILS_ORDERTYPES,");
				INSERT_SQL_STR(valueStr, details.orderTypes)
				valueStr.append(",");

			}

			if (details.validExchanges != "") {						// valid exchanges

				fieldStr.append("CONTRACT_DETAILS_VALID_EXCHANGES,");
				INSERT_SQL_STR(valueStr, details.validExchanges)
				valueStr.append(",");

			}
			
			if (details.priceMagnifier != 0.0) {					// price magnifier

				fieldStr.append("CONTRACT_DETAILS_PRICE_MAGNIFIER,");
				INSERT_SQL_NUM(valueStr, details.priceMagnifier)
				valueStr.append(",");
				
			}
			
			if (details.underConId != 0) {							// valid exchanges

				fieldStr.append("CONTRACT_DETAILS_UNDERLYING_CONTRACT_ID,");
				INSERT_SQL_NUM(valueStr, details.underConId)
				valueStr.append(",");

			}

			if (details.longName != "") {							// valid exchanges

				fieldStr.append("CONTRACT_DETAILS_LONG_NAME,");
				INSERT_SQL_STR(valueStr, details.longName)
				valueStr.append(",");
			
			}

			if (details.contractMonth != "") {						// valid exchanges

				fieldStr.append("CONTRACT_DETAILS_MONTH,");
				INSERT_SQL_STR(valueStr, details.contractMonth)
				valueStr.append(",");

			}

			if (details.industry != "") {							// industry

				fieldStr.append("CONTRACT_DETAILS_INDUSTRY,");
				INSERT_SQL_STR(valueStr, details.industry)
				valueStr.append(",");

			}

			if (details.category != "") {							// category

				fieldStr.append("CONTRACT_DETAILS_CATEGORY,");
				INSERT_SQL_STR(valueStr, details.category)
				valueStr.append(",");

			}

			if (details.subcategory != "") {						// subcategory

				fieldStr.append("CONTRACT_DETAILS_SUBCATEGORY,");
				INSERT_SQL_STR(valueStr, details.subcategory)
				valueStr.append(",");

			}

			if (details.timeZoneId != "") {						// timezone Id

				fieldStr.append("CONTRACT_DETAILS_TIMEZONE_ID,");
				INSERT_SQL_STR(valueStr, details.timeZoneId)
				valueStr.append(",");

			}

			if (details.tradingHours != "") {					// timezone Id

				fieldStr.append("CONTRACT_DETAILS_TRADINGHOURS,");
				INSERT_SQL_STR(valueStr, details.tradingHours)
				valueStr.append(",");

			}

			if (details.liquidHours != "") {						// timezone Id

				fieldStr.append("CONTRACT_DETAILS_LIQUIDHOURS,");
				INSERT_SQL_STR(valueStr, details.liquidHours)
				valueStr.append(",");

			}

			if (details.evRule != "") {								// ev rule

				fieldStr.append("CONTRACT_DETAILS_EVRULE,");
				INSERT_SQL_STR(valueStr, details.evRule)
				valueStr.append(",");

			}

			if (details.evMultiplier != 0.0) {						// ev multiplier

				fieldStr.append("CONTRACT_DETAILS_EVRULE_MULTIPLIER,");
				INSERT_SQL_NUM(valueStr, details.evMultiplier)
				valueStr.append(",");

			}

			if (details.ratings != "") {						// ratings

				fieldStr.append("CONTRACT_DETAILS_BOND_RATINGS,");
				INSERT_SQL_STR(valueStr, details.ratings)
				valueStr.append(",");

			}

			if (details.descAppend != "") {						// description

				fieldStr.append("CONTRACT_DETAILS_BOND_DESCRIPTION,");
				INSERT_SQL_STR(valueStr, details.descAppend)
				valueStr.append(",");

			}

			if (details.bondType != "") {						// type

				fieldStr.append("CONTRACT_DETAILS_BOND_TYPE,");
				INSERT_SQL_STR(valueStr, details.bondType)
				valueStr.append(",");

			}

			if (details.couponType != "") {						// description

				fieldStr.append("CONTRACT_DETAILS_BOND_COUPONTYPE,");
				INSERT_SQL_STR(valueStr, details.couponType)
				valueStr.append(",");

			}

			if (details.callable == true) {						// bool callable

				fieldStr.append("CONTRACT_DETAILS_BOND_CALLABLE,");
				
				valueStr
					.append("TRUE")
					.append(",");

			} else {
			
				fieldStr.append("CONTRACT_DETAILS_BOND_CALLABLE,");

				valueStr
					.append("FALSE")
					.append(",");
			
			}

			if (details.putable == true) {						// bool putable

				fieldStr.append("CONTRACT_DETAILS_BOND_PUTABLE,");

				valueStr
					.append("TRUE")
					.append(",");

			}
			else {

				fieldStr.append("CONTRACT_DETAILS_BOND_PUTABLE,");

				valueStr
					.append("FALSE")
					.append(",");

			}

			if (details.coupon != 0.0) {						// coupon

				fieldStr.append("CONTRACT_DETAILS_BOND_COUPON,");
				INSERT_SQL_NUM(valueStr, details.evMultiplier)
				valueStr.append(",");

			}

			if (details.convertible == true) {					// bool convertible

				fieldStr.append("CONTRACT_DETAILS_BOND_CONVERTIBLE,");
				
				valueStr
					.append("TRUE")
					.append(",");

			}
			else {

				fieldStr.append("CONTRACT_DETAILS_BOND_CONVERTIBLE,");
				
				valueStr
					.append("FALSE")
					.append(",");

			}

			if (details.maturity != "") {						// maturity

				fieldStr.append("CONTRACT_DETAILS_BOND_MATURITY,");
				INSERT_SQL_STR(valueStr, details.maturity)
				valueStr.append(",");

			}
			
			if (details.issueDate != "") {						// issue date

				fieldStr.append("CONTRACT_DETAILS_BOND_ISSUEDATE,");
				INSERT_SQL_STR(valueStr, details.issueDate)
				valueStr.append(",");

			}
			
			if (details.nextOptionDate != "") {						// next option date

				fieldStr.append("CONTRACT_DETAILS_BOND_NEXTOPTIONDATE,");
				INSERT_SQL_STR(valueStr, details.nextOptionDate)
				valueStr.append(",");

			}

			if (details.nextOptionType != "") {						// next option type

				fieldStr.append("CONTRACT_DETAILS_BOND_NEXTOPTIONTYPE,");
				INSERT_SQL_STR(valueStr, details.nextOptionType)
				valueStr.append(",");

			}
			
			if (details.nextOptionPartial == true) {					// bool convertible

				fieldStr.append("CONTRACT_DETAILS_BOND_NEXTOPTIONPARTIAL,");
				
				valueStr
					.append("TRUE")
					.append(",");

			}
			else {

				fieldStr.append("CONTRACT_DETAILS_BOND_NEXTOPTIONPARTIAL,");

				valueStr
					.append("FALSE")
					.append(",");

			}

			if (details.notes != "") {						// next option type

				fieldStr.append("CONTRACT_DETAILS_BOND_NOTE,");
				INSERT_SQL_STR(valueStr, details.notes)
				valueStr.append(",");

			}

			fieldStr.pop_back();							// erase extra characters
			valueStr.pop_back();

			std::string insertStatement("INSERT INTO table_contract (");
			insertStatement
				.append(fieldStr)
				.append(") VALUES (")
				.append(valueStr)
				.append(")");

			if (mysql_query(connection_, insertStatement.c_str()) != 0)		// throw on an error
				throw std::exception(mysql_error(connection_));

			return true;													// return true otherwise

		}

		bool tableContractRecordset::deleteQ(const std::string & deleteStr) {

			mysql_query(												// query to run
				connection_,
				deleteStr.c_str());

			// todo: error management
			return true;

		}
	}
}