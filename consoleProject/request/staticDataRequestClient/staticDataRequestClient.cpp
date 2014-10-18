/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "request/staticDataRequestClient/staticDataRequestClient.hpp"

namespace IB {

	staticDataRequestClient::staticDataRequestClient(const Contract & ct) : requestClient(ct) {};

	void staticDataRequestClient::requestStaticData() {
	
		requestId();										// generates a new id
		m_pClient->reqContractDetails(						// call the corresponding EClientSocketBase method
			id_,
			contract_);
		
		m_state = ST_REQUEST_ACK;
	
	}

	void staticDataRequestClient::processMessages() {

		fd_set readSet, writeSet;

		struct timeval tval;
		tval.tv_usec = 0;
		tval.tv_sec = 0;

		time_t now = time(NULL);

		switch (m_state) {

		case ST_REQUEST:
			requestStaticData();

		case ST_REQUEST_ACK:
			break;

		case ST_PING:
			reqCurrentTime();
			break;

		case ST_PING_ACK:
			if (m_sleepDeadline < now) {

				disconnect();
				return;
			
			}
			
			break;
		
		case ST_IDLE:
			if (m_sleepDeadline < now) {

				m_state = ST_PING;
				return;
			
			}
			break;
		}
		
		if (m_sleepDeadline > 0)							// initialize timeout with m_sleepDeadline - now
			tval.tv_sec = static_cast<long>(m_sleepDeadline - now);

		if (m_pClient->fd() >= 0) {

			FD_ZERO(&readSet);
			writeSet = readSet;

			FD_SET(m_pClient->fd(), &readSet);

			if (!m_pClient->isOutBufferEmpty())
				FD_SET(m_pClient->fd(), &writeSet);

			int ret = select(m_pClient->fd() + 1, &readSet, &writeSet, NULL, &tval);

			if (ret == 0)									// timeout
				return;

			if (ret < 0) {									// error
				disconnect();
				return;
			}

			if (FD_ISSET(m_pClient->fd(), &writeSet))				
				m_pClient->onSend();						// socket is ready for writing

			if (m_pClient->fd() < 0)
				return;

			if (FD_ISSET(m_pClient->fd(), &readSet))				
				m_pClient->onReceive();						// socket is ready for reading

		}
	}

	void staticDataRequestClient::contractDetails(			// eWrapper implementation 
		int reqId,
		const ContractDetails& contractDetails) {

		endOfData_ = true;
		disconnect();
		contractDetails_ = contractDetails;
		notifyObservers();
		return;

	}

}
