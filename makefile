test: ValueCounter.o ValueCounterTests.o
	g++ -std=c++11 -lboost_unit_test_framework -o ValueCounterTests ValueCounter.o ValueCounterTests.o
	./ValueCounterTests

ValueCounter.o: ValueCounter.h ValueCounter.cpp
	g++ -std=c++11 -c ValueCounter.cpp

ValueCounterTests.o: ValueCounterTests.cpp ValueCounter.h
	g++ -std=c++11 -lboost_unit_test_framework -c ValueCounterTests.cpp

clean:
	rm -f *.o *.oi ValueCounter.h.gch ValueCounterTests
