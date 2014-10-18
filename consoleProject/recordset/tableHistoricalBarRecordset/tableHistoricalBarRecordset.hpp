#ifndef table_historical_bar_recordset_hpp
#define table_historical_bar_recordset_hpp

#include <thOth/bar/bar.hpp>

#include "recordset/recordset.hpp"
//#include "utilities/conversion/convertDatetime/convertDatetime.hpp"

namespace IB {

	namespace dataBase {

		class barRecord {

		public:

			barRecord(recordId instrumentId,
				      const thOth::timeSeries<thOth::bar> & bars,
				      const std::string & exchange);
			barRecord(const barRecord &);
			~barRecord() {};

			recordId        instrumentIdentifier () const { return id_      ; };
			thOth::timeSeries<thOth::bar> & bars ()       { return bars_    ; };
			std::string                 exchange () const { return exchange_; };

		protected:

			recordId                      id_      ;					// instrument db identifier
			thOth::timeSeries<thOth::bar> bars_    ;
			std::string                   exchange_;

		};

		class tableHistoricalBarRecordset : public recordset<barRecord> {

			public:

				 tableHistoricalBarRecordset(MYSQL *);
				 tableHistoricalBarRecordset(const tableHistoricalBarRecordset &);
				~tableHistoricalBarRecordset();

				tableHistoricalBarRecordset & operator =(const tableHistoricalBarRecordset &);

				bool selectQ(const std::string &);						// run a select statement
				bool deleteQ(const std::string &);						// delete records 
				bool insert (const barRecord   &);						// insert a bar
				

			protected:

				tableHistoricalBarRecordset() {};
				
		};
	}
}

#endif 