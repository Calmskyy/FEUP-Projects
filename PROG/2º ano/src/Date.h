#pragma once

#include <iostream>
#include <string>

using namespace std;

class Date {
private:
	unsigned short day;
	unsigned short month;
	unsigned year;

public:
	Date();
	Date(string fileLine);

	// GET methods
	unsigned short getDay() const;
	unsigned short getMonth() const;
	unsigned getYear() const;

	// SET methods

	void setDay(unsigned short day);
	void setMonth(unsigned short month);
	void setYear(unsigned year);

	// other methods */

	friend ostream& operator<<(ostream& out, const Date & date); // display a date
	bool checkOrderDates(Date end); // check if the first date is before the second date
	bool checkValidYear(); // check if the year is past 2019, and reasonably close in the future
	bool checkValidMonth(); // check if the month is valid (1-12)
	bool checkValidDay(); // check if the day is valid (accounts for different months of the year)
};