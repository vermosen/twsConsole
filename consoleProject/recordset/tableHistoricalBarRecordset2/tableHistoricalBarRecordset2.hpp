#ifndef table_historical_bar_recordset_2_hpp
#define table_historical_bar_recordset_2_hpp

#include <thOth/bar/bar.hpp>
#include <thOth/time/DateTime.hpp>
#include <thOth/time/timeSeries.hpp>

#include "contract.h"
#include "recordset/recordset2.hpp"
#include "utilities/conversion/convertDateTime/convertDateTime.hpp"

namespace IB {

	namespace dataBase {

		class tableHistoricalBarRecordset2 
			: public recordset2<thOth::bar, 
							    thOth::dateTime, 
							    thOth::timeSeries> {

			public:

				 tableHistoricalBarRecordset2(MYSQL *);
				 ~tableHistoricalBarRecordset2() {};

				tableHistoricalBarRecordset2 & operator =(const tableHistoricalBarRecordset2 &);

				// recordset interface
				bool selectStr(const std::string &);					// run a select statement
				bool deleteStr(const std::string &);					// delete records 

				// insert
				bool insert(
					const std::pair<recordId, ContractDetails> &, 
					const thOth::timeSeries<thOth::bar> &);
				
			protected:

				tableHistoricalBarRecordset2() {};
				
		};
	}
}

#endif 