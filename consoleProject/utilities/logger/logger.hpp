/*
*
* custom TwsApi
* Copyright (C) 2014 Jean-Mathieu Vermosen
*
*/

#ifndef logger_hpp
#define logger_hpp

#include <thOth/utilities/csvBuilder.hpp>

namespace IB {

	// a basic logger class
	class logger : protected thOth::utilities::csvBuilder {

	public:

		logger(const std::string & str) : csvBuilder(str) {}; 	// specifies the file path
		logger(const logger & o       ) = delete;				// no copy ctor

		inline void path(const std::string & path_) { csvBuilder::path(path_); };
																// set the current path
		void push_back(const std::string &);

	};

}

#endif