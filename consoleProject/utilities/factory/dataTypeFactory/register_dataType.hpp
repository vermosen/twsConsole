/*
 *
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#ifndef register_data_type_hpp
#define register_data_type_hpp

#include <utilities/factory/dataTypeFactory/dataTypeFactory.hpp>

namespace IB {

	namespace utilities {

		void registerDataType() {

			dataTypeFactory factory;

			factory.registerType("TRADES"				    , new IB::dataType(IB::trade 				  ));
			factory.registerType("MIDPOINT"				    , new IB::dataType(IB::midPoint				  ));
			factory.registerType("BID"					    , new IB::dataType(IB::bid					  ));
			factory.registerType("ASK"					    , new IB::dataType(IB::ask					  ));
			factory.registerType("BID_ASK"				    , new IB::dataType(IB::bidAsk				  ));
			factory.registerType("HISTORICAL_VOLATILITY"    , new IB::dataType(IB::historicalVolatility   ));
			factory.registerType("OPTION_IMPLIED_VOLATILITY", new IB::dataType(IB::optionImpliedVolatility));
			factory.registerType("unkown size"              , new IB::dataType(IB::unknownType            ));

		};

	}

}

#endif
