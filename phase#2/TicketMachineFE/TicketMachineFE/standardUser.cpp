//Function Definitions

#include "standardUser.h"



//constructor
standardUser::standardUser() {

	double credit = 0.00;
	ifstream userAccounts;


}

//overloaded constructor to set up the username, account type as well as credit amount
standardUser::standardUser(string user, string type, double credit) {


	currentUsername = user;
	accountType = type;
	credit = credit;

}

//deconstructor
standardUser::~standardUser() {


}

//Getter Functions

//get username
string standardUser::getcurrent_username() {

	return currentUsername;

}


//get account type
string standardUser::getaccount_type() {

	return accountType;

}

//get credit
double standardUser::getCredit() {

	return credit;

}



//Mutator Functions

//set credit
void standardUser::setCredit(double newAmount) {

	credit = newAmount;

}
