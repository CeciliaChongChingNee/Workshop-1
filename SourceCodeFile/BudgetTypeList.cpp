/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of BudgetTypeList.
*/

#include <iostream>
#include <iomanip>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "List.h"
using namespace std;

//constructor of BudgetTypeList
BudgetTypeList::BudgetTypeList() {
	BudgetTypeList* next = NULL;
}

//set budgetTypeID
void BudgetTypeList::setBudgetTypeID(string budgetTypeID) {

	this->budgetTypeID = budgetTypeID;
}

//get budgetTypeID
string BudgetTypeList::getBudgetTypeID() {

	if (this->budgetTypeID.empty()) {
		this->budgetTypeID = generateBudgetTypeID();
	}
	return budgetTypeID;

}

//set budgetLabel
void BudgetTypeList::setBudgetLabel(string budgetLabel) {
	this->budgetLabel = budgetLabel;
}

//get budgetLabel
string BudgetTypeList::getBudgetLabel() {
	return budgetLabel;
}

//set budgetDuration
void BudgetTypeList::setBudgetDuration(string budgetDuration) {
	this->budgetDuration = budgetDuration;
}

//get budgetDuration
string BudgetTypeList::getBudgetDuration() {
	return budgetDuration;
}

//function to display as a row
void BudgetTypeList::displayAsRow() {

	cout << "| " << getBudgetTypeID() <<" | " 
	<< left << setw(15) << getBudgetLabel() << "| "
	<< setw(10) << getBudgetDuration() << "|" << endl;

	cout << "-------------------------------------";
	cout << endl;
}

//function to save local BudgetType object to database
void BudgetTypeList::save()
{
	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//check if entity exist in database
	string select_query = "SELECT * FROM `budget type`"
		"WHERE Budget_Type_ID = "
		"'" + this->getBudgetTypeID() + "'";

	//Execute query (get the data from database)
	mysql_query(conn, select_query.c_str());

	//Extract data into result
	res = mysql_store_result(conn);
	
	int num_row;

	//if result is returned
	if (res) {

		//Get number of row and column
		num_row = mysql_num_rows(res);
	
	}

	//if result not returned
	else {
	
		num_row = 0;

	}

	//if result returned more than 0 row
	if (num_row > 0) {

		//update the local menu object to database
		string updateQuery = "UPDATE `budget type` SET "
			"Budget_Label = "
			" '" + getBudgetLabel() + "', "
			"Budget_Duration = "
			" '" + getBudgetDuration() + "' "
			" WHERE Budget_Type_ID = "
			" '" + getBudgetTypeID() + "' ";


		//execute update query
		int state = mysql_query(conn, updateQuery.c_str());

		if (state != 0) {

			cout << mysql_error(conn);

		}

	}

	//if result returned 0 row
	else {

		//do an insert
		string insertQuery = " INSERT INTO `budget type` "
			" (Budget_Type_ID, Budget_Label, Budget_Duration) "
			" VALUES('" + getBudgetTypeID() + "', "
			" '" + getBudgetLabel() + "', "
			" '" + getBudgetDuration() + "') ";

		//Execute query (send to databse)
		mysql_query(conn, insertQuery.c_str());

	}
}

//function to generate BudgetTypeID
string BudgetTypeList::generateBudgetTypeID()
{
	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//calculate total amount of budget type ID in database
	string count_query = "SELECT * FROM `budget type`";

	//Execute query (get the data from database)
	mysql_query(conn, count_query.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	int num_row;
	
	//if result returned
	if (res) {
		
		num_row = mysql_num_rows(res);

	}

	//if result not returned
	else {
	
		num_row = 0;

	}

	//turn number of row into a string
	string digit = to_string(num_row + 1);

	//set the first character of the string to be G
	string tempID = "G";

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
