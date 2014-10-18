#ifndef request_exception_hpp
#define request_exception_hpp

#include <exception>

#include "commonDefs.h"

namespace IB {

		class requestException : public std::exception {
		
			public:
				requestException(const TickerId & id) : std::exception(), id_(id) {};

				TickerId id_;										// request identifier
		
		};

		class requestTimeoutException : public requestException {
		
			public:
				requestTimeoutException(const TickerId & id) : requestException(id) {};
		
		};

		class lostConnectionException : public requestException {

			public:
				lostConnectionException(const TickerId & id) : requestException(id) {};

		};

		class unmatchedContractException : public requestException {

			public:
				unmatchedContractException(const TickerId & id) : requestException(id) {};

		};

		class unknownException : public requestException {

			public:
				unknownException(const TickerId & id) : requestException(id) {};

		};

		class pacingViolationHistoricalException : public requestException {

			public:
				pacingViolationHistoricalException(const TickerId & id) : requestException(id) {};

		};
		

}

#endif 