#include "utilities/factory/dataDurationFactory/dataDurationFactory.hpp"

namespace IB {

	namespace utilities {
		
		IB::dataDuration dataDurationFactory::operator()(const IB::IBString & str) {
		
			if (ObjectHandler::RegistryManager<IB::dataDuration, ObjectHandler::EnumTypeRegistry>::checkType(str)) {

				return *(static_cast<IB::dataDuration *>(this->getType(str.substr(3, 1))));

			} else {

				return IB::unknownDuration;

			}
		}

		IB::IBString dataDurationFactory::operator()(const IB::dataDuration & bar, const int n) {
		
			// use the static definitions
			std::ostringstream oss;
			oss << n
				<< " "
				<< IB::ToString(bar);

			return oss.str();

		}

		void dataDurationFactory::registerType(const std::string & str, void * o) {
		
			ObjectHandler::RegistryManager<IB::dataDuration, ObjectHandler::EnumTypeRegistry>::registerType(str, o);
		
		}
	}
}