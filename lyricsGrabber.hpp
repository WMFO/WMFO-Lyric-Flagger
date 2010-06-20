#include <list>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

namespace lyricGrabber {
    extern list<string>* getLyrics(string title, string artist, string album);
    static int lyricsFly(string title, string artist, string album,
			 string& lyrics);
}
