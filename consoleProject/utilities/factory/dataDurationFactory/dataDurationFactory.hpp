#ifndef data_duration_factory_hpp
#define data_duration_factory_hpp

#include <oh/enumerations/typefactory.hpp>

#include <IBString.h>

#include "utilities/type/dataDuration.hpp"

namespace IB {

	namespace utilities {
	
		class dataDurationFactory :

			private ObjectHandler::RegistryManager<IB::dataDuration, ObjectHandler::EnumTypeRegistry> {

		public:

			 dataDurationFactory()                            {};
			 dataDurationFactory(const dataDurationFactory &) {};
			~dataDurationFactory()                            {};

			dataDurationFactory & operator =(const dataDurationFactory &);

			IB::dataDuration operator()(const IB::IBString     &           );
			IB::IBString     operator()(const IB::dataDuration &, const int);

			void registerType(const std::string &, void *);

		};	
	}
}

#endif