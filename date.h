#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
class Date {
	public:
	Date();
	Date(const int& year,const int& month,const int& day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	private:
	int year_,month_,day_;
};

Date ParseDate(istream& is);
string to_string(const Date& d);

ostream& operator << (ostream& output, const Date& d);
istream& operator >> (istream& input, Date& d);
istream& Input(istream& input, Date& d, int& i);
bool operator == (const Date& ld,const Date& rd );
bool operator != (const Date& ld,const Date& rd );
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
