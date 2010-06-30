//Work in progress
//For the time being, header and a test main will be here.
//TODO: Minor idealogical cleanup, formatting, group change function

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <typeinfo>
#include <iostream>

using namespace std;


class lyrics_mysql {
	public:
		void getSong(int i);
		void getSongbyID();
		string artist();
		string title();
		string album();
		int mark(string group);
		void connect(string host, unsigned int port, string user, string pass, string db);
		int query(string q);
		lyrics_mysql();
	private:
		string s_artist;
		string s_title;
		string s_album;
		int ID;
		mysqlpp::Connection myConnect;
		mysqlpp::StoreQueryResult res;

};

lyrics_mysql::lyrics_mysql() {
	s_artist.clear();
	s_title.clear();
	s_album.clear();
	ID = -1;
}

void lyrics_mysql::connect(string host, unsigned int port, string user, string pass, string db) {

	try {
		myConnect.connect(db.c_str(), host.c_str(), user.c_str(), pass.c_str(), port);
	}
	catch(exception& e) {
		cerr << "Exception passed while attempting to connect to database." << endl;
		cerr << "In lyrics_mysql::connect" << endl;
		cerr << e.what() << endl;
		exit(-1);
	}
	return; 

}

int lyrics_mysql::query(string q) {

	try {
		mysqlpp::Query myQuery = myConnect.query(q.c_str());
		res = myQuery.store();
	}
	catch (exception& e) {
		cerr << "Exception thrown when trying to query!\n";
		cerr << "Inside lyrics_mysql::query\n";
		cerr << e.what() << endl;
		exit(-1);
	}

	return res.num_rows();	

}

void lyrics_mysql::getSong(int i) {

	if (i < 0 || i >= res.num_rows()) {
		cerr << "Invalid index passed!\n";
		cerr << "Inside lyrics_mysql::getSong\n";
		exit(-1);
	}

	try {
		s_artist = (string)res[i]["ARTIST"];
		s_title = (string)res[i]["TITLE"];
		s_album = (string)res[i]["ALBUM"];
	}

	catch(exception& e) {
		cerr << "Exception in fetching the song from results!\n";
		cerr << "Inside lyrics_mysql::getSong\n";
		cerr << e.what() << endl;
		exit(-1);
	}

}

string lyrics_mysql::artist() {
	return s_artist;
}

string lyrics_mysql::title() {
	return s_title;
}

string lyrics_mysql::album() {
	return s_album;
}

	

int main() {
	lyrics_mysql a;
	a.connect("127.0.0.1", 0, "root", "", "Rivendell");
	int num_row = a.query("select ARTIST,TITLE,ALBUM from CART WHERE ARTIST=\"David Bowie\"");

	for (int i = 0; i = num_row; i++) {
		a.getSong(i);
		cout << a.artist() << endl << a.title() << endl << a.album() << endl << endl;
	}
	return 0;
}

