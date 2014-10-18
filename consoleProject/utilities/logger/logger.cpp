/*
*
* custom TwsApi
* Copyright (C) 2014 Jean-Mathieu Vermosen
*
*/

#include "utilities/logger/logger.hpp"

namespace IB {

	void logger::push_back(const std::string & str) {		// simple push_back method for log

		add(str, rMax_ + 1, 1);								// sole call the add method

	};

}