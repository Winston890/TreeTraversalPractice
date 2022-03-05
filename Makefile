#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

all: Order DictionaryTest DictionaryClient

Order : Dictionary.o Order.o
	g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

DictionaryClient : DictionaryClient.o Dictionary.o 
	g++ -std=c++17 -Wall -o DictionaryClient DictionaryClient.o Dictionary.o

DictionaryTest : DictionaryTest.o Dictionary.o 
	g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o

Order.o : Order.cpp Dictionary.h
	g++ -std=c++17 -Wall -c Order.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
	g++ -std=c++17 -Wall -c Dictionary.cpp 

clean :
	rm -f DictionaryClient DictionaryClient.o Order Order.o DictionaryTest DictionaryTest.o Dictionary.o 
