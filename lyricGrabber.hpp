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
	list<string>* getLyrics(string title, string artist, string album);
	int lyricsFly(string title, string artist, string album, string& lyrics);
}
