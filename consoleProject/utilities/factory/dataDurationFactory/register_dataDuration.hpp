#ifndef register_data_duration_hpp
#define register_data_duration_hpp

#include <utilities/factory/dataDurationFactory/dataDurationFactory.hpp>

namespace IB {

	namespace utilities {

		void registerDataDuration() {

			dataDurationFactory factory;

			factory.registerType("S", new IB::dataDuration(IB::second));
			factory.registerType("D", new IB::dataDuration(IB::day   ));
			factory.registerType("W", new IB::dataDuration(IB::week  ));

		};

	}

}

#endif
