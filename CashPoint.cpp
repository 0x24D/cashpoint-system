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
{}

CashPoint::~CashPoint()
{
	assert(p_theActiveAccount_ == nullptr);
	assert(p_theCashCard_ == nullptr);
}

//____other public member functions

void CashPoint::activateCashPoint() {
	int command;
	UserInterface::getInstance()->showWelcomeScreen();
    command = UserInterface::getInstance()->readInCardIdentificationCommand();
	while (command != QUIT_COMMAND)
    {
		performCardCommand(command);
	    UserInterface::getInstance()->showByeScreen();
		command = UserInterface::getInstance()->readInCardIdentificationCommand();
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
			string cashCardNum(UserInterface::getInstance()->readInCardToBeProcessed());
			string cashCardFilename(FILEPATH + "card_" + cashCardNum + ".txt");	//read in card name & produce cashcard filename
			int validCardCode(validateCard(cashCardFilename));		//check valid card
			UserInterface::getInstance()->showValidateCardOnScreen(validCardCode, cashCardNum);
			if (validCardCode == VALID_CARD) //valid card
			{
				//dynamically create a cash card and store card data
				activateCashCard(cashCardFilename);
				//display card data with available accounts
				string s_card(p_theCashCard_->toFormattedString());
				UserInterface::getInstance()->showCardOnScreen(s_card);
				//process all request for current card (& bank accounts)
				processOneCustomerRequests();
				//free memory space used by cash card
				releaseCashCard();
			}
			break;
		}
		default: UserInterface::getInstance()->showErrorInvalidCommand();
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
	if (!canOpenFile(filename)) //cannot open file
		if (!p_theCashCard_->onCard(filename)) //account does not exist
			return UNKNOWN_ACCOUNT;
		else
			return OPEN_ACCOUNT; //account already open
	else//unaccessible account (exist but not listed on card)
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
	string anAccountNumber(UserInterface::getInstance()->readInAccountToBeProcessed());
	string bankAccountFilename(FILEPATH + "account_" + anAccountNumber + ".txt");
	int validAccountCode(validateAccount(bankAccountFilename));  //check valid account
    UserInterface::getInstance()->showValidateAccountOnScreen(validAccountCode, anAccountNumber);
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
  	option = UserInterface::getInstance()->readInAccountProcessingCommand();
	while (option != QUIT_COMMAND)
	{
		performAccountProcessingCommand(option);   //process command for selected option
		UserInterface::getInstance()->wait();
        option = UserInterface::getInstance()->readInAccountProcessingCommand();   //select another option
	}
}

void CashPoint::searchTransactions() const{
	UserInterface::getInstance()->showSearchMenu();
	int opt = UserInterface::getInstance()->readInSearchCommand();
	switch (opt)
	{
	case 1:m7a_showTransactionsForAmount();
		break;
	case 2:m7b_showTransactionsForTitle();
		break;
	case 3:m7c_showTransactionsForDate();
		break;
	default:
		break;
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
		case 6: m6_showMiniStatement();
				break;
		case 7: m7_searchForTransactions();
				break;
		case 8: m8_clearTransactionsUpToDate();
				break;
		case 9: m9_showFundsAvailableOnAllAccounts();
				break;
		case 10: m10_transferCashToAnotherAccount();
				break;
		default:UserInterface::getInstance()->showErrorInvalidCommand();
	}
}

void CashPoint::attemptTransfer(BankAccount* transferAccount) const{
	double transferAmount(UserInterface::getInstance()->readInTransferAmount());
	bool trOutOK(p_theActiveAccount_->canTransferOut(transferAmount));
	bool trInOK(transferAccount->canTransferIn(transferAmount));
	if (trOutOK && trInOK)
		recordTransfer(transferAmount, transferAccount);
	UserInterface::getInstance()->showTransferOnScreen(trOutOK, trInOK, transferAmount);
}




void CashPoint::recordTransfer(const double& transferAmount, BankAccount* transferAccount) const{
	string tAN(transferAccount->getAccountNumber());
	p_theActiveAccount_->recordTransferOut(transferAmount, tAN);
	string aAN(p_theActiveAccount_->getAccountNumber());
	transferAccount->recordTransferIn(transferAmount, aAN);
}

//------ menu options
//---option 1
void CashPoint::m1_produceBalance() const {
	assert(p_theActiveAccount_ != nullptr);
	double balance(p_theActiveAccount_->getBalance());
	UserInterface::getInstance()->showProduceBalanceOnScreen(balance);
}
//---option 2
void CashPoint::m2_withdrawFromBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToWithdraw(UserInterface::getInstance()->readInWithdrawalAmount());
    bool transactionAuthorised(p_theActiveAccount_->canWithdraw(amountToWithdraw));
    if (transactionAuthorised)
    {   //transaction is accepted: money can be withdrawn from account
        p_theActiveAccount_->recordWithdrawal(amountToWithdraw);
    }   //else do nothing
    UserInterface::getInstance()->showWithdrawalOnScreen(transactionAuthorised, amountToWithdraw);
}
//---option 3
void CashPoint::m3_depositToBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToDeposit(UserInterface::getInstance()->readInDepositAmount());
    p_theActiveAccount_->recordDeposit(amountToDeposit);
    UserInterface::getInstance()->showDepositOnScreen(true, amountToDeposit);
}
//---option 4
void CashPoint::m4_produceStatement() const {
	assert(p_theActiveAccount_ != nullptr);
	UserInterface::getInstance()->showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
}
//---option 5
void CashPoint::m5_showAllDepositsTransactions() const {
	assert(p_theActiveAccount_ != nullptr);
	bool noTransaction(p_theActiveAccount_->isEmptyTransactionList());
	string str;
	double total(0.0);
	if (!noTransaction)
		p_theActiveAccount_->produceAllDepositTransactions(str, total);
	UserInterface::getInstance()->showDepositOnScreen(noTransaction, str, total);
}
//---option 6
void CashPoint::m6_showMiniStatement() const{
	assert(p_theActiveAccount_ != nullptr);
	bool isEmpty(p_theActiveAccount_->isEmptyTransactionList());
	string str, mad;
	double total(0.0);
	if (!isEmpty){
		int numTransactions(UserInterface::getInstance()->readInNumberOfTransactions());
		p_theActiveAccount_->produceNMostRecentTransactions(numTransactions, str, total);
		mad = p_theActiveAccount_->prepareFormattedMiniAccountDetails();
	}
	UserInterface::getInstance()->showMiniStatementOnScreen(isEmpty, total, (mad + str));
}
//---option 7
void CashPoint::m7_searchForTransactions() const{
	assert(p_theActiveAccount_ != nullptr);
	bool isEmpty(p_theActiveAccount_->isEmptyTransactionList());
	if (isEmpty)
		UserInterface::getInstance()->showNoTransactionsOnScreen();
	else
		searchTransactions();
}
void CashPoint::m7a_showTransactionsForAmount() const{
	assert(p_theActiveAccount_ != nullptr);
	double a = UserInterface::getInstance()->readInAmount();
	int n;
	string str;
	p_theActiveAccount_->produceTransactionsForSearchCriterion(a, n, str);
	UserInterface::getInstance()->showMatchingTransactionsOnScreen(a, n, str);
}
void CashPoint::m7b_showTransactionsForTitle() const{
	assert(p_theActiveAccount_ != nullptr);
	string title = UserInterface::getInstance()->readInTitle();
	int n;
	string str;
	p_theActiveAccount_->produceTransactionsForSearchCriterion(title, n, str);
	UserInterface::getInstance()->showMatchingTransactionsOnScreen(title, n, str);
}
void CashPoint::m7c_showTransactionsForDate() const{
	assert(p_theActiveAccount_ != nullptr);
	Date date = UserInterface::getInstance()->readInValidDate(p_theActiveAccount_->getCreationDate());
	int n;
	string str;
	p_theActiveAccount_->produceTransactionsForSearchCriterion(date, n, str);
	UserInterface::getInstance()->showMatchingTransactionsOnScreen(date, n, str);
}
//---option 8
void CashPoint::m8_clearTransactionsUpToDate() const{
	assert(p_theActiveAccount_ != nullptr);
	bool isEmpty(p_theActiveAccount_->isEmptyTransactionList());
	Date d;
	int n;
	string str;
	if (!isEmpty){
		Date cd(p_theActiveAccount_->getCreationDate());
		d = UserInterface::getInstance()->readInValidDate(cd);
		p_theActiveAccount_->produceTransactionsUpToDate(d, n, str);
	}
	UserInterface::getInstance()->showTransactionsUpToDateOnScreen(isEmpty, d, n, str);
	if (!isEmpty && !str.empty()){
		bool deletionConfirmed(UserInterface::getInstance()->readInConfirmDeletion());
		if (deletionConfirmed)
			p_theActiveAccount_->recordDeleteTransactionsUpToDate(d);
		UserInterface::getInstance()->showDeletionOfTransactionsUpToDateOnScreen(n, d, deletionConfirmed);
	}
}
//---option 9
void CashPoint::m9_showFundsAvailableOnAllAccounts(){
	assert(p_theActiveAccount_ != nullptr);
	List<string> accts(p_theCashCard_->getAccountsList());
	bool isEmpty(accts.isEmpty());
	string mad("");
	double m(0.0);
	while (!isEmpty){
		string first = FILEPATH + "account_" + accts.first() + ".txt";
		BankAccount* p_acct(activateBankAccount(first));
		m += p_acct->maxWithdrawalAllowed();
		mad += p_acct->prepareFormattedMiniAccountDetails();
		p_acct = releaseBankAccount(p_acct, first);
		accts.deleteFirst();
		isEmpty = accts.isEmpty();
	}
	UserInterface::getInstance()->showFundsAvailableOnScreen(isEmpty, mad, m);
}
//---option 10
void CashPoint::m10_transferCashToAnotherAccount(){
	assert(p_theActiveAccount_ != nullptr);
	string str(p_theCashCard_->toFormattedString());
	UserInterface::getInstance()->showCardOnScreen(str);
	str = UserInterface::getInstance()->readInAccountToBeProcessed();
	char validAccountCode(validateAccount(FILEPATH + "account_" + str + ".txt"));
	UserInterface::getInstance()->showValidateAccountOnScreen(validAccountCode, str);
	if (validAccountCode == 0){
		BankAccount* p_transferAccount(activateBankAccount(FILEPATH + "account_" + str + ".txt"));
		attemptTransfer(p_transferAccount);
		p_transferAccount = releaseBankAccount(p_transferAccount, FILEPATH + "account_" + str + ".txt");
	}
		
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
   //  	case BANKACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
   //  		p_BA = new BankAccount;    //points to a BankAccount object
			//assert(p_BA != nullptr);
			//p_BA->readInBankAccountFromFile(filename); //read account details from file
			//break;
		case CURRENTACCOUNT_TYPE:
			p_BA = new CurrentAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename);
			break;
		/*case SAVINGSACCOUNT_TYPE:
			p_BA = new SavingsAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename);
			break;*/
		case CHILDACCOUNT_TYPE:
			p_BA = new ChildAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename);
			break;
		case ISAACCOUNT_TYPE:
			p_BA = new ISAAccount;
			assert(p_BA != nullptr);
			p_BA->readInBankAccountFromFile(filename);
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

