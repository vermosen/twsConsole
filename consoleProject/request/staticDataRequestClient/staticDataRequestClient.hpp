/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#ifndef static_data_request_client_hpp
#define static_data_request_client_hpp

#include <memory>

#include <stdio.h>																	// printf()
#include <time.h>

#include "request/request.hpp"
#include "utilities/conversion/convertDateTime/convertDateTime.hpp"

namespace IB {

	class EPosixClientSocket;
	struct Contract;

	class staticDataRequestClient : public requestClient {

	private:														
		staticDataRequestClient() = delete;											// no default ctor, cc ctor 
		staticDataRequestClient(const staticDataRequestClient &) = delete;			// or assignement operator	
		staticDataRequestClient & operator =(const staticDataRequestClient &) = delete;

	public:

		staticDataRequestClient(const Contract &);
		~staticDataRequestClient() {};												// destructor

		// accessors
		ContractDetails contractDetails() const { return contractDetails_; };		// contract details

		void processMessages();														// request interface

	private:

		void requestStaticData();													// request static data
		ContractDetails contractDetails_;											// the contract details returned

		// implemented interface
		void contractDetails(int reqId, const ContractDetails& contractDetails);

		// not implemented
		void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) {};
		void tickSize(TickerId tickerId, TickType field, int size) {};
		void tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta,
			double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {};
		void tickGeneric(TickerId tickerId, TickType tickType, double value) {};
		void tickString(TickerId tickerId, TickType tickType, const IBString& value) {};
		void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
			double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {};
		void orderStatus(OrderId orderId, const IBString &status, int filled,
			int remaining, double avgFillPrice, int permId, int parentId,
			double lastFillPrice, int clientId, const IBString& whyHeld) {};
		void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&) {};
		void openOrderEnd() {};
		void winError(const IBString &str, int lastError) {};
		void connectionClosed() {};
		void updateAccountValue(const IBString& key, const IBString& val,
			const IBString& currency, const IBString& accountName) {};
		void updatePortfolio(const Contract& contract, int position,
			double marketPrice, double marketValue, double averageCost,
			double unrealizedPNL, double realizedPNL, const IBString& accountName) {};
		void updateAccountTime(const IBString& timeStamp) {};
		void accountDownloadEnd(const IBString& accountName) {};
		void bondContractDetails(int reqId, const ContractDetails& contractDetails) {};
		void execDetails(int reqId, const Contract& contract, const Execution& execution) {};
		void execDetailsEnd(int reqId) {};
		void updateMktDepth(TickerId id, int position, int operation, int side,
			double price, int size) {};
		void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
			int side, double price, int size) {};
		void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {};
		void managedAccounts(const IBString& accountsList) {};
		void receiveFA(faDataType pFaDataType, const IBString& cxml) {};
		void historicalData(TickerId reqId, const IBString& date, double open, double high,
			double low, double close, int volume, int barCount, double WAP, int hasGaps) {};
		void scannerParameters(const IBString &xml) {};
		void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
			const IBString &distance, const IBString &benchmark, const IBString &projection,
			const IBString &legsStr) {};
		void scannerDataEnd(int reqId) {};
		void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
			long volume, double wap, int count) {};
		void fundamentalData(TickerId reqId, const IBString& data) {};
		void deltaNeutralValidation(int reqId, const UnderComp& underComp) {};
		void tickSnapshotEnd(int reqId) {};
		void marketDataType(TickerId reqId, int marketDataType) {};
		void commissionReport(const CommissionReport &commissionReport) {};
		void position(const IBString& account, const Contract& contract, int position, double avgCost) {};
		void positionEnd() {};
		void accountSummary(int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {};
		void accountSummaryEnd(int reqId) {};

	};

}
#endif