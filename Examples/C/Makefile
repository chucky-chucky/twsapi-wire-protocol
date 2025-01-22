
Default: com_test

com_test.o: com_test.cpp
	g++ -Wall -c com_test.cpp -o com_test.o

com_test: com_test.o
	g++ -Wall com_test.cpp -o com_test
	
clean:
	rm -f com_test
	rm -f com_test.o
