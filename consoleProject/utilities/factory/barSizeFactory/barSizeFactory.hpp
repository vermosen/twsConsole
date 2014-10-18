#ifndef bar_size_factory_hpp
#define bar_size_factory_hpp

#include <oh/enumerations/typefactory.hpp>
#include <IBString.h>
#include "utilities/type/barSize.hpp"

namespace IB {

	namespace utilities {
	
		class barSizeFactory :

			private ObjectHandler::RegistryManager<IB::barSize, ObjectHandler::EnumTypeRegistry> {

		public:

			barSizeFactory() {};
			barSizeFactory(const barSizeFactory &) {};
			~barSizeFactory() {};

			barSizeFactory & operator =(const barSizeFactory &);

			IB::barSize  operator () (const IB::IBString &);
			IB::IBString operator () (const IB::barSize  &);

			void registerType(const std::string &, void *);

		};	
	
	}

}

#endif