#include <iostream>
#include <string>
#include <time.h>
#include <mysql.h>
#include "List.h"
#include "MyList.h"
#include "Login.h"
#include "DatabaseConnection.h"
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

#ifndef VENDORORDERMANAGEMENT_H
#define VENDORORDERMANAGEMENT_H

void vendorOrderManagement(Session currentSession);
void viewVendorOrder(Session currentSession);
void vendorManageOrder(Session currentSession);

void vendorOrderManagement(Session currentSession) {

	//variable of budgetManagement
	string vendorInput;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');

	int numberOfWrongInput = 0;

	//loop for vendor menu management main screen
	while (true) {

		system("CLS");

		//Start for display screen for manage budget module
		cout << "1. View order" << endl;
		cout << "2. Manage order" << endl;
		cout << "3. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, vendorInput);
		cout << endl;
		//End for display screen for manage budget module

		//if vendorInput is equal to 1
		if (vendorInput == "1") {

			//call view vendor menu function
			viewVendorOrder(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if vendorInput is equal to 2
		else if (vendorInput == "2") {

			//call manage menu function
			vendorManageOrder(currentSession);

		}

		//if vendorInput is equal to 3
		else if (vendorInput == "3") {

			return;

		}

		//if vendorInput is not equal to the choice above
		else {

			//display error messenge
			cout << "Sorry, please enter the correct choice.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to admin modue main screen
			cout << "You have entered the wrong input more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to prfile main screen
			return;

		}

	}

}

//function view vendor Order
void viewVendorOrder(Session currentSession) {

	MyList<OrderList> orders;
	MyList<OrderDetailList> details;
	string vendorInputOrderID;

	//select orders that belong to vendor to display
	string select_query = "SELECT * FROM `order` WHERE "
						  " Vendor_ID = "
						  "" + to_string(currentSession.userID) + ""
						  " AND Order_ID IN ("
						  " SELECT Order_ID FROM `payment` "
						  ")";

	int state = mysql_query(conn, select_query.c_str());

	if (state != 0) {

		cout << select_query;
		cout << endl;
		cout << mysql_error(conn);
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

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

		while (row = mysql_fetch_row(res)) {
		
			OrderList temp;
			temp.setOrderID(row[0]);
			temp.setCustomerID(stoi(row[1]));
			temp.setVendorID(stoi(row[2]));
			temp.setOrderType(row[3]);
			temp.setOrderAddress(row[4]);
			temp.setOrderDate(row[5]);
			temp.setOrderExpectedTime(row[6]);
			temp.setOrderTotalAmount(stof(row[7]));
			temp.setOrderStatus(row[8]);

			if (orders.isEmpty()) {

				orders.setHead(temp);

			}
			else {

				orders.addToList(temp);

			}
		
		}

	}

	//if result returned 0 row
	else {
	
		cout << "You have no orders currently";
		cout << endl;
		system("pause");
		cout << endl;
		
		return;

	}

	//ask for orderID to check

	int numberOfTries = 0;

	//loop to check order ID input exist and belongs to vendor
	while (true) {

		//number of times failed in entering menu ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			cout << "Order List" << endl;

			cout << "---------------------------------------";
			cout << "---------------------------------------";
			cout << "-----------------------------------";
			cout << endl;

			cout << "| " << " ID " << " | "
				<< left << setw(4) << "C_ID" << "| "
				<< setw(4) << "V_ID" << "| "
				<< setw(10) << "Type" << "| "
				<< setw(30) << "Address" << "| "
				<< setw(12) << "Date" << "| "
				<< setw(10) << "ETA" << "| "
				<< setw(7) << "Amount" << "| "
				<< setw(12) << "Status" << "| " << endl;

			cout << "---------------------------------------";
			cout << "---------------------------------------";
			cout << "-----------------------------------";
			cout << endl;

			orders.displayList();

			//get menu ID from admin
			cout << "Please enter order ID that you want to view";
			cout << endl;
			cout << "Note: DXXX (e.g: D001)";
			cout << endl;
			getline(cin, vendorInputOrderID);
			cout << endl;

			//get length of user input
			int a = vendorInputOrderID.length();

			//set initial value for boolean flag
			bool hasD = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only D
						if (vendorInputOrderID.at(0) == 'D') {

							//set hasD to true
							hasD = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (vendorInputOrderID.at(i) >= 48 && vendorInputOrderID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasD and hasDigit to false
							hasD = false;
							hasDigit = false;


							//break out of the for loop and go to check hasD and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasD)) {

					//userInput format is wrong
					cout << "Sorry, please follow the format given.";
					cout << endl;
					cout << "Please try again.";
					cout << endl;
					system("pause");
					cout << endl;

					//count number of ID failed
					numberOfIDFailed++;

				}

				//if ID format is correct
				else {

					//break and go to next loop
					break;

				}

			}

			//if the length of userInput is not <= 5
			else {

				//display error message
				cout << "The order ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfIDFailed++;

			}

			if (numberOfIDFailed >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for order ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		//check the order ID in database or not
		string select_query = "SELECT * FROM `order` WHERE "
			" Vendor_ID = "
			"" + to_string(currentSession.userID) + ""
			" AND "
			" Order_ID = "
			"'"+ vendorInputOrderID +"'";

		//execute query (get the data from database)
		int state = mysql_query(conn, select_query.c_str());

		if (state != 0) {

			cout << select_query;
			cout << endl;
			cout << mysql_error(conn);
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

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

			break;
		
		}

		//if result returned 0 row
		else {

			cout << "The orderID you entered is invalid";
			cout << endl;
			system("pause");
			cout << endl;
		
			numberOfTries++;

		}

		//if number of tries is more than equal to 3
		if (numberOfTries >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for menu ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

	}

	//select orde details that belong to this order ID
	select_query = "SELECT * FROM `order detail` WHERE "
		" Order_ID = "
		"'" + vendorInputOrderID + "'";

	state = mysql_query(conn, select_query.c_str());

	if (state != 0) {

		cout << select_query;
		cout << endl;
		cout << mysql_error(conn);
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

	res = mysql_store_result(conn);

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

		//get order details and add it to list
		while (row = mysql_fetch_row(res)) {
		
			OrderDetailList tempDetail;
			tempDetail.setOrderDetailID(row[0]);
			tempDetail.setOrderID(row[1]);
			tempDetail.setCustomerID(stoi(row[2]));
			tempDetail.setMenuID(row[3]);
			tempDetail.setItemQuantity(stoi(row[4]));
			tempDetail.setTotalItemPrice(stof(row[5]));

			if (details.isEmpty()) {

				details.setHead(tempDetail);

			}

			else {

				details.addToList(tempDetail);

			}
		
		}

		cout << "Order Details" << endl;

		cout << "----------------------------------------";
		cout << endl;


		cout << "| " << left << setw(5) << "No." << " | "
			<< left << setw(10) << "Menu_ID" << "| "
			<< setw(8) << "Quantity" << "| "
			<< setw(7) << "Price" << "| " << endl;

		cout << "----------------------------------------";
		cout << endl;

		details.displayList();

		return;

	}

	//if result returned 0 row
	else {
	
		cout << "Order does not have order details";
		cout << endl;
		system("pause");
		cout << endl;

		return;
	
	}

}

//function manage vendor Order
void vendorManageOrder(Session currentSession) {

	MyList<OrderList> orders;
	OrderList order;
	string vendorInputOrderID;
	string vendorInput;

	//select orders that belong to vendor to display
	string select_query = "SELECT * FROM `order` WHERE "
		" Vendor_ID = "
		"" + to_string(currentSession.userID) + "";

	int state = mysql_query(conn, select_query.c_str());

	if (state != 0) {

		cout << select_query;
		cout << endl;
		cout << mysql_error(conn);
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

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

		while (row = mysql_fetch_row(res)) {

			OrderList temp;
			temp.setOrderID(row[0]);
			temp.setCustomerID(stoi(row[1]));
			temp.setVendorID(stoi(row[2]));
			temp.setOrderType(row[3]);
			temp.setOrderAddress(row[4]);
			temp.setOrderDate(row[5]);
			temp.setOrderExpectedTime(row[6]);
			temp.setOrderTotalAmount(stof(row[7]));
			temp.setOrderStatus(row[8]);

			if (orders.isEmpty()) {

				orders.setHead(temp);

			}
			else {

				orders.addToList(temp);

			}

		}

	}

	//if result returned 0 row
	else {

		cout << "You have no orders currently";
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

	//ask for orderID to check

	int numberOfTries = 0;

	//loop to check order ID input exist and belongs to vendor
	while (true) {

		//number of times failed in entering menu ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			cout << "Order List" << endl;

			cout << "---------------------------------------";
			cout << "---------------------------------------";
			cout << "-----------------------------------";
			cout << endl;

			cout << "| " << " ID " << " | "
				<< left << setw(4) << "C_ID" << "| "
				<< setw(4) << "V_ID" << "| "
				<< setw(10) << "Type" << "| "
				<< setw(30) << "Address" << "| "
				<< setw(12) << "Date" << "| "
				<< setw(10) << "ETA" << "| "
				<< setw(7) << "Amount" << "| "
				<< setw(12) << "Status" << "| " << endl;

			cout << "---------------------------------------";
			cout << "---------------------------------------";
			cout << "-----------------------------------";
			cout << endl;

			orders.displayList();

			//get menu ID from admin
			cout << "Please enter order ID that you want to view";
			cout << endl;
			cout << "Note: DXXX (e.g: D001)";
			cout << endl;
			getline(cin, vendorInputOrderID);
			cout << endl;

			//get length of user input
			int a = vendorInputOrderID.length();

			//set initial value for boolean flag
			bool hasD = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only D
						if (vendorInputOrderID.at(0) == 'D') {

							//set hasD to true
							hasD = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (vendorInputOrderID.at(i) >= 48 && vendorInputOrderID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasD and hasDigit to false
							hasD = false;
							hasDigit = false;


							//break out of the for loop and go to check hasD and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasD)) {

					//userInput format is wrong
					cout << "Sorry, please follow the format given.";
					cout << endl;
					cout << "Please try again.";
					cout << endl;
					system("pause");
					cout << endl;

					//count number of ID failed
					numberOfIDFailed++;

				}

				//if ID format is correct
				else {

					//break and go to next loop
					break;

				}

			}

			//if the length of userInput is not <= 5
			else {

				//display error message
				cout << "The order ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfIDFailed++;

			}

			if (numberOfIDFailed >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for order ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		//check the order ID in database or not
		string select_query = "SELECT * FROM `order` WHERE "
			" Vendor_ID = "
			"" + to_string(currentSession.userID) + ""
			" AND "
			" Order_ID = "
			"'" + vendorInputOrderID + "'";

		//execute query (get the data from database)
		int state = mysql_query(conn, select_query.c_str());

		if (state != 0) {

			cout << select_query;
			cout << endl;
			cout << mysql_error(conn);
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

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

			while (row = mysql_fetch_row(res)) {

				order.setOrderID(row[0]);
				order.setCustomerID(stoi(row[1]));
				order.setVendorID(stoi(row[2]));
				order.setOrderType(row[3]);
				order.setOrderAddress(row[4]);
				order.setOrderDate(row[5]);
				order.setOrderExpectedTime(row[6]);
				order.setOrderTotalAmount(stof(row[7]));
				order.setOrderStatus(row[8]);

			}

			break;

		}

		//if result returned 0 row
		else {

			cout << "The orderID you entered is invalid";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfTries++;

		}

		//if number of tries is more than equal to 3
		if (numberOfTries >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for menu ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

	}

	//show status of the order first and ask whether want to update
	cout << "The current order status of " << order.getOrderID();
	cout << " is :";
	cout << endl;
	cout << order.getOrderStatus();
	cout << endl;

	if (!checkContinue()) {

		return;
	
	}

	int numberOfWrongInput = 0;

	//loop for vendor order status option
	while (true) {

		system("CLS");

		//Start for display screen for manage budget module
		cout << "1. Accept" << endl;
		cout << "2. Reject" << endl;
		cout << "3. Processing" << endl;
		cout << "4. Done" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, vendorInput);
		cout << endl;
		//End for display screen for manage budget module

		//if vendorInput is equal to 1
		if (vendorInput == "1") {

			order.setOrderStatus("Accept");
			break;

		}

		//if vendorInput is equal to 2
		else if (vendorInput == "2") {

			order.setOrderStatus("Reject");
			break;

		}

		//if vendorInput is equal to 3
		else if (vendorInput == "3") {

			order.setOrderStatus("Processing");
			break;

		}

		//if vendorInput is equal to 4
		else if (vendorInput == "4") {

			order.setOrderStatus("Done");
			break;

		}

		//if vendorInput is not equal to the choice above
		else {

			//display error messenge
			cout << "Sorry, please enter the correct choice.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to admin modue main screen
			cout << "You have entered the wrong input more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to prfile main screen
			return;

		}

	}

	order.save();
	return;

}


#endif // !VENDORORDERMANAGEMENT_H


