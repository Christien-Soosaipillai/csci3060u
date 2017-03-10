//Function Definitions

#include "ticketSession.h"
#include "standardUser.h"
#include "fileOperations.h"

//Constructor
ticketSession::ticketSession() {
	vector<string> usernamesList;
}

//Overloaded Constructor
ticketSession::ticketSession(vector<string> _usernamesList, string _userAccountsFile, string _availableTicketsFile) {
	usernamesList = _usernamesList;
	userAccountsFile = _userAccountsFile;
	availableTicketsFile = _availableTicketsFile;
}

//Deconstructor
ticketSession::~ticketSession() {

}

//WriteOutFunction
void ticketSession::writeOut(vector<string> vec) {
	ofstream outPut(transactionFile);
	for (int i = 0; i < vec.size(); i++) {
		outPut << vec[i] + "\n";
	}
}

//Transaction Functions
void ticketSession::sell(string selfName) {
	string titleName;
	int numTickets;
	double priceOfTicket;
	fileOperations tempOperator(userAccountsFile, availableTicketsFile, transactionFile);
	cout << "Please enter the name of the ticket(s) you wish to sell: " << endl;
	cin >> titleName;
	if (titleName.size() < 26 && titleName.size() > 0) {
		if (titleName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos) {
			cout << "Invalid titleName!The username must be 1 - 25  ASCII characters long." << endl;
			return;
		}
		else {
			cout << "Please state how many tickets you wish to sell:" << endl;
			cin >> numTickets;
			if (isalpha(numTickets)) {
				cout << "Please enter integer value." << endl;
				return;
			}
			if (numTickets > 0 && numTickets < 101) {
				cout << "Please enter the price of each ticket:" << endl;
				cin >> priceOfTicket;
				if (priceOfTicket >= 0.00 && priceOfTicket < 99.99) {
					cout << "Success, ticket sale is created." << endl;
					transactionLog.push_back(tempOperator.sbTransactions(sellNum, titleName, selfName, to_string(numTickets), to_string(priceOfTicket)));
					return;
				}
				else {
					cout << "Invalid ticket price." << endl;
					return;
				}
			}else {
				cout << "Invalid Account Type. The account must one of the following; SS, FS, BS, or AA." << endl;
				return;
			}
		}
	}
	else {
		cout << "Invalid titleName! The username must be 1 - 25  ASCII characters long." << endl;
		return;
	}
}

void ticketSession::buy(double userCredit) {
	vector<vector<string>> listOfEvents;
	vector<string> allEventInfo;
	string eventTitle;
	string sellerName;
	string command;
	int numTickets = 1;
	double pricePerTicket;
	double total;

	fileOperations tempOperator(userAccountsFile, availableTicketsFile, transactionFile);
	listOfEvents = tempOperator.ticketInfo();

	string temp;
	cout << "Please enter the event title for the tickets you wish to purchase:" << endl;
	cin >> command; //first word
	getline(cin, temp); //everything else

	command = command + temp;
	eventTitle = command;
	for (int i = 0; i < listOfEvents[0].size(); i++) {
		if (command == listOfEvents[0][i]) {
			cout << "What is the username of the seller:";
			cin >> sellerName;
			cout << endl;
			//cout << eventTitle;
			for (int j = 0; j < listOfEvents[1].size(); j++) {
				if (sellerName == listOfEvents[1][i]) {
					cout << "How many tickets do you wish to purchase:" << endl;
					cin >> command;
					allEventInfo = tempOperator.allEventInfo(eventTitle, sellerName, listOfEvents);
					numTickets = stoi(allEventInfo[2]);
					pricePerTicket = stod(allEventInfo[3]);

					//check for a positive amount of tickets purchased {max 4}
					if ((stoi(command) <= 4) && (stoi(command) > 0)) {
						if ((numTickets - stoi(command)) >= 0) {
							double finalCost = (stod(command) * pricePerTicket);
							cout << "The cost of each ticket is: " << pricePerTicket << endl;
							cout << "The total cost is: " << finalCost << endl;;
							cout << "Please confirm your purchase(yes/no{exact}):" << endl;
							cin >> command;
							if (command == "yes") {
								if ((userCredit - finalCost) >= 0.00) {
									cout << "Ticket Purchased." << endl;
									transactionLog.push_back(tempOperator.sbTransactions(buyNum, eventTitle, sellerName, to_string(numTickets), to_string(pricePerTicket)));
									return;
								}else {
									cout << "Not enough funds." << endl; 
									return;
								}
							}
							else if (command == "no") {
								cout << "Tickets not purchased." << endl;
								return;
							}else {
								cout << "Invalid input." << endl;
								return;
							}
						}else {
							//Not enough tickets available
							cout << "Not enough tickets to sell." << endl;
							return;
						}
					}else {
						//Not enough tickets to sell
						cout << "Invalid ticket amount." << endl;
						return;
					}
				}else {
					//Seller username not found
					cout << "Seller user name not found." << endl;
					return;
				}
			}
		}
		else {
			//event name not found
			cout << "Event Name not found." << endl;
			return;
		}
	}
	return;
}

void ticketSession::deleteAccount() {
	string requestedUsername;
	vector<string> accountFile;
	vector<string> userInformation;
	string credit;
	string type;
	
	cout << "Please enter a user you wish to delete:" << endl;
	cin >> requestedUsername;
	fileOperations tempOperator(userAccountsFile, availableTicketsFile, transactionFile);
	accountFile = tempOperator.listOfUsers();
	for (int i = 0; i < accountFile.size(); i++) {
		if (requestedUsername == accountFile[i]) {
			userInformation = tempOperator.allUserInfo(requestedUsername);
			type = userInformation[1];
			credit = userInformation[2];
			cout << "Account is deleted." << endl;
			transactionLog.push_back(tempOperator.cdaeTransactions(deleteNum, requestedUsername,type,credit));
			toBeDeleted.push_back(requestedUsername);
			return;
		}
	}
	cout << "User not found." << endl;
	return;
}

void ticketSession::create() {
	string newName;
	string newType;
	double credit;
	vector<string> accountFile;
	vector<string> userInformation;
	double TotalCredit;
	fileOperations tempOperator(userAccountsFile, availableTicketsFile, transactionFile);
	accountFile = tempOperator.listOfUsers();
	cout << "Please create a username: " << endl;
	cin >> newName;
	if (newName.size() < 16 && newName.size() > 0) {
		if (newName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos) {
			cout << "Invalid Username!The username must be 1 - 15  ASCII characters long" << endl;
			return;
		}else {
			cout << "Please state the account type: " << endl;
			cin >> newType;
			if (newType == "SS" || newType == "FS" || newType == "BS" || newType == "AA") {
				cout << "Please enter a beginning credit amount: " << endl;
				cin >> credit;
				if (credit >= 0.00 && credit < 999.99) {
					cout << "Success, account is created." << endl;
					transactionLog.push_back(tempOperator.cdaeTransactions(createNum, newName, newType, to_string(credit)));
					return;
				}else {
					cout << "Invalid credit amount." << endl;
					return;
				}
			}else {
				cout << "Invalid Account Type. The account must one of the following; SS, FS, BS, or AA." << endl;
				return;
			}
		}
	}else {
		cout << "Invalid Username! The username must be 1 - 15  ASCII characters long." << endl;
		return;
	}
}

void ticketSession::refund() {

	string buyersName;
	string sellersName;
	string credit;
	vector<string> accountFile;
	vector<string> buyerInfo;
	vector<string> sellerInfo;
	double TotalCredit;

	fileOperations tempOperator(userAccountsFile, availableTicketsFile, transactionFile);
	accountFile = tempOperator.listOfUsers();

	cout << "Please state the buyer's username:" << endl;
	cin >> buyersName;

	for (int i = 0; i < accountFile.size(); i++) {

		if (buyersName == accountFile[i]) {

			buyerInfo = tempOperator.allUserInfo(buyersName);

			cout << "Please enter the seller's username:" << endl;
			cin >> sellersName;

			for (int j = 0; j < accountFile.size(); j++) {

				if (sellersName == accountFile[j]) {

					sellerInfo = tempOperator.allUserInfo(sellersName);

					cout << "How much credit is to be transfered:" << endl;
					cin >> credit;

					if (stod(sellerInfo[2]) >= 0.00) {

						if (stod(buyerInfo[2]) <= 999.99) {

							cout << "Refund complete" << endl;
							transactionLog.push_back(tempOperator.rTransactions(refundNum, buyersName, sellersName, credit));
							return;
						}

					}
					else {
						cout << "Seller amount would be below 0.00" << endl;
					}

				}

			}
			cout << "Sorry that username doesn't exist." << endl;
			return;

		}
		else {


		}
	}
	cout << "Sorry that username doesn't exist." << endl;
	return;

}

void ticketSession::addCredit(string userType, string selfName) {
	string intendedUser;
	string credit;
	vector<string> accountFile;
	vector<string> userInformation;
	double TotalCredit;
	fileOperations tempOperator(userAccountsFile, availableTicketsFile, transactionFile);
	accountFile = tempOperator.listOfUsers();

	if (userType == "AA") {
		cout << "Who do you wish to addcredit to?" << endl;
		cin >> command;
		intendedUser = command;
		for (int i = 0; i < accountFile.size(); i++) {
			if (intendedUser == accountFile[i]) {
				userInformation = tempOperator.allUserInfo(command);
				cout << "How much credit do you wish to add to this account:" << endl;
				cin >> credit;
				TotalCredit = stod(userInformation[2]) + stod(credit);
				if ((TotalCredit) > 999.99 || credit == "0" || credit == "0.00") {
					cout << "Invalid Request, User will be over credit amount." << endl;
				}
				else {
					cout << "Credit added! Your new credit will be: " << TotalCredit << endl;
					transactionLog.push_back(tempOperator.cdaeTransactions(addCreditNum, intendedUser, userType, credit));
					return;
				}
			}
		}
		cout << "Invalid request." << endl;
	}else if (userType == "BS" || userType == "SS" || userType == "FS") {
	
		for (int i = 0; i < accountFile.size(); i++) {
			if (selfName == accountFile[i]) {
				userInformation = tempOperator.allUserInfo(selfName);
				cout << "How much credit do you wish to add to this account:" << endl;
				cin >> credit;
				TotalCredit = stod(userInformation[2]) + stod(credit);
				if ((TotalCredit) > 999.99 || credit == "0" || credit == "0.00") {
					cout << "Invalid Request, User will be over credit amount." << endl;
				}
				else {
					cout << "Credit added! Your new credit will be: " << TotalCredit << endl;
					transactionLog.push_back(tempOperator.cdaeTransactions(addCreditNum, selfName, userType, credit));
					return;
				}
			}
		}
		cout << "Invalid request." << endl;
	}
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
	cout << "Enter username:" << endl;
	cin >> command;

	//reading stream for the file to be accessed
	ifstream AccountFileStream("current_user_accounts.txt");

	//vector containing the usernames 
	vector<string> accountFile;

	//vector containing a specified users account information
	vector<string> userInformation;

	//string to hold type of account
	string type;

	//string to hold username
	string username;

	//double to hold credit on account
	double availlableCredit;

	//deletedUser boolean variable
	bool deletedUser = false;

	//Call Instance of fileOperations to get account information for users
	fileOperations userOperator(userAccountsFile, availableTicketsFile, transactionFile);
	accountFile = userOperator.listOfUsers();
	
	//while loop to read through linesof the file and assign each word seperated by a space to each designated variable
	
	for (int i = 0; i < accountFile.size(); i++) {
		if (command == accountFile[i]) {
			userInformation = userOperator.allUserInfo(command);
			for (int i = 0; i < userInformation.size(); i++) {
				username = userInformation[0];
				type = userInformation[1];
				availlableCredit = stod(userInformation[2]);
			}
			standardUser currentUser(username, type, availlableCredit);
			cout << "Welcome "<< username << "." << endl;

			//while loop to hold all transactions in and prompt user after each transaction is made for
			//the actions they wish to make after. breaks only if users prompts for "logout"
			while (true) {
				for (int z = 0; z < toBeDeleted.size(); z++) {
					if (currentUser.getcurrent_username() == toBeDeleted[z]) {
						deletedUser = true;
					}
				}
				cout << "Please enter a function:" << endl;
				cin >> command;
				if(command == "buy"){
					if (deletedUser == true) {
						cout << "Deleted Users can't use the buy function." << endl;
					}
					else {
						if (currentUser.getaccount_type() == "SS") {
							cout << "Sell-standard type accounts cannot use the buy function." << endl;
						}
						else {
							buy(currentUser.getCredit());
						}
					}
				}else if (command == "refund") {
					if (currentUser.getaccount_type() == "AA") {
						refund();
					}else {
						cout << "Sorry only Admins can use the refund function." << endl;
					}
					//Refund Function
					//Privileged transaction
					//takes user type
				}else if (command == "addcredit") {
					//checks type and then initiates one fo the 2 kinds of addcredits
					addCredit(currentUser.getaccount_type(), currentUser.getcurrent_username());
				}
				else if (command == "delete") {
					if (currentUser.getaccount_type() == "AA") {
						deleteAccount();
					}
					else {
						cout << "Invalid request. Need to be an admin in order to proceed." << endl;
					}					
				}else if (command == "sell") {
					if (deletedUser == true) {
						cout << "Deleted Users can't use the buy function." << endl;
					}
					else {
						//checks type to see if user is full/sell standard or admin
						if (currentUser.getaccount_type() == "BS") {
							cout << "Buy-standard type accounts cannot use the sell function." << endl;
						}
						else {
							sell(currentUser.getcurrent_username());
						}
					}				
				}else if (command == "create"){
					if (currentUser.getaccount_type() == "AA") {
						create();
					}
					else {
						cout << "Sorry only admins can use the create function." << endl;
					}
				}else if (command == "logout") {
					userOperator.cdaeTransactions(endsessionNum, currentUser.getcurrent_username(), currentUser.getaccount_type(), to_string(currentUser.getCredit()));
					break;
				}else {
					cout << "Invalid request." << endl;
				}
			}
			cout << "Logout successful." << endl;
		}
	}
}


//This will start the actual ticket machine and prompt the user for their username 
//and check with the vector of strings to verify it exsits
void ticketSession::start_Session() {
	while (true) {
		cout << "Welcome to ticket kiosk. To quit at anytime please enter 'quit'." << endl << "Please enter 'login' to begin:" << endl;
		cin >> command;
		//begins process if "login"  is entered
		if (command == "login") {
			//calls on transaction function to begin process
			transactions(usernamesList);
		}
		//breaks if "quit" is entered
		else if (command == "quit") {
			writeOut(transactionLog);
			break;
		}
		else {
			cout << "Invalid Request. Need to be logged in." << endl;
		}
	}
}