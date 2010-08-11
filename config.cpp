#include "config.hpp"
#include <fstream>
#include <regex.h>
#include <map>
#include <cstring>
#include <iostream>

using namespace std;

namespace lyric_con {

	map<string,string> config_info;
	bool configured = false;

	static void config_populate() {
		ifstream in;
		in.open("lyrics.config");

		in.seekg(0, ios::end);
		unsigned long length = in.tellg();
		in.seekg(0, ios::beg);
		char* buf = new char[length+1];
		in.read(buf, length);
		//cout << buf;
		buf[length] = '\0';
		in.close();

		regex_t* re;
		regmatch_t* mat;


		char* pos = buf;
		int status = 0;
		do {
			re = new regex_t;
			mat = new regmatch_t;
			regcomp(re, "[[:alnum:]]*=[^\n]*", REG_EXTENDED|REG_ICASE);
			status = regexec(re, pos, 1, mat, 0);
			if (status == 0) {

				unsigned int so = mat->rm_so;
				unsigned int eo = mat->rm_eo;
				unsigned int off = 0;

				char* sub_string = pos+so;

				while (*sub_string != '=') {
					sub_string++;
					off++;
				}

				char* lhs = new char[off + 1];
				char* rhs = new char[eo - so - off];
				lhs[off] = '\0';
				rhs[eo - so - off - 1] = '\0';

				strncpy(lhs, pos + so, off);
				strncpy(rhs, sub_string + 1, eo - so - off - 1);

				string a = lhs;
				string b = rhs;

				delete[] lhs;
				delete[] rhs;

				config_info[a]=b;

				pos = pos + eo;
			}
			regfree(re);
			delete mat;
			delete re;
		} while(status == 0);

		delete[] buf;


	}


	string return_config(string in) {
		if (configured == false)
			config_populate();
		string out;

		out = config_info[in];
		return out;
	}


}

