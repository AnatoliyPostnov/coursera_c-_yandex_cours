#include "database.h"
//#include <algorithm>
void Database::Add(const Date& date, const string& event){
	if (DataBase_[date].count(event) == 0) {
		DataBase_[date].insert(event);
		DataBase[date].push_back(event);
	}
}

void Database::Find(const Date& date) const{
	for(const auto& bd : DataBase_){
		if(bd.first==date){
			for(const auto& event:bd.second){
				cout << event << endl;
			}
		}
	}
}

 void Database::Print(ostream& cout) const{
 	for(const auto& db : DataBase){
		for(const auto& s:db.second){
			cout << db.first << " " << s << endl;
		}
  	}
  }


string Database::Last(const Date& date) const{
	//string str;
	auto Date=DataBase.upper_bound(date);
	//auto Date2=DataBase_.lower_bound(date);
	if (DataBase.begin() == DataBase.end()){
		return "No entries";
	}else if(Date==begin(DataBase)){
		return "No entries";
	}else if(Date==end(DataBase)){
		Date=prev(Date);
		return to_string(Date->first) + " " + *(prev(Date->second.end()));
	}else if(Date==DataBase.lower_bound(date)){
		Date=prev(Date);
		return to_string(Date->first) + " " + *(prev(Date->second.end()));
	}else {
		Date=DataBase.lower_bound(date);
		return to_string(Date->first) + " " + *(prev(Date->second.end()));
	}
}

