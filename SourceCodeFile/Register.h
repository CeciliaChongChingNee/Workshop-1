/*
*This program demonstrates a simple C++ program.
*The function in this program is register.
*/

#include <iostream>
#include <string>
#include <mysql.h>
#include "List.h"
#include "DatabaseConnection.h"
using namespace std;

#ifndef REGISTER_H
#define REGISTER_H

int registerUser() {

	//variable of function register
	int userID;
	string userInputType;
	string userName;
	string userType;
	string userIdentityCard;
	string userPassword;
	string userGender;
	string userPhoneNumber;

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;

	//initialize connection
	MYSQL* conn = connection();

	//track number of wrong input
	int numberOfWrongInput;

	//initialize to 0
	numberOfWrongInput = 0;
	cin.ignore(1, '\n');

	//loop for userName input
	while (true) {

		//get userName from user input
		cout << "Please insert your name" << endl;
		getline(cin, userName);
		cout << endl;

		//if userName is not empty
		if (userName.length() != 0) {

			//exit loop and go to next loop
			break;

		}

		//if username has no value
		else {

			//display error message
			cout << "Please enter your name";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of wrong input and repeat again
			numberOfWrongInput++;

			//clear screen
			system("CLS");

		}

		//if number of wrong input is more than 3 times then go back to main screen
		if (numberOfWrongInput >= 3) {

			//display error message and go back to main screen
			cout << "You have entered the wrong input for username more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return 0;

		}

	}

	//initialize to 0
	numberOfWrongInput = 0;

	//loop for userType input
	while (true) {

		//get userType from user input
		cout << "1. Customer " << endl;
		cout << "2. Vendor " << endl;
		cout << "Please enter your type" << endl;
		cout << "*Note: Please enter 1 if you are customer or 2 if you are vendor.";
		cout << endl;
		getline(cin, userInputType);
		cout << endl;

		//get length of user input type
		int a = userInputType.length();

		//set initial value for boolean flag
		bool hasDigit = false;

		//if the length of userInput <= 1
		if (a <= 1) {

			//loop to check format of user input type
			for (int i = 0; i < a; i++) {

				//check if input is only digit
				if (userInputType.at(i) >= 48 && userInputType.at(i) <= 57) {

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

				//count number of wrong input and repeat again
				numberOfWrongInput++;

				//clear screen
				system("CLS");

			}

			//if user type format is correct
			else {

				//if userInputType is 1, then it will update userType is customer
				if (userInputType == "1") {

					//set user type to customer
					userType = "Customer";

					//exit loop and go to next loop
					break;

				}

				//if userInputType is 2, then it will update userType is vendor
				else if (userInputType == "2") {

					//set user type to vendor
					userType = "Vendor";

					//exit loop and go to next loop
					break;

				}

				//if userInput Type is others, then it will return to main screen
				else {

					//display error messenge
					cout << "Sorry. Please select either 1 or 2. ";
					cout << "Please try again.";
					cout << endl;
					system("pause");

					//count number of wrong input and repeat again
					numberOfWrongInput++;

					//clear screen
					system("CLS");

				}

			}

		}

		//if the length of userInput is not <= 1
		else {

			//display error message
			cout << "The input entered is too long." << endl;
			system("pause");
			cout << endl;

			//count number of wrong input and repeat again
			numberOfWrongInput++;

			//clear screen
			system("CLS");

		}

		//if number of wrong input is more than 3 times then go back to main screen
		if (numberOfWrongInput >= 3) {

			//display error message and go back to main screen
			cout << "You have entered the wrong input for user type more than 3 times";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return 0;

		}

	}

	//initialize to 0
	numberOfWrongInput = 0;

	//loop for userIdentityCard input
	while (true) {

		//get userIdentityCard from user input
		cout << "Please insert your Identity Card Number (IC)";
		cout << endl;
		cout << "Note: XXXXXX-XX-XXXX" << endl;
		getline(cin, userIdentityCard);
		cout << endl;

		//get length of user identityCard
		int m = userIdentityCard.length();

		//if the length of the input of userIdentityCard is equal to 14
		if (m == 14) {

			//set initial value for boolean flag
			bool hasDigit = false;
			bool hasDash = false;

			//loop to check format of identity card is correct or not
			for (int i = 0; i < m; i++) {

				//check digit
				if (userIdentityCard.at(i) >= 48
					&& userIdentityCard.at(i) <= 57) {

					//set hasDigit to true
					hasDigit = true;

				}

				//check dash line
				else if (userIdentityCard.at(6) == '-'
						 && userIdentityCard.at(9) == '-') {

						//set hasDash to true
						hasDash = true;

				}

				//check others
				else {

					//set condition to always fail since format is wrong
					hasDigit = false;
					hasDash = false;

					//break and go to check condition of hasDigit and hasDash
					break;
				}
			}

			//if input_char attain this two condition
			if (hasDigit && hasDash) {

				//identity card format is correct and go to next loop
				break;
			}

			//if input_char does not attain condition above
			else {

				//display error message
				cout << "Sorry, please follow the format given.";
				cout << "Please try again.";
				cout << endl;
				system("pause");
				cout << endl;

				//count number of wrong input and repeat again
				numberOfWrongInput++;

				//clear screen
				system("CLS");

			}

		}

		//if the length of the input of userIdentityCard is not equal to 14
		else {

			//display error message
			cout << "The length of Identity Card number must be 14.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of wrong input and repeat again
			numberOfWrongInput++;

			//clear screen
			system("CLS");

		}

		//if number of wrong input is more than 3 times then go back to main screen
		if (numberOfWrongInput >= 3) {

			//display error message
			cout << "You have entered the wrong input for user identity card more than 3 times";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return 0;

		}

	}

	//initialize to 0
	numberOfWrongInput = 0;

	//loop for userPassword input
	while (true) {

		//get userPassword from user input
		cout << "Please enter your User_Password" << endl;
		cout << "Note: It must be alphabet and digit.";
		cout << endl;
		getline(cin, userPassword);
		cout << endl;

		//get length of userPassword
		int n = userPassword.length();

		//if the length of userPassword is {5 <= n <= 9}
		if (n >= 5 && n <= 9) {

			//set initial value for boolean flag
			bool hasAlphabet = false;
			bool hasDigit = false;

			//loop to check password format correct or not
			for (int i = 0; i < n; i++) {

				//check for alphabet
				if ((userPassword.at(i) >= 65 && userPassword.at(i) <= 90)
					|| (userPassword.at(i) >= 97 && userPassword.at(i) <= 122)) {

					//set hasAlphabet to true
					hasAlphabet = true;

				}

				//check for digit
				else if (userPassword.at(i) >= 48 && userPassword.at(i) <= 57) {

					//set hasDigit to true
					hasDigit = true;

				}

				//check for others
				else {

					//set condition to always false since format is wrong
					hasAlphabet = false;
					hasDigit = false;

					//break and go to check condition of hasAlphabet and hasDigit
					break;

				}

			}

			//if input_char correct format
			if (hasAlphabet && hasDigit) {

				//password format is correct and go to next loop
				break;

			}

			//if input_char has wrong format
			else {
				
				//display error message
				cout << "Sorry, please follow the format.";
				cout << "Please try again.";
				cout << endl;
				system("pause");
				cout << endl;

				//count number of wrong input and repeat again
				numberOfWrongInput++;

				//clear screen
				system("CLS");

			}

		}

		//if the length of userPassword is not {5 <= n <= 9}
		else {

			//display error message
			cout << "The length of password is not sufficient.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of wrong input and repeat again
			numberOfWrongInput++;

			//clear screen
			system("CLS");
			
		}

		//if number of wrong input is more than 3 times then go back to main screen
		if (numberOfWrongInput >= 3) {

			//display error message
			cout << "You have entered the wrong input for username more than 3 times";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return 0;

		}

	}

	//initialize to 0
	numberOfWrongInput = 0;

	//loop for userGender input
	while (true) {

		//get userGender from user input
		cout << "Please enter your gender" << endl;
		cout << "Note: Please enter L/l for Male or P/p for female" << endl;
		cin >> userGender;
		cout << endl;

		//if the input is uppercase or lowercase of L
		if (userGender == "l" || userGender == "L") {

			//set gender to L
			userGender = "L";

			//correct value and exit loop to go next loop
			break;

		}

		//if the input is uppercase or lowercase of P
		else if (userGender == "p" || userGender == "P") {

			//set gender to P
			userGender = "P";

			//correct value and exit loop to go next loop
			break;

		}

		//if the input is not the correct values
		else {

			//display error message
			cout << "Sorry, please insert either L or P.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of wrong input and repeat again
			numberOfWrongInput++;

			//clear screen
			system("CLS");

		}

		//if number of wrong input is more than 3 times then get back to main page
		if (numberOfWrongInput >= 3) {

			//display error message
			cout << "You have entered the wrong input for username more than 3 times";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return 0;

		}

	}

	//initialize to 0
	numberOfWrongInput = 0;
	cin.ignore(1, '\n');

	//loop for userPhoneNumber input
	while (true) {

		//get userPhoneNumber from user input
		cout << "Please insert your phone number" << endl;
		cout << "Note: XXX-XXXXXXXX" << endl;
		getline(cin, userPhoneNumber);
		cout << endl;

		//get length of userPhoneNumber
		int p = userPhoneNumber.length();

		//if the length of userPhoneNumber is {11 <= p <= 12}
		if (p >= 11 && p <= 12) {

			//set initial value of boolean flag
			bool hasDigit = false;
			bool hasDash = false;

			//loop to check format of userPhoneNumber
			for (int i = 0; i < p; i++) {

				//check digit
				if (userPhoneNumber.at(i) >= 48 && userPhoneNumber.at(i) <= 57) {

					//set hasDigit to true
					hasDigit = true;

				}

				//check dash line
				else if (userPhoneNumber.at(3) == '-') {

					//set hasDash to true
					hasDash = true;

				}

				//check others
				else {

					//set condition to always fail since format is wrong
					hasDash = false;
					hasDigit = false;

					//break and go to check condition of hasDigit and hasDash
					break;

				}
			}

			//if input_char correct format
			if (hasDigit && hasDash) {

				//phone number format is correct go to next loop
				break;

			}

			//if input_char does not attain two condition above
			else {

				//display error message
				cout << "Sorry, please follow the format given.";
				cout << "Please try again.";
				cout << endl;
				system("pause");
				cout << endl;

				//count number of wrong input and repeat again
				numberOfWrongInput++;

				//clear screen
				system("CLS");

			}

		}

		//if the length of userPhoneNumber is not {11 <= p <= 12}
		else {

			//display error message
			cout << "The length of phone number is not sufficient.";
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of wrong input and repeat again
			numberOfWrongInput++;

			//clear screen
			system("CLS");

		}

		//If number of wrong input is more than 3 times then get back to main page
		if (numberOfWrongInput >= 3) {

			//display error message
			cout << "You have entered the wrong input for phone number more than 3 times";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return 0;

		}

	}


	//Create object for UserList
	UserList tempUser;
	tempUser.setUserName(userName);
	tempUser.setUserType(userType);
	tempUser.setUserIdentityCard(userIdentityCard);
	tempUser.setUserPassword(userPassword);
	tempUser.setUserGender(userGender);
	tempUser.setUserPhoneNumber(userPhoneNumber);

	//Verify user exist in database 
	string selectQuery = " SELECT * FROM user "
						 " WHERE User_IdentityCard = "
						 " '" + tempUser.getUserIdentityCard() + "' ";

	//Execute query (send the data from database)
	mysql_query(conn, selectQuery.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	int num_row;

	//If the result is more than 0 row
	if (res) {

		num_row = mysql_num_rows(res);

	}

	//If the result is equal to 0 row
	else {

		num_row = 0;

	}

	//if result returned more than 0 row
	if (num_row > 0) {

		cout << "User already exist.";
		cout << endl;
		system("pause");
		cout << endl;
	
	}

	//if result returned returned 0 row
	else {

		//Insert userDetail to database
		string insertQuery = " INSERT INTO user "
			" (User_Name, User_Type, User_IdentityCard, "
			" User_Password, User_Gender, User_PhoneNumber) "
			" VALUES('" + tempUser.getUserName() + "', "
			" '" + tempUser.getUserType() + "', "
			" '" + tempUser.getUserIdentityCard() + "', "
			" '" + tempUser.getUserPassword() + "', "
			" '" + tempUser.getUserGender() + "', "
			" '" + tempUser.getUserPhoneNumber() + "') ";

		//Execute query (send to databse)
		mysql_query(conn, insertQuery.c_str());

		//Get userID from database
		string selectQuery = " SELECT  User_ID FROM user "
			" WHERE User_IdentityCard =  "
			" '" + tempUser.getUserIdentityCard() + "' ";

		//Execute query (get the data from database)
		mysql_query(conn, selectQuery.c_str());

		//Extract data into result
		res = mysql_store_result(conn);

		//Convert result into integer
		while ((row = mysql_fetch_row(res))) {

			userID = atoi(row[0]);

		}

		//get userID and return to main screen
		return userID;
	
	}

	//return to main screen
	return 0;
}

#endif