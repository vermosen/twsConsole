#ifndef convert_date_time
#define convert_date_time

#include <thOth/time/dateTime.hpp>
#include <IBString.h>

thOth::dateTime convertDateTime	   (const IB::IBString    &);	// parse a date string into some dateTime
IB::IBString    convertDateTime    (const thOth::dateTime &);	// date into string

thOth::dateTime convertDateTime_sql(const std::string     &);	// sql string into date
std::string     convertDateTime_sql(const thOth::dateTime &);	// date into sql string

#endif