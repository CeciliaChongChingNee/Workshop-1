/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of PaymentList.
*/

#include <iostream>
#include <iomanip>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "List.h"
using namespace std;

//constructor of PaymentList
PaymentList::PaymentList() {
	PaymentList* next = NULL;
}

//set orderID
void PaymentList::setOrderID(string orderID) {
	this->orderID = orderID;
}

//get orderID
string PaymentList::getOrderID() {
	return orderID;
}

//set customerid
void PaymentList::setCustomerID(int userID) {
	this->customerID = userID;
}

//get customerID
int PaymentList::getCustomerID() {
	return customerID;
}

//set paymentTotalAmount
void PaymentList::setPaymentTotalAmount(double paymentTotalAmount) {
	this->paymentTotalAmount = paymentTotalAmount;
}

//get paymentTotalAmount
double PaymentList::getPaymentTotalAmount() {
	return paymentTotalAmount;
}

//set paymentDate
void PaymentList::setPaymentDate(string paymentDate) {
	this->paymentDate = paymentDate;
}

//get paymentDate
string PaymentList::getPaymentDate() {
	return paymentDate;
}

//set paymentTime
void PaymentList::setPaymentTime(string paymentTime) {
	this->paymentTime = paymentTime;
}

//get paymentTime
string PaymentList::getPaymentTime() {
	return paymentTime;
}

//save the class to database
void PaymentList::save() {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = connection();

	//check if entity exist in database
	string select_query = "SELECT * FROM payment WHERE Order_ID = "
						  "'" + getOrderID() + "'"
						  " AND "
						  " Customer_ID = "
						  " " + to_string(getCustomerID()) + " ";


	//Execute query (get the data from database)
	int state = mysql_query(conn, select_query.c_str());

	if (state != 0) {
	
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
		string updateQuery = "UPDATE order SET "
							 "Payment_TotalAmount = "
							 " " + to_string(getPaymentTotalAmount()) + ", "
							 "Payment_Date = "
							 " '" + getPaymentDate() + "', "
							 "Payment_Time = "
							 " '" + getPaymentDate() + "', "
							 " WHERE Order_ID = "
							 " '" + getOrderID() + "' "
							 " AND "
							 " Customer_ID = "
							 " " + to_string(getCustomerID()) + " ";

		//execute update query
		int state = mysql_query(conn, updateQuery.c_str());

		if (state != 0) {

			cout << mysql_error(conn) << endl;
			system("pause");
			cout << endl;

		}

	}

	//if result returned 0 row
	else {

		//do an insert
		string insertQuery = " INSERT INTO payment "
							 " (Order_ID, Customer_ID, Payment_TotalAmount, "
							 " Payment_Date, Payment_Time)"
							 " VALUES('" + getOrderID() + "', "
							 " " + to_string(getCustomerID()) + ", "
							 " " + to_string(getPaymentTotalAmount()) + ", "
							 " '" + getPaymentDate() + "', "
							 " '" + getPaymentTime() + "') ";

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

//function to display as a row
void PaymentList::displayAsRow() {

	cout << "| " << getOrderID() << " | "
		<< left << setw(15) << to_string(getCustomerID()) << "| "
		<< setw(15) << fixed << setprecision(2)
		<< getPaymentTotalAmount() << "| "
		<< setw(15) << getPaymentDate() << "| "
		<< setw(5) << getPaymentTime() << "| " << endl;

	cout << "-------------------------------------";
	cout << endl;
}

