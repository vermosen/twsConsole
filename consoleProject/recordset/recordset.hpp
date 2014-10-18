#ifndef tws_recordset_hpp
#define tws_recordset_hpp

#include <string>
#include <map>

#include <stdint.h>

#include <mysql.h>

#include <thOth/time/DateTime.hpp>

#include "recordset/recordsetException/recordsetException.hpp"
#include "utilities/define.hpp"

// insert a string value
#define INSERT_SQL_STR(X,Y) \
	X.append("'" )          \
	 .append(Y   )          \
	 .append("'");

// insert a num value
#define INSERT_SQL_NUM(X,Y) \
	 X.append(boost::lexical_cast<std::string>(Y));

// insert a date value
#define INSERT_SQL_DATE(X,Y)     \
	X.append("'")                \
	 .append(convertDateTime_sql(Y)) \
	 .append("'");

namespace IB {

	namespace dataBase {

		typedef uint64_t recordId;								// equivalent of a big int

		template <class T>
		class recordset {

			public:

				typedef typename std::map<recordId, T>::const_iterator const_iterator;
				typedef typename std::map<recordId, T>::iterator iterator;

			public:

				recordset(MYSQL *);								// ctor
				recordset(const recordset &);					// copy ctor

				virtual ~recordset();							// virtual destructor

				recordset & operator =(const recordset &);

				// database methods
				virtual bool selectQ(const std::string &) = 0;	// return true if the select statement is non empty
				virtual bool deleteQ(const std::string &) = 0;	// return true if the delete statement succeed
				virtual bool insert(const T			   &) = 0;	// insert method
				bool insert(const std::vector<T> &);			// bulk insert

				// iterators
				typename const_iterator cbegin() const;
				typename const_iterator cend  () const;

				typename iterator begin ();
				typename iterator end   ();

				recordId size() const;

			protected:

				recordset() {};									// protected default ctor

				MYSQL * connection_;			// connection objects
				MYSQL_RES * reception_ ;

				std::map<recordId, T> records_;					// a pile of records for data management, 
																// assumes the primary key of every table is a BIGINT
																// otherwise some internal key will be allocated
		};

		// implementation
		template <class T>
		recordset<T>::recordset(MYSQL * connection) : connection_(connection){};
		
		template<class T>
		recordset<T>::recordset(const recordset<T> & o) {

			connection_ = o.connection_;
			reception_  = o.reception_ ;

		};
		
		template <class T>
		recordset<T>::~recordset() {};

		template <class T>
		recordset<T> & recordset<T>::operator = (const recordset<T> & o) {

			if (this != &o) {

				// copy stuff
				// DO NOT DUPLICATE FIELDS AND RECORDS HERE
				connection_ = o.connection_;
				reception_  = o.reception_ ;

			}

			return * this;

		}

		// bulk insert
		template <typename T>
		bool recordset<T>::insert(const std::vector<T> & data) {
		
			for (std::vector<T>::const_iterator
				It = data.cbegin(); It != data.cend(); It++)

				insert(*It);

			return true;
		
		};

		template <typename T>
		inline typename recordset<T>::const_iterator
			recordset<T>::cbegin() const {

			return records_.cbegin();

		}

		template <class T>
		inline typename recordset<T>::const_iterator
			recordset<T>::cend() const {

			return records_.cend();

		}

		template <typename T>
		inline typename recordset<T>::iterator
			recordset<T>::begin() {

			return records_.begin();

		}

		template <class T>
		inline typename recordset<T>::iterator
			recordset<T>::end() {

			return records_.end();

		}

		template <class T>
		inline recordId recordset<T>::size() const {

			return records_.size();

		}
	
	}

}

#endif