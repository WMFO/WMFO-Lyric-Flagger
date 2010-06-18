//WMFO
//Andy Sayler
//lyricsCheck.cpp

#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

class LyricChecker {

public:
    //Constructors
    LyricChecker(void);
    LyricChecker(const char* filename);

    //Destructor
    ~LyricChecker(void);
    
    //Functions
    void printWords(void);

private:
    //Data
    list<string>* checkWords;

    //Functions
    list<string>* readWords(const char* filename);

};
