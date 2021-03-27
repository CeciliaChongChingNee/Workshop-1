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

#ifndef VENDORMENUMANAGEMENT_H
#define VENDORMENUMANAGEMENT_H

void vendorMenuManagement(Session currentSession);
void viewVendorMenu(Session currentSession);
void vendorManageMenu(Session currentSession);


void vendorMenuManagement(Session currentSession) {

	//view menu (belong to current vendor)
	//edit menu quantity

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
		cout << "1. View menu" << endl;
		cout << "2. Manage menu" << endl;
		cout << "3. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, vendorInput);
		cout << endl;
		//End for display screen for manage budget module

		//if vendorInput is equal to 1
		if (vendorInput == "1") {

			//call view vendor menu function
			viewVendorMenu(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if vendorInput is equal to 2
		else if (vendorInput == "2") {

			//call manage menu function
			vendorManageMenu(currentSession);
			

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

//function view vendor menu
void viewVendorMenu(Session currentSession) {

	//clear screen
	system("CLS");

	MyList<MenuList> list;
	MenuList temp;

	string select_query = "SELECT * FROM `menu` WHERE "
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

		//set value to menu from database
		while ((row = mysql_fetch_row(res))) {

			//initialize temp menu to store value
			temp.setMenuID(row[0]);
			temp.setVendorID(atoi(row[1]));
			temp.setMealTypeID(row[2]);
			temp.setMenuName(row[3]);
			temp.setMenuDescription(row[4]);
			temp.setMenuQuantity(stoi(row[5]));
			temp.setMenuPrice(stod(row[6]));

			//if this is the first element added to list
			if (list.isEmpty()) {

				//set element as head of list
				list.setHead(temp);
			}

			//If not the first element
			else {

				//add element to list
				list.addToList(temp);
			}

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

	//if result returned 0 row
	else {

		cout << "You do not have any menu item";
		cout << endl;
		cout << "Please contact admin to add more menu";
		cout << endl;
		system("pause");
		cout << endl;

		return;
	
	}

}

//function manage vendor menu
void vendorManageMenu(Session currentSession) {

	string vendorInputMenuID;
	int vendorInputStockAmount;
	MenuList menu;

	//number of tries in checking ID exist
	int numberOfTries = 0;

	//loop to check ID exist
	while (true) {

		//number of times failed in entering menu ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			viewVendorMenu(currentSession);

			//get menu ID from admin
			cout << "Please enter menu ID that you want to edit";
			cout << endl;
			cout << "Note: MXXX (e.g: M001)";
			cout << endl;
			getline(cin, vendorInputMenuID);
			cout << endl;

			//get length of user input
			int a = vendorInputMenuID.length();

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
						if (vendorInputMenuID.at(0) == 'M') {

							//set hasM to true
							hasM = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (vendorInputMenuID.at(i) >= 48 && vendorInputMenuID.at(i) <= 57) {

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

				return;

			}

		}

		//check the vendor ID in database or not
		string selectQuery = "SELECT * FROM menu "
							 " WHERE Menu_ID = '" + vendorInputMenuID + "' "
							 " AND "
							 " Vendor_ID = "
							 ""+ to_string(currentSession.userID) +"";

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

			return;

		}

	}

	bool results = getInput("Please enter stock amount", vendorInputStockAmount);

	//if fail to get input
	if (!results) {

		//display error message and go back to vendor main screen
		cout << "You have entered the wrong format for more than 3 times.";
		cout << endl;
		cout << "Please try again later.";
		cout << endl;
		system("pause");
		cout << endl;

		//return to vendor main screen
		return;

	}

	cout << "Menu stock amount has been updated";
	cout << endl;

	menu.setMenuQuantity(vendorInputStockAmount);
	menu.save();

	return;

}

#endif // !VENDORMENUMANAGEMENT_H
