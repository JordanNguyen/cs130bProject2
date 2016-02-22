all: main.cpp
	clang++ -std=c++11 main.cpp -o findLCS

clean:
	rm -f *.o findLCS
