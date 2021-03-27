/*
*This program demonstrates a simple C++ program.
*The function in this program is login.
*/

#include<iostream>
#include<string>
#include <mysql.h>
#include "DatabaseConnection.h"
using namespace std;
#ifndef LOGIN_H
#define LOGIN_H

//create structure for session
struct Session {

	//variable of struct
	int userID;
	string userType;
};

bool login(Session& currentSession) {

	//clear screen
	system("CLS");

	//variables of function login
	int userID;
	string userInput;
	string userPassword;

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;

	//initialize connection
	MYSQL* conn = connection();


	//number of times failed in entering correct userID and password
	int numberOfLoginFailed = 0;
	cin.ignore(1, '\n');

	//loop for ID and password searching
	while (true) {
		
		//number of times failed in entering user ID		
		int numberOfIDFailed = 0;
		
		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get userID from user input
			cout << "Please insert your User_ID" << endl;
			getline(cin, userInput);
			cout << endl;

			//get length of user input
			int a = userInput.length();

			//set initial value for boolean flag
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//check if input is only digit
					if (userInput.at(i) >= 48 && userInput.at(i) <= 57) {

						//set hasDigit to true
						hasDigit = true;

					}

					//if input not only have digit
					else {

						//set hasDigit to false
						hasDigit = false;

					}

				}

				//if input_char not having correct format
				if (hasDigit == false) {

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
				cout << "The ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfIDFailed++;

			}

			if (numberOfIDFailed >= 3) {
				
				//display error messenge and exit to main screen
				cout << "You have entered wrong input for ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return false;

			}

		}

		//convert userInput to integer for userID
		userID = stoi(userInput);

		//get user password from User
		cout << "Please enter your User_Password" << endl;
		getline(cin, userPassword);
		cout << endl;

		//verify user exist in database 
		string selectQuery = "SELECT User_Type FROM user "
							 " WHERE User_ID = " + to_string(userID) + " "
							 " AND User_Password = '" + userPassword + "' ";

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
		if (num_row>0) {

			//store userType into current session
			while ((row = mysql_fetch_row(res))) {

				currentSession.userType = row[0];

			}

			currentSession.userID = userID;

			//logged in and return to main screen
			return true;

		}

		//if result returned 0 row
		else {

			//display error messenge
			cout << "Login failed.";
			cout << "Please enter the correct ID and password.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of login fails
			numberOfLoginFailed++;

		}

		//If more than 3 error then go back to main screen
		if (numberOfLoginFailed >= 3) {

			//display error message and go back to main screen
			cout << "You have entered wrong ID or password for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return false;

		}

	}

}

#endif