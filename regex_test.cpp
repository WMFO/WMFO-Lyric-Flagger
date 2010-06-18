#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;

int main() {
    
    string s, sre;
    boost::regex re;
    
    while(true) {
	cout << "Expression: ";
	cin >> sre;
	if (sre == "quit") {
	    break;
	}
	cout << "String: ";
	cin >> s;
	
	try {
	    re.assign(sre, boost::regex_constants::icase);
	}
	catch (boost::regex_error& e) {
	    cout << sre << 
		" is not a valid regualr expression: \""
		 << e.what() << "\"" << endl;
	    continue;
	}
	if (boost::regex_match(s, re)) {
	    cout << re << " matches " << s << endl;
	}
    }
    
}
