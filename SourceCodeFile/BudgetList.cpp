/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of BudgetList.
*/

#include <iostream>
#include <iomanip>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "List.h"
using namespace std;

//constructor of BudgetList
BudgetList::BudgetList() {
	BudgetList* next = NULL;
}

//set budgetID
void BudgetList::setBudgetID(string budgetID) {
	this->budgetID = budgetID;
}

//get budgetID
string BudgetList::getBudgetID() {
	if (this->budgetID.empty()) {
		this->budgetID = generateBudgetID();
	}
	return budgetID;
}

//set customerID
void BudgetList::setCustomerID(int userID) {
	this->customerID = userID;
}

//get customerID
int BudgetList::getCustomerID() {
	return customerID;
}

//set budgetTypeID
void BudgetList::setBudgetTypeID(string budgetTypeID) {
	this->budgetTypeID = budgetTypeID;
}

//get budgetTypeID
string BudgetList::getBudgetTypeID() {
	return budgetTypeID;
}

//set budgetStartDate
void BudgetList::setBudgetStartDate(string budgetStartDate) {
	this->budgetStartDate = budgetStartDate;
}

//get budgetStartDate
string BudgetList::getBudgetStartDate() {
	return budgetStartDate;
}

//set budgetStatus
void BudgetList::setBudgetStatus(string budgetStatus) {
	this->budgetStatus = budgetStatus;
}

//get budgetStatus
string BudgetList::getBudgetStatus() {
	return budgetStatus;
}

//set budgetTotalAmount
void BudgetList::setBudgetTotalAmount(double budgetTotalAmount) {
	this->budgetTotalAmount = budgetTotalAmount;
}

//get budgetTotalAmount
double BudgetList::getBudgetTotalAmount() {
	return budgetTotalAmount;
}

//set budgetRepeated
void BudgetList::setBudgetRepeated(char budgetRepeated) {
	this->budgetRepeated = budgetRepeated;
}

//get budgetRepeated
char BudgetList::getBudgetRepeated() {
	return budgetRepeated;
}

//save the class to database
void BudgetList::save() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//check if entity exist in database
	string select_query = "SELECT * FROM `budget` WHERE Budget_ID = '" +
		this->getBudgetID() + "'";

	//Execute query (get the data from database)
	int state = mysql_query(conn, select_query.c_str());

	if (state != 0) {
	
		cout << select_query;
		cout << endl;
		cout << mysql_error(conn);
		cout << endl;
		system("pause");
		cout << endl;

	}

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

	//if result returned more than 0 row
	if (num_row > 0) {

		//update the local menu object to database
		string updateQuery = "UPDATE `budget` SET "
							 "Customer_ID = "
							 " " + to_string(getCustomerID()) + ", "
							 "Budget_Type_ID = "
							 " '" + getBudgetTypeID() + "', "
							 "Budget_StartDate = "
							 " '" + getBudgetStartDate() + "', "
							 "Budget_Status = "
							 " '" + getBudgetStatus() + "', "
							 "Budget_TotalAmount = "
							 " " + to_string(getBudgetTotalAmount()) + ", "
							 "Budget_Repeated = "
							 " '" + getBudgetRepeated() + "' "
							 " WHERE Budget_ID = "
							 " '" + getBudgetID() + "' ";

		//execute update query
		int state = mysql_query(conn, updateQuery.c_str());

		if (state != 0) {

			cout << mysql_error(conn) << endl;
			system("pause");
			cout << endl;

		}

		system("pause");

	}

	//if result returned 0 row
	else {

		//do an insert
		string insertQuery = " INSERT INTO `budget` "
			" (Budget_ID, Customer_ID, Budget_Type_ID, "
			" Budget_Status, Budget_TotalAmount, Budget_Repeated)"
			" VALUES('" + getBudgetID() + "', "
			" " + to_string(getCustomerID()) + ", "
			" '" + getBudgetTypeID() + "', "
			" '" + getBudgetStatus() + "', "
			" " + to_string(getBudgetTotalAmount()) + ", "
			" '" + getBudgetRepeated() + "') ";

		//Execute query (send to database)
		int state = mysql_query(conn, insertQuery.c_str());

		//if error with sql 
		if (state != 0) {

			cout << insertQuery << endl;

			cout << mysql_error(conn) << endl;
			system("pause");
			cout << endl;
		}

	}

}

//generate Order ID
string BudgetList::generateBudgetID() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//calculate total amount of payment ID in database
	string count_query = "SELECT * FROM `budget`";

	//Execute query (get the data from database)
	mysql_query(conn, count_query.c_str());

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

	//set the first character of the string to be B
	string tempID = "B";

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

//function to display as a row
void BudgetList::displayAsRow() {

	cout << "| " << getBudgetID() << " | "
		<< left << setw(5) << to_string(getCustomerID()) << "| "
		<< setw(5) << getBudgetTypeID() << "| "
		<< setw(15) << getBudgetStartDate() << "| "
		<< setw(10) << getBudgetStatus() << "| "
		<< setw(7) << fixed << setprecision(2)
		<< getBudgetTotalAmount() << "| "
		<< setw(6) << getBudgetRepeated() << "| " << endl;

	cout << "---------------------------------------";
	cout << "-----------------------------";
	cout << endl;
}