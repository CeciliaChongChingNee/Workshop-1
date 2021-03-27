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

#ifndef BUDGETMANAGEMENT_H
#define BUDGETMANAGEMENT_H

void budgetManagement(Session currentSession);
void addNewBudget(Session currentSession);
void viewBudgetTypeChoices(Session currentSession);
void viewActiveBudget(Session currentSession);
void setActiveBudget(Session currentSession);
bool deactivateBudget(Session currentSession);
void viewAllBudget(Session currentSession);
void deleteBudget(Session currentSession);
void editBudget(Session currentSession);
void editBudgetTotalAmount(Session currentSession, BudgetList budget);
void editBudgetRepeat(Session currentSession, BudgetList budget);




void budgetManagement(Session currentSession) {

	//view budget (active only)
	//set active budget
	//add new budget
	//edit budget (cannot edit active budget)
	//deactivate budget (if there is active)
	//delete budget

	//variable of budgetManagement
	string customerInput;

	//initialize connection
	conn = connection();
	cin.ignore(1, '\n');

	int numberOfWrongInput = 0;

	//loop for budget management main screen
	while (true) {

		system("CLS");

		//Start for display screen for manage budget module
		cout << "1. View active budget" << endl;
		cout << "2. Set active budget" << endl;
		cout << "3. Add new budget" << endl;
		cout << "4. Edit budget" << endl;
		cout << "5. Deactivate budget" << endl;
		cout << "6. Delete budget" << endl;
		cout << "7. Go back" << endl;
		cout << "Please enter your choice" << endl;
		getline(cin, customerInput);
		cout << endl;
		//End for display screen for manage budget module

		//if customerInput is equal to 1
		if (customerInput == "1") {

			//call view active budget function
			viewActiveBudget(currentSession);

			//check if want to continue
			if (!(checkContinue())) {
				return;
			}

		}

		//if customerInput is equal to 2
		else if (customerInput == "2") {

			setActiveBudget(currentSession);

		}

		//if customerInput is equal to 3
		else if (customerInput == "3") {

			addNewBudget(currentSession);

			//check if want to continue
			if (!checkContinue()) {
				return;
			}

		}

		//if customerInput is equal to 4
		else if (customerInput == "4") {

			editBudget(currentSession);

		}

		//if customerInput is equal to 5
		else if (customerInput == "5") {

			//call deactivateBudget function
			deactivateBudget(currentSession);

		}

		//if customerInput is equal to 6
		else if (customerInput == "6") {

			//call delete budget function
			deleteBudget(currentSession);

			//go back to main screen
			return;

		}

		//if customerInput is equal to 7
		else if (customerInput == "7") {

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

void addNewBudget(Session currentSession) {

	//variable for addNewBudget function
	string customerInputBudgetTypeID;
	double customerInputBudgetTotalAmount;
	string customerInputBudgetRepeatChoice;
	char isBudgetRepeat;

	//temp budget type object to store details
	BudgetTypeList tempBudgetType;

	//temp budget object to store value
	BudgetList tempBudget;

	//count number of tries
	int numberOfTries = 0;

	//loop for getting budget Type ID
	while (true) {

		//number of times failed in entering budget type ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			viewBudgetTypeChoices(currentSession);

			//get budget type ID from admin
			cout << "Please enter your budget type choice";
			cout << endl;
			cout << "Note: GXXX (e.g: G001)";
			cout << endl;
			getline(cin, customerInputBudgetTypeID);
			cout << endl;

			//get length of user input
			int a = customerInputBudgetTypeID.length();

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
						if (customerInputBudgetTypeID.at(0) == 'G') {

							//set hasG to true
							hasG = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (customerInputBudgetTypeID.at(i) >= 48 && customerInputBudgetTypeID.at(i) <= 57) {

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
				cout << "You have entered wrong input for budget type ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		string select_query = "SELECT * FROM `budget type` WHERE Budget_Type_ID = '" + customerInputBudgetTypeID + "'";

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

			while (row = mysql_fetch_row(res)) {

				tempBudgetType.setBudgetTypeID(customerInputBudgetTypeID);
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

	bool results = getInput("Please enter the total spending limit of this budget", customerInputBudgetTotalAmount);

	//if fail to get input
	if (!results) {

		//display error message and go back to user management main screen
		cout << "You have entered the wrong format for more than 3 times.";
		cout << endl;
		cout << "Please try again later.";
		cout << endl;
		system("pause");
		cout << endl;

		//return to budget management main screen
		return;

	}

	numberOfTries = 0;

	//loop to get isBudgetRepeat
	while (true) {

		cout << "Do you want to repeat this budget";
		cout << endl;
		getline(cin, customerInputBudgetRepeatChoice);
		cout << endl;

		//if customer choice is yes
		if (customerInputBudgetRepeatChoice == "Y" || customerInputBudgetRepeatChoice == "y") {

			isBudgetRepeat = 'Y';
			break;

		}

		//if customer choice is no
		else if (customerInputBudgetRepeatChoice == "N" || customerInputBudgetRepeatChoice == "n") {

			isBudgetRepeat = 'N';
			break;

		}

		//if customer enters wrong input
		else {

			cout << "Please follow the format given";
			cout << endl;
			cout << "'Please try again";
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

	//initialize tempBudget object for saving
	tempBudget.setCustomerID(currentSession.userID);
	tempBudget.setBudgetTypeID(tempBudgetType.getBudgetTypeID());
	tempBudget.setBudgetStatus("STANDBY");
	tempBudget.setBudgetTotalAmount(customerInputBudgetTotalAmount);
	tempBudget.setBudgetRepeated(isBudgetRepeat);

	//save tempbudget to database
	tempBudget.save();

	//display new budget ID
	cout << "The new budget ID is " << tempBudget.getBudgetID();
	cout << endl;
	system("pause");
	cout << endl;

	return;

}

//function view budget type
void viewBudgetTypeChoices(Session currentSession) {

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

			//initialize temp budget type to store value
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

	cout << "Budget Type Table";
	cout << endl;

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

//function view active budget
void viewActiveBudget(Session currentSession) {

	//clear screen
	system("CLS");

	//variable for function viewActiveBudget
	BudgetList temp;
	MyList<BudgetList> budgets;
	MyList<PaymentList> payments;
	double totalSpending = 0;

	string select_query = "SELECT * FROM `budget` WHERE "
						  " Customer_ID = "
						  "" + to_string(currentSession.userID) + ""
						  " AND "
						  " Budget_Status = 'ACTIVE' ";
	
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

		//get budget object from sql result and add to list
		while (row = mysql_fetch_row(res)) {

			temp.setBudgetID(row[0]);
			temp.setCustomerID(stoi(row[1]));
			temp.setBudgetTypeID(row[2]);
			temp.setBudgetStartDate(row[3]);
			temp.setBudgetStatus(row[4]);
			temp.setBudgetTotalAmount(stof(row[5]));
			string tempString = row[6];
			temp.setBudgetRepeated(tempString.at(0));

			if (budgets.isEmpty()) {
			
				budgets.setHead(temp);
				
			}
			else {

				budgets.addToList(temp);

			}
		
		}

		cout << "Active Budget Information" << endl;

		cout << "---------------------------------------";
		cout << "-----------------------------";
		cout << endl;

		cout << "| " << " ID " << " | "
			<< left << setw(5) << "User" << "| "
			<< setw(5) << "Type" << "| "
			<< setw(15) << "Start Date" << "| "
			<< setw(10) << "Status" << "| "
			<< setw(7) << "Amount" << "| "
			<< setw(6) << "Repeat" << "| " << endl;

		cout << "---------------------------------------";
		cout << "-----------------------------";
		cout << endl;

		//display active budgets
		budgets.displayList();

		//displays for time difference and remaining budget
		DateManager start = DateManager(temp.getBudgetStartDate());

		//get DateManager for current Date;
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		//get current date
		int day = newtime.tm_mday;
		int month = newtime.tm_mon + 1;
		int year = newtime.tm_year + 1900;

		string date = "";
		date.append(to_string(year));
		date.append("-");
		date.append(to_string(month));
		date.append("-");
		date.append(to_string(day));

		DateManager current = DateManager(date);
		int daysPassed = current.getDifference(start);

		//get Budget Type to get the duration
		BudgetTypeList tempType;

		//query for select budget type from db
		string select_query = " SELECT * FROM  `budget type` WHERE "
							  " Budget_Type_ID  = "
							  "'" + temp.getBudgetTypeID() + "'";

		//execute query and store sucess/failure
		int state = mysql_query(conn, select_query.c_str());

		//if sql have issues
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
		if (num_row > 0){

			//initialize budget type object
			while (row = mysql_fetch_row(res)) {

				tempType.setBudgetTypeID(row[0]);
				tempType.setBudgetLabel(row[1]);
				tempType.setBudgetDuration(row[2]);
			
			}

			int duration = stoi(tempType.getBudgetDuration());

			if (daysPassed < duration) {

				//display remaining days of the budget
				cout << "Remaining days = " << duration - daysPassed;
				cout << endl;
							
			}
			else {
			
			}
		
		}
		else {

			cout << "Budget Type does not exist";
			cout << endl;
			system("pause");
			cout << endl;

			return;		
		
		}

		//get total spending where payment date is >= budget start date and <= current date
		select_query = " SELECT * FROM  `payment` WHERE "
							  " Payment_Date >= "
							  "'" + temp.getBudgetStartDate() + "'"
							  " AND "
							  " Payment_Date <= "
							  "'" + date + "'";

		state = mysql_query(conn, select_query.c_str());

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

		//if result returned
		if (res) {

			num_row = mysql_num_rows(res);

		}

		//if result not returned
		else {

			num_row = 0;

		}

		if (num_row > 0) {

			while (row = mysql_fetch_row(res)) {
			
				PaymentList tempPayment;
				tempPayment.setOrderID(row[0]);
				tempPayment.setCustomerID(stoi(row[1]));
				tempPayment.setPaymentTotalAmount(stof(row[2]));
				tempPayment.setPaymentDate(row[3]);
				tempPayment.setPaymentTime(row[4]);

				if (payments.isEmpty()) {
				
					payments.setHead(tempPayment);

				}
				else {
				
					payments.addToList(tempPayment);

				}
							
			}
		
		}

		else {

			cout << "No spending history found";
			cout << endl;
		
		}

		//get total amount spent
		if (!payments.isEmpty()) {
		
			payments.goToHead();
			for (int i = 1; i <= payments.getLength(); i++) {
			
				totalSpending += payments.getCurrent()->element.getPaymentTotalAmount();
				payments.moveToNext();
			
			}

		}

		if (totalSpending <= temp.getBudgetTotalAmount()) {

			cout << "Remaining budget = " << temp.getBudgetTotalAmount() - totalSpending;
			cout << endl;
			system("pause");
			cout << endl;
			
			return;
		
		}
		else {

			cout << "You have gone over the budget";
			cout << endl;
			system("pause");
			cout << endl;

			return;
		
		}

	
	}

	//if result returned 0 row
	else {

		cout << "You currently have no active budget";
		cout << endl;
		cout << "Please activate a budget";
		cout << endl;
		system("pause");
		cout << endl;
		
		return;

	}
}

//function set active budget
void setActiveBudget(Session currentSession) {

	//variable for function setActiveBudget
	string customerInputBudgetID;
	BudgetList budget;

	//if user deactivated or dont have active budget
	if (deactivateBudget(currentSession)) {

		int numberOfTries = 0;

		//loop for getting budget ID
		while (true) {

			//number of times failed in entering budget ID		
			int numberOfIDFailed = 0;

			//loop for checking ID format
			while (true) {

				viewAllBudget(currentSession);

				//get budget type ID from admin
				cout << "Please enter your budget ID choice";
				cout << endl;
				cout << "Note: BXXX (e.g: B001)";
				cout << endl;
				getline(cin, customerInputBudgetID);
				cout << endl;

				//get length of user input
				int a = customerInputBudgetID.length();

				//set initial value for boolean flag
				bool hasB = false;
				bool hasDigit = false;

				//if the length of userInput <= 5
				if (a <= 5) {

					//loop to check the char is available or not
					for (int i = 0; i < a; i++) {

						//if currently is the first index
						if (i == 0) {

							//check if input is only G
							if (customerInputBudgetID.at(0) == 'B') {

								//set hasG to true
								hasB = true;

							}

						}

						//if currently is not the first index
						else {

							//check if input is only digit
							if (customerInputBudgetID.at(i) >= 48 && customerInputBudgetID.at(i) <= 57) {

								//set hasDigit to true
								hasDigit = true;

							}

							//if input is others
							else {

								//set hasG and hasDigit to false
								hasB = false;
								hasDigit = false;


								//break out of the for loop and go to check hasG and hasDigit
								break;

							}

						}

					}

					//if input_char not having correct format
					if (!(hasDigit && hasB)) {

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
					cout << "The budget ID entered is too long." << endl;
					system("pause");
					cout << endl;

					//count number of ID failed
					numberOfIDFailed++;

				}

				if (numberOfIDFailed >= 3) {

					//display error messenge and exit to main screen
					cout << "You have entered wrong input for budget ID more than 3 times.";
					cout << endl;
					cout << "Please try again later.";
					cout << endl;
					system("pause");
					cout << endl;

					return;

				}

			}

			string select_query = "SELECT * FROM `budget` WHERE Budget_ID = '" + customerInputBudgetID + "'";

			//Execute query (get the data from database)
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

				while (row = mysql_fetch_row(res)) {

					budget.setBudgetID(row[0]);
					budget.setCustomerID(stoi(row[1]));
					budget.setBudgetTypeID(row[2]);
					budget.setBudgetStatus(row[4]);
					budget.setBudgetTotalAmount(stof(row[5]));
					string tempString = row[6];
					budget.setBudgetRepeated(tempString.at(0));

				}

				break;

			}

			//if result returned 0 row
			else {

				cout << "Budget does not exist in database.";
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

		//initialize time object
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		//get current date
		int day = newtime.tm_mday;
		int month = newtime.tm_mon + 1;
		int year = newtime.tm_year + 1900;

		string date = "";
		date.append(to_string(year));
		date.append("-");
		date.append(to_string(month));
		date.append("-");
		date.append(to_string(day));

		budget.setBudgetStatus("ACTIVE");
		budget.setBudgetStartDate(date);

		budget.save();

		return;

	}
	//if user error or dont want to deactivate their budget
	else {

		return;
	
	}

}

//function deactivateBudget
bool deactivateBudget(Session currentSession) {

	//check if user have active budget
	//variable for function viewActiveBudget
	BudgetList temp;
	MyList<BudgetList> budgets;
	string customerInputKeepActive;
	string customerInputBudgetID;

	string select_query = "SELECT * FROM `budget` WHERE "
						  " Customer_ID = "
						  "" + to_string(currentSession.userID) + ""
						  " AND "
						  " Budget_Status = 'ACTIVE' ";

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

		//get budget object from sql result and add to list
		while (row = mysql_fetch_row(res)) {

			temp.setBudgetID(row[0]);
			temp.setCustomerID(stoi(row[1]));
			temp.setBudgetTypeID(row[2]);
			temp.setBudgetStartDate(row[3]);
			temp.setBudgetStatus(row[4]);
			temp.setBudgetTotalAmount(stof(row[5]));
			string tempString = row[6];
			temp.setBudgetRepeated(tempString.at(0));

			if (budgets.isEmpty()) {

				budgets.setHead(temp);

			}
			else {

				budgets.addToList(temp);

			}

		}

		int numOfWrongInput = 0;

		//loop for current active budget 
		while (true) {

			system("CLS");

			cout << "Active Budget Information" << endl;

			cout << "---------------------------------------";
			cout << "-----------------------------";
			cout << endl;

			cout << "| " << " ID " << " | "
				<< left << setw(5) << "User" << "| "
				<< setw(5) << "Type" << "| "
				<< setw(15) << "Start Date" << "| "
				<< setw(10) << "Status" << "| "
				<< setw(7) << "Amount" << "| "
				<< setw(6) << "Repeat" << "| " << endl;

			cout << "---------------------------------------";
			cout << "-----------------------------";
			cout << endl;

			//display active budgets
			budgets.displayList();

			cout << "You currently have the above budget active";
			cout << endl;
			cout << "Would you like to keep this budget as active? (Y/N)";
			cout << endl;
			getline(cin, customerInputKeepActive);
			cout << endl;

			//if customer wants to keep it active
			if (customerInputKeepActive == "Y" || customerInputKeepActive == "y") {

				cout << "No changes is made";
				cout << endl;
				system("pause");
				cout << endl;

				return false;

			}

			//if customer dont want to keep it active
			else if (customerInputKeepActive == "N" || customerInputKeepActive == "n") {

				//change this budget status to standby and go on to select new active budget 
				temp.setBudgetStatus("STANDBY");
				temp.save();

				return true;

			}

			//if customer has wrong input
			else {

				//display error message
				cout << "Sorry please follow the format given";
				cout << endl;
				cout << "Please try again";
				cout << endl;

				numOfWrongInput++;

			}

			//if number of wrong input is more than 3
			if (numOfWrongInput >= 3) {

				//display error message and go back to budget management main screen
				cout << "You have entered the wrong input for more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				//return to budget management main screen
				return false;

			}


		}

	}

	else {

		return true;

	}

}

//function viewAllBudget
void viewAllBudget(Session currentSession) {

	//variable for function viewAllBudget
	BudgetList temp;
	MyList<BudgetList> budgets;

	string select_query = " SELECT * FROM `budget` WHERE "
						  " Customer_ID = "
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

	//if reuslt not returned
	else {
	
		num_row = 0;

	}

	//if result returned more than 0 row
	if (num_row > 0) {
	
		//get budget object and add to list
		while (row = mysql_fetch_row(res)) {
		
			temp.setBudgetID(row[0]);
			temp.setCustomerID(stoi(row[1]));
			temp.setBudgetTypeID(row[2]);
			temp.setBudgetStatus(row[4]);
			temp.setBudgetTotalAmount(stof(row[5]));
			string tempString = row[6];

			if (tempString == "Y") {

				temp.setBudgetRepeated('Y');

			}

			else {

				temp.setBudgetRepeated('N');

			}

			if (budgets.isEmpty()) {

				budgets.setHead(temp);

			}
			else {

				budgets.addToList(temp);

			}

		
		}

		system("CLS");

		cout << "Budget List" << endl;

		cout << "---------------------------------------";
		cout << "-----------------------------";
		cout << endl;

		cout << "| " << " ID " << " | "
			<< left << setw(5) << "User" << "| "
			<< setw(5) << "Type" << "| "
			<< setw(15) << "Start Date" << "| "
			<< setw(10) << "Status" << "| "
			<< setw(7) << "Amount" << "| "
			<< setw(6) << "Repeat" << "| " << endl;

		cout << "---------------------------------------";
		cout << "-----------------------------";
		cout << endl;

		budgets.displayList();
		cout << endl;
		system("pause");
		cout << endl;

	}

	//if result returned 0 row
	else {
	
	
	}

}

//function delete budget type
void deleteBudget(Session currentSession) {

	//variable for delete budget type
	string customerInputBudgetID;
	string customerInputPassword;

	int numberOfWrongInput = 0;

	while (true) {

		//number of times failed in entering menu ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get budget type ID from admin
			cout << "Please enter budget ID that you want to delete";
			cout << endl;
			cout << "Note: BXXX (e.g: B001)";
			cout << endl;
			getline(cin, customerInputBudgetID);
			cout << endl;

			//get length of user input
			int a = customerInputBudgetID.length();

			//set initial value for boolean flag
			bool hasB = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only B
						if (customerInputBudgetID.at(0) == 'B') {

							//set hasB to true
							hasB = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (customerInputBudgetID.at(i) >= 48 && customerInputBudgetID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasB and hasDigit to false
							hasB = false;
							hasDigit = false;


							//break out of the for loop and go to check hasB and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasB)) {

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
				cout << "The budget ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfIDFailed++;

			}

			if (numberOfIDFailed >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for budget ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		string select_query = "SELECT * FROM `budget` WHERE Budget_ID = '" + customerInputBudgetID + "'";

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
				cout << "Please enter your password";
				cout << endl;
				getline(cin, customerInputPassword);
				cout << endl;

				//verify user exist in database 
				string selectQuery = "SELECT User_Type FROM user "
					" WHERE User_ID = " + to_string(currentSession.userID) + " "
					" AND User_Password = '" + customerInputPassword + "' ";

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
					string delete_query = "DELETE FROM `budget` "
						" WHERE Budget_ID = '" + customerInputBudgetID + "' ";

					//execute update query
					mysql_query(conn, delete_query.c_str());

					cout << "The budget with budget ID " << customerInputBudgetID << " is deleted";
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

				//If more than 3 error then go back to budget management main screen
				if (numberOfWrongPassword >= 3) {

					//display error message and go back to budget management main screen
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

		//if result returned 0 row
		else {

			cout << "The budget does not exist in database.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for budget type ID more than 3 times.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			return;

		}

	}

}

void editBudget(Session currentSession) {

	//variable for delete budget type
	string customerInputBudgetID;
	string customerInputEditType;
	BudgetList budget;

	int numberOfWrongInput = 0;

	//get non active budget to edit
	while (true) {

		//number of times failed in entering budget ID		
		int numberOfIDFailed = 0;

		//loop for checking ID format
		while (true) {

			//clear screen
			system("CLS");

			//get budget type ID from customer
			cout << "Please enter budget ID that you want to edit";
			cout << endl;
			cout << "Note: BXXX (e.g: B001)";
			cout << endl;
			getline(cin, customerInputBudgetID);
			cout << endl;

			//get length of user input
			int a = customerInputBudgetID.length();

			//set initial value for boolean flag
			bool hasB = false;
			bool hasDigit = false;

			//if the length of userInput <= 5
			if (a <= 5) {

				//loop to check the char is available or not
				for (int i = 0; i < a; i++) {

					//if currently is the first index
					if (i == 0) {

						//check if input is only B
						if (customerInputBudgetID.at(0) == 'B') {

							//set hasB to true
							hasB = true;

						}

					}

					//if currently is not the first index
					else {

						//check if input is only digit
						if (customerInputBudgetID.at(i) >= 48 && customerInputBudgetID.at(i) <= 57) {

							//set hasDigit to true
							hasDigit = true;

						}

						//if input is others
						else {

							//set hasB and hasDigit to false
							hasB = false;
							hasDigit = false;


							//break out of the for loop and go to check hasB and hasDigit
							break;

						}

					}

				}

				//if input_char not having correct format
				if (!(hasDigit && hasB)) {

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
				cout << "The budget ID entered is too long." << endl;
				system("pause");
				cout << endl;

				//count number of ID failed
				numberOfIDFailed++;

			}

			if (numberOfIDFailed >= 3) {

				//display error messenge and exit to main screen
				cout << "You have entered wrong input for budget ID more than 3 times.";
				cout << endl;
				cout << "Please try again later.";
				cout << endl;
				system("pause");
				cout << endl;

				return;

			}

		}

		string select_query = "SELECT * FROM `budget` WHERE Budget_ID = '" + customerInputBudgetID + "'";

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

			//get budget object from query
			while (row = mysql_fetch_row(res)) {

				budget.setBudgetID(row[0]);
				budget.setCustomerID(stoi(row[1]));
				budget.setBudgetTypeID(row[2]);
				budget.setBudgetStatus(row[4]);
				budget.setBudgetTotalAmount(stof(row[5]));
				string tempString = row[6];
				budget.setBudgetRepeated(tempString.at(0));

			}

			//if budget is active
			if (budget.getBudgetStatus().compare("ACTIVE") == 0) {
			
				cout << "You may not edit an active budget";
				cout << endl;
				cout << "Please try again";
				cout << endl;
				system("pause");
				cout << endl;

				numberOfWrongInput++;

			}

			//if budget is not active
			else {
			
				break;

			}

		}

		//if result returned 0 row
		else {

			cout << "The budget does not exist in database.";
			cout << endl;
			cout << "Please try again later.";
			cout << endl;
			system("pause");
			cout << endl;

			numberOfWrongInput++;

		}

		if (numberOfWrongInput >= 3) {

			//display error messenge and exit to main screen
			cout << "You have entered wrong input for budget ID more than 3 times.";
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
		cout << "1. Edit budget total amount" << endl;
		cout << "2. Edit budget repeat" << endl;
		cout << "3. Go back" << endl;
		cout << "Please insert your choice" << endl;
		getline(cin, customerInputEditType);
		cout << endl;
		//End to display option 

		//if customerInputEditType is equal to 1
		if (customerInputEditType == "1") {

			//call edit budget total amount function
			editBudgetTotalAmount(currentSession, budget);

		}

		//if customerInputEditType is equal to 2
		else if (customerInputEditType == "2") {

			//call edit budget repeat function
			editBudgetRepeat(currentSession, budget);

		}

		//if customerInputEditType is equal to 3
		else if (customerInputEditType == "3") {

			//go back to budgetManagement main screen
			return;

		}

		//if customerInputEditType is not equal to the choice above
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

void editBudgetTotalAmount(Session currentSession, BudgetList budget) {

	double customerInputBudgetTotalAmount;

	bool results = getInput("Please enter the total spending limit of this budget", customerInputBudgetTotalAmount);

	//if fail to get input
	if (!results) {

		//display error message and go back to user management main screen
		cout << "You have entered the wrong format for more than 3 times.";
		cout << endl;
		cout << "Please try again later.";
		cout << endl;
		system("pause");
		cout << endl;

		//return to budget management main screen
		return;

	}

	budget.setBudgetTotalAmount(customerInputBudgetTotalAmount);
	budget.save();

}

void editBudgetRepeat(Session currentSession, BudgetList budget) {

	string customerInputBudgetRepeatChoice;
	char isBudgetRepeat;

	int numberOfTries = 0;

	//loop to get isBudgetRepeat
	while (true) {

		cout << "Do you want to repeat this budget";
		cout << endl;
		getline(cin, customerInputBudgetRepeatChoice);
		cout << endl;

		//if customer choice is yes
		if (customerInputBudgetRepeatChoice == "Y" || customerInputBudgetRepeatChoice == "y") {

			isBudgetRepeat = 'Y';
			break;

		}

		//if customer choice is no
		else if (customerInputBudgetRepeatChoice == "N" || customerInputBudgetRepeatChoice == "n") {

			isBudgetRepeat = 'N';
			break;

		}

		//if customer enters wrong input
		else {

			cout << "Please follow the format given";
			cout << endl;
			cout << "'Please try again";
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

	budget.setBudgetRepeated(isBudgetRepeat);
	budget.save();

}

#endif // !BUDGETMANAGEMENT_H
