/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of MealTypeList.
*/
#include <iostream>
#include <iomanip>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "List.h"
using namespace std;

//constructor of MealTypeList
MealTypeList::MealTypeList() {
	MealTypeList* next = NULL;
}

//set mealTypeID
void MealTypeList::setMealTypeID(string mealTypeID) {
	this->mealTypeID = mealTypeID;
}

//get mealTypeID
string MealTypeList::getMealTypeID() {

	if (this->mealTypeID.empty()) {
		this->mealTypeID = generateMealTypeID();
	}
	return mealTypeID;
}

//set typeName
void MealTypeList::setTypeName(string typeName) {
	this->typeName = typeName;
}

//get typeName
string MealTypeList::getTypeName() {
	return typeName;
}

//set timeStart
void MealTypeList::setTimeStart(string timeStart) {
	this->timeStart = timeStart;
}

//get timeStart
string MealTypeList::getTimeStart() {
	return timeStart;
}

//set timeEnd
void MealTypeList::setTimeEnd(string timeEnd) {
	this->timeEnd = timeEnd;
}

//get timeEnd
string MealTypeList::getTimeEnd() {
	return timeEnd;
}

//function to display as a row
void MealTypeList::displayAsRow() {
	
	cout << "| " << getMealTypeID() << " | " 
	<< left << setw(15) << getTypeName() << "| "
	<< setw(10) << getTimeStart() << "| "
	<< setw(10) << getTimeEnd() << "|"<< endl;

	cout << "-------------------------------------";
	cout << "------------";
	cout << endl;

}

//function to save local MealType object to database
void MealTypeList::save()
{
	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//check if entity exist in database
	string select_query = " SELECT * FROM `meal type` " 
						  " WHERE Meal_Type_ID = " 
						  "'" + this->getMealTypeID() + "'";

	//Execute query (get the data from database)
	mysql_query(conn, select_query.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	int num_row;

	//if exist in database
	if (res) {

		num_row = mysql_num_rows(res);

	}

	//if not exist in database
	else {

		num_row = 0;

	}

	//if result returned more than 0 row
	if (num_row > 0) {
	
		//update the local menu object to database
		string updateQuery = "UPDATE `meal type` SET "
							 "Type_Name = "
							 " '" + getTypeName() + "', "
							 "Time_Start = "
							 " '" + getTimeStart() + "', "
							 "Time_End = "
							 " '" + getTimeEnd() + "' "
							 " WHERE Meal_Type_ID = "
							 " '" + getMealTypeID() + "' ";

		//execute update query
		int state = mysql_query(conn, updateQuery.c_str());

		if (state != 0) {

			cout << mysql_error(conn);
			cout << endl;

		}


	}

	//if result returned 0 row
	else {

		//do an insert
		string insertQuery = " INSERT INTO `meal type` "
			" (Meal_Type_ID, Type_Name, Time_Start, Time_End) "
			" VALUES('" + getMealTypeID() + "', "
			" '" + getTypeName() + "', "
			" '" + getTimeStart() + "', "
			" '" + getTimeEnd() + "') ";

		//Execute query (send to databse)
		mysql_query(conn, insertQuery.c_str());

	}
}

//function to generate MealTypeID
string MealTypeList::generateMealTypeID()
{
	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//calculate total amount of meal type ID in database
	string count_query = "SELECT * FROM `meal type`";

	//Execute query (get the data from database)
	mysql_query(conn, count_query.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	int num_row;

	if (res) {

		//Get number of row
		num_row = mysql_num_rows(res);

	}
	//result not returned
	else {

		num_row = 0;
	
	}

	//turn number of row into a string
	string digit = to_string(num_row + 1);

	//set the first character of the string to be T
	string tempID = "T";

	//loop for 3 - (the amount of character in digit) 
	for (int i = 0; i < 3 - digit.length(); i++) {

		//append 0 to tempID
		tempID.append("0");

	}

	//append Digit to tempID
	tempID.append(digit);

	mysql_close(conn);

	//return tempID
	return tempID;
}
