/*
*This program demonstrates a simple C++ program.
*This cpp file is stored function definition of UserList.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include "List.h"
using namespace std;

//constructor of UserList
UserList::UserList() {
	userBalance = 0;
	UserList* next = NULL;
}

//set userID
void UserList::setUserID(int userID) {
	this->userID = userID;
}

//get userID
int UserList::getUserID() {
	return userID;
}

//set userName
void UserList::setUserName(string userName) {
	this->userName = userName;
}

//get userName
string UserList::getUserName() {
	return userName;
}

//set userType
void UserList::setUserType(string userType) {
	this->userType = userType;
}

//get userType
string UserList::getUserType() {
	return userType;
}

//set userIdentityCard
void UserList::setUserIdentityCard(string userIdentityCard) {
	this->userIdentityCard = userIdentityCard;
}

//get userIdentityCard
string UserList::getUserIdentityCard() {
	return userIdentityCard;
}

//set userPassword
void UserList::setUserPassword(string userPassword) {
	this->userPassword = userPassword;
}

//get userPassword
string UserList::getUserPassword() {
	return userPassword;
}

//set userGender
void UserList::setUserGender(string userGender) {
	this->userGender = userGender;
}

//get userGender
string UserList::getUserGender() {
	return userGender;
}

//set userPhoneNumber
void UserList::setUserPhoneNumber(string userPhoneNumber) {
	this->userPhoneNumber = userPhoneNumber;
}

//get userPhoneNumber
string UserList::getUserPhoneNumber() {
	return userPhoneNumber;
}

//set userBalance
void UserList::setUserBalance(double userBalance) {
	this->userBalance = userBalance;
}

//get userBalance
double UserList::getUserBalance() {
	return userBalance;
}

void UserList::displayAsRow() {

	cout << "| " << left << setw(3) << to_string(getUserID()) << "| "
		<< left << setw(40) << getUserName() << "| "
		<< setw(10) << getUserType() << "| "
		<< setw(20) << getUserIdentityCard() << "| "
		<< setw(5) << getUserGender() << "| "
		<< setw(15) << getUserPhoneNumber() << "| "
		<< setw(10) << fixed << setprecision(2) << getUserBalance() << "|";
	cout<< endl;

	cout << "---------------------------------------------";
	cout << "---------------------------------------------";
	cout << "----------------------------";
	cout << endl;
}