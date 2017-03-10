#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;


#ifndef fileOperations_H
#define fileOperations_H

class fileOperations {

public:

	//Constructor
	fileOperations();

	//Overloaded Constructor
	fileOperations(string, string, string);

	//Destructor
	~fileOperations();

	//Getter Functions

	//Transactions file

	//returns an vector of vectors for all ticket information
	vector<vector<string>> ticketInfo();
	
	//returns a vector of vectors conataining all username info
	vector<vector<string>> usernameInfo();

	//Get usernames
	vector<string> listOfUsers();
	
	//Get event titles
	vector<string> listOfEvents();
	
	//Get Account Type

	//Get Amounts

	//Get all information for specific user
	vector<string> allUserInfo(string);

	//Get all information for a specific event
	vector<string> allEventInfo(string,string, vector<vector<string>>);

	//Daily Transaction for create, delete, addCredit and end-of-session
	string cdaeTransactions(string, string, string, string);

	//Daily Transaction for refund
	string rTransactions(string, string, string, string);

	//Daily transaction for sell and buy
	string sbTransactions(string, string, string, string, string);

	//Get Credit

	//getRid of whitespace
	string clearWhite(string);

	
	
	
	
	//pubic variables
	string column1;
	string column2;
	string column3;
	string column4;
	vector<vector<string>> userInformation;
	vector<vector<string>> ticketInformation;

private:

	string accountsFile;
	string availableTicketsFile;
	string transactionsFile;
	


};

#endif