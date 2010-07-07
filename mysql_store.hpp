#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <typeinfo>
#include <iostream>
#include <sstream>

using namespace std;

class lyrics_mysql {
	public:
		void getSong(unsigned int i);
		string artist();
		string title();
		string album();
		int mark(string group);
		void connect(string host, unsigned int port, string user, string pass, string db);
		int query(string q);
		lyrics_mysql();
		~lyrics_mysql();
	private:
		string s_artist;
		string s_title;
		string s_album;
		int ID;
		mysqlpp::Connection myConnect;
		mysqlpp::StoreQueryResult res;

};

