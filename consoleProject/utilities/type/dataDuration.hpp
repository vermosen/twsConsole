/*
 *
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#ifndef data_duration_hpp
#define data_duration_hpp

#include <IBString.h>

namespace IB {

	enum dataDuration : unsigned int{

		second          = 0,
		day             = 1,
		week            = 2,
		unknownDuration = 3

	};

	// conversion into the corresponding IB strings
	inline const IBString ToString(dataDuration v) {

		switch (v) {

			case second         : return "S"           ;
			case day            : return "D"           ;
			case week           : return "W"           ;
			case unknownDuration: return "unknown type";

			default: return "unkown type";

		}
	}
}



#endif