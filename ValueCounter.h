/**
 * Interface to count unique values
 *
 * @author Marius Hoch
 */

#include<unordered_map>
#include<map>
#include<vector>
#include<cstddef>
using std::vector;
using std::pair;
using std::unordered_map;

#ifndef VALUECOUNTER_H
#define VALUECOUNTER_H

template <class valueType>
class ValueCounter {
	public:
		/**
		 * Count a hit for the given value
		 */
		void countUp( const valueType value );

		/**
		 * Get the number of distinct values
		 */
		size_t getNumberOfValues();

		/**
		 * Return a vector with number of hits -> value
		 */
		vector< pair< unsigned int, valueType > > * getTop( size_t maxRows = ~0 );
	private:
		/**
		 * Hash map pointing value -> int
		 */
		unordered_map<valueType, unsigned int> valueAndCount;
};

#endif
