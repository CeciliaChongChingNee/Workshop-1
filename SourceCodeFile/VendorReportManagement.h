#include <iostream>
#include <iomanip>
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

struct MenuTotalSale {

	string menu;
	double totalSale;

};

#ifndef VENDORREPORTMANAGEMENT_H
#define VENDORREPORTMANAGEMENT_H

void vendorReportManagement(Session currentSession);
void generateReport(Session currentSession);
void ranking(Session currentSession);

void vendorReportManagement(Session currentSession) {

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
		cout << "1. Generate report" << endl;
		cout << "2. Ranking" << endl;
		cout << "3. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, vendorInput);
		cout << endl;
		//End for display screen for manage budget module

		//if vendorInput is equal to 1
		if (vendorInput == "1") {

			generateReport(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if vendorInput is equal to 2
		else if (vendorInput == "2") {

			ranking(currentSession);

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

void generateReport(Session currentSession) {

	MyList<string> orderIDList;
	MyList<OrderDetailList> orderDetails;

	//variable of generateReport
	string vendorInput;
	string date;
	string startDate;
	string endDate;
	string select_query;
	int month;
	int year;

	//initialize connection
	conn = connection();

	int numberOfWrongInput = 0;

	//loop for generate report option
	while (true) {

		system("CLS");

		//Start for display screen for manage budget module
		cout << "Please select your report type" << endl;
		cout << "1. Daily" << endl;
		cout << "2. Monthly" << endl;
		cout << "3. Yearly" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, vendorInput);
		cout << endl;
		//End for display screen for manage budget module

		//if vendorInput is equal to 1
		if (vendorInput == "1") {

			//call view vendor menu function
			cout << "Please specify the date: ";
			cout << endl;
			cout << "Note: YYYY-MM-DD (e.g: 2020-12-31)";
			cout << endl;
			getline(cin, date);
			cout << endl;

			select_query = "SELECT Order_ID FROM `payment` WHERE "
				"Payment_Date = "
				"'" + date + "'"
				" AND Order_ID IN ("
				" SELECT Order_ID FROM `order` WHERE "
				" Vendor_ID = "
				""+to_string(currentSession.userID)+""
				")";

			break;

		}

		//if vendorInput is equal to 2
		else if (vendorInput == "2") {

			//call view vendor menu function
			bool results = getInput("Please specify the month", month);

			if (!results) {

				cout << "You have enter the wrong input for more than 3 times";
				cout << endl;
				cout << "Please try again later";
				cout << endl;
				system("pause");
				cout << endl;

				return;
			
			}

			results = getInput("Please specify the year", year);

			if (!results) {

				cout << "You have enter the wrong input for more than 3 times";
				cout << endl;
				cout << "Please try again later";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

			//set start date
			startDate = to_string(year);
			startDate.append("-");
			startDate.append(to_string(month));
			startDate.append("-1");

			//set end date
			if (month == 12) {
				month = 1;
				year += 1;
			}
			else {

				month += 1;
			
			}
			endDate = to_string(year);
			endDate.append("-");
			endDate.append(to_string(month));
			endDate.append("-1");

			select_query = "SELECT Order_ID FROM `payment` WHERE "
								  "Payment_Date >= "
								  "'" + startDate + "'"
								  " AND Payment_Date < "
								  "'"+ endDate +"'"
								  " AND Order_ID IN ("
								  " SELECT Order_ID FROM `order` WHERE "
								  " Vendor_ID = "
								  "" + to_string(currentSession.userID) + ""
								  ")";

			break;

		}

		//if vendorInput is equal to 3
		else if (vendorInput == "3") {

			bool results = getInput("Please specify the year", year);

			if (!results) {

				cout << "You have enter the wrong input for more than 3 times";
				cout << endl;
				cout << "Please try again later";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

			//set start date
			startDate = to_string(year);
			startDate.append("-1-1");

			//set end date
			endDate = to_string(year);
			endDate.append("-12-31");

			select_query = "SELECT Order_ID FROM `payment` WHERE "
								  "Payment_Date >= "
								  "'" + startDate + "'"
								  " AND Payment_Date <= "
								  "'" + endDate + "'"
								  " AND Order_ID IN ("
								  " SELECT Order_ID FROM `order` WHERE "
								  " Vendor_ID = "
								  "" + to_string(currentSession.userID) + ""
								  ")";

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

	//execute update query
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

	int num_row;

	//result is returned
	if (res) {

		num_row = mysql_num_rows(res);

	}

	//result is not returned
	else {

		num_row = 0;

	}

	//if result returned more than 0 row
	if (num_row > 0) {

		while (row = mysql_fetch_row(res)) {

			if (orderIDList.isEmpty()) {

				orderIDList.setHead(row[0]);
			
			}

			else {

				orderIDList.addToList(row[0]);
			
			}
		
		}
	
	}

	//if result returned 0 row
	else {

		cout << "There is not enough data to generate report";
		cout << endl;
		cout << "Please try again later.";
		cout << endl;
		system("pause");
		cout << endl;

		return;
	
	}

	double totalAmount = 0;

	while (!orderIDList.isEmpty()) {

		string tempOrderID = orderIDList.pop();

		select_query = "SELECT * FROM `order detail` WHERE "
					   " Order_ID = "
					   "'" + tempOrderID + "'";

		//execute update query
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

		int num_row;

		//result is returned
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//result is not returned
		else {

			num_row = 0;

		}

		//if result returned more than 0 row
		if (num_row > 0) {

			cout << endl;
			cout << "Details of " << tempOrderID;
			cout << endl;

			while (row = mysql_fetch_row(res)) {
			
				OrderDetailList tempOrderDetail;
				tempOrderDetail.setOrderDetailID(row[0]);
				tempOrderDetail.setOrderID(row[1]);
				tempOrderDetail.setCustomerID(stoi(row[2]));
				tempOrderDetail.setMenuID(row[3]);
				tempOrderDetail.setItemQuantity(stoi(row[4]));
				tempOrderDetail.setTotalItemPrice(stof(row[5]));

				totalAmount += tempOrderDetail.getTotalItemPrice();

				if (orderDetails.isEmpty()) {

					orderDetails.setHead(tempOrderDetail);
				
				}

				else {
				
					orderDetails.addToList(tempOrderDetail);
				
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

			orderDetails.displayList();

			while (!orderDetails.isEmpty()) {

				orderDetails.pop();
			
			}
		
		}

	}

	cout << endl;
	cout << "Total sales amount is RM " << fixed << setprecision(2) << totalAmount;
	cout << endl;

	system("pause");
	cout << endl;

	return;

}

void ranking(Session currentSession) {

	MyList<MenuTotalSale> menuTotalSales;
	string menuName;
	int month, year;

	//create current time date manager and set time for startOfMonth and currentDate
	//dummy date
	//date = "30-12-2020";

	bool results = getInput("Please specify the month", month);

	if (!results) {

		cout << "You have enter the wrong input for more than 3 times";
		cout << endl;
		cout << "Please try again later";
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

	results = getInput("Please specify the year", year);

	if (!results) {

		cout << "You have enter the wrong input for more than 3 times";
		cout << endl;
		cout << "Please try again later";
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

	//set start date
	string startDate = to_string(year);
	startDate.append("-");
	startDate.append(to_string(month));
	startDate.append("-1");

	//set end date
	if (month == 12) {
		month = 1;
		year += 1;
	}
	else {

		month += 1;

	}
	string endDate = to_string(year);
	endDate.append("-");
	endDate.append(to_string(month));
	endDate.append("-1");

	string select_query = " SELECT SUM(Total_Item_Price) AS Total_Profit, Menu_ID "
						  " FROM `order detail` WHERE "
						  " Menu_ID IN ("
						  " SELECT Menu_ID FROM `menu` WHERE "
						  " Vendor_ID = "
						  "" + to_string(currentSession.userID) + ""
						  ") AND Order_ID IN ("
						  " SELECT Order_ID FROM `payment` WHERE "
						  " Payment_Date >= "
						  "'" + startDate + "'"
						  " AND Payment_Date < "
						  "'" + endDate + "'"
						  " AND Order_ID IN ("
						  " SELECT Order_ID FROM `order` WHERE "
						  " Vendor_ID = "
						  "" + to_string(currentSession.userID) + ""
						  ")"
						  ") GROUP BY Menu_ID "
						  " ORDER BY Total_Profit ASC";

	//execute update query
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

	int num_row;

	//result is returned
	if (res) {

		num_row = mysql_num_rows(res);

	}

	//result is not returned
	else {

		num_row = 0;

	}

	//if result returned more than 0 row
	if (num_row > 0) {

		//get ranking from query
		while (row = mysql_fetch_row(res)) {
		
			struct MenuTotalSale tempSales;
			tempSales.totalSale = stof(row[0]);
			tempSales.menu = row[1];

			if (menuTotalSales.isEmpty()) {

				menuTotalSales.setHead(tempSales);
			
			}

			else {

				menuTotalSales.addToList(tempSales);
			
			}
		
		}
	
	}

	//if result returned 0 row
	else {

		cout << "No result returned";
		cout << endl;
		system("pause");
		cout << endl;

		return;
	
	}

	menuTotalSales.goToHead();

	struct MenuTotalSale temp;

	int counter = 1;

	cout << "------------------------";
	cout << "------------------------";
	cout << endl;

	//display ranking
	while (!menuTotalSales.isEmpty()) {

		temp = menuTotalSales.pop();
		cout <<"|"<< "Top " << counter++ << "\t|";

		string select_query = "SELECT Menu_Name FROM `menu` WHERE "
							  " Menu_ID = "
							  "'" + temp.menu + "'";

		//execute update query
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

		int num_row;

		//result is returned
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//result is not returned
		else {

			num_row = 0;

		}

		if (num_row > 0) {
		
			while (row = mysql_fetch_row(res)) {
			
				menuName = row[0];

			}
		
		}

		else {
		
			cout << "No menu name for menu ID - " << temp.menu;
			cout << endl;
			system("pause");
			cout << endl;

			return;
		
		}

		cout << temp.menu << "\t|" << left << setw(30) << menuName<<"|";
		cout << endl;
	
	}

	cout << "------------------------";
	cout << "------------------------";
	cout << endl;

	system("pause");
	cout << endl;

	return;

}


#endif // !VENDORREPORTMANAGEMENT_H
