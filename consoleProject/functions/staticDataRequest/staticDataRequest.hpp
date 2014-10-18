#ifndef tws_function_static_data_request
#define tws_function_static_data_request

#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#include <boost/thread.hpp>

// thOth components
#include <thOth/time/DateTime.hpp>

#include "request/staticDataRequestClient/staticDataRequestClient.hpp"
#include "recordset/tableContractRecordset/tableContractRecordset.hpp"

// this procedure is meant to request 
// missing static data about a given contract
// opt1
void staticDataRequest(const std::string & code,
					   bool deletionPolicy = false);

#endif