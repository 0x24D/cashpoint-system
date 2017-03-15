#include "CashPoint.h"

//---------------------------------------------------------------------------
//CashPoint: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CashPoint::CashPoint()
	: p_theActiveAccount_(nullptr), p_theCashCard_(nullptr)
{ }

CashPoint::~CashPoint()
{
	assert(p_theActiveAccount_ == nullptr);
	assert(p_theCashCard_ == nullptr);
}

//____other public member functions

void CashPoint::activateCashPoint() {
	int command;
	theUI_.showWelcomeScreen();
    command = theUI_.readInCardIdentificationCommand();
	while (command != QUIT_COMMAND)
    {
		performCardCommand(command);
	    theUI_.showByeScreen();
		command = theUI_.readInCardIdentificationCommand();
	}

}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void CashPoint::performCardCommand(int option) {
	switch (option)
	{
		case 1:
		{
			string cashCardNum(theUI_.readInCardToBeProcessed());
			string cashCardFilename(FILEPATH + "card_" + cashCardNum + ".txt");	//read in card name & produce cashcard filename
			int validCardCode(validateCard(cashCardFilename));		//check valid card
			theUI_.showValidateCardOnScreen(validCardCode, cashCardNum);
			if (validCardCode == VALID_CARD) //valid card
			{
				//dynamically create a cash card and store card data
				activateCashCard(cashCardFilename);
				//display card data with available accounts
				string s_card(p_theCashCard_->toFormattedString());
				theUI_.showCardOnScreen(s_card);
				//process all request for current card (& bank accounts)
				processOneCustomerRequests();
				//free memory space used by cash card
				releaseCashCard();
			}
			break;
		}
		default:theUI_.showErrorInvalidCommand();
	}
}

int CashPoint::validateCard(const string& filename) const {
	//check that the card exists (valid)
	if (!canOpenFile(filename))   //invalid card
        return UNKNOWN_CARD;
    else    
		//card empty (exist but no bank account listed on card)
		if (!accountsListedOnCard(filename))
			return EMPTY_CARD;
		else
			//card valid (exists and linked to at least one bank account)
			return VALID_CARD;
}

int CashPoint::validateAccount(const string& filename) const {
//check that the account is valid 
//NOTE: MORE WORK NEEDED here in case of transfer
	if (!canOpenFile(filename))
		//account does not exist
		return UNKNOWN_ACCOUNT;
	else
		//unaccessible account (exist but not listed on card)
		if (!p_theCashCard_->onCard(filename))
			return UNACCESSIBLE_ACCOUNT;
		else
			//account type not recognised
			if (BankAccount::accountType(checkAccountType(filename)) == "UNKNOWN")
				return UNKNOWN_ACCOUNT_TYPE;
			else
				//account valid (exists and accessible)
       			return VALID_ACCOUNT;
}

void CashPoint::processOneCustomerRequests() {
//process from one account
    //select active account and check that it is valid
	string anAccountNumber(theUI_.readInAccountToBeProcessed());
	string bankAccountFilename(FILEPATH + "account_" + anAccountNumber + ".txt");
	int validAccountCode(validateAccount(bankAccountFilename));  //check valid account
    theUI_.showValidateAccountOnScreen(validAccountCode, anAccountNumber);
	if (validAccountCode == VALID_ACCOUNT) //valid account: exists, accessible with card and not already open
	{
       	//dynamically create a bank account to store data from file
		p_theActiveAccount_ = activateBankAccount(bankAccountFilename);
		//process all request for current card (& bank accounts)
    	processOneAccountRequests();
		//store new state of bank account in file & free bank account memory space
		p_theActiveAccount_ = releaseBankAccount(p_theActiveAccount_, bankAccountFilename);
	}
}

void CashPoint::processOneAccountRequests() {
    int option;
	//select option from account processing menu
  	option = theUI_.readInAccountProcessingCommand();
	while (option != QUIT_COMMAND)
	{
		performAccountProcessingCommand(option);   //process command for selected option
		theUI_.wait();
        option = theUI_.readInAccountProcessingCommand();   //select another option
	}
}
void CashPoint::performAccountProcessingCommand(int option) {
	switch (option)
	{
		case 1:	m1_produceBalance();
				break;
		case 2: m2_withdrawFromBankAccount();
 				break;
		case 3:	m3_depositToBankAccount();
				break;
		case 4:	m4_produceStatement();
				break;
		case 5: m5_showAllDepositsTransactions();
				break;
		default:theUI_.showErrorInvalidCommand();
	}
}
//------ menu options
//---option 1
void CashPoint::m1_produceBalance() const {
	assert(p_theActiveAccount_ != nullptr);
	double balance(p_theActiveAccount_->getBalance());
	theUI_.showProduceBalanceOnScreen(balance);
}
//---option 2
void CashPoint::m2_withdrawFromBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToWithdraw(theUI_.readInWithdrawalAmount());
    bool transactionAuthorised(p_theActiveAccount_->canWithdraw(amountToWithdraw));
    if (transactionAuthorised)
    {   //transaction is accepted: money can be withdrawn from account
        p_theActiveAccount_->recordWithdrawal(amountToWithdraw);
    }   //else do nothing
    theUI_.showWithdrawalOnScreen(transactionAuthorised, amountToWithdraw);
}
//---option 3
void CashPoint::m3_depositToBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToDeposit(theUI_.readInDepositAmount());
    p_theActiveAccount_->recordDeposit(amountToDeposit);
    theUI_.showDepositOnScreen(true, amountToDeposit);
}
//---option 4
void CashPoint::m4_produceStatement() const {
	assert(p_theActiveAccount_ != nullptr);
	theUI_.showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
}
//---option 5
void CashPoint::m5_showAllDepositsTransactions() const {
	assert(p_theActiveAccount_ != nullptr);
	bool noTransaction(p_theActiveAccount_->isEmptyTransactionList());
	string str;
	double total(0.0);
	if (!noTransaction)
		p_theActiveAccount_->produceAllDepositTransactions(str, total);
	theUI_.showDepositOnScreen(noTransaction, str, total);
}

//------private file functions

bool CashPoint::canOpenFile(const string& filename) const {
//check if a file already exist
	ifstream inFile;
	inFile.open(filename.c_str(), ios::in); 	//open file
	//if does not exist fail() return true
    return (!inFile.fail());	//close file automatically when inFile goes out of scope
}


bool CashPoint::accountsListedOnCard(const string& cashCardFileName) const {
//check that card is linked with account data
	ifstream inFile;
	inFile.open(cashCardFileName.c_str(), ios::in); 	//open file
	assert(!inFile.fail()); //file should exist at this point 
	//check that it contains some info in addition to card number
	string temp;
	inFile >> temp; //read card number
	inFile >> temp;	//ready first account data or eof if end of file found
	return (!inFile.eof());
}

void CashPoint::activateCashCard(const string& filename) {
//dynamically create a cash card to store data from file
    //effectively create the cash card instance with the data
	p_theCashCard_ = new CashCard;
	assert(p_theCashCard_ != nullptr);
	p_theCashCard_->readInCardFromFile(filename);
}

void CashPoint::releaseCashCard() {
//release the memory allocated to the dynamic instance of a CashCard
	delete p_theCashCard_;
	p_theCashCard_ = nullptr;
}
//static member function
char CashPoint::checkAccountType(const string& filename)  {
    //(simply) identify type/class of account from the account number
    //start with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return filename[13]; //13th char from the filename ("data/account_101.txt")
}

BankAccount* CashPoint::activateBankAccount(const string& filename) {
	//check the type of the account (already checked for validity)
	char accType(checkAccountType(filename));
    //effectively create the active bank account instance of the appropriate class
	//and store the appropriate data read from the file
	BankAccount* p_BA(nullptr);
	switch(accType)
    {
     	case BANKACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
     		p_BA = new BankAccount;    //points to a BankAccount object
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename); //read account details from file
			break;
    }
	//use dynamic memory allocation: the bank account created will have to be released in releaseBankAccount
	return p_BA;
}

BankAccount* CashPoint::releaseBankAccount(BankAccount* p_BA, string filename) {
//store (possibly updated) data back in file
	assert(p_BA != nullptr);
	p_BA->storeBankAccountInFile(filename);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}
