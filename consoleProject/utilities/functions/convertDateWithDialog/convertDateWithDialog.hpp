#ifndef convert_date_with_dialog_hpp
#define convert_date_with_dialog_hpp

// stl headers
#include <string>

// boost components
#include <boost/lexical_cast.hpp>

// thOth components
#include <thOth/time/DateTime.hpp>

// twsapi
#include "utilities/type/all.hpp"
#include "utilities/define.hpp"

// optionally opens a dialog with the user
// and safely convert the result in a dateTime objet
thOth::dateTime convertDateWithDialog(
	const std::string & dateName = std::string("date"),
	std::string dtStr = std::string());

#endif