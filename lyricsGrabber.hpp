#include <list>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//Constants
//LyricsFly Key File
#define LYRICSFLY_KEYFILE "lyricsfly_key"

namespace lyricsGrabber {
    //Public Functions
    extern list<string>* getLyrics(string title, string artist, string album);
}
