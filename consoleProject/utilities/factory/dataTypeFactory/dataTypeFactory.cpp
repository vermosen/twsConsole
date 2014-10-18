/*
 *
 * custom TwsApi
 * Copyright (C) 2014 Jean-Mathieu Vermosen
 *
 */

#include "utilities/factory/dataTypeFactory/dataTypeFactory.hpp"

namespace IB {

	namespace utilities {

		dataTypeFactory & dataTypeFactory::operator = (const dataTypeFactory & o) {
		
			if (&o != this) {
				
				// members copy
			
			}

			return *this;
		
		}
		
		IB::dataType dataTypeFactory::operator()(const IB::IBString & str) {
		
			if (ObjectHandler::RegistryManager<IB::dataType, ObjectHandler::EnumTypeRegistry>::checkType(str)) {

				return *(static_cast<IB::dataType *>(this->getType(str)));

			} else {

				return IB::unknownType;

			}
		
		}

		IB::IBString dataTypeFactory::operator()(const IB::dataType & bar) {
		
			// use the static definitions
			return IB::ToString(bar);

		}

		void dataTypeFactory::registerType(const std::string & str, void * o) {
		
			ObjectHandler::RegistryManager<IB::dataType, ObjectHandler::EnumTypeRegistry>::registerType(str, o);
		
		}


	}

}