#include "UserInterface.h" 

//---------------------------------------------------------------------------
//UserInterface: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

void UserInterface::wait() const {
	char ch;
	cout << "\n\nPress RETURN to go back to menu\n";
	cin.get(ch);
	cin.get(ch);
}
int UserInterface::readInCardIdentificationCommand() const {
    showCardIdentificationMenu();
    return (readInCommand());
}
void UserInterface::showCardIdentificationMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      _______CARD IDENTIFICATION MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0           Quit CashPoint application";
	cout << "\n       1              Enter your card details";
	cout << "\n      ________________________________________";
}
int UserInterface::readInAccountProcessingCommand() const{
    showAccountProcessingMenu();
    return (readInCommand());
}
void UserInterface::showAccountProcessingMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      ________ACCOUNT PROCESSING MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0 End account processing & remove card";
	cout << "\n       1                      Display balance";
	cout << "\n       2                Withdraw from account";
	cout << "\n       3                 Deposit into account";
	cout << "\n       4                       Show statement";
	cout << "\n       5                    Show all deposits";
	cout << "\n       6                  Show mini statement";
	cout << "\n       7                  Search Transactions  //TO BE IMPLEMENTED FOR Task 1c";
	cout << "\n       8    Clear all transactions up to date  //TO BE IMPLEMENTED FOR Task 1c";
	cout << "\n       9                 Show Funds Available  //TO BE IMPLEMENTED FOR Task 1c";
	cout << "\n       10         Transfer to another account  //TO BE IMPLEMENTED FOR Task 1c";
	cout << "\n         ________________________________________";
}

const string UserInterface::readInCardToBeProcessed() const {
	string cardNumber;
	cout << "\n SELECT THE CARD ...\n";
	cout << "   CARD NUMBER:  ";         //ask for card number
    cin >> cardNumber;
    cout << "\n=========================================";
	return cardNumber;
}

void UserInterface::showValidateCardOnScreen(int validCode, const string& cardNumber) const {
    switch(validCode)
    {
    	case VALID_CARD:		//card valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
			cout << "\nTHE CARD (NUMBER: " << cardNumber << ") EXIST!";
            break;
    	case UNKNOWN_CARD:		//card does not exist
			cout << "\nERROR: INVALID CARD\n"
				<< "\nTHE CARD (NUMBER: " << cardNumber << ") DOES NOT EXIST!";
            break;
    	case EMPTY_CARD:		//account exists but is not accessible with that card
        	cout << "\nERROR: EMPTY CARD"
				<< "\nTHE CARD (NUMBER: " << cardNumber << ") DOES NOT LINK TO ANY ACCOUNT!";
             break;
    }
}

void UserInterface::showCardOnScreen(const string& cardDetails) const {
    cout << "\n=========================================";
    cout << "\n________ CARD DETAILS ___________________";
	cout << cardDetails;
    cout << "\n________ END CARD DETAILS _______________";
    cout << "\n=========================================";
}

const string UserInterface::readInAccountToBeProcessed() const {
    cout << "\n SELECT THE ACCOUNT ...\n";
	cout << "   ACCOUNT NUMBER:  ";	//ask for account number
	string accountNumber;
	cin >> accountNumber;
    cout << "\n=========================================";
    //create account file name
	return accountNumber;
}

void UserInterface::showValidateAccountOnScreen(int validCode, const string& accNum) const {
	switch(validCode)
    {
    	case VALID_ACCOUNT:		//account valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
        	cout << "\nTHE ACCOUNT (NUMBER: " << accNum << ") IS NOW OPEN!";
            break;
    	case UNKNOWN_ACCOUNT:		//account does not exist
        	cout << "\nERROR: INVALID ACCOUNT"
                 << "\nTHE ACCOUNT (NUMBER: " << accNum << ") DOES NOT EXIST!";
            break;
    	case UNACCESSIBLE_ACCOUNT:		//account exists but is not accessible with that card
        	cout << "\nERROR: INVALID ACCOUNT"
             	 << "\nTHE ACCOUNT (NUMBER: " << accNum << ") IS NOT ACCESSIBLE WITH THIS CARD!";
            break;
		case UNKNOWN_ACCOUNT_TYPE:		//account type not recognised
			cout << "\nERROR: INVALID ACCOUNT"
				<< "\nTHE ACCOUNT (NUMBER: " << accNum << ") IS NOT A RECOGNISED TYPE OF ACCOUNT!";
			break;
	}
}

//input functions

double UserInterface::readInWithdrawalAmount() const {
    //ask for the amount to withdraw
    cout << "\nAMOUNT TO WITHDRAW: \234" ;
	return (readInPositiveAmount());
}
double UserInterface::readInDepositAmount() const {
    //ask for the amount to deposit
    cout << "\nAMOUNT TO DEPOSIT: \234" ;
	return (readInPositiveAmount());
}
int UserInterface::readInNumberOfTransactions() const{
	cout << "\n NUMBER OF TRANSACTIONS: ";
	return (readInPositiveNumber());
}
//output functions

void UserInterface::showProduceBalanceOnScreen(double balance) const {
	cout << fixed << setprecision(2) << setfill(' ');
    cout << "\nTHE CURRENT BALANCE IS: \234" << setw(12) << balance;//display balance
}
void UserInterface::showWithdrawalOnScreen(bool trAuthorised, double withdrawnAmount) const {
    if (trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!: \n\234"
			 << setw(0) << withdrawnAmount
             << " WITHDRAWN FROM ACCOUNT";
    else //not enough money
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showDepositOnScreen(bool trAuthorised, double depositAmount) const {
    if (trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!:\n\234"
			 << setw(0) << depositAmount
             << " DEPOSITED INTO ACCOUNT";
    else //too much to deposit
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showStatementOnScreen(const string& statement) const {
    cout << "\nPREPARING STATEMENT...";
    cout << "\n________ ACCOUNT STATEMENT _____";
	cout << statement;
    cout << "\n________ END ACCOUNT STATEMENT _____";
}
void UserInterface::showMiniStatementOnScreen(const bool& isEmpty, const double& total, const string& str) const {
	if (isEmpty)
		cout << "\nNO TRANSACTIONS IN BANK ACCOUNT";
	else{
		cout << "\nRECENT TRANSACTIONS REQUESTED AT " << Time::currentTime() << " ON " << Date::currentDate();
		cout << "\n________ ACCOUNT STATEMENT _____";
		cout << str;
		cout << "TOTAL CUMULATED AMOUNT: \234" << total;
		cout << "\n________ END ACCOUNT STATEMENT _____";
	}
}

void UserInterface::showDepositOnScreen(bool noTransaction, const string& str, double total) const {
	if (noTransaction)
		cout << "NO TRANSACTIONS IN BANK ACCOUNT";
	else {
		cout << "ALL DEPOSIT TRANSACTIONS REQUESTED AT " << Time::currentTime() << " ON " << Date::currentDate();
		cout << "\n" << str;
		cout << fixed << setprecision(2) << setfill(' ');
		cout << "\n TOTAL AMOUNT: \234" << total;
	}
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void UserInterface::showWelcomeScreen() const {
	cout << "\n\n\n             _____WELCOME TO THE ATM_____";
}
void UserInterface::showByeScreen() const {
    cout << "\n\n\n________________NEXT CUSTOMER...\n\n";
}
int UserInterface::readInCommand() const{
	int com;
	cout << "\n          ENTER YOUR COMMAND: ";
	cin >> com;
	return com;
}
void UserInterface::showErrorInvalidCommand() const {
	cout << "\nINVALID COMMAND CHOICE, TRY AGAIN";
}
double UserInterface::readInPositiveAmount() const {
    double amount;
	cin >> amount;
	while (amount <= 0.0)
    {
	    cout << "\nAMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ";
		cin >> amount;
	}
    return amount;
}
int UserInterface::readInPositiveNumber() const {
	int number;
	cin >> number;
	while (number <= 0)
	{
		cout << "\nNUMBER SHOULD BE A POSITIVE NUMBER, TRY AGAIN: ";
		cin >> number;
	}
	return number;
}