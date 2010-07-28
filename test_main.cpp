//Andy Sayler
//WMFO
//andy@wmfo.org
//6-26-10

#include "lyricsChecker.hpp"
#include <pthread.h>

using namespace std;

//Test main
int main(int argv, char** argc){
    
    cout << "---Test Explicit Detection---" << endl;
    LyricChecker test("check_res");
    cout << "Searching For:" << endl;
    test.printREs();

    //list<string>* test = lyricsGrabber::getLyrics("Working Class Hero",
    //						  "John Lennon", "");
    //list<string>::iterator test_iter;
    //for (test_iter = test->begin(); test_iter != test->end(); test_iter++) {
    //	cout << *test_iter << "\n";
    //}
    //delete test;

    string title = "Working Class Hero";
    string artist = "John Lennon";
    string album = "";

    list< list<int> > occurances = test.checkLyrics(title, artist, album);

    cout << "Counts Detected:" << endl;
    list<int>::iterator int_iter;
    list< list<int> >::iterator list_iter;
    for (list_iter = occurances.begin(); list_iter != occurances.end();
    	 list_iter++) {
    	for (int_iter = list_iter->begin(); int_iter != list_iter->end();
    	     int_iter++) {
    	    cout << *int_iter << " ";
    	}
    	cout << endl;
    }

    sleep(4);

    bool isMatch = test.isPositiveMatch(title, artist, album);
    cout << "Match?: " << isMatch << endl;
};
