CC = gcc
CXX = g++

docs:
	doxygen

test:

.PHONY: clean

clean:
	rm -rf docs
