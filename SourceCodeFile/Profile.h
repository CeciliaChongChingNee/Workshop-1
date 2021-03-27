/*
*This program demonstrates a simple C++ program.
*The function in this program is profile.
*/

#include <iostream>
#include <string>
#include <mysql.h>
#include "List.h"
#include "Login.h"
#include "DatabaseConnection.h"
using namespace std;

#ifndef PROFILE_H
#define PROFILE_H

//variable to store rows of result set
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL* conn;

//function prototype
void viewProfile(Session currentSession);
void editProfile(Session currentSession);
void changePassword(Session currentSession);
void changePhoneNumber(Session currentSession);

//function for profile to show profile main screen
void profile(Session currentSession) {

	//variable of profile
	string userInput;

	//initialize connection
	conn = connection();

	//Initialize number of wrong input		
	int numberOfWrongInput = 0;
	cin.ignore(1, '\n');

	//loop for profile menu
	while (true) {

		//clear screen
		system("CLS");

		//Start for display the screen for profile module
		cout << "1. View profile" << endl;
		cout << "2. Edit profile" << endl;
		cout << "3. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, userInput);
		cout << endl;
		//End for display the screen for profile module

		//get length of user input type
		int a = userInput.length();

		//set initial value for boolean flag
		bool hasDigit = false;

		//if the length of userInput <= 1
		if (a <= 1) {

			//loop to check format of user input type
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

				//count number of wrong input and repeat again
				numberOfWrongInput++;

			}

			//if user type format is correct
			else {

				//check userInput is equal to 1
				if (userInput == "1") {

					//call view profile function
					viewProfile(currentSession);

					//if user do not want to continue
					if (!checkContinue()) {

						// go back to main screen
						return;

					}

				}

				//check userInput is equal to 2
				else if (userInput == "2") {


					//call edit profile function
					editProfile(currentSession);

					//if user do not want to continue
					if (!checkContinue()) {

						// go back to main screen
						return;

					}

				}

				//check userInput is equal to  3
				else if (userInput == "3") {

					//go back to main screen
					return;
				}

				//check others
				else {

					//display error messenge
					cout << "Sorry, please enter the correct choice.";
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

		}

		//if the length of userInput is not <= 1
		else {

			//display error message
			cout << "The input entered is too long.";
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
			cout << "You have entered the wrong input for choice more than 3 times";
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

//function of viewProfile
void viewProfile(Session currentSession) {

	//clear screen
	system("CLS");

	//retrieve user details
	string selectQuery = "SELECT * FROM user "
						 " WHERE User_ID =  "
						 " " + to_string(currentSession.userID) + " ";

	//Execute query (get the data from database)
	mysql_query(conn, selectQuery.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	//declare temp user object
	UserList temp;

	//set value to user from database
	while ((row = mysql_fetch_row(res))) {

		//initialize temp user to store value
		temp.setUserID(atoi(row[0]));
		temp.setUserName(row[1]);
		temp.setUserType(row[2]);
		temp.setUserIdentityCard(row[3]);
		temp.setUserPassword(row[4]);
		temp.setUserGender(row[5]);
		temp.setUserPhoneNumber(row[6]);
		temp.setUserBalance(atoi(row[7]));

	}

	//Start to display the user details
	cout << "ID\t\t: ";
	cout << temp.getUserID() << endl;
	cout << "Name\t\t: ";
	cout<< temp.getUserName() <<endl;
	cout << "Type\t\t: ";
	cout << temp.getUserType() << endl;
	cout << "Identity Card\t: ";
	cout << temp.getUserIdentityCard() << endl;
	cout << "Gender\t\t: ";
	cout << temp.getUserGender() << endl;
	cout << "Phone Number\t: ";
	cout << temp.getUserPhoneNumber() << endl;
	cout << "Balance\t\t: ";
	cout << temp.getUserBalance() << endl;
	cout << endl;
	//End for display user details

	//go back to profile screen
	return;

}

//function of editProfile
void editProfile(Session currentSession) {

	//initialize number of wrong input
	int numOfWrongInput = 0;

	//while user have not choose to exit
	while (true) {

		//clear screen
		system("CLS");
		
		//Variable for edit profile
		string userProfileInput;

		//get user profile input from user input
		cout << "1. Change password" << endl;
		cout << "2. Change phone number" << endl;
		cout << "3. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, userProfileInput);
		cout << endl;

		//get length of user profile input
		int a = userProfileInput.length();

		//set initial value for boolean flag
		bool hasDigit = false;

		//if the length of userProfileInput <= 1
		if (a <= 1) {

			//loop to check the char is available or not
			for (int i = 0; i < a; i++) {

				//check if input is only digit
				if (userProfileInput.at(i) >= 48 && userProfileInput.at(i) <= 57) {

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

				//userProfileInput format is wrong
				cout << "Sorry, please follow the format given.";
				cout << "Please try again.";
				cout << endl;
				system("pause");
				cout << endl;

				//count number of wrong input amd repeat again
				numOfWrongInput++;

			}

			//if input format is correct
			else {

				//check userProfileInput is equal to 1
				if (userProfileInput == "1") {

					//go to change password function
					changePassword(currentSession);
				}

				//check userProfileInput is equal to 2
				else if (userProfileInput == "2") {

					//go to change phone number function
					changePhoneNumber(currentSession);
				}

				//check userProfileInput is equal to 3
				else if (userProfileInput == "3") {

					//go back to profile main screen
					return;
				}

				//check others
				else {

					//display error messenge
					cout << "Sorry, please enter the correct choice.";
					cout << "Please try again.";
					cout << endl;
					system("pause");
					cout << endl;

					//count number of wrong input
					numOfWrongInput++;
				}


			}

		}

		//if the length of userInput is not <= 1
		else {

			//display error message
			cout << "The ID entered is too long.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of wrong input and repeat again
			numOfWrongInput++;

		}

		if (numOfWrongInput >= 3) {

			//display error messenge and exit to profile screen
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

//function of change password
void changePassword(Session currentSession) {

	//clear screen
	system("CLS");

	//initialize number of wrong input
	int numberOfWrongInputOldPassword = 0;

	//Start for display change password screen
	while (true) {

		//variable for change password function
		string userOldPassword;

		//get old password
		cout << "Please enter your old password";
		cout << endl;
		getline(cin,userOldPassword);
		cout << endl;
	
		//verify user exist in database 
		string selectQuery = "SELECT User_Type FROM user "
							 " WHERE User_ID = " + to_string(currentSession.userID) + " "
							 " AND User_Password = '" + userOldPassword + "' ";

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

			//loop for user new password input
			//variable for change password function
			string userNewPassword1;
			string userNewPassword2;

			//initialize number of wrong input for new password1
			int numOfWrongInputPassword1Format = 0;

			//loop for new password 1 format
			while (true) {

				//get new password
				cout << "Please enter your new password";
				cout << endl;
				getline(cin, userNewPassword1);
				cout << endl;

				//check the new password available or not
				int n = userNewPassword1.length();

				//If the length of userPassword is between this series of number
				if (n >= 5 && n <= 9) {

					bool hasAlphabet = false;
					bool hasDigit = false;

					//Loop to check the new password 1 format
					for (int i = 0; i < n; i++) {

						//Check for alphabet
						if ((userNewPassword1.at(i) >= 65 && userNewPassword1.at(i) <= 90)
							|| (userNewPassword1.at(i) >= 97 && userNewPassword1.at(i) <= 122)) {

							//set hasAlphabet to true
							hasAlphabet = true;

						}

						//Check for digit
						else if (userNewPassword1.at(i) >= 48 && userNewPassword1.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//Check for others
						else {

							//set condition to always because format is wrong
							hasAlphabet = false;
							hasDigit = false;

							//break to check condition for hasAlphabet and hasDigit
							break;

						}
					}

					//If input_char is correct format
					if (hasAlphabet && hasDigit) {

						//break and go to check for second new password
						break;

					}

					//If input_char has wrong format
					else {

						//display error message
						cout << "Sorry, please follow the format.";
						cout << "Please try again.";
						cout << endl;
						system("pause");

						//count number of wrong input and repeat again
						numOfWrongInputPassword1Format++;

						//clear screen
						system("CLS");

					}

				}

				//If the length of userPassword is not between series of number above
				else {

					//display error message
					cout << "The length of password is not sufficient.";
					cout << "Please try again.";
					cout << endl;
					system("pause");

					//count number of wrong input and repeat again
					numOfWrongInputPassword1Format++;

					//clear screen
					system("CLS");

				}

				//if number of wrong input is more than 3 times then go back to main screen
				if (numOfWrongInputPassword1Format >= 3) {

					//display error message and go back to profile main screen
					cout << "You have entered the wrong input for password more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					//return to profile main screen
					return;

				}

			}

			//initialize numOfWrongInputPassword2Format
			int numOfWrongInputPassword2Format = 0;

			//loop for second new Password
			while (true) {
				
				//get new password again
				cout << "Please enter again your new password";
				cout << endl;
				cin >> userNewPassword2;
				cout << endl;

				//check same as the previous new password or not 
				if (userNewPassword1 == userNewPassword2) {

					//set query for update 
					string updateQuery = "UPDATE user SET User_Password = " 
										 " '" + userNewPassword2 + "' "
										 " WHERE User_ID = "
										 " " + to_string(currentSession.userID) + " ";

					//execute update query
					mysql_query(conn, updateQuery.c_str());

					//display update success message and return to profile main screen
					cout << "Password is updated successfully!";
					cout << endl;
					system("pause");
					cout << endl;

					//return to profile main screen
					return;

				}

				//check do not same as previous new password
				else {

					//repeat again 
					cout << "Sorry, this password is not same as previous one. ";
					cout << " Please try again." << endl;
					system("pause");

					//count number of wrong input and repeat again
					numOfWrongInputPassword2Format++;

					//clear screen
					system("CLS");

				}

				//if number of wrong input is more than 3 times then go back to main screen
				if (numOfWrongInputPassword2Format >= 3) {

					//display error message and go back to profile main screen
					cout << "You have entered the wrong input for username more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					//return to profile main screen
					return;

				}

			}

		}

		//if result returned 0 row
		else {

			//display error messenge
			cout << "Wrong Password.";
			cout << "Please enter the correct password.";
			cout << endl;
			system("pause");
			cout << endl;

			//count number of login fails and repeat again
			numberOfWrongInputOldPassword++;

			//clear screen
			system("CLS");

		}

		//if number of wrong input is more than 3 times then go back to main screen
		if (numberOfWrongInputOldPassword >= 3) {

			//display error message and go back to profile main screen
			cout << "You have entered the wrong input for password more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to profile main screen
			return;

		}

	}

}

//function of change phone number
void changePhoneNumber(Session currentSession) {

	//clear screen
	system("CLS");

	//variable for changePhoneNumber function
	string userPhoneNumber;

	//initialize number of wrong input
	int numberOfWrongInput = 0;

	//loop for userPhoneNumber input
	while (true) {

		//get userPhoneNumber from user input
		cout << "Please insert your new phone number" << endl;
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
			return;

		}

	}

	//set query for update 
	string updateQuery = "UPDATE user SET User_PhoneNumber = "
		" '" + userPhoneNumber + "' "
		" WHERE User_ID = "
		" " + to_string(currentSession.userID) + " ";

	//execute update query
	mysql_query(conn, updateQuery.c_str());

	//display update success message and return to profile main screen
	cout << "Phone number is updated successfully!";
	cout << endl;
	system("pause");
	cout << endl;

	//return to profile main screen
	return;

}

//function for check continue
bool checkContinue() {

	//variable for checkContinue function
	string userProfileChoice;

	//initialize number of wrong input
	int numberOfWrongInput = 0;

	//check next action
	while (true) {

		//get user profile choice from user
		cout << endl;
		cout << "Do you want to continue? (Y/N)";
		cout << endl;
		getline(cin, userProfileChoice);
		cout << endl;

		//get length of userProfileChoice
		int a = userProfileChoice.length();

		//if user profile choice length is longer than 1
		if (a <= 1) {

			//if user choose to continue
			if (userProfileChoice == "Y" || userProfileChoice == "y") {

				//return true
				return true;

			}

			//if user choose to not continue
			else if (userProfileChoice == "N" || userProfileChoice == "n") {

				//go back main screen
				return false;

			}

			//user enter wrong input
			else {

				//user profile choice format is wrong
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

		//if length of user profile choice is more than 1
		else {

			//display error message
			cout << "The input entered is too long.";
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
			cout << "You have entered the wrong input for choice more than 3 times";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to main screen
			return false;

		}

	}
}


#endif