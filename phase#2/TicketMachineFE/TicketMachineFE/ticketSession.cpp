//Function Definitions

#include "ticketSession.h"
#include "standardUser.h"




//Constructor
ticketSession::ticketSession() {

	vector<string> usernamesList;

}


//Overloaded Constructor
ticketSession::ticketSession(vector<string> usernamesList, string userAccountsFile, string availableTicketsFile) {

	usernamesList = usernamesList;
	userAccountsFile = userAccountsFile;
	availableTicketsFile = availableTicketsFile;

}

//Deconstructor
ticketSession::~ticketSession() {


}

//Transaction Functions
//To be completed later
void ticketSession::Login(string) {}

void ticketSession::Logout() {}

void ticketSession::sell(string, double, int) {}

void ticketSession::buy(string, int, string) {}

void ticketSession::addFunds() {

	cout << "Testing for depth" << endl;
	cout << "transaction complete" << endl;
}


//transactions -  is will start the task of determining with the session to be created 
//is just for a standard user or admin and will provide different transaction options for each.
//
//start by asking for the users username and getting all of the information associated with it
//reads through the file and retrieves information. stores into variables 
//
//creates an instance of either an admin or standard user based on account type
//
//begins login section and takes in "command" as an argument

void ticketSession::transactions(vector<string> usernamesList) {


	//string argument to be entered by user
	cout << "Enter Username: ";
	cin >> command;

	//reading stream for the file to be accessed
	ifstream AccountFileStream("current_user_accounts.txt");

	//vector containing the usernames 
	vector<string> accountFile;

	//string to hold type of account
	string type;

	//string to hold username
	string username;

	//double to hold credit on account
	double availlableCredit;

	//while loop to read through linesof the file and assign each word seperated by a space to each designated variable
	while (AccountFileStream >> username >> type >> availlableCredit) {

		//if username is found
		if (command == username) {

			//if account type is admin
			if (type == "AA") {
			
				//Still have to implement the administrator class with its own privileged functions

			}

			//else account type is standard
			else {
			
				standardUser currentUser(username, type, availlableCredit);
			
			}
		}
	}

		

		cout << "Login Accepted, welcome user!" << endl;

		//while loop to hold all transactions in and prompt user after each transaction is made for
		//the actions they wish to make after. breaks only if users prompts for "logout"
		while (true) {
			cout << "Please enter a transaction you wish to make" << endl;
			cin >> command;

			if (command == "addfunds") {

				addFunds();

			}
			else if (command == "logout") {
			
				break;
			}
			else {

				cout << "sorry that is the wrong command" << endl;
				cout << command << endl;
			}
		}
		cout << "you have logged out" << endl;
		cout << endl;
}


//This will start the actual ticket machine and prompt the user for their username 
//and check with the vector of strings to verify it exsits
void ticketSession::start_Session() {



	while (true) {
		cout << "Welcome to ticket kiosk.To quit at anytime please enter 'quit'. Please enter 'login' to begin: " << endl;

		cin >> command;
		//begins process if "login"  is entered
		if (command == "login") {

			//calls on transaction function to begin process
			transactions(usernamesList);

		}
		//breaks if "quit" is entered
		else if (command == "quit") {
		
			break;
		}
		else {
			cout << "Invalid Request. Need to be logged in." << endl;

		}

	}
	cout << "exiting the ticket system" << endl;

}