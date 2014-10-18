/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "request/request.hpp"

namespace IB {

	requestClient::requestClient(const Contract & ct)						// ctor

		: m_pClient(new EPosixClientSocket(this)),
		  m_state(ST_CONNECT),
		  m_sleepDeadline(0),
		  contract_(ct) {
	
		requestId();														// generate the id
	
	};

	bool requestClient::connect(
		const char *host,
		unsigned int port) {

		return m_pClient->eConnect2(											// trying to connect
			host, port, id_);

	}

	void requestClient::reqCurrentTime() {

		m_sleepDeadline = time(NULL) + PING_DEADLINE;						// set ping deadline to "now + n seconds"
		m_state = ST_PING_ACK;
		m_pClient->reqCurrentTime();

	}

	void requestClient::nextValidId(OrderId orderId) {

		m_state = ST_REQUEST;

	}

	void requestClient::currentTime(long time) {

		if (m_state == ST_PING_ACK) {

			time_t t = (time_t)time;
			struct tm * timeinfo = localtime(&t);
			time_t now = ::time(NULL);
			m_sleepDeadline = now + SLEEP_BETWEEN_PINGS;
			m_state = ST_IDLE;

		}
	}

	void requestClient::error(												// error management
		const int id,														// todo: create exceptions and throw
		const int errorCode,
		const IBString errorString) {

		if (errorCode == 2104) {											// information code management, we're not throwing
		
			TWS_LOG_V(
				std::string("request information: ")						// log
				.append("request object with id ")
				.append(boost::lexical_cast<std::string>(id_))
				.append("generated the following message: ")
				.append(errorString), 0)
		
		}
		else if (errorCode == 2106) {										// information code management, we're not throwing

			TWS_LOG_V(
				std::string("request information: ")						// log
				.append("request object with id ")
				.append(boost::lexical_cast<std::string>(id_))
				.append("generated the following message: ")
				.append(errorString), 0)

		}
		else if (errorCode == 1100) {										// if "Connectivity between IB and TWS has been lost"

			TWS_LOG_V(
				std::string("request error: ")								// log
				.append("request object with id ")
				.append(boost::lexical_cast<std::string>(id_))
				.append("lost the connection with IB server"), 0)

			disconnect();
			throw lostConnectionException(id_);

		}
		else if (errorCode == 200) {										// contract has no match

			TWS_LOG_V(
				std::string("request error: ")								// log
				.append("request object with id ")
				.append(boost::lexical_cast<std::string>(id_))
				.append("contract has no match"), 0)

			disconnect();
			throw unmatchedContractException(id_);

		} 
		else if (errorCode == 162){											// pacing violation

			TWS_LOG_V(
				std::string("request error: ")								// log
				.append("request object with id ")
				.append(boost::lexical_cast<std::string>(id_))
				.append("pacing violation"), 0)

			throw pacingViolationHistoricalException(id_);

		}
		else {																// unmanaged error


			disconnect();
			throw unknownException(id_);
			

		}
	}

	void requestClient::contractDetailsEnd(int reqId) {

		// no idea of it's usage
		std::cout << "contractDetailsEnd has been called" << std::endl;

	}

}
