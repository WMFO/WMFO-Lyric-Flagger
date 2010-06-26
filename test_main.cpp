//Andy Sayler
//WMFO
//andy@wmfo.org
//6-26-10

#include "lyricsChecker.hpp"

//Test main
int main(int argv, char** argc){
    
    cout << "test1\n";
    LyricChecker test1;
    test1.printREs();

    cout << "test2\n";
    LyricChecker test2("check_res2");
    test2.printREs();

};
