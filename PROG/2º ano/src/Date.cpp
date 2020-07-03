#include "Date.h"

Date::Date() {
}

Date::Date(string fileLine) {

	size_t pos = 0;
	size_t temp_pos = 0;
	char delim = '/';
	string data;

	Date date;

	pos = fileLine.find(delim, temp_pos);
	data = fileLine.substr(temp_pos, pos - temp_pos);
	year = (unsigned short)stoi(data, nullptr, 0);
	temp_pos = pos + 1;

	pos = fileLine.find(delim, temp_pos);
	data = fileLine.substr(temp_pos, pos - temp_pos);
	if (data[0] == '0') {
		data = data.substr(1, 1); // remove the 0, count only the number
		month = (unsigned short)stoi(data, nullptr, 0);
	}
	else
		month = (unsigned short)stoi(data, nullptr, 0);
	temp_pos = pos + 1;

	pos = fileLine.find(delim, temp_pos);
	data = fileLine.substr(temp_pos, pos - temp_pos);
	if (data[0] == '0') {
		data = data.substr(1, 1);
		day = (unsigned short)stoi(data, nullptr, 0);
	}
	else
		day = (unsigned short)stoi(data, nullptr, 0);
}

/*********************************
 * GET Methods
 ********************************/
unsigned short Date::getDay() const {

	return day;
}


unsigned short Date::getMonth() const {

	return month;
}

unsigned Date::getYear() const {

	return year;
}

/*********************************
 * SET Methods
 ********************************/

void Date::setDay(unsigned short day) {

	this->day = day;
}
void Date::setMonth(unsigned short month) {

	this->month = month;
}

void Date::setYear(unsigned year) {

	this->year = year;
}

bool Date::checkOrderDates(Date end) {

	Date begin = *this;
	bool check = true;

	if (begin.year > end.year)
		check = false;
	else if (begin.year < end.year)
		check = true;
	else if (begin.year == end.year) {
		if (begin.month > end.month)
			check = false;
		else if (begin.month < end.month)
			check = true;
		else if (begin.month == end.month) {
			if (begin.day > end.day)
				check = false;
			else if (begin.day <= end.day)
				check = true;
		}
	}

	return check;
}

bool Date::checkValidYear()
{
	if (year >= 2019 && year <= 2030)
		return true;
	else
		return false;
}

bool Date::checkValidMonth()
{
	if (month >= 1 && month <= 12)
		return true;
	else
		return false;
}

bool Date::checkValidDay()
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) // 31 day months
		if (day >= 1 && day <= 31)
			return true;
		else
			return false;

	else if (month == 4 || month == 6 || month == 9 || month == 11) // 30 day months
		if (day >= 1 && day <= 30)
			return true;
		else
			return false;

	else if (month == 2) // february (accounts for 28/29 day cycles)
		if (year % 4)
			if (day >= 1 && day <= 29)
				return true;
			else
				return false;
		else
			if (day >= 1 && day <= 28)
				return true;
			else
				return false;
	else return false;
}


/*********************************
 * Show Date
 ********************************/

ostream& operator<<(ostream& out, const Date & date) {

	out << date.year << "/" << date.month << "/" << date.day;
	return out;
}
