/*
*This program demonstrates a simple C++ program.
*The function in this program is customerOrderManagement.
*/

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

#ifndef CUSTOMERORDERMANAGEMENT_H
#define CUSTOMERORDERMANAGEMENT_H

//function prototype
void displayMenuCustomer(Session currentSession, string time);
MyList<OrderDetailList> customerOrder(Session currentSession, string time);
void checkOut(Session currentSession, MyList<OrderDetailList>& orderDetails, OrderList templateOrder);
bool payment(Session currentSession, double totalAmount);
void deleteOrderDetails(Session currentSession, MyList<OrderDetailList>& orderDetails);
void arrangeOrderDetails(MyList<OrderDetailList>& orderDetails);
void editOrderDetail(MyList<OrderDetailList>& orderDetails);
void editItemInList(MyList<OrderDetailList>& orderDetails, int index, int quantity);
MyList<OrderDetailList> getDifferentOrderDetails(MyList<OrderDetailList> orderDetails);
bool existingMenuID(MyList<OrderDetailList> differentOrderDetail, string menuID);
bool existingMenuID(MyList<string> differentOrderDetails, string menuID);
MyList<string> getMenuIDList(MyList<OrderDetailList> uniqueOrderDetails);


//function customerOrderManagement to show the customer order main screen
void customerOrderManagement(Session currentSession) {

	//variable of customerOrderManagement
	string customerInput;
	string customerChoiceInput;
	string customerInputDineIn;
	string customerInputTime;
	string customerInputAddress;
	string date;
	MyList<OrderDetailList> orderDetails;
	OrderList order;

	//initialize time object
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	//get current date
	int day = newtime.tm_mday;
	int month = newtime.tm_mon + 1;
	int year = newtime.tm_year + 1900;

	date = "";
	date.append(to_string(year));
	date.append("-");
	date.append(to_string(month));
	date.append("-");
	date.append(to_string(day));

	//initialize order list object
	order.setOrderID(order.generateOrderID());
	order.setOrderDate(date);

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');

	int numberOfWrongInput = 0;

	//loop to get time
	while (true) {

		//clear screen
		system("CLS");

		//Start for display customer order management main screen
		cout << "Do you want to have meal now? (Y/N)";
		cout << endl;
		getline(cin, customerInput);
		cout << endl;

		//if customer input is yes
		if (customerInput == "Y" || customerInput == "y") {

			order.setOrderType("Order");

			//set the time to current time
			int hour = newtime.tm_hour;
			int min = newtime.tm_min;
			int sec = newtime.tm_sec;

			customerInputTime = "";
			customerInputTime.append(to_string(hour));
			customerInputTime.append(":");
			customerInputTime.append(to_string(min));
			customerInputTime.append(":");
			customerInputTime.append(to_string(sec));

			cout << "Current time is " << customerInputTime << endl;
			cout << "Current Date is " << date << endl;

			//dummy value set for current time (comment this if dont want to manual set)
			//customerInputTime = "10:00:00";

			break;
			
		}

		//if customer input is no
		else if (customerInput == "N" || customerInput == "n") {

			order.setOrderType("Booking");

			//get the time to meal from customer
			cout << "Please enter time that you want to eat";
			cout << endl;
			cout << "Note: Use 24 hours format (e.g: 16:00)";
			cout << endl;
			getline(cin, customerInputTime);
			cout << endl;

			break;

		}

		//if customer input is others
		else {

			//display error messenge
			cout << "Sorry, please follow the correct format.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		//if number of wrong input is more than 3
		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

	}

	numberOfWrongInput = 0;

	while (true) {
	
		//get customer input
		cout << "Do you want to dine in? (Y/N)";
		cout << endl;
		getline(cin, customerInputDineIn);
		cout << endl;

		//if customer input is yes
		if (customerInputDineIn == "Y" || customerInputDineIn == "y") {

			//set the address to default (do not know required or not)
			order.setOrderAddress("CAFE");
			break;

		}

		//if customer input is no
		else if (customerInputDineIn == "N" || customerInputDineIn == "n") {

			int numberOfWrongInput2 = 0;

			//loop to get address
			while (true) {

				//get address
				cout << "What is the address that deliver?";
				cout << endl;
				getline(cin, customerInputAddress);
				cout << endl;

				//if user has not entered anything
				if (customerInputAddress.empty()) {

					cout << "You have not enter anything";
					cout << endl;
					cout << "Please try again";
					cout << endl;

					numberOfWrongInput2++;

				}

				//if user has entered something
				else {

					break;

				}

				//if number of wrong input is more than 3
				if (numberOfWrongInput2 >= 3) {

					//display error messenge and exit to main screen
					cout << "You have entered wrong input for more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					return;

				}

			}

			order.setOrderAddress(customerInputAddress);
			break;

		}

		//if customer input is others
		else {

			//display error messenge
			cout << "Sorry, please follow the correct format.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		//if number of wrong input is more than 3
		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

	}

	order.setOrderExpectedTime(customerInputTime);

	//loop options after we got the time
	while (true) {
	
		system("CLS");

		//Start for display screen for manage order details module
		cout << "1. View order details" << endl;
		cout << "2. Edit order details" << endl;
		cout << "3. Add order details" << endl;
		cout << "4. Delete order details" << endl;
		cout << "5. Check Out" << endl;
		cout << "6. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, customerChoiceInput);
		cout << endl;
		//End for display screen for manage order details module

		//if customerChoiceInput is equal to 1
		if (customerChoiceInput == "1") {

			//if list is empty
			if (orderDetails.getLength() == 0) {

				cout << "You have not selected any menu item";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

			}

			//if list is not empty
			else {

				system("CLS");

				cout << "Order Details" << endl;

				cout << "----------------------------------------";
				cout << endl;


				cout << "| " << left << setw(5) << "No." << " | "
					<< left << setw(10) << "Menu_ID" << "| "
					<< setw(8) << "Quantity" << "| "
					<< setw(7) << "Price" << "| " << endl;

				cout << "----------------------------------------";
				cout << endl;

				//display list of order details
				orderDetails.displayList();
				system("pause");
				cout << endl;
			
			}

		}

		//if customerChoiceInput is equal to 2
		else if (customerChoiceInput == "2") {

			//call edit order details function
			editOrderDetail(orderDetails);

		}

		//if customerChoiceInput is equal to 3
		else if (customerChoiceInput == "3") {

			if (orderDetails.isEmpty()) {

				//call customer order function and get a list of order details
				orderDetails = customerOrder(currentSession, customerInputTime);
			
			}
			//add to order details if order details is not empty
			else {

				MyList<OrderDetailList> tempOrderDetails = customerOrder(currentSession, customerInputTime);

				int tempLength = tempOrderDetails.getLength();

				//loop through all order details returned from customerOrder function
				while (!tempOrderDetails.isEmpty()) {
					
					//pop the element out of temp list and add it to order details list
					orderDetails.addToList(tempOrderDetails.pop());

				}

				arrangeOrderDetails(orderDetails);
			
			}

		}

		//if customerChoiceInput is equal to 4
		else if (customerChoiceInput == "4") {

			//call delete order details function
			deleteOrderDetails(currentSession, orderDetails);
			arrangeOrderDetails(orderDetails);

		}

		//if customerChoiceInput is equal to 5
		else if (customerChoiceInput == "5") {

			//call check out function 
			checkOut(currentSession, orderDetails, order);

			return;

		}

		//if customerChoiceInput is equal to 6
		else if (customerChoiceInput == "6") {

			//go back to main screen
			return;

		}

		//if adminInput is not equal to the choice above
		else {

			//display error messenge
			cout << "Sorry, please enter the correct choice.";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

		}
	
	}

}

//function display menu customer function
void displayMenuCustomer(Session currentSession, string time) {

	string select_Query = "SELECT * FROM menu WHERE Meal_Type_ID IN ("
						  "SELECT Meal_Type_ID FROM `meal type` WHERE "
						  " Time_Start < '" + time + "' "
						  " AND "
						  " Time_End > '" + time + "' "
						  ")";

	//Execute query (get the data from database)
	int state = mysql_query(conn, select_Query.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	//declare temp menu list object
	MenuList temp;

	//count number of menu list added to list
	int counter = 0;

	//declare list
	MyList<MenuList> list;

	int num_row;

	//result is returned
	if (res) {

		num_row = mysql_num_rows(res);

	}

	//result is not returned
	else {

		num_row = 0;

	}

	//if result is not 0 row
	if (num_row > 0) {

		//set value to menu from database
		while ((row = mysql_fetch_row(res))) {

			//initialize temp menu to store value
			temp.setMenuID(row[0]);
			temp.setVendorID(atoi(row[1]));
			temp.setMealTypeID(row[2]);
			temp.setMenuName(row[3]);
			temp.setMenuDescription(row[4]);
			temp.setMenuQuantity(atoi(row[5]));
			temp.setMenuPrice(atof(row[6]));


			//if this is the first element added to list
			if (counter == 0) {

				//set element as head of list
				list.setHead(temp);
			}

			//If not the first element
			else {

				//add element to list
				list.addToList(temp);
			}

			//count number of element added to list
			counter++;

		}

		cout << "Menu List" << endl;

		cout << "-------------------------------------";
		cout << "-------------------------------------";
		cout << "-------------------------------------";
		cout << "---------";
		cout << endl;

		cout << "| " << " ID " << " | "
			<< left << setw(4) << "V_ID" << "| "
			<< setw(6) << "TypeID" << "| "
			<< setw(30) << "Name" << "| "
			<< setw(50) << "Description" << "| "
			<< setw(5) << "Qty" << "| "
			<< setw(5) << "Price" << "|" << endl;

		cout << "-------------------------------------";
		cout << "-------------------------------------";
		cout << "-------------------------------------";
		cout << "---------";
		cout << endl;

		//display list
		list.displayList();
		cout << endl;

	}

	//if result is 0 row
	else {

		cout << "There is no food at this hour";
		cout << endl;
		cout << "Please try again later";
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

}

//function customer order
MyList<OrderDetailList> customerOrder(Session currentSession, string time) {

	//variable of customer order
	string customerInputMenuID;
	string customerInput;
	int customerInputItemQuantity;
	MenuList menu;
	MyList<OrderDetailList> myOrderDetails;

	int numberOfWrongInput = 0;

	while (true) {

		//number of tries in checking ID exist
		int numberOfTries = 0;

		//loop to check ID exist - to get menu object
		while (true) {

			//number of times failed in entering menu ID		
			int numberOfIDFailed = 0;

			//loop for checking ID format
			while (true) {

				//clear screen
				system("CLS");

				//call display menu customer function
				displayMenuCustomer(currentSession, time);

				//get menu ID from admin
				cout << "Please insert your menu ID that you want to eat";
				cout << endl;
				cout << "Note: MXXX (e.g: M001)";
				cout << endl;
				getline(cin, customerInputMenuID);
				cout << endl;

				//get length of user input
				int a = customerInputMenuID.length();

				//set initial value for boolean flag
				bool hasM = false;
				bool hasDigit = false;

				//if the length of userInput <= 5
				if (a <= 5) {

					//loop to check the char is available or not
					for (int i = 0; i < a; i++) {

						//if currently is the first index
						if (i == 0) {

							//check if input is only M
							if (customerInputMenuID.at(0) == 'M') {

								//set hasM to true
								hasM = true;

							}

						}

						//if currently is not the first index
						else {

							//check if input is only digit
							if (customerInputMenuID.at(i) >= 48 && customerInputMenuID.at(i) <= 57) {

								//set hasDigit to true
								hasDigit = true;

							}

							//if input is others
							else {

								//set hasM and hasDigit to false
								hasM = false;
								hasDigit = false;


								//break out of the for loop and go to check hasM and hasDigit
								break;

							}

						}

					}

					//if input_char not having correct format
					if (!(hasDigit && hasM)) {

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
					cout << "The menu ID entered is too long." << endl;
					system("pause");
					cout << endl;

					//count number of ID failed
					numberOfIDFailed++;

				}

				if (numberOfIDFailed >= 3) {

					//display error messenge and exit to main screen
					cout << "You have entered wrong input for menu ID more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					return myOrderDetails;

				}

			}

			//check the vendor ID in database or not
			string selectQuery = "SELECT * FROM menu "
				" WHERE Menu_ID = '" + customerInputMenuID + "' ";

			//execute query (get the data from database)
			mysql_query(conn, selectQuery.c_str());

			//extract data into result
			res = mysql_store_result(conn);

			//if there is at least 1 row of result returned
			if (res) {

				//set value for menu object
				while (row = mysql_fetch_row(res)) {

					menu.setMenuID(row[0]);
					menu.setVendorID(stoi(row[1]));
					menu.setMealTypeID(row[2]);
					menu.setMenuName(row[3]);
					menu.setMenuDescription(row[4]);
					menu.setMenuQuantity(stoi(row[5]));
					menu.setMenuPrice(stod(row[6]));

				}

				//break and head to next loop
				break;

			}

			//if there is no result
			else {

				cout << "The menu ID does not exist !";
				cout << endl;
				cout << "Please try again.";
				cout << endl;
				system("pause");

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

				return myOrderDetails;

			}

		}

		//get menu item quantity from customer
		int results = getInput("Please enter the quantity to order"
							  , customerInputItemQuantity);

		//if fail to get input
		if (!results) {

			//display error message and go back to user management main screen
			cout << "You have entered the wrong format for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to user management main screen
			return myOrderDetails;

		}

		//initialize order detail object
		OrderDetailList tempOrderDetail;
		tempOrderDetail.setOrderDetailID(to_string(myOrderDetails.getLength() + 1));
		tempOrderDetail.setMenuID(menu.getMenuID());
		tempOrderDetail.setItemQuantity(customerInputItemQuantity);
		tempOrderDetail.setTotalItemPrice(menu.getMenuPrice()*customerInputItemQuantity);
	
		//if empty list
		if (myOrderDetails.getLength() == 0) {

			myOrderDetails.setHead(tempOrderDetail);

		}

		//if not empty list
		else {

			myOrderDetails.addToList(tempOrderDetail);

		}

		cout << "Do you want to continue order ? (Y/N)";
		cout << endl;
		getline(cin, customerInput);
		cout << endl;
		
		//if customer wants to continue to order
		if (customerInput == "Y" || customerInput == "y") {
			
			//do nothing

		}

		//if customer want to proceed to checkout
		else if (customerInput == "N" || customerInput == "n") {

			return myOrderDetails;
		
		}

		//if customer enters wrong input
		else {

			cout << "Sorry please follow the format given";
			cout << endl;
			cout << "Please try again";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;
		
		}

		//if number of wrong input is more than equal 3
		if (numberOfWrongInput >= 3) {

			//display error message and return to customer order management screen;
			cout << "You have entered the wrong input for more than 3 times";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return myOrderDetails;
		
		}
	
	}

}

//function check out
void checkOut(Session currentSession, MyList<OrderDetailList>& orderDetails, OrderList templateOrder) {

	//variable of check out
	string customerInputCheckOut;
	string customerInputDelete;
	int customerInputDeleteItemNumber;
	string customerInputAddOn;
	string customerInputPay;
	

	//get list of order details based on menuID
	MyList<OrderDetailList> uniqueOrderDetails = getDifferentOrderDetails(orderDetails);

	//get a list of menu ID from the unique order details list
	MyList<string> menuIDList = getMenuIDList(uniqueOrderDetails);

	//get from database the vendor ID needed

	string select_query = "SELECT * FROM `user`"
						  " WHERE User_ID IN"
						  " ( SELECT Vendor_ID FROM `menu` "
						  " WHERE Menu_ID IN "
						  " (";

	menuIDList.goToHead();

	MyList<int> vendorIDList;

	for (int i = 1; i <= menuIDList.getLength(); i++) {

		select_query.append("'");
		select_query.append(menuIDList.getCurrentElement());
		select_query.append("'");

		if (i != menuIDList.getLength()) {

			select_query.append(",");
		
		}

		menuIDList.moveToNext();
	
	}

	select_query.append("))");

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

	//if result returned more than 0 row - initialize vendorIDList
	if (num_row > 0) {

		//get list of vendorID
		while (row = mysql_fetch_row(res)) {

			if (vendorIDList.isEmpty()) {

				vendorIDList.setHead(stoi(row[0]));
			
			}
			else {

				vendorIDList.addToList(stoi(row[0]));
			
			}
		
		}
	
	}

	//if result returned 0 row
	else{

		//shouldn't happen
		cout << "Error near fetching vendorID based on menuID";
		cout << endl;
		system("pause");
		cout << endl;

		return;
	
	}

	vendorIDList.goToHead();

	for (int i = 1; i <= vendorIDList.getLength(); i++) {

		//set values for order list
		OrderList order;
		order.setOrderID(order.generateOrderID());
		order.setCustomerID(currentSession.userID);
		order.setVendorID(vendorIDList.getCurrentElement());
		order.setOrderType(templateOrder.getOrderType());
		order.setOrderAddress(templateOrder.getOrderAddress());
		order.setOrderDate(templateOrder.getOrderDate());
		order.setOrderExpectedTime(templateOrder.getOrderExpectedTime());
		order.setOrderStatus("Processing");

		MyList<OrderDetailList> groupedOrderDetails;

		//extract list of order details for this order
		//find for match of vendorID and menuID with each order detail if match then pop out and add to list
		double totalAmount = 0;
		int j = 1;

		orderDetails.goToHead();

		while (j <= orderDetails.getLength()) {
		
			string select_query = "SELECT * FROM menu WHERE "
								 " Menu_ID = "
								 "'" + orderDetails.getCurrent()->element.getMenuID() + "'"
								 " AND "
								 " Vendor_ID = "
								 "" + to_string(order.getVendorID()) + "";

			int state = mysql_query(conn, select_query.c_str());

			if (state != 0) {
			
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

				//remove and get that element 
				//add that to a new list
				if (groupedOrderDetails.isEmpty()) {
				
					OrderDetailList tempOrderDetail = orderDetails.removeFromList(j);
					tempOrderDetail.setOrderID(order.getOrderID());
					totalAmount += tempOrderDetail.getTotalItemPrice();
					groupedOrderDetails.setHead(tempOrderDetail);

					//go back to the start (could be refactored)
					j = 1;
					orderDetails.goToHead();

				}

				//if not empty list
				else {
				
					OrderDetailList tempOrderDetail = orderDetails.removeFromList(j);
					tempOrderDetail.setOrderID(order.getOrderID());
					groupedOrderDetails.addToList(tempOrderDetail);
					totalAmount += tempOrderDetail.getTotalItemPrice();
					//go back to the start (could be refactored)
					j = 1;
					orderDetails.goToHead();

				}
			
			}

			//if result returned 0 row
			else {
			
				j++;
				orderDetails.moveToNext();

			}
		}

		//after gt list of completed order Details
		order.setOrderTotalAmount(totalAmount);
		order.save();

		//pop the element out of the grouped order details and update to database
		while (!groupedOrderDetails.isEmpty()) {
		
			OrderDetailList temp = groupedOrderDetails.pop();
			temp.setOrderDetailID(temp.generateOrderDetailID());
			temp.setCustomerID(currentSession.userID);
			temp.save();

			//update the menu stock as well
			select_query = "SELECT * FROM `menu` WHERE"
						   " Menu_ID = "
						   "'" + temp.getMenuID() + "'";

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

				while (row = mysql_fetch_row(res)) {
				
					MenuList tempMenu;
					tempMenu.setMenuID(row[0]);
					tempMenu.setVendorID(stoi(row[1]));
					tempMenu.setMealTypeID(row[2]);
					tempMenu.setMenuName(row[3]);
					tempMenu.setMenuDescription(row[4]);
					tempMenu.setMenuQuantity(stoi(row[5]));
					tempMenu.setMenuPrice(stof(row[6]));

					tempMenu.setMenuQuantity(tempMenu.getMenuQuantity() - temp.getItemQuantity());
					tempMenu.save();

				}

			}

			//if result returned 0 row
			else {


			
			}

		}

		//clear screen 
		system("CLS");

		//get customer input
		cout << "Currently processing payment for order ID ";
		cout << order.getOrderID();
		cout << endl;
		cout << "Do you want to pay now ? (Y/N)";
		cout << endl;
		getline(cin, customerInputPay);
		cout << endl;

		//if customer input is yes
		if (customerInputPay == "Y" || customerInputPay == "y") {

			if (payment(currentSession, totalAmount)) {

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

				PaymentList payment;
				payment.setOrderID(order.getOrderID());
				payment.setCustomerID(currentSession.userID);
				payment.setPaymentTotalAmount(totalAmount);
				payment.setPaymentDate(order.getOrderDate());
				payment.setPaymentTime(time);

				payment.save();

				string select_query = "SELECT * FROM `user` WHERE "
									  " User_ID = "
									  "" + to_string(vendorIDList.getCurrent()->element) + "";

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
						""+to_string(vendorIDList.getCurrent()->element)+"";

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
				
					cout << "There is no such vendor with vendor ID " << vendorIDList.getCurrent()->element;
					cout << endl;
					system("pause");
					cout << endl;

					return;
				
				}

				cout << "Payment for order ID " << payment.getOrderID() << " is successful";
				cout << endl;
				system("pause");
				cout << endl;

				vendorIDList.moveToNext();
			
			}

		}

		//if customer input is no
		else if (customerInputPay == "N" || customerInputPay == "n") {

			//do nothing

			vendorIDList.moveToNext();

		}

	}

}

//function payment 
bool payment(Session currentSession, double amount) {

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

//function delete order detail
void deleteOrderDetails(Session currentSession, MyList<OrderDetailList>& orderDetails) {

	int customerInputDeleteItemNumber;

	int numberOfTries = 0;

	//loop for deleting item
	while (true) {

		int numberOfWrongInput = 0;

		//loop for getting item to be deleted
		while (true) {

			system("CLS");

			cout << "Order Details" << endl;

			cout << "----------------------------------------";
			cout << endl;


			cout << "| " << left << setw(5) << "No." << " | "
				<< left << setw(10) << "Menu_ID" << "| "
				<< setw(8) << "Quantity" << "| "
				<< setw(7) << "Price" << "| " << endl;

			cout << "----------------------------------------";
			cout << endl;

			orderDetails.displayList();

			bool results = getInput("Please enter item number that you want to delete"
				, customerInputDeleteItemNumber);

			//if fail to get input
			if (!results) {

				//display error message and go back to user management main screen
				cout << "You have entered the wrong format for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				//return to user management main screen
				return;

			}

			//if customer anything not within the list
			if (customerInputDeleteItemNumber > orderDetails.getLength()) {

				cout << "Please refer to the list of item shown";
				cout << endl;
				cout << " Please try again";
				cout << endl;
				system("pause");
				cout << endl;

				numberOfWrongInput++;

			}

			//if not error or issues with the input then break out
			else {

				break;

			}

			//if number of wrong input is more than equal 3
			if (numberOfWrongInput >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		//delete from order detail list
		orderDetails.removeFromList(customerInputDeleteItemNumber);

		//if list after delete is not empty
		if (orderDetails.isEmpty()) {

			cout << "The list is now empty.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

		//if list after delete is empty
		else {

			//show updated list
			system("CLS");
			cout << "Updated list:";
			cout << endl;
			arrangeOrderDetails(orderDetails);

			cout << "Order Details" << endl;

			cout << "----------------------------------------";
			cout << endl;


			cout << "| " << left << setw(5) << "No." << " | "
				<< left << setw(10) << "Menu_ID" << "| "
				<< setw(8) << "Quantity" << "| "
				<< setw(7) << "Price" << "| " << endl;

			cout << "----------------------------------------";
			cout << endl;

			orderDetails.displayList();

			//if customer do not want to continue delete item
			if (!checkContinue()) {

				return;

			}
		
		}
	
	}

}

//function to arrange order detail
void arrangeOrderDetails(MyList<OrderDetailList>& orderDetails) {

	int length = orderDetails.getLength();

	orderDetails.goToHead();

	for (int i = 1; i <= length; i++) {

		orderDetails.getCurrent()->element.setOrderDetailID(to_string(i));
		orderDetails.moveToNext();
	
	}
	
}

//function to edit order detail
void editOrderDetail(MyList<OrderDetailList>& orderDetails) {


	int customerInputEditItemNumber;
	int customerInputItemQuantity;

	int numberOfTries = 0;

	//loop for edit item
	while (true) {

		int numberOfWrongInput = 0;

		//loop for getting item to be edit
		while (true) {

			system("CLS");

			cout << "Order Details" << endl;

			cout << "----------------------------------------";
			cout << endl;


			cout << "| " << left << setw(5) << "No." << " | "
				<< left << setw(10) << "Menu_ID" << "| "
				<< setw(8) << "Quantity" << "| "
				<< setw(7) << "Price" << "| " << endl;

			cout << "----------------------------------------";
			cout << endl;

			orderDetails.displayList();

			bool results = getInput("Please enter item number that you want to edit"
				, customerInputEditItemNumber);

			//if fail to get input
			if (!results) {

				//display error message and go back to user management main screen
				cout << "You have entered the wrong format for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				//return to user management main screen
				return;

			}

			//if customer anything not within the list
			if (customerInputEditItemNumber > orderDetails.getLength()) {

				cout << "Please refer to the list of item shown";
				cout << endl;
				cout << " Please try again";
				cout << endl;
				system("pause");
				cout << endl;

				numberOfWrongInput++;

			}

			//if not error or issues with the input then break out
			else {

				break;

			}

			//if number of wrong input is more than equal 3
			if (numberOfWrongInput >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		//get menu item quantity from customer
		int results = getInput("Please enter the quantity to order"
			, customerInputItemQuantity);

		//if fail to get input
		if (!results) {

			//display error message and go back to user management main screen
			cout << "You have entered the wrong format for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to user management main screen
			return;

		}

		editItemInList(orderDetails, customerInputEditItemNumber, customerInputItemQuantity);

		//if list after delete is empty
		if(!orderDetails.isEmpty()) {

			//show updated list
			system("CLS");
			cout << "Updated list:";
			cout << endl;
			arrangeOrderDetails(orderDetails);

			cout << "Order Details" << endl;

			cout << "----------------------------------------";
			cout << endl;


			cout << "| " << left << setw(5) << "No." << " | "
				<< left << setw(10) << "Menu_ID" << "| "
				<< setw(8) << "Quantity" << "| "
				<< setw(7) << "Price" << "| " << endl;

			cout << "----------------------------------------";
			cout << endl;

			orderDetails.displayList();

			//if customer do not want to continue delete item
			if (!checkContinue()) {

				return;

			}

		}

	}

}

//function to edit item in list
void editItemInList(MyList<OrderDetailList>& orderDetails, int index, int quantity) {

	orderDetails.goToHead();
	for (int i = 1; i < index; i++) {
		orderDetails.moveToNext();
	}

	orderDetails.getCurrent()->element.setItemQuantity(quantity);

}

//function to get unique order detail
MyList<OrderDetailList> getDifferentOrderDetails(MyList<OrderDetailList> orderDetails) {

	MyList<OrderDetailList> differentOrderDetails;
	orderDetails.goToHead();

	for (int i = 1; i <= orderDetails.getLength(); i++) {

		//first element will always go in since its empty
		if (differentOrderDetails.isEmpty()) {

			differentOrderDetails.setHead(orderDetails.getCurrentElement());
		
		}
		else {

			//check for repeating in list
			if (!existingMenuID(differentOrderDetails, orderDetails.getCurrent()->element.getMenuID())) {
			
				differentOrderDetails.addToList(orderDetails.getCurrentElement());

			}

		
		}
		orderDetails.moveToNext();

	}

	return differentOrderDetails;

}

//function for existing menu ID
bool existingMenuID(MyList<OrderDetailList> differentOrderDetails, string menuID) {

	bool flag = false;
	differentOrderDetails.goToHead();

	for (int i = 1; i <= differentOrderDetails.getLength(); i++) {
	
		if (differentOrderDetails.getCurrent()->element.getMenuID().compare(menuID) == 0) {
			flag = true;
			return flag;
		}
		differentOrderDetails.moveToNext();

	}
	return flag;

}

//overload function for existing menu ID
bool existingMenuID(MyList<string> menuList, string menuID) {

	bool flag = false;
	menuList.goToHead();

	for (int i = 1; i <= menuList.getLength(); i++) {

		if (menuList.getCurrent()->element.compare(menuID) == 0) {
			flag = true;
			return flag;
		}
		menuList.moveToNext();

	}
	return flag;

}

//function to get list of menuID 
MyList<string> getMenuIDList(MyList<OrderDetailList> uniqueOrderDetails) {

	uniqueOrderDetails.goToHead();

	MyList<string> menuList;

	for (int i = 1; i <= uniqueOrderDetails.getLength(); i++) {

		if (menuList.isEmpty()) {
		
			menuList.setHead(uniqueOrderDetails.getCurrent()->element.getMenuID());

		}
		else {

			if (!existingMenuID(menuList, uniqueOrderDetails.getCurrent()->element.getMenuID())) {
			
				menuList.addToList(uniqueOrderDetails.getCurrent()->element.getMenuID());

			}
		
		}
		uniqueOrderDetails.moveToNext();
	}
	
	return menuList;

}


#endif