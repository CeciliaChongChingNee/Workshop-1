/*
*This program demonstrates a simple C++ program.
*The function in this program is budgetTypeManagement.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <mysql.h>
#include "List.h"
#include "MyList.h"
#include "Login.h"
#include "DateManager.h"
#include "DatabaseConnection.h"
using namespace std;

#ifndef BUDGETTYPEMANAGEMENT_H
#define BUDGETTYPEMANAGEMENT_H

//function prototype
void budgetTypeManagement(Session currentSession);
void viewBudgetType(Session currentSession);
void editBudgetType(Session currentSession);
void addBudgetType(Session currentSession);
void deleteBudgetType(Session currentSession);
void editBudgetLabel(Session currentSession, BudgetTypeList tempBudgetTypeList);
void editBudgetDuration(Session currentSession, BudgetTypeList tempBudgetTypeList);

//function budgetTypeManagement to show budget type management main screen
void budgetTypeManagement(Session currentSession) {

	//variable of budgetTypeManagement
	string adminInput;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');

	int numberOfWrongInput = 0;

	//loop for budget type management main screen
	while (true) {

		//clear screen
		system("CLS");

		//Start for display screen for manage budget type module
		cout << "1. View budget type" << endl;
		cout << "2. Edit budget type" << endl;
		cout << "3. Add budget type" << endl;
		cout << "4. Delete budget type" << endl;
		cout << "5. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, adminInput);
		cout << endl;
		//End for display screen for manage budget type module

		//if adminInput is equal to 1
		if (adminInput == "1") {

			//call view budget type function
			viewBudgetType(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if adminInput is equal to 2
		else if (adminInput == "2") {

			//call edit budget type function
			editBudgetType(currentSession);

			//check if want to continue
			if (!checkContinue()) {
				return;
			}

		}

		//if adminInput is equal to 3
		else if (adminInput == "3") {

			//call add budget type function
			addBudgetType(currentSession);

			//check if want to continue
			if (!checkContinue()) {
				return;
			}

		}

		//if adminInput is equal to 4
		else if (adminInput == "4") {

			//call delete budget type function
			deleteBudgetType(currentSession);

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
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to admin module main screen
			cout << "You have entered the wrong input more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return;

		}

	}

}

//function view budget type
void viewBudgetType(Session currentSession) {

	//clear screen
	system("CLS");

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;

	//get budget type from database
	string selectQuery = "SELECT * FROM `budget type`";

	//Execute query (get the data from database)
	mysql_query(conn, selectQuery.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	//declare temp budget type object
	BudgetTypeList temp;

	//count number of budget type list added to list
	int counter = 0;

	//declare list
	MyList<BudgetTypeList> list;

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

		//set value to budget type from database
		while ((row = mysql_fetch_row(res))) {

			//initialize temp meal type to store value
			temp.setBudgetTypeID(row[0]);
			temp.setBudgetLabel(row[1]);
			temp.setBudgetDuration(row[2]);

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

	
	}

	//if result returned 0 row
	else {

		cout << "These is no data in the database";
		cout << endl;
		cout << "Please try again later";
		cout << endl;
		system("pause");
		cout << endl;

		return;
	}

	cout << "Budget Type List" << endl;

	cout << "-------------------------------------";
	cout << endl;

	cout << "| " << " ID " << " | "
		<< left << setw(15) << "Label" << "| "
		<< setw(10) << "Duration" << "|" << endl;

	cout << "-------------------------------------";
	cout << endl;

	//display list
	list.displayList();
	cout << endl;

}

//function edit budget type
void editBudgetType(Session currentSession) {

	//clear screen
	system("CLS");

	//variable for edit budget type
	string adminInputBudgetTypeID;
	string adminInputEditType;
	string adminInputAdminPassword;

	//temp budget type object to store details
	BudgetTypeList tempBudgetType;

	//count number of tries
	int numberOfTries = 0;

	//loop for checking ID correct
	while (true) {

		//number of times failed in entering budget type ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get budget type ID from admin
			cout << "Please enter budget type ID that you want to edit";
			cout << endl;
			cout << "Note: GXXX (e.g: G001)";
			cout << endl;
			getline(cin, adminInputBudgetTypeID);
			cout << endl;

			//get length of user input
			int a = adminInputBudgetTypeID.length();

			//set initial value for boolean flag
			bool hasG = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only G
						if (adminInputBudgetTypeID.at(0) == 'G') {

							//set hasG to true
							hasG = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputBudgetTypeID.at(i) >= 48 && adminInputBudgetTypeID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasG and hasDigit to false
							hasG = false;
							hasDigit = false;


							//break out of the for loop and go to check hasG and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasG)) {

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
				cout << "The budget type ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfIDFailed++;

			}

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

		string select_query = "SELECT * FROM `budget type` WHERE Budget_Type_ID = '" + adminInputBudgetTypeID + "'";

		//Execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//Extract data into result
		res = mysql_store_result(conn);

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
		if (num_row> 0) {

			while (row = mysql_fetch_row(res)) {

				tempBudgetType.setBudgetTypeID(adminInputBudgetTypeID);
				tempBudgetType.setBudgetLabel(row[1]);
				tempBudgetType.setBudgetDuration(row[2]);

			}

			break;

		}

		//if result returned 0 row
		else {

			cout << "Budget type does not exist in database.";
			cout << endl;
			cout << "Please try again";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfTries++;

		}

		//if the number of tries is >= 3
		if (numberOfTries >= 3) {

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

	//loop for checking edit type format
	while (true) {

		//clear screen
		system("CLS");

		//Start to display option
		cout << "1. Edit budget label" << endl;
		cout << "2. Edit budget duration" << endl;
		cout << "3. Go back" << endl;
		cout << "Please insert your choice" << endl;
		getline(cin, adminInputEditType);
		cout << endl;
		//End to display option 

		//if adminInputEditType is equal to 1
		if (adminInputEditType == "1") {

			//call edit budget label function
			editBudgetLabel(currentSession, tempBudgetType);

		}

		//if adminInputEditType is equal to 2
		else if (adminInputEditType == "2") {

			//call edit budget duration function
			editBudgetDuration(currentSession, tempBudgetType);

		}

		//if adminInputEditType is equal to 3
		else if (adminInputEditType == "3") {

			//go back to budgetTypeManagement main screen
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

		}
	}
}

//function add budget type
void addBudgetType(Session currentSession) {

	//variable of add budget type
	string adminInputNewBudgetLabel;
	string adminInputNewBudgetDuration;
	string adminInputAdminPassword;

	//count the number of tries
	int numberOfTries = 0;

	//loop to get new budget label
	while (true) {

		//clear screen
		system("CLS");

		int numberOfWrongInput = 0;

		//loop for budget label input
		while (true) {

			//get new budget label from admin
			cout << "Please enter new budget label that you want to created" << endl;
			getline(cin, adminInputNewBudgetLabel);
			cout << endl;

			//if user did not enter value
			if (adminInputNewBudgetLabel.empty()) {

				//display error message and add to numberOfWrongInput counter
				cout << "User has not entered budget label";
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

				//display error message and go back to meal type management main screen
				cout << "You have entered the wrong input for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				//return to meal type management main screen
				return;

			}

		}

		string select_query = "SELECT * FROM 'buget type' WHERE Budget_Label = "
			" '" + adminInputNewBudgetLabel + "' ";

		//execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//extract data into result
		res = mysql_store_result(conn);

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

			//display error message
			cout << "There is existing budget type with this name.";
			cout << endl;
			cout << "Please try another name";
			cout << "endl";

			system("pause");

			numberOfTries++;

		}

		//if result returned 0 row
		else {

			break;

		}

		if (numberOfTries >= 3) {

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

	//get budget duration from admin
	cout << "Please insert the budget duration for this new budget type" << endl;
	getline(cin, adminInputNewBudgetDuration);
	cout << endl;

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

			//create temp BudgetTypeList and update to database
			BudgetTypeList temp;
			temp.setBudgetLabel(adminInputNewBudgetLabel);
			temp.setBudgetDuration(adminInputNewBudgetDuration);

			temp.save();

			cout << "The new budget type ID is " << temp.getBudgetTypeID();
			cout << endl;

			return;
		}

		//if result returned 0 row
		else {

			//display error messenge
			cout << "Please enter the correct password.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of login fails
			numberOfWrongPassword++;

		}

		//If more than 3 error then go back to budget type management main screen
		if (numberOfWrongPassword >= 3) {

			//display error message and go back to budget type management main screen
			cout << "You have entered wrong password for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to budget type management main screen
			return;
		}

	}

}

//function delete budget type
void deleteBudgetType(Session currentSession) {

	//variable for delete budget type
	string adminInputBudgetTypeID;
	string adminInputAdminPassword;

	int numberOfWrongInput = 0;

	while (true) {

		//number of times failed in entering budget ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get budget type ID from admin
			cout << "Please enter budget type ID that you want to delete";
			cout << endl;
			cout << "Note: GXXX (e.g: G001)";
			cout << endl;
			getline(cin, adminInputBudgetTypeID);
			cout << endl;

			//get length of user input
			int a = adminInputBudgetTypeID.length();

			//set initial value for boolean flag
			bool hasG = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only G
						if (adminInputBudgetTypeID.at(0) == 'G') {

							//set hasG to true
							hasG = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputBudgetTypeID.at(i) >= 48 && adminInputBudgetTypeID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasG and hasDigit to false
							hasG = false;
							hasDigit = false;


							//break out of the for loop and go to check hasG and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasG)) {

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
				cout << "The budget type ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfIDFailed++;

			}

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

		string select_query = "SELECT * FROM `budget type` WHERE Budget_Type_ID = '" + adminInputBudgetTypeID + "'";

		//Execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//Extract data into result
		res = mysql_store_result(conn);

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

					//delete the budget type from database
					string delete_query = "DELETE FROM `budget type` "
						" WHERE Budget_Type_ID = '" + adminInputBudgetTypeID + "' ";

					//execute update query
					mysql_query(conn, delete_query.c_str());

					cout << "The budget type with budget type ID " << adminInputBudgetTypeID << " is deleted";
					cout << endl;
					system("pause");
					cout << endl;

					return;

				}

				//if result returned 0 row
				else {

					//display error messenge
					cout << "Please enter the correct password.";
					cout << endl;
					system("pause");
					cout << endl;

					//count number of login fails
					numberOfWrongPassword++;

				}

				//If more than 3 error then go back to budget type management main screen
				if (numberOfWrongPassword >= 3) {

					//display error message and go back to budget type management main screen
					cout << "You have entered wrong password for more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					//return to budget type management main screen
					break;
				}

			}

		}

		//if result returned 0 row
		else {

			cout << "The budget type does not exist in database.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		if (numberOfWrongInput >= 3) {

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

}

//function edit budget label
void editBudgetLabel(Session currentSession, BudgetTypeList tempBudgetTypeList) {

	//variable of editBudgetLabel
	string adminInputNewBudgetLabel;
	string adminInputAdminPassword;

	//clear screen
	system("CLS");

	//display current budget label
	cout << "The current budget label is " << tempBudgetTypeList.getBudgetLabel();
	cout << endl;

	//check if want to continue
	if (!checkContinue()) {
		return;
	}

	//count the number of tries
	int numberOfTries = 0;

	//loop to get new budget label
	while (true) {

		int numberOfWrongInput = 0;

		//loop for budget label input
		while (true) {

			//get new budget label from admin
			cout << "Please enter new budget label that you want to created" << endl;
			getline(cin, adminInputNewBudgetLabel);
			cout << endl;

			//if user did not enter value
			if (adminInputNewBudgetLabel.empty()) {

				//display error message and add to numberOfWrongInput counter
				cout << "User has not entered budget label";
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

				//display error message and go back to meal type management main screen
				cout << "You have entered the wrong input for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				//return to meal type management main screen
				return;

			}

		}

		string select_query = "SELECT * FROM `budget type`" 
							  "WHERE Budget_Label = "
			" '" + adminInputNewBudgetLabel + "' ";

		//execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//extract data into result
		res = mysql_store_result(conn);

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

			//display error message
			cout << "There is existing budget label with this name.";
			cout << endl;
			cout << "Please try another name";
			cout << endl;

			system("pause");

			numberOfTries++;

		}

		//if result returned 0 row
		else {

			break;

		}

		if (numberOfTries >= 3) {

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

			//set new budget label and save to database
			tempBudgetTypeList.setBudgetLabel(adminInputNewBudgetLabel);

			tempBudgetTypeList.save();

			//display success message
			cout << "Budget label has been updated to database";
			cout << endl;
			system("pause");
			cout << endl;

			//return to edit screen
			return;

		}

		//if result returned 0 row
		else {

			//display error messenge
			cout << "Please enter the correct password.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of login fails
			numberOfWrongPassword++;

		}

		//If more than 3 error then go back to budget type management main screen
		if (numberOfWrongPassword >= 3) {

			//display error message and go back to budget type management main screen
			cout << "You have entered wrong password for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to budget type management main screen
			break;
		}

	}


}

//function edit budget duration
void editBudgetDuration(Session currentSession, BudgetTypeList tempBudgetTypeList) {

	//variable of editBudgetDuration
	string adminInputNewBudgetDuration;
	string adminInputAdminPassword;

	//clear screen
	system("CLS");

	//display current budget duration
	cout << "The current budget duration is " << tempBudgetTypeList.getBudgetDuration();
	cout << endl;

	//check if want to continue
	if (!checkContinue()) {
		return;
	}

	//get new budget duration from admin
	cout << "Please enter new budget duration" << endl;
	getline(cin, adminInputNewBudgetDuration);
	cout << endl;

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

			//set new budget duration and save to database
			tempBudgetTypeList.setBudgetDuration(adminInputNewBudgetDuration);

			tempBudgetTypeList.save();

			//display success message
			cout << "Budget duration has been updated to database";
			cout << endl;
			system("pause");
			cout << endl;

			//return to edit screen
			return;

		}

		//if result returned 0 row
		else {

			//display error messenge
			cout << "Please enter the correct password.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of login fails
			numberOfWrongPassword++;

		}

		//If more than 3 error then go back to budget type management main screen
		if (numberOfWrongPassword >= 3) {

			//display error message and go back to budget type management main screen
			cout << "You have entered wrong password for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to budget management main screen
			break;
		}

	}

}

#endif