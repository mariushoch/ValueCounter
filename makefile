default:
test: ValueCounter.o ValueCounterTests.o
	$(CXX) -std=c++0x -lboost_unit_test_framework-mt -o ValueCounterTests ValueCounter.o ValueCounterTests.o
	./ValueCounterTests

ValueCounter.o: ValueCounter.h ValueCounter.cpp
	$(CXX) -std=c++0x -c ValueCounter.cpp

ValueCounterTests.o: ValueCounterTests.cpp ValueCounter.h
	$(CXX) -std=c++0x -c ValueCounterTests.cpp

clean:
	rm -f *.o *.oi ValueCounter.h.gch ValueCounterTests
