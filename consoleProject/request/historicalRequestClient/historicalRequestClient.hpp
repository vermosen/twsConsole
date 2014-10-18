/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#ifndef historical_request_client_hpp
#define historical_request_client_hpp

#include <memory>

#include <stdio.h>																		// printf()
#include <time.h>

#include <thOth/time/timeseries.hpp>
#include <thOth/bar/bar.hpp>

#include "request/request.hpp"
#include "utilities/conversion/convertDateTime/convertDateTime.hpp"
#include "utilities/factory/barSizeFactory/barSizeFactory.hpp"							// factories
#include "utilities/factory/dataTypeFactory/dataTypeFactory.hpp"
#include "utilities/factory/dataDurationFactory/dataDurationFactory.hpp"

namespace IB {

	class EPosixClientSocket;
	struct Contract;

	class historicalRequestClient : public requestClient {

	private:			

		historicalRequestClient() = delete;										// no default, cc ctor and assignement op
		historicalRequestClient(const historicalRequestClient &) = delete;
		historicalRequestClient & operator =(const historicalRequestClient &) = delete;
																			
	public:

		historicalRequestClient(const Contract &,							// public ctor
								const thOth::dateTime &,
								const barSize bs = barSize::oneSecond,
								const int lenght = 1,
								const dataDuration dur = dataDuration::day,
								const dataType = dataType::trade);

		~historicalRequestClient() {};										// destructor

		// const iterators
		thOth::timeSeries<thOth::bar>::const_iterator cbegin () const { return bars_.cbegin(); };
		thOth::timeSeries<thOth::bar>::const_iterator cend   () const { return bars_.cend()  ; };

		thOth::timeSeries<thOth::bar>::const_reverse_iterator crbegin () const { return bars_.crbegin (); };
		thOth::timeSeries<thOth::bar>::const_reverse_iterator crend   () const { return bars_.crend   (); };

		void processMessages();

		// accessors
		inline void clear() { bars_.clear(); };

	protected:

		void requestHistoricalData();										// request data

	private:

		thOth::dateTime endDate_  ;											// the end date
		int length_               ;											// lenght of the period
		barSize barSize_		  ;											// bar size
		dataDuration dataDuration_;											// data duration
		dataType dataType_		  ;											// data Type

		thOth::timeSeries<thOth::bar> bars_;         						// bars

		// implemented interface
		void historicalData(TickerId reqId, const IBString& date, double open, double high,
			double low, double close, int volume, int barCount, double WAP, int hasGaps);

		bool isEndOfHistoricalData(const IBString& Date) {					// check if historical data is finished

			endOfData_ = 1 + strncmp((const char*)Date.data(), "finished", 8);
			return endOfData_;

		}

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
		void contractDetails(int reqId, const ContractDetails& contractDetails) {};
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