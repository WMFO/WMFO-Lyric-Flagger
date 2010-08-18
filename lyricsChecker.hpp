//WMFO
//Andy Sayler
//lyricsCheck.hpp

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#include <boost/regex.hpp>
//#include <regex>

#include "lyricsGrabber.hpp"

//Constants
//Check REs File
#define DEFAULT_FILENAME "check_res"

using namespace std;

enum lyric_code {EXPLICIT, SAFE, NOT_FOUND};

class LyricChecker {

public:
    //Constructors
    LyricChecker(void);
    LyricChecker(const char* filename);

    //Destructor
    ~LyricChecker(void);
    
    //Functions
    void printREs(void);
    list< list<int> > checkLyrics(string title, string artist, string album);
    lyric_code isPositiveMatch(string title, string artist, string album);

private:
    //Data
    list<boost::regex>* checkREs;

    //Functions
    list<boost::regex>* readREs(const char* filename);

};
