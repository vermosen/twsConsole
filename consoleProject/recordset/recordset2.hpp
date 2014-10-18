#ifndef tws_recordset_2_hpp
#define tws_recordset_2_hpp

#include <string>
#include <map>
#include <xstddef>

#include <stdint.h>

#include <mysql.h>

#include <thOth/time/dateTime.hpp>

#include "recordset/recordsetException/recordsetException.hpp"
#include "utilities/conversion/convertDateTime/convertDateTime.hpp"
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

		enum deletionPolicy : unsigned char {					// defines deletion policy

			authorizeCopy      = 0,
			preserveFormerData = 1,
			EraseFormerData    = 2

		};

		typedef uint64_t recordId;								// equivalent of a big int

		template<
			typename Key, 
			typename T, 
			template<
				typename Key, 
				typename T, 
				typename Rel = std::less<Key>, 
				typename All = std::allocator<std::pair<const Key, T>>>
			class Container>
		class recordset2 {

		public:

			typedef typename Container<Key, T>::const_iterator const_iterator;
			typedef typename Container<Key, T>::iterator iterator;

			recordset2(MYSQL * connection)					// ctor
				: connection_(connection) {};				
			
			recordset2(const recordset2 & o) {				// copy ctor

				connection_ = o.connection_;
				reception_ = o.reception_;

			};

			virtual ~recordset2() {};						// virtual destructor

			recordset2 & operator =(const recordset2 & o) {

				if (this != &o) {

					// copy stuff
					// should we delete this one for performance concern ?
					connection_ = o.connection_;
					reception_ = o.reception_;
					records_ = o.records_;

				}

				return *this;

			};

			// database methods, return true is the statement succeed, throw otherwise
			virtual bool selectStr (const std::string &) = 0;
			virtual bool deleteStr (const std::string &) = 0;

			//TODO: synchronization method with deletion policy defined + error management
			//void synchronize(deletionPolicy);

			// iterators
			typename const_iterator cbegin () const { return records_.cbegin(); };
			typename const_iterator cend   () const { return records_.cend  (); };

			typename iterator begin() { return records_.begin(); };
			typename iterator end  () { return records_.end  (); };

			thOth::size size() const { return records_.size(); };

		protected:

			recordset2() {};									// protected default ctor

			MYSQL *     connection_;						// connection objects
			MYSQL_RES * reception_ ;

			// a pile of records for data management, 
			Container<Key, T> records_;
			
		};
	}
}

#endif