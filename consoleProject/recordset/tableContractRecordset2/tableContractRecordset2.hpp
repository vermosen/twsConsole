#ifndef table_contract_recordset_2_hpp
#define table_contract_recordset_2_hpp

#include <contract.h>

#include <map>
#include <vector>

#include "recordset/recordset2.hpp"

#include <boost/lexical_cast.hpp>

namespace IB {

	namespace dataBase {

		typedef std::pair<recordId, ContractDetails> contractRecord;

		class tableContractRecordset2 
			: public recordset2<recordId, ContractDetails, std::map> {

			public:

				tableContractRecordset2  (MYSQL *);
				~tableContractRecordset2 () {};

				bool selectStr (const std::string &    );				// run a select statement
				bool deleteStr (const std::string &    );				// run a select statement
				bool insert    (const ContractDetails &);				// insert a contract detail in the database
				
		};
	}
}

#endif 