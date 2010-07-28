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

    list<boost::regex>* regexs = new list<boost::regex>;
    string sre;
    boost::regex re;
    
    if(reFile.is_open()) {
	while(!reFile.eof()) {
	    getline(reFile,sre);
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
		regexs->push_back(re);
	    }
	}
    }
    else {
	cerr << "Could not open file: " << filename << endl;
    }
    
    return regexs;
}

//Public Functions
void LyricChecker::printREs(void) {
    list<boost::regex>::iterator iter;
    for (iter = checkREs->begin(); iter != checkREs->end(); iter++) {
	cout << iter->str() << endl;
    }
}


list< list<int> > LyricChecker::checkLyrics(string title,
					    string artist, string album) {
    list< list<int> > occurances;
    
    //Fetch linked list of lyrics
    list<string>* lyrics = lyricsGrabber::getLyrics(title, artist, album);

    //Loop through all regexs
    list<boost::regex>::iterator re_iter;
    for (re_iter = checkREs->begin(); re_iter != checkREs->end(); re_iter++) {
	boost::regex re = *re_iter;

	list<int> counts;
	
	//Loop through all lyric sets
	list<string>::iterator s_iter;
	for (s_iter = lyrics->begin(); s_iter != lyrics->end(); s_iter++) {
	    
	    string s = *s_iter;

	    //Perform Search
	    boost::sregex_token_iterator p(s.begin(), s.end(), re, 0);
	    boost::sregex_token_iterator end;
	    
	    //Count occurances
	    int count = 0;
	    while(p != end){
		count++;
		p++;
	    }
	    counts.push_back(count);
	}
	occurances.push_back(counts);
    }

    delete lyrics;
    return occurances;
}

bool LyricChecker::isPositiveMatch(string title, string artist, string album){
    bool posMatch = false;
    list< list<int> > occurances = checkLyrics(title, artist, album);

    //Loop through occurances for each regex
    list< list<int> >::iterator out_iter;
    for (out_iter = occurances.begin();
	 (out_iter != occurances.end()) && (posMatch == false);
	 out_iter++) {
	//Loop throguh occurances for each lyric set
	list<int>::iterator in_iter;
	for (in_iter = out_iter->begin();
	     (in_iter != out_iter->end()) && (posMatch == false);
	     in_iter++) {
	    if ((*in_iter) > 0) {
		posMatch = true;
	    }
	}
    }
    return posMatch;
}
