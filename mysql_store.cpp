//Work in progress
//For the time being, header and a test main will be here.
//TODO: Minor idealogical cleanup, formatting, group change function
#include "mysql_store.hpp"


lyrics_mysql::lyrics_mysql() {
	s_artist.clear();
	s_title.clear();
	s_album.clear();
	ID = -1;
}

lyrics_mysql::~lyrics_mysql() {
	myConnect.disconnect();
}


int lyrics_mysql::mark(string group) {
	stringstream a;
	a << "UPDATE CART SET SCHED_CODES=\"" << group << "\" WHERE ARTIST=\"" << s_artist \
		<< "\" AND TITLE=\"" << s_title << "\" AND ALBUM=\"" << s_album << "\"\n";

	mysqlpp::Query myQuery = myConnect.query(a.str().c_str());
	myQuery.use();
	
	return 1;
};

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

void lyrics_mysql::getSong(unsigned int i) {

	if ((i < 0) || (i >= res.num_rows())) {
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

