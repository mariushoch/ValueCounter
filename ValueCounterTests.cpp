/**
 * Test for the ValueCounter class.
 *
 * @author Marius Hoch
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ValueCounterTest

#include<map>
using std::pair;
#include<cstddef>
#include<boost/test/unit_test.hpp>
#include"ValueCounter.h"
#include"ValueCounter.cpp"

ValueCounter<int> getIntValueCounter() {
	ValueCounter<int> intTestValueCounter;

	intTestValueCounter.countUp( 5 );
	intTestValueCounter.countUp( 7 );
	intTestValueCounter.countUp( 5 );
	intTestValueCounter.countUp( 45 );
	intTestValueCounter.countUp( -99 );
	intTestValueCounter.countUp( 5 );

	return intTestValueCounter;
}

ValueCounter<char> getCharValueCounter() {
	ValueCounter<char> charTestValueCounter;

	charTestValueCounter.countUp( 'A' );
	charTestValueCounter.countUp( 'B' );
	charTestValueCounter.countUp( 'A' );
	charTestValueCounter.countUp( 'A' );
	charTestValueCounter.countUp( 'C' );
	charTestValueCounter.countUp( 'Z' );
	charTestValueCounter.countUp( 'B' );
	charTestValueCounter.countUp( 'D' );

	return charTestValueCounter;
}

ValueCounter<bool> getEmptyValueCounter() {
	ValueCounter<bool> emptyValueCounter;

	return emptyValueCounter;
}

BOOST_AUTO_TEST_CASE( getNumberOfValues ) {
	ValueCounter<int> intTestValueCounter = getIntValueCounter();
	ValueCounter<char> charTestValueCounter = getCharValueCounter();
	ValueCounter<bool> emptyValueCounter = getEmptyValueCounter();

	BOOST_CHECK_EQUAL( intTestValueCounter.getNumberOfValues(), 4 );
	BOOST_CHECK_EQUAL( charTestValueCounter.getNumberOfValues(), 5 );
	BOOST_CHECK_EQUAL( emptyValueCounter.getNumberOfValues(), 0 );
}

BOOST_AUTO_TEST_CASE( getTop_returned_rows ) {
	ValueCounter<int> intTestValueCounter = getIntValueCounter();
	ValueCounter<char> charTestValueCounter = getCharValueCounter();
	ValueCounter<bool> emptyValueCounter = getEmptyValueCounter();

	BOOST_CHECK_EQUAL( intTestValueCounter.getTop( 1 )->size(), 1 );
	BOOST_CHECK_EQUAL( intTestValueCounter.getTop( 5000 )->size(), intTestValueCounter.getNumberOfValues() );
	BOOST_CHECK_EQUAL( intTestValueCounter.getTop()->size(), intTestValueCounter.getNumberOfValues() );

	BOOST_CHECK_EQUAL( charTestValueCounter.getTop( 3 )->size(), 3 );

	BOOST_CHECK_EQUAL( emptyValueCounter.getTop()->size(), 0 );
	BOOST_CHECK_EQUAL( emptyValueCounter.getTop( 5 )->size(), 0 );
}

BOOST_AUTO_TEST_CASE( getTop_sorting ) {
	ValueCounter<int> intTestValueCounter = getIntValueCounter();
	ValueCounter<char> charTestValueCounter = getCharValueCounter();
	ValueCounter<bool> emptyValueCounter = getEmptyValueCounter();

	vector< pair< unsigned int, bool > > emptyIntBoolVector;

	// 5 appears 3 times in intTestValueCounter
	BOOST_CHECK_EQUAL( (* intTestValueCounter.getTop( 1 ) )[0].first, 3 );
	BOOST_CHECK_EQUAL( (* intTestValueCounter.getTop( 1 ) )[0].second, 5 );

	// 'A' appears three times in charTestValueCounter and 'B' appears twice
	BOOST_CHECK_EQUAL( (* charTestValueCounter.getTop() )[0].first, 3 );
	BOOST_CHECK_EQUAL( (* charTestValueCounter.getTop() )[0].second, 'A' );
	BOOST_CHECK_EQUAL( (* charTestValueCounter.getTop() )[1].first, 2 );
	BOOST_CHECK_EQUAL( (* charTestValueCounter.getTop() )[1].second, 'B' );

	BOOST_CHECK_MESSAGE( (* emptyValueCounter.getTop() ) == emptyIntBoolVector, "getTop works on empty result set" );
}
