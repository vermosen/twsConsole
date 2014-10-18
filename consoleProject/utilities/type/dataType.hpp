/*
 *
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#ifndef data_type_hpp
#define data_type_hpp

#include <IBString.h>

namespace IB {

	enum dataType : unsigned char {

		trade                   = 0,
		midPoint                = 1,
		bid                     = 2,
		ask                     = 3,
		bidAsk                  = 4,
		historicalVolatility    = 5,
		optionImpliedVolatility = 6,
		unknownType             = 7
	
	};

	// conversion into the corresponding IB strings
	inline const IBString ToString(dataType v) {

		switch (v) {

			case trade                  : return "TRADES"                   ;
			case midPoint               : return "MIDPOINT"                 ;
			case bid                    : return "BID"                      ;
			case ask                    : return "ASK"                      ;
			case bidAsk                 : return "BID_ASK"                  ;
			case historicalVolatility   : return "HISTORICAL_VOLATILITY"    ;
			case optionImpliedVolatility: return "OPTION_IMPLIED_VOLATILITY";
			case unknownType            : return "unkown type"              ;

			default                     : return "unkown type"              ;

		}
	}
}



#endif