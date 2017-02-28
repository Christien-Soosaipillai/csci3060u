//Function Declarations
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

#include "standardUser.h"

using namespace std;

#ifndef ticketSession_H
#define ticketSession_H

class ticketSession {

public:


	//Constructor
	ticketSession();


	//Overloaded Constructor
	ticketSession(vector<string>, string, string);

	//Deconstructor
	~ticketSession();

	//Transaction Functions
	void Login(string);

	void Logout();

	void sell(string, double, int);

	void buy(string, int, string);

	void addFunds();
	void transactions(vector<string> usernamesList);

	void start_Session();

	


	//Variables

	//user entered command
	string command;
	
	//vector of strings to hold usernames
	vector<string> usernamesList;

	//transaction logs to keep track of all transactions in a vector of strings
	vector<string> transactionsLog;

	//instance of the class standardUser
	standardUser currentUser;

private:

	//user account information file name
	string userAccountsFile;

	//ticket file name
	string availableTicketsFile;




};



#endif


