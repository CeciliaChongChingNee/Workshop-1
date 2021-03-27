#include <iostream>
#include <string>
#include "MyList.h"
using namespace std;

#ifndef DATEMANAGER
#define DATEMANAGER

/*
count number of leap year before year x (year x will be counted differently)
get years in term of days before year x (year * 365 + numberOfLeapYear)
calculate number of month in terms of days before year x (based on odd and even number and which portion < June or > June)
February will be dealt differently (check leap year)
finally all add to the day

get the difference in day between the two to get the result

*/


class DateManager {

private:
	int day, month, year;
	bool isLeapYear;


public:
	DateManager(string date);
	void setDay(int day);
	int getDay();
	void setMonth(int month);
	int getMonth();
	void setYear(int year);
	int getYear();
	void setLeapYear(bool isLeapYear);
	bool getLeapYear();
	void checkLeapyear();
	int getDifference(DateManager date);
	int getNumberOfDays();
	int getNumberOfLeapYear(int year);
	int getNumberOfMonthInDays(int month);

};

//split the string into list of integers
MyList<int> splitDate(string date) {

	string number = "";
	MyList<int> numberList;

	for (int i = 0; i <= date.length(); i++) {
	
		if (i != date.length()) {

			if (date.at(i) != '-') {

				number.append(1, date.at(i));

			}
			else {

				if (numberList.isEmpty()) {

					numberList.setHead(stoi(number));
					number = "";

				}
				else {

					numberList.addToList(stoi(number));
					number = "";

				}

			}

		
		}

		else {

			numberList.addToList(stoi(number));
			number = "";		
		
		}

		
	
	}

	return numberList;

}

//count the number of leap year before current year
int DateManager::getNumberOfLeapYear(int year) {

	int counter = 0;

	//count number of multiple from		
	for (int i = 1; i < year; i *= 4) {

		if (year % 4 == 0) {
			if (year % 100 == 0) {
				if (year % 400 == 0) {

					//leap year
					counter++;
				
				}
			}
			else {

				//is leap year
				counter++;

			}

		}
	
	}

	return counter;

}

//count the number of days before the current month
int DateManager::getNumberOfMonthInDays(int month) {

	int days = 0;

	for (int i = 1; i < month; i++) {

		if (i <= 7) {
		
			if (i % 2 == 0) {

				if (i == 2 && getLeapYear()) {

					days += 29;
				
				}
				else if(i==2 && !getLeapYear()){

					days += 28;
				
				}
				else {

					days += 30;
				
				}
			
			}
			else {

				days += 31;
			
			}
		
		}
		else {

			if (i % 2 == 0) {
			
				days += 31;
			
			}
			else {
			
				days += 30;

			}
		
		}
	
	}

	return days;

}

//constructor for Date Manager
DateManager::DateManager(string date) {

	//TODO : convert 27/12/2020 to value for day, month and year
	MyList<int> numberList = splitDate(date);

	//hardcode add item into this datemanager
	numberList.goToHead();
	this->year = numberList.getCurrent()->element;
	numberList.moveToNext();
	this->month = numberList.getCurrent()->element;
	numberList.moveToNext();
	this->day = numberList.getCurrent()->element;

	checkLeapyear();

}

//setter for day
void DateManager::setDay(int day) {

	this->day = day;
}

//getter for day
int DateManager::getDay() {

	return this->day;

}

//setter for month
void DateManager::setMonth(int month) {

	this->month = month;

}

//getter for month
int DateManager::getMonth() {

	return this->month;

}

//setter for year
void DateManager::setYear(int year) {

	this->year = year;

}

//getter for year
int DateManager::getYear() {

	return this->year;

}

//setter for leap year
void DateManager::setLeapYear(bool isLeapYear) {

	this->isLeapYear = isLeapYear;

}

//getter for leap year
bool DateManager::getLeapYear() {

	return this->isLeapYear;

}

//check Leap year
void DateManager::checkLeapyear() {

	bool isLeapYear = false;

	if (this->year % 4 == 0) {
		if (this->year % 100 == 0) {
			if (this->year % 400 == 0) {

				//leap year
				isLeapYear = true;

			}
		}
		else {

			//is leap year
			isLeapYear = true;

		}

	}

	setLeapYear(isLeapYear);

}

//get difference between this date and another date
int DateManager::getDifference(DateManager date) {

	return getNumberOfDays() - date.getNumberOfDays();

}

//get total number of days 
int DateManager::getNumberOfDays() {

	//count number of leap years before this year
	int numberOfYearInDays = (365 * (getYear() - 1)) + getNumberOfLeapYear(getYear());
	int numberOfMonthInDays = getNumberOfMonthInDays(getMonth());

	return numberOfYearInDays + numberOfMonthInDays + getDay();

}


#endif // !DATEMANAGER
