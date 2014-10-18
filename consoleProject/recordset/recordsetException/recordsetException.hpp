#ifndef recordset_exception_hpp
#define recordset_exception_hpp

#include <exception>

namespace IB {

	namespace dataBase {

		class recordsetException : public std::exception {};

		// select query exceptions
		class selectQueryException             : public recordsetException {};
		class selectQueryExceptionNoSelection  : public selectQueryException {};
		class selectQueryExceptionSelectFailed : public selectQueryException {};
		class selectQueryExceptionUnknownField : public selectQueryException {};

		// insert query exceptions
		class insertQueryException             : public recordsetException {};
		class insertQueryExceptionUnknownField : public insertQueryException {};
	}
}

#endif 