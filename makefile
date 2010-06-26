# WMFO-Lyric-Flager Makefile
# A Sayler
# 6-18-10
# makefile

CC=g++
CFLAGS=-c -Wall -g
LFLAGS=-static
EXECUTABLE=test_main
OBJECTS=lyricsChecker.o lyricsGrabber.o test_main.o
EXECUTABLE_TEST=regex_test
LIBS=-L/usr/lib -lboost_regex -lpthread

all: $(EXECUTABLE)

test_main: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LIBS)

test_main.o: test_main.cpp
	$(CC) $(CFLAGS) test_main.cpp

lyricsChecker.o: lyricsChecker.cpp lyricsChecker.hpp
	$(CC) $(CFLAGS) lyricsChecker.cpp

lyricsGrabber.o: lyricsGrabber.cpp lyricsGrabber.hpp
	$(CC) $(CFLAGS) lyricsGrabber.cpp

test: $(EXECUTABLE_TEST)

regex_test: regex_test.o
	$(CC) $(LFLAGS) regex_test.o -o $(EXECUTABLE_TEST) $(LIBS)

regex_test.o: regex_test.cpp
	$(CC) $(CFLAGS) regex_test.cpp

clean:
	rm -rf *.o $(EXECUTABLE) $(EXECUTABLE_TEST)
