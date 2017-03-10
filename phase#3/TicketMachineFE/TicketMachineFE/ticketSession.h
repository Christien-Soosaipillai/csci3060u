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

	void sell(string);

	void buy(double);

	void addCredit(string,string);

	void create();

	void refund();

	void transactions(vector<string> usernamesList);

	void start_Session();

	void deleteAccount();


	//Variables

	//user entered command
	string command;
	
	//vector of strings to hold usernames
	vector<string> usernamesList;

	//transaction logs to keep track of all transactions in a vector of strings
	vector<string> transactionsLog;

	//instance of the class standardUser
	standardUser currentUser;

	void writeOut(vector<string>);

private:

	//user account information file name
	string userAccountsFile;

	//ticket file name
	string availableTicketsFile;

	//transactionFile
	string transactionFile = "transaction_file.txt";

	vector<string> transactionLog;
	vector<string> toBeDeleted;



	string createNum = "01";
	string deleteNum = "02";
	string addCreditNum = "06";
	string endsessionNum = "00";
	string refundNum = "05";
	string sellNum = "03";
	string buyNum = "04";

};



#endif


