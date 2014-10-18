#include "functions/multiThreadedSetting/multiThreadedSetting.hpp"

void acquireTickerId(std::string & result) {					// returns a message

	boost::this_thread::sleep_for(								// sleep for a random time
		boost::chrono::milliseconds(100));
	
	result
		.append("thread number ")
		.append(boost::lexical_cast<std::string>(
			boost::this_thread::get_id()))
		.append(" get the id ")
		.append(boost::lexical_cast<std::string>(
			IB::settings::instance().idGen().next()));

	TWS_LOG_V(result, 1)										// log

}

void multiThreadedSetting() {

	std::cout
		<< "multi-threaded Settings Test"
		<< std::endl
		<< "----------------------------"
		<< std::endl;

	boost::timer tt;											// timer

	unsigned int const min_number =  2;							// min number of threads
	unsigned int const max_number = 20;							// max number of threads

	unsigned int threadNum =									// available hardware ressources
		boost::thread::hardware_concurrency();

	threadNum =													// define number of threads
		min(max(threadNum, min_number), max_number);

	threadNum = 20;												// enforce number of threads to max

	std::vector<boost::thread> threads (threadNum);				// trying to call testLog function
	std::vector<std::string>  messages (threadNum);				// the messages

	for (unsigned int i = 0; i < threadNum; i++)				// launches a new thread
		threads[i] = boost::thread(acquireTickerId, std::ref(messages[i]));
			
	for (unsigned int i = 0; i < threadNum; i++)				// join threads
		threads[i].join();

	for (unsigned int i = 0; i < threadNum; i++)				// read the messages

		std::cout 
			<< messages[i]
			<< std::endl;

	TWS_LOG_V(std::string("main thread ")
		.append(boost::lexical_cast<std::string>(
			boost::this_thread::get_id()))
		.append(" get the id ")
		.append(boost::lexical_cast<std::string>(
			IB::settings::instance().idGen().next())), 0)

	TWS_LOG_V(std::string("multi-threaded settings test executed in ")
		.append(boost::lexical_cast<std::string>(tt.elapsed()))
		.append(" seconds"), 0)

};