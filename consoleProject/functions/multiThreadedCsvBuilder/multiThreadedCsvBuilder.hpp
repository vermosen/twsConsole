#ifndef tws_function_multi_threaded_csv_builder
#define tws_function_multi_threaded_csv_builder

#include <thread>

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#include <boost/numeric/ublas/matrix.hpp>

// twsapi
#include "utilities/type/all.hpp"
#include "utilities/settings/settings.hpp"
#include "utilities/define.hpp"

#define CSVPATH  "C://Temp/"

// this procedure is meant to test multi-threading
// it separates a lin alg calculation in two pieces
// and merge the resulting values
void multiThreadedCsvBuilder();

#endif