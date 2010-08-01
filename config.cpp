#include <fstream>
#include <string>
#include <regex.h>

struct config_t {
	int delay;
	string lyrics_key;
	string query;
};

void config populate(config_t& con) {
	ifstream in;
	in.open("lyrics.config");

	regex_t re;
	regmatch_t mat;

	regcomp(&re, "(^key=.*$)(^delay=.*)(^query=.*$)", REG_EXTENDED|REG_ICASE);
