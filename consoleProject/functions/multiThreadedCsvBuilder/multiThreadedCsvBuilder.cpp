#include "functions/multiThreadedCsvBuilder/multiThreadedCsvBuilder.hpp"

void insertUpperMatrix(thOth::utilities::csvBuilder & csv) {								

	boost::numeric::ublas::matrix<double> upperMatrix(50, 100, 0.0);

	for (unsigned int i = 0; i < upperMatrix.size1(); i++) {	// upper half matrix
	
		for (unsigned int j = 0; j < upperMatrix.size2(); j++)
			upperMatrix(i, j) = log((i + 1) * (j + 1));
	
	}

	csv.add(upperMatrix, 1, 1);
		
}

void insertLowerMatrix(thOth::utilities::csvBuilder & csv) {

	boost::numeric::ublas::matrix<double> lowerMatrix(50, 100, 0.0);

	for (unsigned int i = 0; i < lowerMatrix.size1(); i++) {	// lower half matrix

		for (unsigned int j = 0; j < lowerMatrix.size2(); j++)
			lowerMatrix(i, j) = log((i + 51) * (j + 1));

	}

	csv.add(lowerMatrix, 51, 1);
	
}

void multiThreadedCsvBuilder() {

	std::cout
		<< "multi-threaded csv builder test"
		<< std::endl
		<< "-------------------------------"
		<< std::endl;

	boost::timer tt;											// timer

	thOth::utilities::csvBuilder csv(							// shared csv file
		std::string(CSVPATH)
		.append("csvTest")
		.append("_")
		.append(boost::posix_time::to_iso_string(
			boost::posix_time::second_clock::local_time()))
		.append("_")
		.append(".csv"));

	boost::thread thread2(insertUpperMatrix, boost::ref(csv));
	boost::thread thread1(insertLowerMatrix, boost::ref(csv));

	thread2.join(); thread1.join();

	if (IB::settings::instance().verbosity() > 0)				// verbose

		TWS_LOG_V(std::string("multi-threaded csv builder test executed in ")
			.append(boost::lexical_cast<std::string>(tt.elapsed()))
			.append(" seconds"), 0)

};