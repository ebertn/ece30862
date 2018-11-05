CXX=g++
CXXFLAGS=-g -std=c++0x -Wall -pedantic
BIN=zork

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(Cxx) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean: 
	rm -f *.o
	rm $(BIN)