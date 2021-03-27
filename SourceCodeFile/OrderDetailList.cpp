/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of OrderDetailList.
*/

#include <iostream>
#include <iomanip>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "List.h"
using namespace std;

//constructor of OrderDetailList
OrderDetailList::OrderDetailList() {
	OrderDetailList* next = NULL;
}

//set orderDetailList
void OrderDetailList::setOrderDetailID(string orderDetailID) {
	this->orderDetailID = orderDetailID;
}

//get orderDetailList
string OrderDetailList::getOrderDetailID() {
	if (this->orderDetailID.empty()) {
		this->orderDetailID = generateOrderDetailID();
	}
	return orderDetailID;
}

//set orderID
void OrderDetailList::setOrderID(string orderID) {
	this->orderID = orderID;
}

//get orderID
string OrderDetailList::getOrderID() {
	return orderID;
}

//set customerID
void OrderDetailList::setCustomerID(int customerID) {
	this->customerID = customerID;
}

//get customerID
int OrderDetailList::getCustomerID() {
	return	this->customerID;
}

//set menuID
void OrderDetailList::setMenuID(string menuID) {
	this->menuID = menuID;
}

//get menuID
string OrderDetailList::getMenuID() {
	return this->menuID;
}

//set itemQuantity
void OrderDetailList::setItemQuantity(int itemQuantity) {
	this->itemQuantity = itemQuantity;
}

//get itemQuantity
int OrderDetailList::getItemQuantity() {
	return itemQuantity;
}

//set totalItemPrice
void OrderDetailList::setTotalItemPrice(double totalItemPrice) {
	this->totalItemPrice = totalItemPrice;
}

//get totalItemPrice
double OrderDetailList::getTotalItemPrice() {
	return totalItemPrice;
}

//save the class to database
void OrderDetailList::save() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//check if entity exist in database
	string select_query = "SELECT * FROM `order detail` WHERE Order_Detail_ID = '" + 
						   this->getOrderDetailID() + "'";

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
		string updateQuery = "UPDATE `order detail` SET "
							 "Order_ID = "
							 " '" + getOrderID() + "', "
							 "Customer_ID = "
							 " " + to_string(getCustomerID()) + ", "
							 "Menu_ID = "
							 " '" + getMenuID() + "', "
							 "Item_Quantity = "
							 " " + to_string(getItemQuantity()) + ", "
							 "Total_Item_Price = "
							 " " + to_string(getTotalItemPrice()) + " "
							 " WHERE Order_Detail_ID = "
							 " '" + getOrderDetailID() + "' ";


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
		string insertQuery = " INSERT INTO `order detail` "
							 " (Order_Detail_ID, Order_ID, Customer_ID, "
							 " Menu_ID, Item_Quantity, Total_Item_Price)"
							 " VALUES('" + getOrderDetailID() + "', "
							 " '" + getOrderID() + "', "
							 " " + to_string(getCustomerID()) + ", "
							 " '" + getMenuID() + "', "
							 " " + to_string(getItemQuantity()) + ", "
							 " " + to_string(getTotalItemPrice()) + ") ";

		//Execute query (send to database)
		int state = mysql_query(conn, insertQuery.c_str());

		//if error with sql 
		if (state != 0) {

			cout << mysql_error(conn) << endl;
			system("pause");
			cout << endl;

		}

	}

}

//generate order detail ID
string OrderDetailList::generateOrderDetailID() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//calculate total amount of payment ID in database
	string count_query = "SELECT * FROM `order detail`";

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

	//set the first character of the string to be L
	string tempID = "L";

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
void OrderDetailList::displayAsRow() {

	cout << "| " <<left << setw(5) << getOrderDetailID() << " | "
		<< left << setw(10) << getMenuID() << "| "
		<< setw(8) << getItemQuantity() << "| "
		<< setw(7) << fixed << setprecision(2)
		<< getTotalItemPrice() << "| " << endl;

	cout << "----------------------------------------";
	cout << endl;
}