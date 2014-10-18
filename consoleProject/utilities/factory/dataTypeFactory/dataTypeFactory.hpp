/*
 *
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#ifndef data_type_factory_hpp
#define data_type_factory_hpp

#include <oh/enumerations/typefactory.hpp>
#include <IBString.h>
#include "utilities/type/dataType.hpp"

namespace IB {

	namespace utilities {
	
		class dataTypeFactory :

			private ObjectHandler::RegistryManager<IB::dataType, ObjectHandler::EnumTypeRegistry> {

		public:

			dataTypeFactory() {};
			dataTypeFactory(const dataTypeFactory &) {};
			~dataTypeFactory() {};

			dataTypeFactory & operator =(const dataTypeFactory &);

			IB::dataType operator()(const IB::IBString &);
			IB::IBString operator()(const IB::dataType &);

			void registerType(const std::string &, void *);

		};	
	
	}

}

#endif