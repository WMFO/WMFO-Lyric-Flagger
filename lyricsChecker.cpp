//WMFO
//Andy Sayler
//lyricsCheck.cpp

#include "lyricsChecker.hpp"

//LyricChecker Constructors
LyricChecker::LyricChecker(void) {
    checkREs = readREs(DEFAULT_FILENAME);
}

LyricChecker::LyricChecker(const char* filename) {
    checkREs = readREs(filename);
}

//LyricChecker Destructors
LyricChecker::~LyricChecker(void) {
    delete checkREs;
}

//Private Functions
list<boost::regex>* LyricChecker::readREs(const char* filename) {
    ifstream reFile;
    reFile.open(filename);

    list<boost::regex>* checkREs = new list<boost::regex>;
    string sre;
    boost::regex re;
    
    if(reFile.is_open()) {
	while(!reFile.eof()) {
	    getline (reFile,sre);
	    if(sre.length()) {
		try {
		    //Set up RE with case insensitivity
		    re.assign(sre, boost::regex_constants::icase);
		}
		catch(boost::regex_error& e) {
		    cerr << sre << " is not a valid regual expression: \""
			 << e.what() << "\"" << endl;
		    continue;
		}
		checkREs->push_front(re);
	    }
	}
    }
    else {
	cerr << "Could not open file: " << filename << endl;
    }
    
    return checkREs;
}

//Public Functions
void LyricChecker::printREs(void) {
    list<boost::regex>::iterator iter;
    for (iter = checkREs->begin(); iter != checkREs->end(); iter++) {
	cout << iter->str() << "\n";
    }
}

//Test main
int main(int argv, char** argc){
    
    cout << "test1\n";
    LyricChecker test1;
    test1.printREs();

    cout << "test2\n";
    LyricChecker test2("checkwords2");
    test2.printREs();

};
