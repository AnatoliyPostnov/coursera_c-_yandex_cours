#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include "date.h"
using namespace std;
class Database {
public:
	void Add(const Date& date,const string& event);
	void Print(ostream& cout) const;
	void Find(const Date& date) const;
  	string Last(const Date& D)const;

  	template <typename T>
  	int RemoveIf(T predicate);
    template <typename H>
    vector<string> FindIf(H predicate) const;

private:
  	map<Date,set<string>> DataBase_;
  	map<Date,vector<string>> DataBase;
};

template <typename H>
vector<string> Database::FindIf(H predicate) const{
   vector<string> entries;
   for(const auto&D:DataBase){
       for(const auto&str:D.second){
           if(predicate(D.first,str)){
               entries.push_back(to_string(D.first) + " " + str);
           }
       }
   }
   return entries;
}

template <typename T>
int Database::RemoveIf(T predicate){
   int count=0;
   vector <Date> Dates;
   DataBase_.clear();
   for(auto i=DataBase.begin();i!=DataBase.end();++i){
	   auto it=stable_partition(i->second.begin(),i->second.end()
			   ,[predicate,i](string str){
       			return !predicate(i->first,str);
       });
	   count += i->second.end() - it;
	   DataBase[i->first].erase(it,i->second.end());
	   DataBase_[i->first].insert(i->second.begin(),it);
	   i->second.erase(it, i->second.end());
	   if (begin(i->second) == end(i->second)){
		   Dates.push_back(i->first);
	   }
   }
   for(const auto& i : Dates) {
	   DataBase.erase(i);
	   DataBase_.erase(i);
   }
   return count;
}

/*
template <class T>
int Database::RemoveIf(T func) {
    int count = 0;
    vector<Date> dates;
    for (auto i = begin(database); i != end(database); i++) {
        auto it = stable_partition(i->second.begin(), i->second.end(), [func, i] (string s) {
            return !func(i->first, s);
        });
        count += i->second.end() - it;
        database_check[i->first].clear();
        database_check[i->first].insert(i->second.begin(), it);
        i->second.erase(it, i->second.end());
        if (begin(i->second) == end(i->second)) dates.push_back(i->first);
    }

    for(const auto& i : dates) {
        database.erase(i);
        database_check.erase(i);
    }
    return count;
}
*/
