/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of MenuList.
*/

#include <iostream>
#include <iomanip>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "List.h"
using namespace std;

//constructor of MenuList
MenuList::MenuList() {
	MenuList* next = NULL;
}

//set menuID
void MenuList::setMenuID(string menuID) {
	this->menuID = menuID;
}

//get menuID
string MenuList::getMenuID() {
	if (this->menuID.empty()) {
		this->menuID = generateMenuID();
	}
	return menuID;
}

//set vendorID
void MenuList::setVendorID(int userID) {
	this->vendorID = userID;
}

//get vendorID
int MenuList::getVendorID() {
	return vendorID;
}

//set mealTypeID
void MenuList::setMealTypeID(string mealTypeID) {
	this->mealTypeID = mealTypeID;
}

//get mealTypeID
string MenuList::getMealTypeID() {
	return mealTypeID;
}

//set menuName
void MenuList::setMenuName(string menuName) {
	this->menuName = menuName;
}

//get menuName
string MenuList::getMenuName() {
	return menuName;
}

//set menuDescription
void MenuList::setMenuDescription(string menuDescription) {
	this->menuDescription = menuDescription;
}

//get menuDescription
string MenuList::getMenuDescription() {
	return menuDescription;
}

//set menuQuantity
void MenuList::setMenuQuantity(int menuQuantity) {
	this->menuQuantity = menuQuantity;
}

//get menuQuantity
int MenuList::getMenuQuantity() {
	return menuQuantity;
}

//set menuPrice
void MenuList::setMenuPrice(double menuPrice) {
	this->menuPrice = menuPrice;
}

//get menuPrice
double MenuList::getMenuPrice() {
	return menuPrice;
}

//display menu as a row
void MenuList::displayAsRow() {

	cout << "| " << getMenuID() << " | "
		<< left << setw(4) << to_string(getVendorID()) << "| "
		<< setw(6) << getMealTypeID() << "| "
		<< setw(30) << getMenuName() << "| "
		<< setw(50) << getMenuDescription() << "| "
		<< setw(5) << getMenuQuantity() << "| "
		<< setw(5) << fixed << setprecision(2)
		<< getMenuPrice() << "|" << endl;

	cout << "-------------------------------------";
	cout << "-------------------------------------";
	cout << "-------------------------------------";
	cout << "---------";
	cout << endl;

}

//save the class to database
void MenuList::save() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//check if entity exist in database
	string select_query = "SELECT * FROM menu WHERE Menu_ID = '" + this->getMenuID() + "'";

	//Execute query (get the data from database)
	mysql_query(conn, select_query.c_str());

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
		string updateQuery = "UPDATE `menu` SET "
							 "Vendor_ID = "
							 " " + to_string(getVendorID()) + ", "
							 "Meal_Type_ID = "
							 " '" + getMealTypeID() + "', "
							 "Menu_Name = "
							 " '" + getMenuName() + "', "
							 "Menu_Description = "
							 " '" + getMenuDescription() + "', "
							 "Menu_Quantity = "
							 " " + to_string(getMenuQuantity()) + ", "
							 "Menu_Price = "
							 " '" + to_string(getMenuPrice()) + "' "
							 " WHERE Menu_ID = "
							 " '" + getMenuID() + "' ";


		//execute update query
		int state = mysql_query(conn, updateQuery.c_str());

		if (state != 0) {

			cout << mysql_error(conn) << endl;
		
		}

		system("pause");

	}

	//if result returned 0 row
	else {

		//do an insert
		string insertQuery = " INSERT INTO menu "
							 " (Menu_ID, Vendor_ID, Meal_Type_ID, "
							 " Menu_Name, Menu_Description, Menu_Quantity, Menu_Price)"
							 " VALUES('" + getMenuID() + "', "
							 " '" + to_string(getVendorID()) + "', "
							 " '" + getMealTypeID() + "', "
							 " '" + getMenuName() + "', "
							 " '" + getMenuDescription() + "', "
							 " '" + to_string(getMenuQuantity()) + "', "
							 " '" + to_string(getMenuPrice()) + "') ";

		//Execute query (send to databse)
		int state = mysql_query(conn, insertQuery.c_str());

		if (state != 0) {
			cout << mysql_error(conn) << endl;
		}

	}

}

string MenuList::generateMenuID() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//calculate total amount of menu ID in database
	string count_query = "SELECT * FROM menu";

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

	//set the first character of the string to be M
	string tempID = "M";

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