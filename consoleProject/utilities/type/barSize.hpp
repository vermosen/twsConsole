/*
 *
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#ifndef bar_size_hpp
#define bar_size_hpp

#include <IBString.h>

#include <boost/date_time.hpp>
#include "thOth/time/period.hpp"

namespace IB {
	
	enum barSize : unsigned char {

		oneSecond      = 0,
		fiveSeconds    = 1,
		fifteenSeconds = 2,
		thirtySeconds  = 3,
		oneMinute      = 4,
		twoMinutes     = 5,
		threeMinutes   = 6,
		fiveMinutes    = 7,
		fifteenMinutes = 8,
		thirtyMinutes  = 9,
		oneHour        = 10,
		oneDay         = 11,
		unknownSize    = 12

	};

	// conversion into the corresponding IB strings
	inline const IBString ToString(barSize v) {

		switch (v) {

			case oneSecond     : return "1 secs"     ;
			case fiveSeconds   : return "5 secs"     ;
			case fifteenSeconds: return "15 secs"    ;
			case thirtySeconds : return "30 secs"    ;
			case oneMinute     : return "1 min"      ;
			case twoMinutes    : return "2 mins"     ;
			case threeMinutes  : return "3 mins"     ;
			case fiveMinutes   : return "5 mins"     ;
			case fifteenMinutes: return "15 mins"    ;
			case thirtyMinutes : return "30 mins"    ;
			case oneHour       : return "1 hour"     ;
			case oneDay        : return "1 day"      ;
			case unknownSize   : return "unkown size";
			default            : return "unkown size";
		
		}
	}

	// conversion into the corresponding boost::posix_time::time_duration
	inline const boost::posix_time::time_duration ToTimeDuration(barSize v) {

		switch (v) {

			case oneSecond      : return boost::posix_time::seconds(1)    ;
			case fiveSeconds    : return boost::posix_time::seconds(5)    ;
			case fifteenSeconds : return boost::posix_time::seconds(15)   ;
			case thirtySeconds  : return boost::posix_time::seconds(30)   ;
			case oneMinute      : return boost::posix_time::minutes(1)    ;
			case twoMinutes     : return boost::posix_time::minutes(2)    ;
			case threeMinutes   : return boost::posix_time::minutes(3)    ;
			case fiveMinutes    : return boost::posix_time::minutes(5)    ;
			case fifteenMinutes : return boost::posix_time::minutes(15)	  ;
			case thirtyMinutes  : return boost::posix_time::minutes(30)   ;
			case oneHour        : return boost::posix_time::hours  (1)    ;
			case oneDay         : return boost::posix_time::hours  (24)   ;
			case unknownSize    : throw std::exception("unknown bar size");
			default             : throw std::exception("unknown bar size");

		}
	}

	// conversion into the corresponding thOth::period
	inline const thOth::period ToPeriod(barSize v) {

		switch (v) {

		case oneSecond      : return thOth::period(thOth::second, 1);
		case fiveSeconds    : return thOth::period(thOth::second, 5);
		case fifteenSeconds : return thOth::period(thOth::second, 15);
		case thirtySeconds  : return thOth::period(thOth::second, 30);
		case oneMinute      : return thOth::period(thOth::minute, 1);
		case twoMinutes     : return thOth::period(thOth::minute, 2);
		case threeMinutes   : return thOth::period(thOth::minute, 3);
		case fiveMinutes    : return thOth::period(thOth::minute, 5);
		case fifteenMinutes : return thOth::period(thOth::minute, 15);
		case thirtyMinutes  : return thOth::period(thOth::minute, 30);
		case oneHour        : return thOth::period(thOth::hour, 1);
		case oneDay         : return thOth::period(thOth::day, 1);
		case unknownSize    : throw std::exception("unknown bar size");
		default             : throw std::exception("unknown bar size");

		}
	}
}



#endif