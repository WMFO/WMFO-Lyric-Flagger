#include "lyricsGrabber.hpp"
#include "config.hpp"
#include <sys/types.h>
#include <regex.h>
#include <ctime>
#include <cstring>
#include <unistd.h>

using namespace std;

namespace lyricsGrabber {
    
    //Static Function Prototypes
    static int lyricsFly(string title, string artist, string album,
			 string& lyrics);

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
	
	lyrics.clear();
	
	
	//First we must sanitize the paramters. Any non-alpha
	//numerics (or spaces) are replaced with '%'
	char* san_title = new char[title.size()+1];
	char* san_artist = new char[artist.size()+1];
	
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
	
	//Clean Up
	delete[] san_title;
	delete[] san_artist;

	//Get Key From Keyfile
	//Weekly keys are available from http://lyricsfly.com/api/
	//Review terms and request permanent keys at
	//http://lyricsfly.com/contact/
	string skey;
	skey = lyric_con::return_config("lyricskey");	
//	keyFile.open(LYRICSFLY_KEYFILE);
//	getline(keyFile,skey);
//	keyFile.close();

	//Creation of the command to run from the shell.
	stringstream curl;
	curl << "curl \"http://api.lyricsfly.com/api/api.php?";
	curl << "i=" << skey << "&a=";
	curl << url_artist.str().c_str() << "&t=" << url_title.str().c_str()
	     << "\"";
	curl << " > tmp 2> /dev/null";


	char* buf;
	int length;
	bool good_to_go = false;
	
	do {
		//System Call
		system(curl.str().c_str());
	
		ifstream in;
		in.open("tmp");
		
		if (in == NULL)
		return  -1;
		
		in.seekg(0,ios::end);
		length = in.tellg();
		in.seekg(0, ios::beg);

		buf = new char[length+1];
		buf[length] = '\0';

		in.read(buf, length);
		in.close();

		regex_t reg;
		if (regcomp(&reg, "<status>...</status>", REG_ICASE|REG_EXTENDED) != 0) {
			cout << "Regex error 1.\n";
			exit(-1);
		}
	
		regmatch_t matches;
		int status = regexec(&reg, buf, 1, &matches, 0);
	
		if (status != 0) {
			char tmp[50];
			regerror(status, NULL, tmp, 50);
			cout << tmp << "\n\n";
			if (status == REG_NOMATCH) {
				good_to_go = false;
				sleep(1);
				delete[] buf;
			} else {
				exit(-1);
			}
		}


		if (status == 0) {
			char* stat_code;
			stat_code = new char[matches.rm_eo-matches.rm_so+1]; //+1 for NULL terminator!
			strncpy(stat_code, buf+matches.rm_so, matches.rm_eo-matches.rm_so);
			stat_code[matches.rm_eo-matches.rm_so] = '\0';
			//cout << stat_code <<"\n\n";	
			if (strcmp(stat_code, "<status>200</status>") != 0) {
				if (strcmp(stat_code, "<status>402</status>") == 0) {
					good_to_go=false;
					delete[] buf;
					sleep(1);
				} else {
					good_to_go = true;
				}
			} else {	
				good_to_go = true;
			}
		}

		regfree(&reg);
	
	} while (good_to_go == false);

	//Take out only the actual lyrics from the stuff.
	stringstream return_buf;
	
	regex_t reg;
	if (regcomp(&reg, "<tx>[^><]*</tx>", REG_ICASE|REG_EXTENDED) != 0) {
		cout << "Regex Error\n\n";
		exit(-1);
	}

	regmatch_t match;

	bool anyLyrics = false;

	char* buf_point = buf;
	int status = regexec(&reg, buf_point, 1, &match, 0);
	while (status == 0) {
		anyLyrics = true;
		int len = match.rm_eo - match.rm_so;
		char* lyrics_buf = new char[len];
		strncpy(lyrics_buf, buf_point+match.rm_so, len);
		lyrics_buf[len-5] = '\0';
		return_buf << lyrics_buf + 4;
		return_buf << "\n\n\n";
		delete[] lyrics_buf;
		buf_point = buf_point + match.rm_eo;
		status = regexec(&reg, buf_point, 1, &match, 0);
	}

	
	delete[] buf;

	//Return the results.
	lyrics = return_buf.str();

	if (anyLyrics == false)
		return -1;

	return 0;
    }
    
}
