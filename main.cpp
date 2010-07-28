#include <iostream>
#include <string>
#include <cstdlib>
#include "mysql_store.hpp"
#include "lyricsGrabber.hpp"
#include "lyricsChecker.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	lyrics_mysql a;
	a.connect("127.0.0.1", 3306, "rduser", "letmein", "Rivendell");

	int num_res = a.query("SELECT ARTIST,TITLE,ALBUM FROM CART WHERE GROUP_NAME=\"MUSIC\"");

	for (int i = 0; i < num_res; i++) {
		a.getSong(i);
		cout << a.artist() << endl << a.title() << endl << a.album() << "\n\n";

		list<string>* lyrics = lyricsGrabber::getLyrics(a.title(), a.artist(), a.album());

		string tmp;
		if (lyrics->size() <= 0) {
			cout << "No lyrics could be found.\n";
		}
	}

	return 0;
}
	
