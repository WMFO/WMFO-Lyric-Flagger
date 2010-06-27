//Andy Sayler
//WMFO
//andy@wmfo.org
//6-26-10

#include "lyricsChecker.hpp"

using namespace std;

//Test main
int main(int argv, char** argc){
    
    //    cout << "test1\n";
    //LyricChecker test1;
    //test1.printREs();

    cout << "test2\n";
    LyricChecker test2("check_res2");
    //test2.printREs();

    //list<string>* test = lyricsGrabber::getLyrics("Working Class Hero",
    //						  "John Lennon", "");
    //list<string>::iterator test_iter;
    //for (test_iter = test->begin(); test_iter != test->end(); test_iter++) {
    //	cout << *test_iter << "\n";
    //}
    //delete test;


    list< list<int> > occurances = test2.checkLyrics("Working Class Hero",
						     "John Lennon", "");

    list<int>::iterator int_iter;
    list< list<int> >::iterator list_iter;
    for (list_iter = occurances.begin(); list_iter != occurances.end();
	 list_iter++) {
	for (int_iter = list_iter->begin(); int_iter != list_iter->end();
	     int_iter++) {
	    cout << *int_iter << " ";
	}
	cout << "\n";
    }
    
};
