//Functions Dfeinitions

#include "fileOperations.h"

//Constructor
fileOperations::fileOperations() {
	//Strings are initiated to null automatically
}


//Overloaded Constructor 
fileOperations::fileOperations(string accountsF, string ticketsF, string transactionsF) {
	accountsFile = accountsF;
	availableTicketsFile = ticketsF;
	transactionsFile = transactionsF;
}

//Deconstructor ~ assign all files as null
fileOperations::~fileOperations() {
	accountsFile = "";
	availableTicketsFile = "";
	transactionsFile = "";
}


//returns an vector of vectors for all username information
vector<vector<string>> fileOperations::usernameInfo() {
	ifstream stream1(accountsFile);
	ifstream stream2(accountsFile);
	ifstream stream3(accountsFile);
	vector<vector<string>> userInformation;
	vector<string> temp1;
	vector<string> temp2;
	vector<string> temp3;

	string column1;
	string column2;
	string column3;
	
	while (stream1 >> column1 >> column2 >> column3) {
		temp1.push_back(column1);
	}

	while (stream2 >> column1 >> column2 >> column3) {
		temp2.push_back(column2);
	}

	while (stream3 >> column1 >> column2 >> column3) {
		temp3.push_back(column3);
	}

	stream1.close();
	stream2.close();
	stream3.close();
			
	userInformation.push_back(temp1);
	userInformation.push_back(temp2);
	userInformation.push_back(temp3);

	return userInformation;
}

//returns a vector of vectors conataining all ticket info
vector<vector<string>> fileOperations::ticketInfo(){
	ifstream stream1(availableTicketsFile);
	
	vector<vector<string>> ticketInformation;
	vector<string> temp1;
	vector<string> temp2;
	vector<string> temp3;
	vector<string> temp4;
	
	//cout << availableTicketsFile << endl;
	string line;
											//Max size for a ticket event title
	char eventTitle[20];
	char sellerName[14];
	char ticketsAmount[4];
	char priceAmount[7];

	int i;
	int j;

	while (getline(stream1, line)) {
		i = 0;
		j = 0;		
		while (i < 19) {
			eventTitle[i] = line[i];
			i++;
		}

		eventTitle[i] = '\0';
		i = 20;
		while (i < 33) {
			sellerName[j] = line[i];
			j++;
			i++;
		}

		sellerName[j] = '\0';
		j = 0;
		i = 34;
		while (i < 37) {
			ticketsAmount[j] = line[i];
			i++;
			j++;
		}

		ticketsAmount[j] = '\0';
		j = 0;
		i = 38;
		while (i < 44) {
			priceAmount[j] = line[i];
			i++;
			j++;
		}

		priceAmount[j] = '\0';
	}

	string str1(eventTitle);
	string str2(sellerName);
	string str3(ticketsAmount);
	string str4(priceAmount);

	//cout << str1 << "_" << str2 << "_" << str3 << "_" << str4 << endl;
	//cout << str1 << endl;
	//cout << string(eventTitle) << endl;

	temp1.push_back(clearWhite(str1));
	temp2.push_back(clearWhite(str2));
	temp3.push_back(clearWhite(str3));
	temp4.push_back(clearWhite(str4));

	ticketInformation.push_back(temp1);
	ticketInformation.push_back(temp2);
	ticketInformation.push_back(temp3);
	ticketInformation.push_back(temp4);

	stream1.close();
	return ticketInformation;
}

vector<string> fileOperations::listOfUsers() {
	vector<vector<string>> temp = usernameInfo();
	vector<string> userList;

	for (int i = 0; i < temp[0].size(); i++) {
		userList.push_back(temp[0][i]);
	}

	return temp[0];
}

vector<string> fileOperations::listOfEvents() {

	vector<vector<string>> temp = ticketInfo();
	vector<string> eventList;

	for (int i = 0; i < temp[0].size(); i++) {
		eventList.push_back(temp[0][i]);
	}
	return temp[0];
}

vector<string> fileOperations::allUserInfo(string requestedName) {

	ifstream stream(accountsFile);
	string username;
	string type;
	string credit;
	vector<string> foundInfo;

	while (stream >> username >> type >> credit) {	
		if (username == requestedName) {
			foundInfo.push_back(username);
			foundInfo.push_back(type);
			foundInfo.push_back(credit);
			break;
		}
	}
	stream.close();
	return foundInfo;
}

vector<string> fileOperations::allEventInfo(string requestedTitle, string requestedName, vector<vector<string>> allInfo) {

	ifstream stream(availableTicketsFile);
	string eventTitle;
	string sellerName;
	string numOfTickets;
	string pricePerTicket;
	vector<string> foundInfo;

	for (int i = 0; i < allInfo.size(); i++) {
		for (int j = 0; j < allInfo[i].size(); j++) {
			if (allInfo[0][j] == requestedTitle) {
				if (allInfo[1][j] == requestedName) {
					eventTitle = allInfo[0][j];
					sellerName = allInfo[1][j];
					numOfTickets = allInfo[2][j];
					pricePerTicket = allInfo[3][j];
				}
			} 
		}
	}

	//cout << eventTitle << "|" << sellerName << "|" << numOfTickets << "|" << pricePerTicket << endl;
	foundInfo.push_back(eventTitle);
	foundInfo.push_back(sellerName);
	foundInfo.push_back(numOfTickets);
	foundInfo.push_back(pricePerTicket);

	stream.close();
	return foundInfo;
}

//Daily Transaction for create, delete, addCredit and end-of-session
string fileOperations::cdaeTransactions(string tCode, string username, string userType, string credit) {

	string officialString;
	string zeros;
	int space;
	officialString = tCode + " ";
	officialString += username;
	space = 15 - username.length();
	if (space != 0) {
		for (int i = 0; i < space; i++) {
			officialString += " ";
		}
	}

	officialString += " " + userType + " ";
	space = 9 - credit.length();
	for (int i = 0; i < space; i++) {
		zeros += "0";
	}

	if (space != 0) {
		officialString += zeros + credit;
	}
	else {
		officialString += credit;
	
	}
	return officialString;
}

//Daily Transaction for refund
string fileOperations::rTransactions(string tCode, string buyerName, string sellerName, string credit) {

	string officialString;
	int space;
	string zeros;

	officialString = tCode + " ";
	officialString += buyerName;
	space = 15 - buyerName.length();
	if (space != 0) {
		for (int i = 0; i < space; i++) {
			officialString += " ";
		}
	}

	officialString += " ";
	officialString += sellerName;
	space = 15 - sellerName.length();
	if (space != 0) {
		for (int i = 0; i < space; i++) {
			officialString += " ";
		}
	}

	officialString += " ";
	space = 9 - credit.length();
	for (int i = 0; i < space; i++) {
		zeros += "0";
	}

	if (space != 0) {
		officialString += zeros + credit;
	}
	else {
		officialString += credit;
	}
	return officialString;
}

//Daily transaction for sell and buy
string fileOperations::sbTransactions(string code, string eventName, string sellerName, string numTickets, string price) {

	string officialString;
	int space;
	string zeros;

	officialString = code + " ";
	officialString += eventName;
	space = 25 - eventName.length();
	if (space != 0) {
		for (int i = 0; i < space; i++) {
			officialString += " ";
		}
	}

	officialString += " ";
	officialString += sellerName;
	space = 15 - sellerName.length();
	if (space != 0) {
		for (int i = 0; i < space; i++) {
			officialString += " ";
		}
	}

	officialString += " ";
	space = 3 - numTickets.length();
	for (int i = 0; i < space; i++) {
		zeros += "0";
	}

	if (space != 0) {
		officialString += zeros + numTickets;
	}
	else {
		officialString += numTickets;
	}

	space = 6 - numTickets.length();
	for (int i = 0; i < space; i++) {
		zeros += "0";
	}

	if (space != 0) {
		officialString += zeros + price;
	}
	else {
		officialString += price;
	}
	return officialString;
}


string fileOperations::clearWhite(string word) {

	int j;
	for(int i = word.length(); i >= 0; i--) {
		j = i;
		if(word[i-1] == ' ') {
			word.erase(j, 1);
		}
		else {
			word.erase(j, 1);
			break;
		}
	}
	return word;
}