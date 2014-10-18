#include "utilities/conversion/convertDateTime/convertDateTime.hpp"

thOth::dateTime convertDateTime(const IB::IBString & dtStr) {

	return thOth::dateTime(								// smallest increments is second
		thOth::dateTime::years  (boost::lexical_cast<int>(dtStr.substr(0 , 4))) ,
		thOth::dateTime::months (boost::lexical_cast<int>(dtStr.substr(4 , 2))) ,
		thOth::dateTime::days   (boost::lexical_cast<int>(dtStr.substr(6 , 2))) ,
		thOth::dateTime::hours  (boost::lexical_cast<int>(dtStr.substr(10, 2))) ,
		thOth::dateTime::minutes(boost::lexical_cast<int>(dtStr.substr(13, 2))) ,
		thOth::dateTime::seconds(boost::lexical_cast<int>(dtStr.substr(16, 2))));

};

IB::IBString convertDateTime(const thOth::dateTime & date) {

	// bug with locale destructor, to be fixed in MSVC 2014...
#if (_MSC_VER <= 1800)

	// std::string to_iso_string(ptime) returns
	// a string in the form of YYYYMMDDTHHMMSS, 
	// fffffffff where T is the date - time separator.
	std::string temp = boost::posix_time::to_iso_string(date);

	IB::IBString ib(temp.substr(0, 8)
		.append("  ")
		.append(temp.substr(9, 2))
		.append(":")
		.append(temp.substr(11, 2))
		.append(":")
		.append(temp.substr(13, 2)));

#else

	std::stringstream stream;
	boost::posix_time::time_facet facet;
	facet.format("%Y%m%d  %H:%M:%S");
	stream.imbue(std::locale(std::locale::classic(), &facet));
	stream << date;

	IBString ib(stream.str());

#endif

	return ib;


};

thOth::dateTime convertDateTime_sql(const std::string & dtStr) {

	return thOth::dateTime(								// smallest increments is second
		thOth::dateTime::years  (boost::lexical_cast<int>(dtStr.substr(0, 4))),
		thOth::dateTime::months (boost::lexical_cast<int>(dtStr.substr(5, 2))),
		thOth::dateTime::days   (boost::lexical_cast<int>(dtStr.substr(8, 2))),
		thOth::dateTime::hours  (boost::lexical_cast<int>(dtStr.substr(11, 2))),
		thOth::dateTime::minutes(boost::lexical_cast<int>(dtStr.substr(14, 2))),
		thOth::dateTime::seconds(boost::lexical_cast<int>(dtStr.substr(17, 2))));

}

std::string convertDateTime_sql(const thOth::dateTime & date) {

	std::string temp = boost::posix_time::to_iso_string(date);

	std::string sql(""); sql
		.append(temp.substr(0, 8))
		//.append(" ")
		.append(temp.substr(9, 6));

	return sql;

}