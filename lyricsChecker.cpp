//WMFO
//Andy Sayler
//lyricsCheck.cpp

#include "lyricsChecker.hpp"

//LyricChecker Constructors
LyricChecker::LyricChecker(void) {
    checkWords = readWords(DEFAULT_FILENAME);
}

LyricChecker::LyricChecker(const char* filename) {
    checkWords = readWords(filename);
}

//LyricChecker Destructors
LyricChecker::~LyricChecker(void) {
    delete checkWords;
}

//Private Functions
list<string>* LyricChecker::readWords(const char* filename) {
    ifstream wordFile;
    wordFile.open(filename);

    list<string>* checkWords = new list<string>;
    string word;
    
    if(wordFile.is_open()) {
	while (!wordFile.eof()) {
	    getline (wordFile,word);
	    if(word.length()) {
		checkWords->push_front(word);
	    }
	}
    }
    else {
	cerr << "Could not open file: " << filename << "\n";
    }
    
    return checkWords;
}

//Public Functions
void LyricChecker::printWords(void) {
    list<string>::iterator iter;
    for (iter = checkWords->begin(); iter != checkWords->end(); iter++) {
	cout << *iter << "\n";
    }
}

//Test main
int main(int argv, char** argc){
    
    cout << "test1\n";
    LyricChecker test1;
    test1.printWords();

    cout << "test2\n";
    LyricChecker test2("checkwords2");
    test2.printWords();

};
