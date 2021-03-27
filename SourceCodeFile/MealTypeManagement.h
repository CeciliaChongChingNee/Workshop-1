/*
*This program demonstrates a simple C++ program.
*The function in this program is mealTypeManagement.
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

#ifndef MEALTYPEMANAGEMENT_H
#define MEALTYPEMANAGEMENT_H

//function prototype
void mealTypeManagement(Session currentSession);
void viewMealType(Session currentSession);
void editMealTypeMenu(Session currentSession);
void addMealType(Session currentSession);
void deleteMealType(Session currentSession);
void editTypeName(Session currentSession,MealTypeList tempMealTypeList);
void editTimeStart(Session currentSession, MealTypeList tempMealTypeList);
void editTimeEnd(Session currentSession, MealTypeList tempMealTypeList);

//function mealTypeManagement to show meal type management main screen
void mealTypeManagement(Session currentSession) {

	//variable of mealTypeManagement
	string adminInput;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');

	int numberOfWrongInput = 0;

	//loop for meal type management main screen
	while (true) {

		system("CLS");

		//Start for display screen for manage meal type module
		cout << "1. View meal type" << endl;
		cout << "2. Edit meal type" << endl;
		cout << "3. Add meal type" << endl;
		cout << "4. Delete meal type" << endl;
		cout << "5. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, adminInput);
		cout << endl;
		//End for display screen for manage meal type module

		//if adminInput is equal to 1
		if (adminInput == "1") {

			//call view meal type function
			viewMealType(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if adminInput is equal to 2
		else if (adminInput == "2") {

			//call edit meal type function
			editMealTypeMenu(currentSession);

		}

		//if adminInput is equal to 3
		else if (adminInput == "3") {

			//call add meal type function
			addMealType(currentSession);

			//check if want to continue
			if (!checkContinue()) {
				return;
			}

		}

		//if adminInput is equal to 4
		else if (adminInput == "4") {

			//call delete meal type function
			deleteMealType(currentSession);

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

//function view meal type
void viewMealType(Session currentSession) {

	//clear screen
	system("CLS");

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;

	//get meal type from database
	string selectQuery = "SELECT * FROM `meal type`";

	//Execute query (get the data from database)
	mysql_query(conn, selectQuery.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	//declare temp meal type object
	MealTypeList temp;

	//count number of meal type list added to list
	int counter = 0;

	//declare list
	MyList<MealTypeList> list;

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
	
		//set value to meal type from database
		while ((row = mysql_fetch_row(res))) {

			//initialize temp meal type to store value
			temp.setMealTypeID(row[0]);
			temp.setTypeName(row[1]);
			temp.setTimeStart(row[2]);
			temp.setTimeEnd(row[3]);


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

	//if result is 0 row
	else {
	
		cout << "No data found in database";
		cout << endl;
		cout << "Please try again later";
		cout << endl;
		system("pause");
		cout << endl;

		return;

	}

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

}

//function edit meal type
void editMealTypeMenu(Session currentSession) {

	//variable for edit meal type
	string adminInputMealTypeID;
	string adminInputEditType;
	string adminInputAdminPassword;

	//temp meal type object to store details
	MealTypeList tempMealType;

	//count number of tries
	int numberOfTries = 0;

	//loop for checking ID correct
	while (true) {
		
		//number of times failed in entering meal type ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get meal type ID from admin
			cout << "Please enter meal type ID that you want to edit";
			cout << endl;
			cout << "Note: TXXX (e.g: T001)";
			cout << endl;
			getline(cin, adminInputMealTypeID);
			cout << endl;

			//get length of user input
			int a = adminInputMealTypeID.length();

			//set initial value for boolean flag
			bool hasT = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only T
						if (adminInputMealTypeID.at(0) == 'T') {

							//set hasT to true
							hasT = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputMealTypeID.at(i) >= 48 && adminInputMealTypeID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasT and hasDigit to false
							hasT = false;
							hasDigit = false;


							//break out of the for loop and go to check hasT and hasDigit
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
				cout << "The meal type ID entered is too long." << endl;
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

		string select_query = "SELECT * FROM `meal type` WHERE Meal_Type_ID = '" + adminInputMealTypeID + "'";

		//Execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//Extract data into result
		res = mysql_store_result(conn);

		int num_row;

		//if meal type exist
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//if meal type doesn't exist
		else {

			num_row = 0;
		
		}

		//if result is more than 0 rows
		if (num_row > 0) {
		
			//set value to tempMealType object
			while (row = mysql_fetch_row(res)) {

				tempMealType.setMealTypeID(adminInputMealTypeID);
				tempMealType.setTypeName(row[1]);
				tempMealType.setTimeStart(row[2]);
				tempMealType.setTimeEnd(row[3]);

			}

			break;

		}

		//if results return 0 rows
		else {
			
			cout << "Meal type does not exist in database.";
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
		cout << "1. Edit type name" << endl;
		cout << "2. Edit time start" << endl;
		cout << "3. Edit time end" << endl;
		cout << "4. Go back" << endl;
		cout << "Please insert your choice" << endl;
		getline(cin, adminInputEditType);
		cout << endl;
		//End to display option 

		//if adminInputEditType is equal to 1
		if (adminInputEditType == "1") {

			//call edit type name function
			editTypeName(currentSession, tempMealType);

		}

		//if adminInputEditType is equal to 2
		else if (adminInputEditType == "2") {

			//call edit time start function
			editTimeStart(currentSession, tempMealType);

		}

		//if adminInputEditType is equal to 3
		else if (adminInputEditType == "3") {

			//call edit time start function
			editTimeEnd(currentSession, tempMealType);

		}

		//if adminInputEditType is equal to 3
		else if (adminInputEditType == "4") {

			//go back to mealTypeManagement main screen
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

//function add meal type
void addMealType(Session currentSession) {

	//variable of add meal type
	string adminInputNewTypeName;
	string adminInputNewTimeStart;
	string adminInputNewTimeEnd;
	string adminInputAdminPassword;

	//count the number of tries
	int numberOfTries = 0;

	//loop to get new meal type name
	while (true) {

		//clear screen
		system("CLS");

		int numberOfWrongInput = 0;

		//loop for meal type name
		while (true) {

			//get new type name from admin
			cout << "Please enter new type name that you want to created" << endl;
			getline(cin, adminInputNewTypeName);
			cout << endl;

			//if user did not enter value
			if (adminInputNewTypeName.empty()) {

				//display error message and add to numberOfWrongInput counter
				cout << "User has not entered type name";
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

		string select_query = "SELECT * FROM `meal type` WHERE Type_Name = "
							  " '" + adminInputNewTypeName + "' ";

		//execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//extract data into result
		res = mysql_store_result(conn);

		int num_row;

		//if result returned
		if (res) {
			
			num_row = mysql_num_rows(res);

		}

		//else if result not returned
		else {
			
			num_row = 0;

		}

		//result returned more than 0 row
		if (num_row > 0) {
			
			//display error message
			cout << "There is existing meal type with this name.";
			cout << endl;
			cout << "Please try another name";
			cout << endl;

			system("pause");

			numberOfTries++;

		}

		//if result returned 0 rows
		else {

			break;
		
		}

		//if number of tries is more than 3
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

	int numberOfWrongInput = 0;

	//loop for time start
	while (true) {

		//TODO : add error handling for time start
		//get time available from admin
		cout << "Please insert the time start for this meal type" << endl;
		getline(cin, adminInputNewTimeStart);
		cout << endl;

		//if user did not enter value
		if (adminInputNewTimeStart.empty()) {

			//display error message and add to numberOfWrongInput counter
			cout << "User has not entered time start";
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

	//loop for time end
	while (true) {

		//TODO : add error handling for time end
		//get time available from admin
		cout << "Please insert the time end for this meal type" << endl;
		getline(cin, adminInputNewTimeEnd);
		cout << endl;

		//if user did not enter value
		if (adminInputNewTimeEnd.empty()) {

			//display error message and add to numberOfWrongInput counter
			cout << "User has not entered time end";
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

		//if the result is not returned
		else {

			num_row = 0;

		}

		//if at least 1 row returned
		if (num_row > 0) {

			//create temp MealTypeList and update to database
			MealTypeList temp;
			temp.setTypeName(adminInputNewTypeName);
			temp.setTimeStart(adminInputNewTimeStart);
			temp.setTimeEnd(adminInputNewTimeEnd);

			temp.save();

			cout << "The new meal type ID is " << temp.getMealTypeID();
			cout << endl;

			return;

		}

		//if no rows returned
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

//function delete meal type
void deleteMealType(Session currentSession) {

	//variable for delete meal type
	string adminInputMealTypeID;
	string adminInputAdminPassword;

	//count the number of wrong ID;
	int numberOfWrongID = 0;

	while (true) {

		//number of times failed in entering menu ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get meal type ID from admin
			cout << "Please enter meal type ID that you want to delete";
			cout << endl;
			cout << "Note: TXXX (e.g: T001)";
			cout << endl;
			getline(cin, adminInputMealTypeID);
			cout << endl;

			//get length of user input
			int a = adminInputMealTypeID.length();

			//set initial value for boolean flag
			bool hasT = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only T
						if (adminInputMealTypeID.at(0) == 'T') {

							//set hasT to true
							hasT = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (adminInputMealTypeID.at(i) >= 48 && adminInputMealTypeID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasT and hasDigit to false
							hasT = false;
							hasDigit = false;


							//break out of the for loop and go to check hasT and hasDigit
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
				cout << "The meal type ID entered is too long." << endl;
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

		string select_query = "SELECT * FROM `meal type` WHERE Meal_Type_ID = '" + adminInputMealTypeID + "'";

		//Execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//Extract data into result
		res = mysql_store_result(conn);

		int num_row;

		//if result is returned 
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//if result is not returned
		else {

			num_row = 0;

		}

		//if result returned at least 1 row
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

				int num_row2;

				//if result is returned
				if (res) {

					num_row2 = mysql_num_rows(res);

				}

				//if result is not returned
				else {

					num_row2 = 0;

				}

				//if result is at least 1 row
				if (num_row2 > 0) {

					//delete the meal type from database
					string delete_query = "DELETE FROM `meal type` "
						" WHERE Meal_Type_ID = '" + adminInputMealTypeID + "' ";

					//execute update query
					mysql_query(conn, delete_query.c_str());

					cout << "The meal type with meal type ID " << adminInputMealTypeID << " is deleted";
					cout << endl;
					system("pause");
					cout << endl;

					return;
					
				}

				//if result is 0 row
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
					break;
				}

			}

		}

		//if result returned 0 rows
		else {

			cout << "The meal type does not exist in database.";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongID++;

		}

		//if number of wrong ID input is more than equal 3
		if (numberOfWrongID >= 3) {

			cout << "You have entered the wrong input for meal type ID for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}
	
	}

}

//function edit type name
void editTypeName(Session currentSession, MealTypeList tempMealTypeList) {

	//variable of editTypeName
	string adminInputNewTypeName;
	string adminInputAdminPassword;

	//clear screen
	system("CLS");

	//display current type name
	cout << "The current meal type name is " << tempMealTypeList.getTypeName();
	cout << endl;

	//check if want to continue
	if (!checkContinue()) {
		return;
	}

	//count the number of tries
	int numberOfTries = 0;

	//loop to get new meal type name
	while (true) {

		int numberOfWrongInput = 0;

		//loop for meal type name
		while (true) {

			//get new type name from admin
			cout << "Please enter new type name that you want to update" << endl;
			getline(cin, adminInputNewTypeName);
			cout << endl;

			//if user did not enter value
			if (adminInputNewTypeName.empty()) {

				//display error message and add to numberOfWrongInput counter
				cout << "User has not entered type name";
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

		string select_query = "SELECT * FROM `meal type` " 
							  "WHERE Type_Name = "
							  " '" + adminInputNewTypeName + "' ";

		//execute query (get the data from database)
		mysql_query(conn, select_query.c_str());

		//extract data into result
		res = mysql_store_result(conn);

		int num_row;

		//if exist in database
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//else if not exist in database
		else {

			num_row = 0;

		}

		//if result returned at least 1 row
		if (num_row > 0) {

			//display error message
			cout << "There is existing meal type with this name.";
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

		//if there is at least 1 row of result returned
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//if the result is equal to 0 row
		else {

			num_row = 0;

		}

		//if result returned more than 0 row
		if (num_row > 0) {

			//set new type name and save to database
			tempMealTypeList.setTypeName(adminInputNewTypeName);

			tempMealTypeList.save();

			//display success message
			cout << "Meal type name has been updated to database";
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
			break;

		}

	}


}

//function edit time start
void editTimeStart(Session currentSession, MealTypeList tempMealTypeList) {

	//variable of editTimeAvailable
	string adminInputNewTimeStart;
	string adminInputAdminPassword;

	//clear screen
	system("CLS");

	//display current time available
	cout << "The current time start is " << tempMealTypeList.getTimeStart();
	cout << endl;

	//check if want to continue
	if (!checkContinue()) {
		return;
	}

	int numberOfWrongInput = 0;

	//loop for time start
	while (true) {

		//TODO : add error handling for time start
		//get time available from admin
		cout << "Please insert the time start for this meal type" << endl;
		getline(cin, adminInputNewTimeStart);
		cout << endl;

		//if user did not enter value
		if (adminInputNewTimeStart.empty()) {

			//display error message and add to numberOfWrongInput counter
			cout << "User has not entered time start";
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

			//set new time available and save to database
			tempMealTypeList.setTimeStart(adminInputNewTimeStart);

			tempMealTypeList.save();

			//display success message
			cout << "Time start has been updated to database";
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
			break;
		}

	}


}

//function edit time end
void editTimeEnd(Session currentSession, MealTypeList tempMealTypeList) {

	//variable of editTimeAvailable
	string adminInputNewTimeEnd;
	string adminInputAdminPassword;

	//clear screen
	system("CLS");

	//display current time available
	cout << "The current time end is " << tempMealTypeList.getTimeEnd();
	cout << endl;

	//check if want to continue
	if (!checkContinue()) {
		return;
	}

	int numberOfWrongInput = 0;

	//loop for time end
	while (true) {

		//TODO : add error handling for time end
		//get time available from admin
		cout << "Please insert the time end for this meal type" << endl;
		getline(cin, adminInputNewTimeEnd);
		cout << endl;

		//if user did not enter value
		if (adminInputNewTimeEnd.empty()) {

			//display error message and add to numberOfWrongInput counter
			cout << "User has not entered time end";
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

			//set new time available and save to database
			tempMealTypeList.setTimeEnd(adminInputNewTimeEnd);

			tempMealTypeList.save();

			//display success message
			cout << "Time end has been updated to database";
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
			break;
		}

	}


}

#endif