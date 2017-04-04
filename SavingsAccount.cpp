#include "SavingsAccount.h"

SavingsAccount::SavingsAccount()
	: BankAccount(), minimumBalance_(0.0)
{}
SavingsAccount::SavingsAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& minBalance)
	: BankAccount(acctNum, cD, b, trList), minimumBalance_(minBalance)
{}
SavingsAccount::~SavingsAccount()
{}

double SavingsAccount::getMinimumBalance() const{
	return minimumBalance_;
}
istream& SavingsAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> minimumBalance_;					//get overdraft limit
	return is;
}

ostream& SavingsAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << minimumBalance_ << "\n";
	return os;
}

const string SavingsAccount::prepareFormattedAccountDetails() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType(getAccountNumber()[0]) << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << getAccountNumber();									//display account number
	os << "\nCREATION DATE:   " << (getCreationDate()).toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << getBalance();	//display balance
	os << "\nMINIMUM BALANCE:         \234" << setw(10) << minimumBalance_; //display overdraft limit
	return os.str();
}
