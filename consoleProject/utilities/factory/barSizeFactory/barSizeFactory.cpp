#include "utilities/factory/barSizeFactory/barSizeFactory.hpp"

namespace IB {

	namespace utilities {
		
		IB::barSize barSizeFactory::operator()(const IB::IBString & str) {
		
			if (ObjectHandler::RegistryManager<IB::barSize, ObjectHandler::EnumTypeRegistry>::checkType(str)) {

				return *(static_cast<IB::barSize *>(this->getType(str)));

			} else {

				return IB::unknownSize;

			}
		}

		IB::IBString barSizeFactory::operator()(const IB::barSize & bar) {
		
			// use the static definitions
			return IB::ToString(bar);

		}

		void barSizeFactory::registerType(const std::string & str, void * o) {
		
			ObjectHandler::RegistryManager<IB::barSize, ObjectHandler::EnumTypeRegistry>::registerType(str, o);
		
		}
	}
}