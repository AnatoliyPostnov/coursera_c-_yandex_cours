#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
class Date {
	public:
	Date(){
		year=0;
		month=0;
		day=0;
	}
	Date(int y,int m,int d){
		year=y;
		month=m;
		day=d;
	}
	void SetYear(int y){
		year=y;
	}
	void SetMonth(int m){
		month=m;
	}
	void SetDay(int d){
		day=d;
	}
	int GetYear() const{
		return year;
	}
	int GetMonth() const{
		return month;
	}
	int GetDay() const{
		return day;
	}
	private:
	int year,month,day;
};
ostream& operator << (ostream& output, const Date& d){
	return output << setfill('0') << setw(4) << d.GetYear() 
	<< "-" << setw(2) << d.GetMonth() << "-" << setw(2) << d.GetDay();
}

istream& operator >> (istream& input, Date& d){
	int year=0,month=0,day=0;
	char c1,c2;
	string data;
	input >> data;
	istringstream Data(data);
	Data >> year >> c1 >> month >> c2;
	string s1;
	Data >> s1;
	if(s1[0]=='0'&&s1.size()>1){
		s1.erase(0,1);
	}
	istringstream Day(s1);
	Day >> day;
	ostringstream oss;
	oss << day;
	string s2=oss.str();
	if(c1=='-'&&c2=='-'&&s1==s2){
		if(month>=1&&month<=12){
			if(day>=1&&day<=31){
				d=Date(year,month,day);
			}else{
				cout << "Day value is invalid: ";
				throw invalid_argument(s1);
			}
		}else{
			cout << "Month value is invalid: ";
			ostringstream o;
			o << month;
			s2=o.str();
			throw invalid_argument(s2);
		}
		
	}else{
		cout << "Wrong date format: ";
		throw invalid_argument(data);
	}
	return input;
}

istream& Input(istream& input, Date& d, int& i){
	try{
		input >> d;
	}catch(invalid_argument& in){
		cout << in.what() << endl;
		i=1;
	}
	return input;
}

bool operator == (const Date& ld,const Date& rd ){
	return ld.GetYear()==rd.GetYear()&&ld.GetMonth()==rd.GetMonth()&&ld.GetDay()==rd.GetDay();
}

bool operator != (const Date& ld,const Date& rd ){
	 if(ld.GetYear()==rd.GetYear()&&ld.GetMonth()==rd.GetMonth()&&ld.GetDay()==rd.GetDay()){}
	 else {return 1;}
	 return 0;
}

bool operator<(const Date& lhs, const Date& rhs){
	if(lhs.GetYear()<rhs.GetYear()){
		return 1;
	}else{
		if(lhs.GetYear()==rhs.GetYear()&&lhs.GetMonth()<rhs.GetMonth()){
			return 1;
		}else{
			if(lhs.GetYear()==rhs.GetYear()&&lhs.GetMonth()==rhs.GetMonth()&&lhs.GetDay()<rhs.GetDay()){
				return 1;
			}
		}
	}
	return 0;
}

class Database {
	public:
	
	void AddEvent(const Date& date, const string& event){
		DataBase[date].insert(event);
	}
	
	bool DeleteEvent(const Date& date, const string& event){
		for(auto& bd : DataBase){
			if(bd.first==date){
				if(bd.second.count(event)){
					bd.second.erase(event);
					if(bd.second.size()==0){
						DataBase.erase(date);
					}
					return 1;
				}
			}
		}
		return 0;
	}
	
	int  DeleteDate(const Date& date){
		int N=0;
		for(auto& bd : DataBase){
			if(bd.first==date){
				N=bd.second.size();
			}
		}
		DataBase.erase(date);				
		return N;
	}

	void Find(const Date& date) const{
		for(const auto& bd : DataBase){
			if(bd.first==date){
				for(const auto& event:bd.second){
					cout << event << endl;
				}
			}
		}
	}

  	void Print() const{
  		for(const auto& db : DataBase){
			for(const auto& s:db.second){
				cout << db.first << " " << s << endl;  
			}
  		}
  	}
	private:
  	map<Date,set<string>> DataBase;
};

void DeleteEvent(Database& db,const Date& data,const string& event){
	if(db.DeleteEvent(data,event)){
		cout << "Deleted successfully" << endl;
	} else{
		cout << "Event not found" << endl;
	}
}

int main() {
	Database db;
	string command;
	int i=0;
	while (getline(cin, command)) {
		istringstream input(command);
		string com;
		input >> com;
		if(com=="Add"){
			Date data;
			string event;
			Input(input,data,i);
			if(i) {return 0;}
			input >> event;
			db.AddEvent(data,event);
		}else{
			if(com=="Del"){
				Date data;
				string event;
				Input(input,data,i);
				if(i) {return 0;}
				input >> event;
				if(event.size()!=0){
					DeleteEvent(db,data,event);
				}
				else{
					cout << "Deleted " << db.DeleteDate(data) << " events" << endl; 
				}	
			}else{
				if(com=="Print"){
					db.Print();
				} else{
					if(com=="Find"){
						Date data;
						Input(input,data,i);
						if(i) {return 0;}
						db.Find(data);
					}
					else{
						if(command.size()!=0){
							cout << "Unknown command: " << com << endl;
						}
					}	
				}
			}
		}
	}
	return 0;
}


