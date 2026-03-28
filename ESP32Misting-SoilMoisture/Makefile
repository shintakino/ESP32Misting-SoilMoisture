CC=g++
CFLAGS=-Wall -Wextra -std=c++17
SRC=src/moisture.cpp
HDR=src/moisture.h
TESTS=tests/moisture_tests.cpp

all: test

test: $(SRC) $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) $(SRC) -o tests/test_moisture

clean:
	rm -f tests/test_moisture
