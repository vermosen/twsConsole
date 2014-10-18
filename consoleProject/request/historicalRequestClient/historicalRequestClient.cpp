/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "request/historicalRequestClient/historicalRequestClient.hpp"

namespace IB {

	historicalRequestClient::historicalRequestClient(						// ctor
		const Contract & ct,
		const thOth::dateTime & dt,
		const barSize bar,
		const int length,
		const dataDuration dur,
		const dataType type) 
		
		: requestClient (ct),
		  endDate_      (dt    ),
		  length_       (length),
		  barSize_      (bar   ),
		  dataDuration_ (dur   ),
		  dataType_     (type  ) {}

	void historicalRequestClient::requestHistoricalData() {

		m_pClient->reqHistoricalData(										// call the corresponding EClientSocketBase method
			id_,															// request id
			contract_,														// contract
			convertDateTime(endDate_),										// date
			IB::utilities::dataDurationFactory()(dataDuration_, length_),	// whole day
			IB::utilities::barSizeFactory     ()(barSize_),					// 1 min bar
			IB::utilities::dataTypeFactory    ()(dataType_),				// dataType: only trades
			1,																// only data with regular trading hours
			1);																// date format: yyyymmdd{ space }{space}hh:mm : dd
	
		m_sleepDeadline = time(NULL) + REQUEST_DEADLINE;					// set request deadline to "now + n seconds"
		m_state = ST_REQUEST_ACK;

	}

	void historicalRequestClient::processMessages() {

		fd_set readSet, writeSet;

		struct timeval tval;
		tval.tv_usec = 0;
		tval.tv_sec = 0;

		time_t now = time(NULL);

		switch (m_state) {

		case ST_REQUEST:
			requestHistoricalData();
			break;

		// in case of pacing violation, stalled on ST_REQUEST_HACK -> need to be fixed
		case ST_REQUEST_ACK: 
			//if (m_sleepDeadline < now) throw requestTimeoutException(id_);
			break;

		case ST_PING:
			reqCurrentTime();
			m_state = ST_PING_ACK;
			break;

		case ST_PING_ACK:
			if (m_sleepDeadline < now) throw requestTimeoutException(id_);
			break;

		case ST_IDLE:
			if (m_sleepDeadline < now) {

				m_state = ST_PING;
				return;

			}
			break;
		}

		if (m_sleepDeadline > 0)											// initialize timeout with m_sleepDeadline - now
			tval.tv_sec = static_cast<long>(m_sleepDeadline - now);

		if (m_pClient->fd() >= 0) {

			FD_ZERO(&readSet);
			writeSet = readSet;

			FD_SET(m_pClient->fd(), &readSet);

			if (!m_pClient->isOutBufferEmpty())
				FD_SET(m_pClient->fd(), &writeSet);

			int ret = select(m_pClient->fd() + 1, &readSet, &writeSet, NULL, &tval);

			if (ret == 0)													// timeout
				return;

			if (ret < 0) {													// error
				disconnect();
				return;
			}

			if (FD_ISSET(m_pClient->fd(), &writeSet))
				m_pClient->onSend();										// socket is ready for writing

			if (m_pClient->fd() < 0)
				return;

			if (FD_ISSET(m_pClient->fd(), &readSet))
				m_pClient->onReceive();										// socket is ready for reading

		}
	}

	void historicalRequestClient::historicalData(
		TickerId reqId,
		const IBString& date,
		double open,
		double high,
		double low,
		double close,
		int volume,
		int barCount,
		double WAP,
		int hasGaps) {
		
		if (isEndOfHistoricalData(date)) {									// control for EoF

			notifyObservers();
			disconnect();
			return;

		}

		bars_.insert(std::pair<thOth::dateTime, thOth::bar>(
			convertDateTime(date),
			thOth::bar(
				open,
				close,
				high,
				low,
				IB::ToPeriod(barSize_),										// we need a factory
				volume)));

	}
}
