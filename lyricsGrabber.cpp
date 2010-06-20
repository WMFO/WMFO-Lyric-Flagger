#include "lyricsGrabber.hpp"

namespace lyricGrabber {
    
    extern list<string>* getLyrics(string title, string artist, string album) {
	
	list<string>* lyrics = new list<string>;
	
	string s;
	
	if ( lyricsFly(title, artist, album, s) == 0) {
	    lyrics->push_front(s);
	}
	
	
	return lyrics;
    }
    
    static int lyricsFly(string title, string artist, string album,
			 string& lyrics) {
	
	
	//7b641f6c9ad39bdc9-temporary.API.access
	//TODO: take care of status codes and such. For example
	//take care of us querying too fast. Also split mult-
	//iple results into different list entries?
	
	lyrics.clear();
	
	
	//First we must sanitize the paramters. Any non-alpha
	//numerics (or spaces) are replaced with '%'
	char* san_title = new char[title.size()];
	char* san_artist = new char[artist.size()];
	
	strcpy(san_title, title.c_str());
	strcpy(san_artist, artist.c_str());
	
	
	for (int i = 0; san_title[i] != '\0'; i++) {
	    if ( !isalnum(san_title[i]) && san_title[i] != ' ' )
		san_title[i] = '%';
	}
	
	for (int i = 0; san_artist[i] != '\0'; i++) {
	    if ( !isalnum(san_artist[i]) && san_artist[i] != ' ')
		san_artist[i] = '%';
	}
	
	
	//Now we must url encode the paramters
	stringstream url_artist, url_title;
	
	for(int i = 0; san_title[i] != '\0'; i++) {
	    
	    switch(san_title[i]) {
	    case ' ':
		url_title << "%20";
		break;
	    case '%':
		url_title << "%25";
		break;
	    default:
		url_title << san_title[i];
	    }
	    
	}
	
	for (int i = 0; san_artist[i] != '\0'; i++) {
	    
	    switch(san_artist[i]) {
	    case ' ':
		url_artist << "%20";
		break;
	    case '%':
		url_artist << "%25";
		break;
	    default:
		url_artist << san_artist[i];
	    }
	}
	
	
	//Creation of the command to run from the shell.
	stringstream curl;
	curl << "curl \"http://api.lyricsfly.com/api/api.php?";
	curl << "i=7b641f6c9ad39bdc9-temporary.API.access&a=";
	curl << url_artist.str().c_str() << "&t=" << url_title.str().c_str()
	     << "\"";
	curl << " > tmp";
	
	//System Call
	system(curl.str().c_str());
	
	//Load the results into a buffer
	ifstream in;
	in.open("tmp");
	
	if (in == NULL)
	    return  -1;
	
	
	stringstream buf;
	while ( !in.eof() ) {
	    char a = in.get();
	    buf << a;
	}
	
	in.close();
	
	//Take out only the actual lyrics from the stuff.
	stringstream return_buf;
	
	char* a = new char[buf.str().size()];
	strcpy(a,buf.str().c_str());
	bool inLyrics = false;
	for (unsigned i = 0; i < buf.str().size() - 5; i++) {
	    if (inLyrics == false) {
		if ( strncmp(a+i, "<tx>", 4) == 0) {
		    inLyrics = true;
		    i = i+3;
		}
	    } else {
		if ( strncmp(a+i, "</tx>", 5) == 0) {
		    inLyrics = false;
		    i = i + 4;
		} else {
		    return_buf << a[i];
		}
	    }
	}
	
	//Return the results.
	lyrics = return_buf.str();
	
	return 0;
    }
    
}
