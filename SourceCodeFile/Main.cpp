/*
*This program demonstrates a simple C++ program.
*This file is stored the main entry point.
*/

#include <iostream>
#include <mysql.h>
#include "DatabaseConnection.h"
#include "Login.h"
#include "Register.h"
#include "Profile.h"
#include "UserManagement.h"
#include "MenuManagement.h"
#include "MealTypeManagement.h"
#include "BudgetTypeManagement.h"
#include "CustomerOrderManagement.h"
#include "CompletePayment.h"
#include "ViewOrderStatus.h"
#include "BudgetManagement.h"
#include "VendorMenuManagement.h"
#include "VendorOrderManagement.h"
#include "VendorReportManagement.h"
#include "List.h"
using namespace std;

int main() {
	
	//initialize connection
	MYSQL* conn = connection();

	//if connection successful
	if (conn) {

		//display database connect success
		cout << "Database connection successfully in main." << endl;

		//display Main Screen
		int choice;
		do {

			//clear screen
			system("CLS");

			//Start for display main screen
			//first line
			cout << "\n\n\n\t\t\t\t\t";
			cout << "******************************";
			cout << "\t\t\t\t\t\t\t\t\t\t\t" << endl;

			//second line
			cout << "\t\t\t\t\t\t   ";
			cout << "Welcome";
			cout << "\t\t\t\t\t\t\t";

			//third line
			cout << "\t\t\t\t\t\t\t\t     ";
			cout << "to";
			cout << "\t\t\t\t\t\t\t";

			//4th line
			cout << "\t\t\t\t\t\t\t\t\t ";
			cout << "e-Cafeteria";
			cout << "\t\t\t\t\t\t\t\t\t";

			//5th line
			cout << "\n\t\t\t\t\t";
			cout << "******************************";
			cout << "\t\t\t\t\t\t\t\t\t\t\t" << endl;
			
			//6 & 7th line
			cout << "\t\t\t\t\t     Login\t  Register\t\t\t\t" << endl;
			cout << "\t\t\t\t\t       1\t     2\t\t\t\t\t" << endl;
			cout << endl;

			//8 & 9th line
			cout << "\t\t\t\t\t\t    Exit\t\t\t\t\t\t" << endl;
			cout << "\t\t\t\t\t\t     0\t\t\t\t\t\t" << endl;
			cout << endl;
			
			//10th line
			cout << "\t\t\t\t      ";
			cout << "Please enter your choice.Thank you!\t\t\t\t" << endl;
			cout << "\t\t\t\t\t\t     ";
			cin >> choice;
			//End for display main screen

			//if the input is 1
			if (choice == 1) {

				//clear screen
				system("CLS");

				//Start for display login screen
				//create object for session
				Session currentSession;

				//if login successfully
				if (login(currentSession)) {
					
					//if userType is customer
					if (currentSession.userType == "Customer") {

						//variable of customer screen
						int customerInput;

						//clear screen
						system("CLS");

						//Start for display customer's main screen
						cout << "1. View and manage profile" << endl;
						cout << "2. View menu and order" << endl;
						cout << "3. Make payments" << endl;
						cout << "4. View order status" << endl;
						cout << "5. Plan budget" << endl;
						cout << "6. Log Out" << endl;
						cout << "Please enter your choice" << endl;
						cin >> customerInput;
						cout << endl;
						//End for display customer's main screen

						//check for choice
						switch (customerInput) {

							//view and manage profile
							case 1:
								profile(currentSession);
								break;

							//view menu and order
							case 2:
								customerOrderManagement(currentSession);
								break;

							//complete payment
							case 3:
								completePayment(currentSession);
								break;

							//view order status
							case 4:
								viewOrderStatus(currentSession);
								break;

							//plan budget
							case 5:
								budgetManagement(currentSession);
								break;

							//log out
							case 6:
								break;

						}

					}

					//if userType is vendor
					else if (currentSession.userType == "Vendor") {
						
						//variable of vendor screen
						int vendorInput;

						//clear screen
						system("CLS");

						//Start for display vendor's main screen
						cout << "1. View and manage profile" << endl;
						cout << "2. View and manage menu" << endl;
						cout << "3. View and manage order" << endl;
						cout << "4. View and manage report" << endl;
						cout << "5. Log Out" << endl;
						cout << "Please enter your choice" << endl;
						cin >> vendorInput;
						cout << endl;
						//End for display vendor's main screen

						//check for choice
						switch (vendorInput) {

							//view and manage profile
							case 1:
								profile(currentSession);
								break;

							//view and manage menu
							case 2:
								vendorMenuManagement(currentSession);
								break;

							//view and manage order
							case 3:
								vendorOrderManagement(currentSession);
								break;

							//view and manage report
							case 4:

								vendorReportManagement(currentSession);
								break;

							//log out
							case 5:
								break;

						}

					}

					//if userType is admin
					else {
						
						//variable of admin screen
						int adminInput;

						//clear screen
						system("CLS");

						//Start for display admin's main screen
						cout << "1. View and manage own profile" << endl;
						cout << "2. View and manage user" << endl;
						cout << "3. View and manage budget type" << endl;
						cout << "4. View and manage meal type" << endl;
						cout << "5. View and manage menu" << endl;
						cout << "6. Log out" << endl;
						cout << "Please enter your choice" << endl;
						cin >> adminInput;
						cout << endl;
						//End for display admin's main screen

						//check for choice
						switch (adminInput) {

							//view and manage own profile
							case 1:
								profile(currentSession);
								break;

							//view and manage user
							case 2:
								userManagement(currentSession);
								break;

							//view and manage budget type
							case 3:
								budgetTypeManagement(currentSession);
								break;

							//view and manage meal type
							case 4:
								mealTypeManagement(currentSession);
								break;

							//view and manage menu
							case 5:
								menuManagement(currentSession);
								break;

							//log out
							case 6:
								break;
						}

					}

				}
				//End for display login screen

			}

			//if the input is 2
			else if (choice == 2) {

				//clear screen
				system("CLS");

				//Start for display register screen
				int userID = registerUser();

				//if userID is not equal to 0
				if (userID != 0) {
					
					//display userID
					cout << "Your User ID is: ";
					cout << userID;
					cout << endl;
					system("pause");
					cout << endl;

				}
				//End for display register screen
				
			}

		} while (choice != 0);

	}

	//if connection does not connect successfully
	else {

		//display database connect failed
		cout << "Database connection failed.";
		cout << endl;

	}

	//close database connection
	mysql_close(conn);

}
