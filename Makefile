CXX=g++
CXXFLAGS=-Isource -std=c++11 -g
#FILES= source/main.cpp source/Arithmetic.cpp source/Huffman.o source/common.o

build: main.o Arithmetic.o Huffman.o common.o
	$(CXX) $(CXXFLAGS) -o press main.o Arithmetic.o common.o Huffman.o

main.o: source/main.cpp
	$(CXX) $(CXXFLAGS) -c source/main.cpp

Arithmetic.o: source/Arithmetic.cpp
	$(CXX) $(CXXFLAGS) -c source/Arithmetic.cpp

Huffman.o: source/Huffman.cpp
	$(CXX) $(CXXFLAGS) -c source/Huffman.cpp

common.o: source/common.cpp
	$(CXX) $(CXXFLAGS) -c source/common.cpp
