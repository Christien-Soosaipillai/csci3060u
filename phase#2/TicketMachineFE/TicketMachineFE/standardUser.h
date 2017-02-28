#pragma once
//Function Declarations
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>


using namespace std;

#ifndef standardUser_H
#define standardUser_H


//Creates an object called student User which will hold the username, account type as well as the credit ammount for the user
class standardUser {
public:

	//Constructor
	standardUser();

	//Overloaded Constructor
	standardUser(string, string, double);

	//Destructor
	~standardUser();

	//Getter Functions

	//getcurrent_username - returns username of current user
	string getcurrent_username();

	//getaccount_type - returns account type of current user
	string getaccount_type();

	//getCredit - returns account credit of current user
	double getCredit();




	//Mutator Function


	//setCredit - changes the value of credit after a purchase
	void setCredit(double);


	//public variable

	ifstream userAccounts;



private:

	//private variables

	string currentUsername;
	string accountType;
	double credit;

};

#endif
