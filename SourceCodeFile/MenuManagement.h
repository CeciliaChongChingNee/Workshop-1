/*
*This program demonstrates a simple C++ program.
*The function in this program is menuManagement.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <mysql.h>
#include "List.h"
#include "MyList.h"
#include "Login.h"
#include "DatabaseConnection.h"
using namespace std;

#ifndef MENUMANAGEMENT_H
#define MENUMANAGEMENT_H

//function prototype
void viewMenu(Session currentSession);
void editMenu(Session currentSession);
void addMenu(Session currentSession);
void deleteMenu(Session currentSession);
void editMealType(Session currentSession, MenuList menu);
void editMenuName(Session currentSession, MenuList menu);
void editMenuDescription(Session currentSession, MenuList menu);
void editMenuPrice(Session currentSession, MenuList menu);

//function menuManagement to show the menu management main screen
void menuManagement(Session currentSession) {

	//variable of menuManagement
	string adminInput;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');

	//loop for menu management main screen
	while (true) {

		system("CLS");

		//Start for display screen for manage menu module
		cout << "1. View menu" << endl;
		cout << "2. Edit menu" << endl;
		cout << "3. Add menu" << endl;
		cout << "4. Delete menu" << endl;
		cout << "5. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, adminInput);
		cout << endl;
		//End for display screen for manage menu module

		//if adminInput is equal to 1
		if (adminInput == "1") {

			//call view menu function
			viewMenu(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if adminInput is equal to 2
		else if (adminInput == "2") {

			//call edit menu function
			editMenu(currentSession);

		}

		//if adminInput is equal to 3
		else if (adminInput == "3") { 

			//call add menu function
			addMenu(currentSession);

			//check if want to continue
			if (!checkContinue()) {
				return;
			}

		}

		//if adminInput is equal to 4
		else if (adminInput == "4") {

			//call delete menu function
			deleteMenu(currentSession);

			//check if want to continue
			if (!checkContinue()) {
				return;
			}


		}

		//if adminInput is equal to 5
		else if (adminInput == "5") {

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

//function view menu
void viewMenu(Session currentSession) {

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;
	
	//clear screen 
	system("CLS");

	//get menu from database
	string selectQuery = "SELECT * FROM menu";

	//Execute query (get the data from database)
	mysql_query(conn, selectQuery.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	//declare temp menu object
	MenuList temp;

	//count number of menu list added to list
	int counter = 0;

	//declare list
	MyList<MenuList> list;

	int num_row;

	//if result is returned
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

	//if result returned 0 row
	else {

		cout << "There is no menu in database.";
		cout << endl;
		cout << "Please try again later";
		cout << endl;
		system("pause");

		return;

	}

}

//function edit menu
void editMenu(Session currentSession) {

	//variable for edit menu
	string adminInputMenuID;
	string adminInputEditType;
	string adminInputMealType;
	string adminInputAdminPassword;
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

			//get menu ID from admin
			cout << "Please enter menu ID that you want to edit";
			cout << endl;
			cout << "Note: MXXX (e.g: M001)";
			cout << endl;
			getline(cin, adminInputMenuID);
			cout << endl;

			//get length of user input
			int a = adminInputMenuID.length();

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
						if (adminInputMenuID.at(0) == 'M') {

							//set hasM to true
							hasM = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputMenuID.at(i) >= 48 && adminInputMenuID.at(i) <= 57) {

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
							 " WHERE Menu_ID = '" + adminInputMenuID + "' ";

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

	int numberOfError = 0;

	//loop for checking edit type format
	while (true) {

		//clear screen
		system("CLS");

		//Start to display option
		cout << "1. Edit meal type" << endl;
		cout << "2. Edit menu name" << endl;
		cout << "3. Edit menu description" << endl;
		cout << "4. Edit menu price" << endl;
		cout << "5. Go back" << endl;
		cout << "Please insert your choice" << endl;
		getline(cin, adminInputEditType);
		cout << endl;
		//End to display option 

		//if adminInputEditType is equal to 1
		if (adminInputEditType == "1") {

			//call edit meal type function
			editMealType(currentSession, menu);

			//check if want to continue
			if (!checkContinue()) {
				return;
			}

		}

		//if adminInputEditType is equal to 2
		else if (adminInputEditType == "2") {

			//call edit menu name function
			editMenuName(currentSession, menu);

		}

		//if adminInputEditType is equal to 3
		else if (adminInputEditType == "3") {

			//call edit menu description function
			editMenuDescription(currentSession, menu);

		}

		//if adminInputEditType is equal to 4
		else if (adminInputEditType == "4") {

			//call edit menu price function
			editMenuPrice(currentSession, menu);

		}

		//if adminInputEditType is equal to 5
		else if (adminInputEditType == "5") {

			//go back to menuManagement main screen
			return;

		}

		//if adminInput is not equal to the choice above
		else {

			//display error messenge
			cout << "Sorry, please enter the correct choice.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfError++;

		}

		if (numberOfError >= 3) {
			
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

}

//function add menu
void addMenu(Session currentSession) {

	//variable of add menu
	string adminInputNewVendorID;
	string adminInputNewMealType;
	string adminInputNewMenuName;
	string adminInputNewMenuDescription;
	double adminInputNewMenuPrice;

	//clear screen
	system("CLS");

	int numberOfVendorIDFail = 0;

	//loop for vendorID
	while (true) {

		int userInput;

		//get balance that want to update
		bool results = getInput("Please insert vendor ID", userInput);

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

		adminInputNewVendorID = to_string(userInput);

		//check the vendor ID in database or not
		string selectQuery = "SELECT * FROM user "
							 " WHERE User_ID = " + adminInputNewVendorID + " "
							 "AND User_Type = 'Vendor' ";

		//execute query (get the data from database)
		mysql_query(conn, selectQuery.c_str());

		//extract data into result
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

			//break out current loop and get to next loop
			break;
		
		}

		//if result returned 0 row
		else {

			//display error messenge and exit to main screen
			cout << "The vendor ID entered does not exist.";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfVendorIDFail++;
		
		}

		if (numberOfVendorIDFail >= 3) {
		
			//display error messenge and exit to main screen
			cout << "You have entered wrong input for vendor ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}
		
	}

	//get all menu type from database
	string select_query = " SELECT * FROM `meal type` ";

	//execute query (get the data from database)
	mysql_query(conn, select_query.c_str());

	//extract data into result
	res = mysql_store_result(conn);

	//declare temp menu object
	MealTypeList temp;

	//count number of menu list added to list
	int counter = 0;

	//declare list
	MyList<MealTypeList> list;

	//result is returned
	if (res) {

		//set value to menu from database
		while ((row = mysql_fetch_row(res))) {

			//initialize temp menu to store value
			temp.setMealTypeID(row[0]);
			temp.setTypeName(row[1]);
			temp.setTimeStart(row[2]);
			temp.setTimeEnd(row[3]);

			//if this is the first element added to list
			if (list.getLength() == 0) {

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
	
	}

	//no result returned
	else {
	
	}
	

	//count number of wrong meal type ID format
	int numberOfIDFailed = 0;

	//loop for checking meal type ID entered exist
	while (true) {

		int numberOfMealTypeIDFormatFail = 0;

		//loop for checking  meal type ID format
		while (true) {

			//clear screen
			system("CLS");

			cout << "Meal Type List" << endl;

			cout << "-------------------------------------";
			cout << "------------";
			cout << endl;

			cout << "| " << " ID " << " | "
				<< left << setw(15) << "Name" << "| "
				<< setw(10) << "Start Time" << "| "
				<< setw(10) << "End Time" << "|" << endl;

			cout << "-------------------------------------";
			cout << "------------";
			cout << endl;

			//display list
			list.displayList();
			cout << endl;

			//get menu ID from admin
			cout << "Please insert meal type ID";
			cout << endl;
			getline(cin, adminInputNewMealType);
			cout << endl;

			//get length of user input
			int a = adminInputNewMealType.length();

			//set initial value for boolean flag
			bool hasT = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only M
						if (adminInputNewMealType.at(0) == 'T') {

							//set hasAlphabet to true
							hasT = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputNewMealType.at(i) >= 48 && adminInputNewMealType.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasAlphabet and hasDigit to false
							hasT = false;
							hasDigit = false;


							//break out of the for loop and go to check hasM and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasT)) {

					//userInput format is wrong
					cout << "Sorry, please follow the format given.";
					cout << "Please try again." << endl;
					system("pause");
					cout << endl;

					//count number of ID failed
					numberOfMealTypeIDFormatFail++;

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
				cout << "The menu type ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfMealTypeIDFormatFail++;

			}

			if (numberOfMealTypeIDFormatFail >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for meal type ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		//select menu name that is the same as user input
		string selectQuery = " SELECT * FROM `meal type` "
							 " WHERE Meal_Type_ID = "
							 " '" + adminInputNewMealType + "' ";

		//execute query (get the data from database)
		mysql_query(conn, selectQuery.c_str());

		//extract data into result
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
		
			//break and go to next part
			break;

		}

		//if result returned 0 row
		else {
			
			//display error message and return to edit menu page
			cout << "The meal type entered does not exist";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfIDFailed++;

		}

		//if the number of meal type id fail is more than equal 3
		if (numberOfIDFailed >= 3) {
		
			//display error messenge and exit to main screen
			cout << "You have entered wrong input for meal type ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}
	
	}

	//loop for checking menu name entered exist
	while (true) {

		int numberOfWrongInput = 0;
		
		//loop for menu name check entered
		while (true) {

			//get menu name from admin
			cout << "Please enter menu name";
			cout << endl;
			getline(cin, adminInputNewMenuName);
			cout << endl;

			//if user did not enter value
			if (adminInputNewMenuName.empty()) {

				//display error message and add to numberOfWrongInput counter
				cout << "User has not entered menu name";
				cout << endl;
				cout << "Please try again.";
				cout << endl;
				system("pause");
				cout << endl;

				numberOfWrongInput++;

			}

			//if user has entered value
			else {

				//break into next part
				break;

			}

			//if number of wrong input is more than 3
			if (numberOfWrongInput >= 3) {

				//display error message and go back to menu management main screen
				cout << "You have entered the wrong input for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				//return to menu management main screen
				return;

			}

		}
		
		//select menu name that is the same as user input
		string selectQuery = " SELECT * FROM menu "
							 " WHERE Menu_Name = "
							 " '" + adminInputNewMenuName + "' ";

		//execute query (get the data from database)
		mysql_query(conn, selectQuery.c_str());

		//extract data into result
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

			//display error message
			cout << "There is existing menu with this name.";
			cout << endl;
			cout << "Please try another name";
			cout << "endl";

			system("pause");
		
		}

		//if result returned 0 row
		else {
		
			//break out of this loop and go to next part
			break;

		}

	}

	int numberOfWrongInput = 0;

	//loop for menu description
	while (true) {

		//get menu description from admin
		cout << "Please insert menu description" << endl;
		getline(cin, adminInputNewMenuDescription);
		cout << endl;

		//if user did not enter value
		if (adminInputNewMenuDescription.empty()) {

			//display error message and add to numberOfWrongInput counter
			cout << "User has not entered menu description";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		//if user has entered value
		else {

			//break into next part
			break;

		}

		//if number of wrong input is more than 3
		if (numberOfWrongInput >= 3) {

			//display error message and go back to menu management main screen
			cout << "You have entered the wrong input for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to menu management main screen
			return;

		}

	}

	//get balance that want to update
	bool results = getInput("Please insert menu price", adminInputNewMenuPrice);

	//if fail to get input
	if (!results) {

		//display error message and go back to menu management main screen
		cout << "You have entered the wrong format for more than 3 times.";
		cout << endl;
		cout << "Please try again later.";
		cout << endl;
		system("pause");
		cout << endl;

		//return to menu management main screen
		return;

	}

	//create temp menu item and insert to database
	MenuList tempMenu;

	tempMenu.setVendorID(stoi(adminInputNewVendorID));
	tempMenu.setMealTypeID(adminInputNewMealType);
	tempMenu.setMenuDescription(adminInputNewMenuDescription);
	tempMenu.setMenuName(adminInputNewMenuName);
	tempMenu.setMenuPrice(adminInputNewMenuPrice);
	tempMenu.setMenuQuantity(1);

	//save the menu to database
	tempMenu.save();

	cout << "New Menu is added";
	cout << endl;
	cout << "The new menu ID is  " << tempMenu.getMenuID();
	cout << endl;
	system("pause");

	return;

}

//function delete menu
void deleteMenu(Session currentSession) {

	//variable for delete menu 
	string adminInputMenuID;
	string adminInputAdminPassword;

	int numberOfWrongInput = 0;

	while (true) {
	
		//number of times failed in entering menu ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get meal type ID from admin
			cout << "Please enter menu ID that you want to delete";
			cout << endl;
			cout << "Note: MXXX (e.g: M001)";
			cout << endl;
			getline(cin, adminInputMenuID);
			cout << endl;

			//get length of user input
			int a = adminInputMenuID.length();

			//set initial value for boolean flag
			bool hasM = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only T
						if (adminInputMenuID.at(0) == 'M') {

							//set hasT to true
							hasM = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputMenuID.at(i) >= 48 && adminInputMenuID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasT and hasDigit to false
							hasM = false;
							hasDigit = false;


							//break out of the for loop and go to check hasT and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasM)) {

					//userInput format is wrong
					cout << "Sorry, please follow the format given.";
					cout << "Please try again." << endl;
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

		string select_query = "SELECT * FROM menu WHERE Menu_ID = '" + adminInputMenuID + "'";

		//Execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//Extract data into result
		res = mysql_store_result(conn);

		int num_row = 0;

		//if result returned
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//if result not returned
		else {

			num_row = 0;

		}

		//if result returned is more than 0 row
		if (num_row > 0) {

			//count number of times wrong password
			int numberOfWrongPassword = 0;

			//loop for checking admin password is correct or not
			while (true) {

				//get admin password from admin
				cout << "Please enter your(admin's) password";
				cout << endl;
				getline(cin, adminInputAdminPassword);
				cout << endl;

				//verify user exist in database 
				string selectQuery = "SELECT User_Type FROM user "
					" WHERE User_ID = " + to_string(currentSession.userID) + " "
					" AND User_Password = '" + adminInputAdminPassword + "' ";

				//execute query (get the data from database)
				mysql_query(conn, selectQuery.c_str());

				//extract data into result
				res = mysql_store_result(conn);

				//if there is at least 1 row of result returned
				if (res) {

					//delete the meal type from database
					string delete_query = "DELETE FROM menu "
						" WHERE Menu_ID = '" + adminInputMenuID + "' ";

					//execute update query
					mysql_query(conn, delete_query.c_str());

					cout << "The menu with menu ID " << adminInputMenuID << " is deleted";
					cout << endl;
					system("pause");
					cout << endl;

					return;

				}

				//if the result is equal to 0 row
				else {

					//display error messenge
					cout << "Please enter the correct password.";
					cout << endl;
					system("pause");
					cout << endl;

					//count number of login fails
					numberOfWrongPassword++;

				}

				//If more than 3 error then go back to meal type management main screen
				if (numberOfWrongPassword >= 3) {

					//display error message and go back to meal type management main screen
					cout << "You have entered wrong password for more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					//return to meal type management main screen
					return;
				}

			}

		}

		//if result returned is 0 row
		else {

			cout << "The menu does not exist";
			cout << endl;
			cout << "Please try again later";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		//if number of wrong input is more than equal 3 times
		if (numberOfWrongInput >= 3) {

			//display error message and go back to meal type management main screen
			cout << "You have entered wrong password for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to meal type management main screen
			break;
			
		}

	}

}

//function edit meal type
void editMealType(Session currentSession, MenuList menu) {

	string adminInputNewMealType;

	//get all menu type from database
	string select_query = " SELECT * FROM `meal type` ";

	//execute query (get the data from database)
	mysql_query(conn, select_query.c_str());

	//extract data into result
	res = mysql_store_result(conn);

	//declare temp menu object
	MealTypeList temp;

	//count number of menu list added to list
	int counter = 0;

	//declare list
	MyList<MealTypeList> list;

	int num_row;

	//if results returned
	if (res) {

		num_row = mysql_num_rows(res);
	
	}

	//if results not returned
	else {

		num_row = 0;
		
	}

	//if result returned more than 0 row
	if (num_row > 0) {

		//set value to menu from database
		while ((row = mysql_fetch_row(res))) {

			//initialize temp menu to store value
			temp.setMealTypeID(row[0]);
			temp.setTypeName(row[1]);
			temp.setTimeStart(row[2]);
			temp.setTimeEnd(row[3]);

			//if this is the first element added to list
			if (list.getLength() == 0) {

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
	
	}

	//if result returned 0 row
	else {
	
	}

	//count number of wrong meal type ID format
	int numberOfIDFailed = 0;

	//loop for checking meal type ID entered exist
	while (true) {

		int numberOfMealTypeIDFormatFail = 0;

		//loop for checking  meal type ID format
		while (true) {

			//clear screen
			system("CLS");

			cout << "Meal Type List" << endl;

			cout << "-------------------------------------";
			cout << "------------";
			cout << endl;

			cout << "| " << " ID " << " | "
				<< left << setw(15) << "Name" << "| "
				<< setw(10) << "Start Time" << "| "
				<< setw(10) << "End Time" << "|" << endl;

			cout << "-------------------------------------";
			cout << "------------";
			cout << endl;

			//display list
			list.displayList();
			cout << endl;

			//get menu ID from admin
			cout << "Please insert meal type ID";
			cout << endl;
			getline(cin, adminInputNewMealType);
			cout << endl;

			//get length of user input
			int a = adminInputNewMealType.length();

			//set initial value for boolean flag
			bool hasT = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only M
						if (adminInputNewMealType.at(0) == 'T') {

							//set hasAlphabet to true
							hasT = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputNewMealType.at(i) >= 48 && adminInputNewMealType.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasAlphabet and hasDigit to false
							hasT = false;
							hasDigit = false;


							//break out of the for loop and go to check hasM and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasT)) {

					//userInput format is wrong
					cout << "Sorry, please follow the format given.";
					cout << "Please try again." << endl;
					system("pause");
					cout << endl;

					//count number of ID failed
					numberOfMealTypeIDFormatFail++;

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
				cout << "The menu type ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfMealTypeIDFormatFail++;

			}

			if (numberOfMealTypeIDFormatFail >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for meal type ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		//select menu name that is the same as user input
		string selectQuery = " SELECT * FROM `meal type` "
							 " WHERE Meal_Type_ID = "
							 " '" + adminInputNewMealType + "' ";

		//execute query (get the data from database)
		mysql_query(conn, selectQuery.c_str());

		//extract data into result
		res = mysql_store_result(conn);

		int num_row2;

		//if result returned
		if (res) {

			num_row2 = mysql_num_rows(res);

		}

		//if result not returned
		else {

			num_row2 = 0;

		}

		//if result returned more than 0 row
		if (num_row2 > 0) {

			//break and go to next part
			break;
		
		}

		//if result returned 0 row
		else {

			//display error message and return to edit menu page
			cout << "The meal type entered does not exist";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfIDFailed++;
		
		}

		//if the number of meal type id fail is more than equal 3
		if (numberOfIDFailed >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for meal type ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

	}

	menu.setMealTypeID(adminInputNewMealType);

	menu.save();


}

//function edit menu name
void editMenuName(Session currentSession, MenuList menu) {

	string adminInputNewMenuName;

	//clear screen
	system("CLS");

	//display current type name
	cout << "The current menu name is " << menu.getMenuName();
	cout << endl;

	//check if want to continue
	if (!checkContinue()) {
		return;
	}

	//loop for checking menu name entered exist
	while (true) {

		int numberOfWrongInput = 0;

		//loop for menu name check entered
		while (true) {

			//get menu name from admin
			cout << "Please enter menu name";
			cout << endl;
			getline(cin, adminInputNewMenuName);
			cout << endl;

			//if user did not enter value
			if (adminInputNewMenuName.empty()) {

				//display error message and add to numberOfWrongInput counter
				cout << "User has not entered menu name";
				cout << endl;
				cout << "Please try again.";
				cout << endl;
				system("pause");
				cout << endl;

				numberOfWrongInput++;

			}

			//if user has entered value
			else {

				//break into next part
				break;

			}

			//if number of wrong input is more than 3
			if (numberOfWrongInput >= 3) {

				//display error message and go back to menu management main screen
				cout << "You have entered the wrong input for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				//return to menu management main screen
				return;

			}

		}

		//select menu name that is the same as user input
		string selectQuery = " SELECT * FROM menu "
			" WHERE Menu_Name = "
			" '" + adminInputNewMenuName + "' ";

		//execute query (get the data from database)
		mysql_query(conn, selectQuery.c_str());

		//extract data into result
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

			//display error message
			cout << "There is existing menu with this name.";
			cout << endl;
			cout << "Please try another name";
			cout << "endl";

			system("pause");

		}

		//if result returned 0 row
		else {

			//break out of this loop and go to next part
			break;

		}

	}

	menu.setMenuName(adminInputNewMenuName);

	menu.save();

}

//function edit menu description
void editMenuDescription(Session currentSession, MenuList menu) {

	string adminInputNewMenuDescription;

	//clear screen
	system("CLS");

	//display current type name
	cout << "The current menu description is " << menu.getMenuDescription();
	cout << endl;

	//check if want to continue
	if (!checkContinue()) {
		return;
	}


	int numberOfWrongInput = 0;

	//loop for menu description
	while (true) {

		//get menu description from admin
		cout << "Please insert menu description" << endl;
		getline(cin, adminInputNewMenuDescription);
		cout << endl;

		//if user did not enter value
		if (adminInputNewMenuDescription.empty()) {

			//display error message and add to numberOfWrongInput counter
			cout << "User has not entered menu description";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		//if user has entered value
		else {

			//break into next part
			break;

		}

		//if number of wrong input is more than 3
		if (numberOfWrongInput >= 3) {

			//display error message and go back to menu management main screen
			cout << "You have entered the wrong input for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to menu management main screen
			return;

		}

	}

	menu.setMenuDescription(adminInputNewMenuDescription);

	menu.save();

}

//function edit menu price
void editMenuPrice(Session currentSession, MenuList menu) {

	//clear screen
	system("CLS");

	double adminInputNewMenuPrice;

	//get balance that want to update
	bool results = getInput("Please insert menu price", adminInputNewMenuPrice);

	//if fail to get input
	if (!results) {

		//display error message and go back to menu management main screen
		cout << "You have entered the wrong format for more than 3 times.";
		cout << endl;
		cout << "Please try again later.";
		cout << endl;
		system("pause");
		cout << endl;

		//return to menu management main screen
		return;

	}

	menu.setMenuPrice(adminInputNewMenuPrice);

	menu.save();

}


#endif