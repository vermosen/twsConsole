/*
 *
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#ifndef id_generator_hpp
#define id_generator_hpp

#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#include <thOth/pattern/singleton.hpp>

#include <commonDefs.h>

namespace IB {

	// a basic id generator with concurrency management
	class idGenerator : public thOth::singleton<idGenerator> {

	public:

		 idGenerator ();					// default ctor
		~idGenerator () {};					// destructor
		
		TickerId next();					// the next id to generate

	private:
		
		TickerId lastId_;
		boost::mutex idMutex_;

	};

}

#endif