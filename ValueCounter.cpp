/**
 * Implementation of ValueCounter which allows counting unique values of any type hashable by
 * std::hash.
 *
 * @author Marius Hoch
 */

#include<unordered_map>
#include<map>
#include<cstddef>
#include<algorithm>
using std::unordered_map;
using std::pair;
using std::sort;
#include"ValueCounter.h"

template <typename valueType>
bool comparePairs( pair<unsigned int, valueType> a, pair<unsigned int, valueType> b ) {
	return ( a.first > b.first );
}

template <class valueType>
void ValueCounter<valueType>::countUp( const valueType value ) {
	if ( this->valueAndCount[ value ] ) {
		this->valueAndCount[ value ]++;
		return;
	}

	this->valueAndCount[ value ] = 1;
}

template <class valueType>
size_t ValueCounter<valueType>::getNumberOfValues() {
	return this->valueAndCount.size();
}

template <class valueType>
vector< pair< unsigned int, valueType > > * ValueCounter<valueType>::getTop( size_t maxRows ) {

	// We need a vector here as that has an order (as opposed to hash maps)
	vector< pair< unsigned int, valueType > > * ordered = new vector< pair< unsigned int, valueType > >;
	ordered->reserve( this->valueAndCount.size() );

	// Create a vector from the data of the unordered_map and switch value/count.
	for ( auto i = this->valueAndCount.begin(); i != this->valueAndCount.end(); ++i ) {
		ordered->push_back( pair< unsigned int, valueType >( i->second, i->first ) );
	}

	sort( ordered->begin(), ordered->end(), &comparePairs<valueType> );

	if ( ordered->size() <= maxRows ) {
		return ordered;
	}

	ordered->resize( maxRows ); // Delete everything we don't want to return

	return ordered;
}
