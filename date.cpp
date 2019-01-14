#include "date.h"
Date::Date()
	:year_(0)
	,month_(0)
	,day_(0){
}
Date::Date(const int& year,const int& month,const int& day)
	:year_(year)
	,month_(month)
	,day_(day){
}

int Date::GetYear() const{
	return year_;
}
int Date::GetMonth() const{
	return month_;
}
int Date::GetDay() const{
	return day_;
}

Date ParseDate(istream& is){
    Date d;
    int i=0;
    Input(is, d, i);
    return d;
}

string to_string(const Date& d){
    stringstream str;
    str << d;
    string s;
    str >> s;
    return s;
}

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

bool operator<=(const Date& lhs, const Date& rhs){
    if(lhs.GetYear()<=rhs.GetYear()){
        return 1;
    }else{
        if(lhs.GetYear()==rhs.GetYear()&&lhs.GetMonth()<=rhs.GetMonth()){
            return 1;
        }else{
            if(lhs.GetYear()==rhs.GetYear()&&lhs.GetMonth()==rhs.GetMonth()&&lhs.GetDay()<=rhs.GetDay()){
                return 1;
            }
        }
    }
    return 0;
}

bool operator>(const Date& lhs, const Date& rhs){
    return !(lhs<=rhs);
}

bool operator>=(const Date& lhs, const Date& rhs){
    return !(lhs<rhs);
}
