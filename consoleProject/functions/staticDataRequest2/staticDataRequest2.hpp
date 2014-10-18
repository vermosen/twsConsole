#ifndef tws_function_static_data_request_2
#define tws_function_static_data_request_2

#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#include <boost/thread.hpp>

// thOth components
#include <thOth/time/DateTime.hpp>

#include "utilities/type/all.hpp"
#include "utilities/settings/settings.hpp"
#include "utilities/define.hpp"
#include "request/staticDataRequestClient/staticDataRequestClient.hpp"
#include "recordset/tableContractRecordset/tableContractRecordset.hpp"

// second version of the staticDataRequest function with callback capacity
void staticDataRequest(bool deletionPolicy, 
					   const std::string & = std::string(""));

// callback Function
class staticDataCallBack : public IB::requestCallBack<IB::ContractDetails> {

	void operator()(const IB::ContractDetails &);

};

#endif
