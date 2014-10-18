#ifndef register_bar_size_hpp
#define register_bar_size_hpp

#include <utilities/factory/barSizeFactory/barSizeFactory.hpp>

namespace IB {

	namespace utilities {

		void registerBarSize() {

			barSizeFactory factory;

			factory.registerType("1 sec"       , new IB::barSize(IB::oneSecond     ));
			factory.registerType("5 secs"      , new IB::barSize(IB::fiveSeconds   ));
			factory.registerType("15 secs"     , new IB::barSize(IB::fifteenSeconds));
			factory.registerType("30 secs"     , new IB::barSize(IB::thirtySeconds ));
			factory.registerType("1 min"       , new IB::barSize(IB::oneMinute     ));
			factory.registerType("2 mins"      , new IB::barSize(IB::twoMinutes    ));
			factory.registerType("3 mins"      , new IB::barSize(IB::threeMinutes  ));
			factory.registerType("5 mins"      , new IB::barSize(IB::fiveMinutes   ));
			factory.registerType("15 mins"     , new IB::barSize(IB::fifteenMinutes));
			factory.registerType("30 mins"     , new IB::barSize(IB::thirtyMinutes ));
			factory.registerType("1 hour"      , new IB::barSize(IB::oneHour       ));
			factory.registerType("1 day"       , new IB::barSize(IB::oneDay        ));
			factory.registerType("unknown size", new IB::barSize(IB::unknownSize   ));

		};

	}

}

#endif
