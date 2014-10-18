/*
*
* custom TwsApi
* Copyright (C) 2014 Jean-Mathieu Vermosen
*
*/

#ifndef request_hpp
#define request_hpp

#include <memory>																		// shared_ptr

#include <stdio.h>																		// printf()
#include <time.h>

#include <thOth/pattern/observable.hpp>

#include "EPosixClientSocket.h"															// tws components
#include "Ewrapper.h"
#include "EPosixClientSocketPlatform.h"
#include "Contract.h"

#include "request/requestException/requestException.hpp"								// exceptions
#include "utilities/define.hpp"															// utilities
#include "utilities/conversion/convertDateTime/convertDateTime.hpp"
#include "utilities/settings/settings.hpp"

#ifndef _MSC_VER
#include <sys/time.h>
#endif

#if defined __INTEL_COMPILER
# pragma warning (disable:869)
#elif defined __GNUC__
# pragma GCC diagnostic ignored "-Wswitch"
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif  /* __INTEL_COMPILER */

namespace IB {

	const int PING_DEADLINE       = 2 ;												// seconds
	const int REQUEST_DEADLINE    = 30;													
	const int SLEEP_BETWEEN_PINGS = 5 ;												

	class EPosixClientSocket;
	struct Contract;

	// base class for any concrete Ewrapper implementation
	// TODO: use observable functionality to call for receiver
	// TODO: turn into a template
	class requestClient : public EWrapper,
					public thOth::observable {

	private:

		requestClient              (                     ) = delete;				// no default ctor
		requestClient			   (const requestClient &) = delete;				// no copy ctor
		requestClient & operator = (const requestClient &) = delete;				// no assignement operator

	protected:

		enum state {																// client states

			ST_CONNECT,
			ST_REQUEST,
			ST_REQUEST_ACK,
			ST_PING,
			ST_PING_ACK,
			ST_IDLE

		};

		inline void requestId() { id_ = IB::settings::instance().idGen().next(); };	// request a new interactive broker uid
		void reqCurrentTime();														// get the current time (TODO: use stl)

		virtual void processMessages() = 0;											// pure virtual method

	public:

		requestClient(const Contract &);											// provides the contract
		virtual ~requestClient() {};												// destructor

		// accessors
		bool endOfData     () const { return endOfData_     ; };					// end of data flag
		Contract contract  () const { return contract_      ; };   					// read access for contract
		int marketDataType () const { return marketDataType_; };   					// read access for market data type
		TickerId requestId () const { return id_            ; };					// read access for the id

		bool connect(																// connect method
			const char * host,
			unsigned int port);

		inline void disconnect () const { m_pClient->eDisconnect       (); };
		inline bool isConnected() const { return m_pClient->isConnected(); };

	protected: 

		bool endOfData_;															// indicate whether the file has been read
		int marketDataType_;														// market data type

		Contract contract_;															// the initial contract
		TickerId id_;																// id of the request

		std::shared_ptr<EPosixClientSocket> m_pClient;								// ptr on posix client

		state m_state;																// current state
		time_t m_sleepDeadline;														// sleep deadline

	protected:

		// implemented interface
		void contractDetailsEnd(int reqId);
		void error(const int id, const int errorCode, const IBString errorString);
		void currentTime(long time);
		void nextValidId(OrderId orderId);

		// not implemented here
		/*
		virtual void tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) = 0;
		virtual void tickSize( TickerId tickerId, TickType field, int size) = 0;
		virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
			double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) = 0;
		virtual void tickGeneric(TickerId tickerId, TickType tickType, double value) = 0;
		virtual void tickString(TickerId tickerId, TickType tickType, const IBString& value) = 0;
		virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
		   double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) = 0;
		virtual void orderStatus( OrderId orderId, const IBString &status, int filled,
		   int remaining, double avgFillPrice, int permId, int parentId,
		   double lastFillPrice, int clientId, const IBString& whyHeld) = 0;
		virtual void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&) = 0;
		virtual void openOrderEnd() = 0;
		virtual void winError( const IBString &str, int lastError) = 0;
		virtual void connectionClosed() = 0;
		virtual void updateAccountValue(const IBString& key, const IBString& val,
			const IBString& currency, const IBString& accountName) = 0;
		virtual void updatePortfolio( const Contract& contract, int position,
			double marketPrice, double marketValue, double averageCost,
			double unrealizedPNL, double realizedPNL, const IBString& accountName) = 0;
		virtual void updateAccountTime(const IBString& timeStamp) = 0;
		virtual void accountDownloadEnd(const IBString& accountName) = 0;
		virtual void contractDetails( int reqId, const ContractDetails& contractDetails) = 0;
		virtual void bondContractDetails( int reqId, const ContractDetails& contractDetails) = 0;
		virtual void execDetails( int reqId, const Contract& contract, const Execution& execution) =0;
		virtual void execDetailsEnd( int reqId) =0;
		virtual void updateMktDepth(TickerId id, int position, int operation, int side,
			double price, int size) = 0;
		virtual void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
			int side, double price, int size) = 0;
		virtual void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) = 0;
		virtual void managedAccounts( const IBString& accountsList) = 0;
		virtual void receiveFA(faDataType pFaDataType, const IBString& cxml) = 0;
		virtual void historicalData(TickerId reqId, const IBString& date, double open, double high, 
			double low, double close, int volume, int barCount, double WAP, int hasGaps) = 0;
		virtual void scannerParameters(const IBString &xml) = 0;
		virtual void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
			const IBString &distance, const IBString &benchmark, const IBString &projection,
			const IBString &legsStr) = 0;
		virtual void scannerDataEnd(int reqId) = 0;
		virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
			long volume, double wap, int count) = 0;
		virtual void fundamentalData(TickerId reqId, const IBString& data) = 0;
		virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp) = 0;
		virtual void tickSnapshotEnd( int reqId) = 0;
		virtual void marketDataType( TickerId reqId, int marketDataType) = 0;
		virtual void commissionReport( const CommissionReport &commissionReport) = 0;
		virtual void position( const IBString& account, const Contract& contract, int position, double avgCost) = 0;
		virtual void positionEnd() = 0;
		virtual void accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) = 0;
		virtual void accountSummaryEnd( int reqId) = 0;
	*/
	};
}
#endif