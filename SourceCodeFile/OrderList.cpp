/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of OrderList.
*/

#include <iostream>
#include <iomanip>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "List.h"
using namespace std;

//constructor of OrderList
OrderList::OrderList() {
	OrderList* next;
}

//set orderID
void OrderList::setOrderID(string orderID) {
	this->orderID = orderID;
}

//get orderID
string OrderList::getOrderID() {
	if (this->orderID.empty()) {
		this->orderID = generateOrderID();
	}
	return orderID;
}

//set customerID
void OrderList::setCustomerID(int userID) {
	this->customerID = userID;
}

//get customerID
int OrderList::getCustomerID() {
	return customerID;
}

//set vendorID
void OrderList::setVendorID(int userID) {
	this->vendorID = userID;
}

//get vendorID
int OrderList::getVendorID() {
	return vendorID;
}

//set orderOrderType
void OrderList::setOrderType(string orderType) {
	this->orderType = orderType;
}

//get orderType
string OrderList::getOrderType() {
	return orderType;
}

//set orderAddress
void OrderList::setOrderAddress(string orderAddress) {
	this->orderAddress = orderAddress;
}

//get orderAddress
string OrderList::getOrderAddress() {
	return orderAddress;
}

//set orderDate
void OrderList::setOrderDate(string orderDate) {
	this->orderDate = orderDate;
}

//get orderDate
string OrderList::getOrderDate() {
	return orderDate;
}

//set orderExpectedTime
void OrderList::setOrderExpectedTime(string orderExpectedTime) {
	this->orderExpectedTime = orderExpectedTime;
}

//get orderExpectedTime
string OrderList::getOrderExpectedTime() {
	return orderExpectedTime;
}

//set orderTotalAmount
void OrderList::setOrderTotalAmount(double orderTotalAmount) {
	this->orderTotalAmount = orderTotalAmount;
}

//get orderTotalAmount
double OrderList::getOrderTotalAmount() {
	return orderTotalAmount;
}

//set orderStatus
void OrderList::setOrderStatus(string orderStatus) {
	this->orderStatus = orderStatus;
}

//get orderStatus
string OrderList::getOrderStatus(){
	return orderStatus;
}

//save the class to database
void OrderList::save() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//check if entity exist in database
	string select_query = "SELECT * FROM `order` WHERE Order_ID = '" +
						   this->getOrderID() + "'";

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
		string updateQuery = "UPDATE `order` SET "
							 "Customer_ID = "
							 " " + to_string(getCustomerID()) + ", "
							 "Vendor_ID = "
							 " " + to_string(getVendorID()) + ", "
							 "Order_Type = "
							 " '" +getOrderType() + "', "
							 "Order_Address = "
							 " '" + getOrderAddress() + "', "
							 "Order_Date = "
							 " '" + getOrderDate() + "', "
							 "Order_ExpectedTime = "
							 " '" + getOrderExpectedTime() + "', "
							 "Order_TotalAmount = "
							 " " + to_string(getOrderTotalAmount()) + ", "
							 "Order_Status = "
							 " '" + getOrderStatus() + "'"
							 " WHERE Order_ID = "
							 " '" + getOrderID() + "' ";

		//execute update query
		int state = mysql_query(conn, updateQuery.c_str());

		if (state != 0) {

			cout << updateQuery;
			cout << endl;
			cout << mysql_error(conn) << endl;
			system("pause");
			cout << endl;

		}

		system("pause");

	}

	//if result returned 0 row
	else {

		//do an insert
		string insertQuery = " INSERT INTO `order` "
							 " (Order_ID, Customer_ID, Vendor_ID, "
							 " Order_Type, Order_Address, Order_Date, "
							 " Order_ExpectedTime, Order_TotalAmount, Order_Status)"
							 " VALUES('" + getOrderID() + "', "
							 " " + to_string(getCustomerID()) + ", "
							 " " + to_string(getVendorID()) + ", "
							 " '" + getOrderType() + "', "
							 " '" + getOrderAddress() + "', "
							 " '" + getOrderDate() + "', "
							 " '" + getOrderExpectedTime() + "', "
							 " " + to_string(getOrderTotalAmount()) + ", "
							 " '" + getOrderStatus() + "') ";

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
string OrderList::generateOrderID() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//calculate total amount of payment ID in database
	string count_query = "SELECT * FROM `order`";

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

	//set the first character of the string to be D
	string tempID = "D";

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
void OrderList::displayAsRow() {

	cout << "| " << getOrderID() << " | "
		 << left << setw(4) << to_string(getCustomerID()) << "| "
		 << setw(4) << to_string(getVendorID()) << "| "
		 << setw(10) << getOrderType() << "| "
		 << setw(30) << getOrderAddress() << "| "
		 << setw(12) << getOrderDate() << "| "
		 << setw(10) << getOrderExpectedTime() << "| "
		 << setw(7) << fixed << setprecision(2)
		 << getOrderTotalAmount() << "| "
		 << setw(12) << getOrderStatus() << "| " << endl;

	cout << "---------------------------------------";
	cout << "---------------------------------------";
	cout << "----------------------------------";
	cout << endl;
}