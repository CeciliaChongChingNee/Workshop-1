/*
*This program demonstrates a simple C++ program.
*This header file is stored whole list of project.
*All of the list is grouped in a class. 
*/

#include <iostream>
#include <string>
using namespace std;

#ifndef LIST_H
#define LIST_H

class UserList {
//attribute of class UserList
private:
	int userID;
	string userName;
	string userType;
	string userIdentityCard;
	string userPassword;
	string userGender;
	string userPhoneNumber;
	double userBalance;
	UserList* next;

//method of class UserList
public:
	UserList();
	void setUserID(int userID);
	int getUserID();
	void setUserName(string userName);
	string getUserName();
	void setUserType(string userType);
	string getUserType();
	void setUserIdentityCard(string userIdentityCard);
	string getUserIdentityCard();
	void setUserPassword(string userPassword);
	string getUserPassword();
	void setUserGender(string userGender);
	string getUserGender();
	void setUserPhoneNumber(string userPhoneNumber);
	string getUserPhoneNumber();
	void setUserBalance(double userBalance);
	double getUserBalance();
	void displayAsRow();
};


class MealTypeList {
//attribute of class MealTypeList
private:
	string mealTypeID;
	string typeName;
	string timeStart;
	string timeEnd;
	MealTypeList* next;

//method of class MealTypeList
public:
	MealTypeList();
	void setMealTypeID(string mealTypeID);
	string getMealTypeID();
	void setTypeName(string typeName);
	string getTypeName();
	void setTimeStart(string timeStart);
	string getTimeStart();
	void setTimeEnd(string timeEnd);
	string getTimeEnd();
	void displayAsRow();
	void save();
	string generateMealTypeID();
};


class MenuList {
//attribute of class MenuList
private:
	string menuID;
	int vendorID;
	string mealTypeID;
	string menuName;
	string menuDescription;
	int menuQuantity;
	double menuPrice;
	MenuList* next;

//method of class MenuList
public:
	MenuList();
	void setMenuID(string menuID);
	string getMenuID();
	void setVendorID(int userID);
	int getVendorID();
	void setMealTypeID(string mealTypeID);
	string getMealTypeID();
	void setMenuName(string menuName);
	string getMenuName();
	void setMenuDescription(string menuDescription);
	string getMenuDescription();
	void setMenuQuantity(int menuQuantity);
	int getMenuQuantity();
	void setMenuPrice(double menuPrice);
	double getMenuPrice();
	void displayAsRow();
	void save();
	string generateMenuID();
};


class OrderList {
//attribute of class OrderList
private:
	string orderID;
	int customerID;
	int vendorID;
	string orderType;
	string orderAddress;
	string orderDate;
	string orderExpectedTime;
	double orderTotalAmount;
	string orderStatus;
	OrderList* next;

//method of class OrderList
public:
	OrderList();
	void setOrderID(string orderID);
	string getOrderID();
	void setCustomerID(int userID);
	int getCustomerID();
	void setVendorID(int userID);
	int getVendorID();
	void setOrderType(string orderType);
	string getOrderType();
	void setOrderAddress(string orderAddress);
	string getOrderAddress();
	void setOrderDate(string orderDate);
	string getOrderDate();
	void setOrderExpectedTime(string orderExpectedTime);
	string getOrderExpectedTime();
	void setOrderTotalAmount(double orderTotalAmount);
	double getOrderTotalAmount();
	void setOrderStatus(string orderStatus);
	string getOrderStatus();
	void save();
	string generateOrderID();
	void displayAsRow();
};


class OrderDetailList {
//attribute of class OrderDetailList
private:
	string orderDetailID;
	string orderID;
	int customerID;
	string menuID;
	int itemQuantity;
	double totalItemPrice;
	OrderDetailList* next;

//method of class OrderDetailList
public:
	OrderDetailList();
	void setOrderDetailID(string orderDetailID);
	string getOrderDetailID();
	void setOrderID(string orderID);
	string getOrderID();
	void setCustomerID(int customerID);
	int getCustomerID();
	void setMenuID(string menuID);
	string getMenuID();
	void setItemQuantity(int itemQuantity);
	int getItemQuantity();
	void setTotalItemPrice(double totalItemPrice);
	double getTotalItemPrice();
	void save();
	string generateOrderDetailID();
	void displayAsRow();
};


class PaymentList {
//attribute of class PaymentList
private:
	string orderID;
	int customerID;
	double paymentTotalAmount;
	string paymentDate;
	string paymentTime;
	PaymentList* next;

//method of class PaymentList
public:
	PaymentList();
	void setOrderID(string orderID);
	string getOrderID();
	void setCustomerID(int userID);
	int getCustomerID();
	void setPaymentTotalAmount(double paymentTotalAmount);
	double getPaymentTotalAmount();
	void setPaymentDate(string paymentDate);
	string getPaymentDate();
	void setPaymentTime(string paymentTime);
	string getPaymentTime();
	void save();
	void displayAsRow();
};


class BudgetTypeList {
//attribute of class BudgetTypeList
private:
	string budgetTypeID;
	string budgetLabel;
	string budgetDuration;
	BudgetTypeList* next;

//method of class BudgetTypeList
public:
	BudgetTypeList();
	void setBudgetTypeID(string budgetTypeID);
	string getBudgetTypeID();
	void setBudgetLabel(string budgetLabel);
	string getBudgetLabel();
	void setBudgetDuration(string budgetDuration);
	string getBudgetDuration();
	void displayAsRow();
	void save();
	string generateBudgetTypeID();
};


class BudgetList {
//attribute of class BudgetList
private:
	string budgetID;
	int customerID;
	string budgetTypeID;
	string budgetStartDate;
	string budgetStatus;
	double budgetTotalAmount;
	char budgetRepeated;
	BudgetList* next;

//method of class BudgetList
public:
	BudgetList();
	void setBudgetID(string budgetID);
	string getBudgetID();
	void setCustomerID(int userID);
	int getCustomerID();
	void setBudgetTypeID(string budgetTypeID);
	string getBudgetTypeID();
	void setBudgetStartDate(string budgetStartDate);
	string getBudgetStartDate();
	void setBudgetStatus(string budgetStatus);
	string getBudgetStatus();
	void setBudgetTotalAmount(double budgetTotalAmount);
	double getBudgetTotalAmount();
	void setBudgetRepeated(char budgetRepeated);
	char getBudgetRepeated();
	void save();
	string generateBudgetID();
	void displayAsRow();
};

bool checkContinue();

template <typename T> bool getInput(string prompt, T &x)
{
	bool ok;
	int numberOfTries = 0;

	//do while loop to check input
	do
	{

		//count number of tries
		numberOfTries++;

		//display the message to ask user for input
		cout << prompt;
		cout << endl;

		//set boolean to true initially
		ok = true;

		//get user input
		cin >> x;
		cout << endl;

		//check if user input is following the variable type 
		//if wrong type of input
		if (!cin) {

			//set boolean to false
			ok = false;

			//clear the error message
			cin.clear();

		}

		//check to see if there is anything left in the buffer after
		string dummy;
		getline(cin, dummy);

		//if got white space in between
		if (dummy.find_first_not_of(" ") != string::npos) { 

			//set boolean to false
			ok = false; 
		}

		//if input is wrong 
		if (!ok) { 

			//display error message
			cout << "Invalid input";
			cout << endl;
			cout << "try again";
			cout << endl;
			system("pause");
			cout << endl;

			system("CLS");

		}

		//if number of tries is more than 3 times
		if (numberOfTries >= 3) {

			//return false response to function
			return false;

		}
	} while (!ok);

	//return true response to function
	return true;
}

#endif