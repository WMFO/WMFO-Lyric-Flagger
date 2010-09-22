#include "config.hpp"
#include "lyricsChecker.hpp"
#include "mysql_store.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

	LyricChecker b;

	lyrics_mysql a;
	a.connect("127.0.0.1", 3306, "rduser", "letmein", "Rivendell");
	
	int count = a.query("SELECT ARTIST,TITLE,ALBUM FROM CART WHERE GROUP_NAME=\"MUSIC\"");
	for (int i = 0; i < count; i++) {
		a.getSong(i);

		string artist,title,album;
		artist = a.artist();
		title = a.title();
		album = a.album();

		lyric_code match;
		match = b.isPositiveMatch(title, artist, album);

		switch (match) {
			case NOT_FOUND:
				cout << "No lyrics could be found.\n\n";
				a.mark("U          .");
				break;

			case SAFE:
				cout << "This song is safe for play!\n\n";
				a.mark("S          .");
				break;

			case EXPLICIT:
				cout << "This song is explicit!\n\n";
				a.mark("E          .");
				break;
		}
	}

	return 0;

}


