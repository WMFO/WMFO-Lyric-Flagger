#include <iostream>
#include <string>
#include <fstream>
#include <boost/regex.hpp>

using namespace std;

int main(int argc, char* argv[]) {

    ifstream reg_file;
    ifstream sample;

    sample.open("sample");
    reg_file.open("reggers");

    int length = 0;

    sample.seekg(0, ios::end);
    length = sample.tellg();
    sample.seekg(0, ios::beg);

    char* buf = new char[length+1];
    sample.read(buf, length);
    sample.close();
    
    string s, sre;
    boost::regex re;

 //  s = "I'm in a lonely room \
Hank Williams sings the Lovesick Blues \
Winter's walkin' up the avenue \
I ain't seen the sunshine \
Since the sixth of June but I tell you this \
fuck you!!!  \
Don't call the doctor, I'm gonna get better \
Don't run for the priest, I'm gonna find some faith \
Just because I burned my Bible, baby \
It don't mean, I'm too sick to pray \
 \
I'm in a crowded place \
But I can't recognize a single face \
And they say the thrill is in the chase \
Well, I ain't got the legs, I ain't got the legs \
To run that race but I tell you this \
 \
Don't call the doctor, I'm gonna get better, yeah \
Don't run for the priest, I'm gonna find some faith \
Just because I burned my Bible, baby \
It don't mean, I'm too sick to pray \
 \
You better burn a candle light \
Raise them some [Incomprehensible] tonight \
 \
[Incomprehensible] my money messing up young minds \
I stooped the congregation and left them crying \
In the rain, yeah, left them with their pain \
Exit your boy with his ill gotten pain \
 \
Well the blood runs deep and the blood runs cold \
As the knife slits so another sucker is born \
And thrown into this world alone \
The doctor came knocking, wasn't nobody home? \
Ease the pain \
 \
Don't call the doctor, I'm gonna get better, yeah \
Don't run for the priest, no, I'm gonna find some faith \
Just because I burned my Bible, baby \
It don't mean, I'm too sick to pray \
 \
Don't call the doctor, I'm gonna get better, yeah \
Don't run for the priest, no, I'm gonna find some faith \
Just because I burned my Bible, baby \
It don't mean, it don't mean, I'm too sick to pray \
 \
I'm too sick to pray, I'm gonna burn a candle light \
I'm too sick to pray, I'm too sick to pray \
It don't mean, I'm too sick to pray \
";
    cin >> s;
    cout << s;
    for(getline(reg_file,sre); reg_file.eof() == false; getline(reg_file, sre)) {
	cout << "Testing: " << sre << "\n\n";
	try {
	    re.assign(sre, boost::regex_constants::icase);
	}
	catch (boost::regex_error& e) {
	    cout << sre << 
		" is not a valid regualr expression: \""
		 << e.what() << "\"" << endl;
	    continue;
	}
	cout << re << endl;
	if (boost::regex_match(s, re)) {
	    cout << re << " matches " << endl;
	}
    }
    
}
