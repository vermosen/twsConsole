#ifndef factory_all_hpp
#define factory_all_hpp

#include <utilities/factory/barSizeFactory/register_barSize.hpp>
#include <utilities/factory/dataDurationFactory/register_dataDuration.hpp>
#include <utilities/factory/dataTypeFactory/register_dataType.hpp>

// call all the register functions
namespace IB {

	namespace utilities {
	
		void registerAllFactories() {

			registerBarSize     ();
			registerDataDuration();
			registerDataType    ();

		}
	
	}

}


#endif