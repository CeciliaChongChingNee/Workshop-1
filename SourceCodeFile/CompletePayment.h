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

#ifndef COMPLETEPAYMENT_H
#define COMPLETEPAYMENT_H

void completePayment(Session currentSession);
bool searchForOrderID(MyList<OrderList>& uncompleteOrder, string orderID);
bool payOrder(Session currentSession, double amount);

//function completePayment
void completePayment(Session currentSession) {

	//variable for complete Payment function
	MyList<OrderList> uncompleteOrder;
	string customerInputOrderID;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');

	//get uncompleted payment
	string select_query = "SELECT * FROM `order` WHERE "
		" Order_ID NOT IN ("
		" SELECT Order_ID FROM `payment` WHERE Customer_ID = "
		" " + to_string(currentSession.userID) + " )"
		" AND "
		" Customer_ID = "
		" " + to_string(currentSession.userID) + " ";

	int state = mysql_query(conn, select_query.c_str());

	if (state != 0) {
	
		cout << mysql_error(conn);
		cout << endl;
		system("pause");
		cout << endl;

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

			if (uncompleteOrder.isEmpty()) {

				uncompleteOrder.setHead(temp);

			}
			else {

				uncompleteOrder.addToList(temp);

			}

		}
		
		int numberOfWrongInput = 0;

		//loop for order ID input and payment
		while (true) {

			int numberOfIDFailed = 0;

			//loop for checking ID format
			while (true) {

				//clear screen
				system("CLS");

				cout << "Unpaid Order" << endl;

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

				//display unpaid orders
				uncompleteOrder.displayList();

				//get menu ID from admin
				cout << "Please enter the order ID that you want to pay";
				cout << endl;
				cout << "Note: DXXX (e.g: D001)";
				cout << endl;
				getline(cin, customerInputOrderID);
				cout << endl;

				//get length of user input
				int a = customerInputOrderID.length();

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
							if (customerInputOrderID.at(0) == 'D') {

								//set hasM to true
								hasD = true;

							}

						}

						//if currently is not the first index
						else {

							//check if input is only digit
							if (customerInputOrderID.at(i) >= 48 && customerInputOrderID.at(i) <= 57) {

								//set hasDigit to true
								hasDigit = true;

							}

							//if input is others
							else {

								//set hasM and hasDigit to false
								hasD = false;
								hasDigit = false;


								//break out of the for loop and go to check hasM and hasDigit
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

			//if found the order
			if (searchForOrderID(uncompleteOrder, customerInputOrderID)) {

				if (payOrder(currentSession, uncompleteOrder.getCurrent()->element.getOrderTotalAmount())) {

					//initialize time object
					struct tm newtime;
					time_t now = time(0);
					localtime_s(&newtime, &now);

					//set the time to current time
					int hour = newtime.tm_hour;
					int min = newtime.tm_min;
					int sec = newtime.tm_sec;

					string time = "";
					time.append(to_string(hour));
					time.append(":");
					time.append(to_string(min));
					time.append(":");
					time.append(to_string(sec));

					//get current date
					int day = newtime.tm_mday;
					int month = newtime.tm_mon + 1;
					int year = newtime.tm_year + 1900;

					string date = "";
					date.append(to_string(year));
					date.append("-");
					date.append(to_string(month));
					date.append("-");
					date.append(to_string(day));

					PaymentList payment;
					payment.setOrderID(uncompleteOrder.getCurrent()->element.getOrderID());
					payment.setCustomerID(currentSession.userID);
					payment.setPaymentTotalAmount(uncompleteOrder.getCurrent()->element.getOrderTotalAmount());
					payment.setPaymentDate(date);
					payment.setPaymentTime(time);

					payment.save();

					string select_query = "SELECT * FROM `user` WHERE "
						" User_ID = "
						"" + to_string(uncompleteOrder.getCurrent()->element.getVendorID()) + "";

					int state = mysql_query(conn, select_query.c_str());

					if (state != 0) {

						cout << select_query;
						cout << endl;
						cout << mysql_error(conn);
						cout << endl;
						system("pause");
						cout << endl;

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

						UserList tempUser;

						while (row = mysql_fetch_row(res)) {

							tempUser.setUserID(stoi(row[0]));
							tempUser.setUserName(row[1]);
							tempUser.setUserType(row[2]);
							tempUser.setUserIdentityCard(row[3]);
							tempUser.setUserPassword(row[4]);
							tempUser.setUserGender(row[5]);
							tempUser.setUserPhoneNumber(row[6]);
							tempUser.setUserBalance(stof(row[7]));

						}

						string select_query = "UPDATE `user` SET User_Balance = "
							"" + to_string(tempUser.getUserBalance() + payment.getPaymentTotalAmount()) + ""
							" WHERE User_ID = "
							"" + to_string(uncompleteOrder.getCurrent()->element.getVendorID()) + "";

						int state = mysql_query(conn, select_query.c_str());

						if (state != 0) {

							cout << select_query;
							cout << endl;
							cout << mysql_error(conn);
							cout << endl;
							system("pause");
							cout << endl;

						}

					}

					else {

						cout << "There is no such vendor with vendor ID " << uncompleteOrder.getCurrent()->element.getVendorID();
						cout << endl;
						system("pause");
						cout << endl;

						return;

					}

					cout << "Payment for order ID " << payment.getOrderID()<<" is successful";
					cout << endl;
					system("pause");
					cout << endl;

					return;

				}

			}

			//if not found the order
			else {

				cout << "There is no such order ID";
				cout << endl;
				cout << "Please try again";
				cout << endl;

				numberOfWrongInput++;

			}

			//if number of wrong input more than equal 3
			if (numberOfWrongInput >= 3) {

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
	
	}

	//if result returned 0 row
	else {

		cout << "You have completed all your payments";
	
	}

}

//function search Order ID
bool searchForOrderID(MyList<OrderList>& uncompleteOrder, string orderID) {

	uncompleteOrder.goToHead();

	bool flag = false;

	for (int i = 1; i <= uncompleteOrder.getLength(); i++) {
	
		//if current is equal to order ID
		if (uncompleteOrder.getCurrent()->element.getOrderID().compare(orderID) == 0) {
		
			flag = true;
			return flag;

		}

		uncompleteOrder.moveToNext();

	}

	return flag;

}

//function payment 
bool payOrder(Session currentSession, double amount) {

	//variable of payment
	string customerInputPay;
	string customerInputDineIn;
	string customerInputAddress;
	bool flag = false;

	//verify user exist in database 
	string selectQuery = " SELECT * FROM user "
		" WHERE User_ID = "
		" " + to_string(currentSession.userID) + " ";

	//execute query (get the data from database)
	mysql_query(conn, selectQuery.c_str());

	//extract data into result
	res = mysql_store_result(conn);

	//create temp UserList Object
	UserList temp;

	int num_row;

	//if result is returned
	if (res) {

		num_row = mysql_num_rows(res);

	}

	//if result is not returned
	else {

		num_row = 0;

	}

	//if result returned more than 0 row
	if (num_row > 0) {

		//get results from query
		while (row = mysql_fetch_row(res)) {

			//initialize temp user to store value
			temp.setUserID(atoi(row[0]));
			temp.setUserName(row[1]);
			temp.setUserType(row[2]);
			temp.setUserIdentityCard(row[3]);
			temp.setUserPassword(row[4]);
			temp.setUserGender(row[5]);
			temp.setUserPhoneNumber(row[6]);
			temp.setUserBalance(atof(row[7]));

		}

	}

	//if result returned 0 row (shouldn;t happen)
	else {

		cout << "User not exist in db";
		cout << endl;
		system("pause");
		cout << endl;

		return flag;

	}

	//check if user have enough to pay
	if (temp.getUserBalance() < amount) {

		cout << "You have insufficient balance.";
		cout << endl;
		cout << "Please top up and try again.";
		cout << endl;
		system("pause");
		cout << endl;

		return flag;

	}
	else {

		//set query for update 
		string updateQuery = "UPDATE `user` SET User_Balance = "
			" " + to_string(temp.getUserBalance() - amount) + " "
			" WHERE User_ID = "
			" " + to_string(temp.getUserID()) + " ";

		//execute update query
		int state = mysql_query(conn, updateQuery.c_str());

		if (state != 0) {

			cout << mysql_error(conn);
			cout << endl;
			system("pause");
			cout << endl;

		}

		//done and return to user management main screen
		flag = true;
		return flag;

	}

}


#endif // !COMPLETEPAYMENT_H
