# WMFO-Lyric-Flager Makefile
# A Sayler
# 6-18-10
# makefile

CC=g++
CFLAGS=-c -Wall
LFLAGS=-static
EXECUTABLE=regex_test
LIBS=-L/usr/lib -lboost_regex -lpthread

all: regex_test

regex_test: regex_test.o
	$(CC) $(LFLAGS) regex_test.o -o $(EXECUTABLE) $(LIBS) -lpthread

regex_test.o: regex_test.cpp
	$(CC) $(CFLAGS) regex_test.cpp

clean:
	rm -rf *o $(EXECUTABLE)
