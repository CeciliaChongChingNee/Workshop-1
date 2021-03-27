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

#ifndef VIEWORDERSTATUS
#define VIEWORDERSTATUS

void viewOrderStatus(Session currentSession);

void viewOrderStatus(Session currentSession) {

	//variable of view order function
	MyList<OrderList> orders;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');


	string select_query = "SELECT * FROM `order` WHERE "
						  " Customer_ID = "
						  " " + to_string(currentSession.userID) + " ";

	int state = mysql_query(conn, select_query.c_str());

	if (state != 0) {

		cout << select_query << endl;
		cout << endl;
	
		cout << mysql_error(conn);
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

	res = mysql_store_result(conn);

	int num_row;

	if (res) {
	
		num_row = mysql_num_rows(res);

	}
	else {

		num_row = 0;
	
	}

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

			//if list is empty
			if (orders.isEmpty()) {
			
				orders.setHead(temp);

			}

			//if list is not empty
			else {

				orders.addToList(temp);
			
			}

		}

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
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

	//if result returned 0 row
	else {

		cout << "You currently have no order.";
		cout << endl;
		cout << "Please try again later";
		cout << endl;
		system("pause");
		cout << endl;

		return;
	
	}

}

#endif // !VIEWORDER


