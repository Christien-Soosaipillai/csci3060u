#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

#include "standardUser.h"
#include "ticketSession.h"
#include "fileOperations.h"

using namespace std;

string currentFile = "current_user_accounts.txt";											
string availableTickets = "available_tickets_file.txt";
string transactionFile = "transaction_file.txt";

//takes a stream to read throught the file stated in main 
//and stores the usernamesinto the vector which is returned
//back to main
vector<string> returnNames(ifstream& file) {
	vector<string> userVec;

	string type;
	string username;
	double availableCredit;

	//while loop to read through file  and assign each word seperated by a space to a variable
	while (file >> username >> type >> availableCredit) {
		userVec.push_back(username);
	}
	return userVec;
}


int main() {	
	vector<string> listOfUsers;
	ifstream accountsFile("current_user_accounts.txt");

	//Create fileOperations class to access all file information
	fileOperations fileOperator(currentFile, availableTickets, transactionFile);
	listOfUsers = fileOperator.listOfUsers();
	
	//creates an instance of the ticket session
	ticketSession starter(listOfUsers, currentFile, availableTickets);

	//begins a ticket session
	starter.start_Session();

	return 0;
}
