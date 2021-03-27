/*
*This program demonstrates a simple C++ program.
*The function in this program is userManagement. 
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

#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

//function prototype
void viewAllUser(Session currentSession);
void resetUserPassword(Session currentSession);
string generateRandomPassword();
void updateBalance(Session currentSession);
void deleteUser(Session currentSession);

//function userManagement to show user management main screen
void userManagement(Session currentSession) {

	//variable of userManagement
	string adminInput;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');


	//loop for user management main screen
	while (true) {

		system("CLS");
	
		//Start for display screen for manage user module
		cout << "1. View all user" << endl;
		cout << "2. Reset password" << endl;
		cout << "3. Update balance" << endl;
		cout << "4. Delete user" << endl;
		cout << "5. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, adminInput);
		cout << endl;
		//End for display screen for manage user module

		//if adminInput is equal to 1
		if (adminInput == "1") {

			//call view all user function
			viewAllUser(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if adminInput is equal to 2
		else if (adminInput == "2") {

			//call reset password function
			resetUserPassword(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if adminInput is equal to 3
		else if (adminInput == "3") {

			//call update balance function
			updateBalance(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if adminInput is equal to 5
		else if (adminInput == "4") {

			//call delete user function
			deleteUser(currentSession);

		}

		//if adminInput is equal to 6
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

		}

	}
}

//function view all user
void viewAllUser(Session currentSession) {

	//clear screen
	system("CLS");

	//variable to store rows of result set
	MYSQL_ROW row;
	MYSQL_RES* res;

	//get all user from database
	string selectQuery = "SELECT * FROM user";

	//Execute query (get the data from database)
	mysql_query(conn, selectQuery.c_str());

	//Extract data into result
	res = mysql_store_result(conn);

	//Get number of row
	int num_row = mysql_num_rows(res);

	//declare temp user object
	UserList temp;

	//count number of user list added to list
	int counter = 0;

	//declare list
	MyList<UserList> list;

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

	cout << "User List" << endl;

	cout << "---------------------------------------------";
	cout << "---------------------------------------------";
	cout << "----------------------------";
	cout << endl;

	cout << "| " << left << setw(3) << "ID" << "| "
		<< left << setw(40) << "Name" << "| "
		<< setw(10) << "Type" << "| "
		<< setw(20) << "IdentityNo" << "| "
		<< setw(5) << "Sex" << "| "
		<< setw(15) << "Phone No" << "| "
		<< setw(10) << "Balance" << "|";
	cout << endl;

	cout << "---------------------------------------------";
	cout << "---------------------------------------------";
	cout << "----------------------------";
	cout << endl;

	//display list
	list.displayList();
	cout << endl;
	
}

//function reset password
void resetUserPassword(Session currentSession){

	//variable for reset user password
	string adminInputUserID;
	string adminInputAdminPassword;

	int numberOfWrongInput = 0;

	while (true) {

		//number of times failed in entering user ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get user ID from admin
			cout << "Please insert userID that you want to reset password";
			cout << endl;
			getline(cin, adminInputUserID);
			cout << endl;

			//get length of user input
			int a = adminInputUserID.length();

			//set initial value for boolean flag
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//check if input is only digit
					if (adminInputUserID.at(i) >= 48 && adminInputUserID.at(i) <= 57) {

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
				cout << "The ID entered is too long.";
				cout << endl;
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

				return;

			}

		}

		//verify user exist in database 
		string selectQuery = " SELECT * FROM user "
			" WHERE User_ID = "
			" " + adminInputUserID + " ";

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
				temp.setUserBalance(atoi(row[7]));

			}

			cout << "---------------------------------------------";
			cout << "---------------------------------------------";
			cout << "----------------------------";
			cout << endl;

			cout << "| " << left << setw(3) << "ID" << "| "
				<< left << setw(40) << "Name" << "| "
				<< setw(10) << "Type" << "| "
				<< setw(20) << "IdentityNo" << "| "
				<< setw(5) << "Sex" << "| "
				<< setw(15) << "Phone No" << "| "
				<< setw(10) << "Balance" << "|";
			cout << endl;

			cout << "---------------------------------------------";
			cout << "---------------------------------------------";
			cout << "----------------------------";
			cout << endl;

			//display results to admin
			temp.displayAsRow();

			//check the user details correct or not
			if (!checkContinue()) {
				return;
			}

			//generate random password
			string password = generateRandomPassword();

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

				//if the result is more than 0 row
				if (res) {

					num_row2 = mysql_num_rows(res);

				}

				//if the result is equal to 0 row
				else {

					num_row2 = 0;

				}

				//if result returned more than 0 row
				if (num_row2 > 0) {

					system("CLS");

					//display new resetted password
					cout << "The new password is: " << password;
					cout << endl;

					//set query for update 
					string updateQuery = "UPDATE user SET User_Password = "
						" '" + password + "' "
						" WHERE User_ID = "
						" " + adminInputUserID + " ";

					//execute update query
					mysql_query(conn, updateQuery.c_str());

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

				//If more than 3 error then go back to user management main screen
				if (numberOfWrongPassword >= 3) {

					//display error message and go back to user management main screen
					cout << "You have entered wrong password for more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					//return to user management main screen
					return;
				}

			}

		}

		//if result returned 0 row
		else {

			cout << "User does not exist in database";
			cout << endl;
			cout << "Please try again";
			cout << endl;
			system("pause");

			numberOfWrongInput++;

		}
	
		//if number of wrong input more than equal 3
		if (numberOfWrongInput >= 3) {

			//display error message and go back to user management main screen
			cout << "You have entered wrong user ID for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to user management main screen
			return;
		
		}

	}

}

//function update balance
void updateBalance(Session currentSession) {

	//variable for update balance
	string adminInputUserID;
	double adminInputUserBalance;
	string adminInputAdminPassword;

	int numberOfTries = 0;

	while (true) {

		//number of times failed in entering user ID		
		int numberOfIDFailed = 0;

		//loop for getting user ID from admin
		while (true) {

			//clear screen
			system("CLS");

			//get user ID from admin
			cout << "Please insert userID that you want to update balance";
			cout << endl;
			getline(cin, adminInputUserID);
			cout << endl;

			//get length of user input
			int a = adminInputUserID.length();

			//set initial value for boolean flag
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//check if input is only digit
					if (adminInputUserID.at(i) >= 48 && adminInputUserID.at(i) <= 57) {

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
				cout << "The ID entered is too long.";
				cout << endl;
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

				return;

			}

		}

		//check userID exist or not
		string selectQuery = " SELECT * FROM user "
			" WHERE User_ID = "
			" " + adminInputUserID + " ";

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
				temp.setUserBalance(atoi(row[7]));

			}

			cout << "---------------------------------------------";
			cout << "---------------------------------------------";
			cout << "----------------------------";
			cout << endl;

			cout << "| " << left << setw(3) << "ID" << "| "
				<< left << setw(40) << "Name" << "| "
				<< setw(10) << "Type" << "| "
				<< setw(20) << "IdentityNo" << "| "
				<< setw(5) << "Sex" << "| "
				<< setw(15) << "Phone No" << "| "
				<< setw(10) << "Balance" << "|";
			cout << endl;

			cout << "---------------------------------------------";
			cout << "---------------------------------------------";
			cout << "----------------------------";
			cout << endl;

			//display results to admin
			temp.displayAsRow();

			//check the user details correct or not
			if (!checkContinue()) {
				return;
			}

			//get balance that want to update
			bool results = getInput("Please enter amount that want to update", adminInputUserBalance);

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

				//if result not returned
				else {

					num_row2 = 0;

				}

				//if result returned more than 0 row
				if (num_row2 > 0) {

					//update new balance to database
					system("CLS");

					//display new resetted password
					cout << "The new balance is: " << temp.getUserBalance()+adminInputUserBalance;
					cout << endl;

					//set query for update 
					string updateQuery = "UPDATE user SET User_Balance = "
						" " + to_string(temp.getUserBalance() + adminInputUserBalance) + " "
						" WHERE User_ID = "
						" " + adminInputUserID + " ";

					//execute update query
					mysql_query(conn, updateQuery.c_str());

					system("pause");
					cout << endl;

					//done and return to user management main screen
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

				//If more than 3 error then go back to user management main screen
				if (numberOfWrongPassword >= 3) {

					//display error message and go back to user management main screen
					cout << "You have entered wrong password for more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					//return to user management main screen
					break;
				}

			}

		}

		//if result returned 0 row
		else {

			cout << "The user does not exist in database";
			cout << endl;
			cout << "Please try again ";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfTries++;

		}

		if (numberOfTries >= 3) {
		
			//display error messenge and exit to main screen
			cout << "You have entered wrong input for ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}
	
	}

	
}

//function delete user
void deleteUser(Session currentSession) {

	//variable for delete user
	string adminInputUserID;
	string adminInputAdminPassword;
	int inputID;

	int numberOfWrongInput = 0;

	while (true) {

		//clear screen
		system("CLS");

		//get id that want to delete
		bool results = getInput("Please insert userID that you want to delete", inputID);

		//if fail to get input
		if (!results) {

			//display error message and go back to user management main screen
			cout << "You have entered wrong ID format for more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			//return to user management main screen
			return;

		}

		//convert id to string
		adminInputUserID = to_string(inputID);

		//check userID exist or not
		string selectQuery = " SELECT * FROM user "
			" WHERE User_ID = "
			" " + adminInputUserID + " ";

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

			//count number of times wrong password
			int numberOfWrongPassword = 0;

			//loop to check if admin password is correct
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

					//delete the user from database
					string delete_query = "DELETE FROM user "
						" WHERE User_ID = " + adminInputUserID + " ";

					//execute update query
					mysql_query(conn, delete_query.c_str());

					cout << "The user with user ID " << adminInputUserID << " is deleted";
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

				//If more than 3 error then go back to user management main screen
				if (numberOfWrongPassword >= 3) {

					//display error message and go back to user management main screen
					cout << "You have entered wrong password for more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					//return to user management main screen
					break;
				}

			}

		}

		//if result returned 0 row
		else {

			cout << "User does not exist";
			cout << endl;
			cout << "Please try again.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}
	
		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

	}

}

//function generate random password
string generateRandomPassword() {

	//variable for generateRandomPassword function
	char randomPassword[6];
	int counter;
	srand(time(NULL));

	//loop for all 6 character of randomPassword
	for (int i = 0; i < 6; i++) {

		//if this is the first 3 character
		if (i < 3) {
			
			//initialize random value for alphabet
			counter = rand() % 26 + 97;

		}

		//if this is the last 3 character
		else {
		
			//initialize random value for digit
			counter = rand() % 10 + 48;

		}

		//set value into randomPassword
		randomPassword[i] = counter;

	}

	//convert randomPassword into a string and return it
	string new_password(randomPassword);
	return new_password;

}


#endif