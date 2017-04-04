#include "CurrentAccount.h"

CurrentAccount::CurrentAccount()
	: BankAccount(), overdraftLimit_(0.0)
{}
CurrentAccount::CurrentAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& overdraftLimit)
	: BankAccount(acctNum, cD, b, trList), overdraftLimit_(overdraftLimit)
{}
CurrentAccount::~CurrentAccount()
{}

double CurrentAccount::getOverdraftLimit() const{
	return overdraftLimit_;
}

double CurrentAccount::maxWithdrawalAllowed() const {
	//return borrowable amount
	return (getBalance() + overdraftLimit_);
}
ostream& CurrentAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << overdraftLimit_ << "\n";
	return os;
}
istream& CurrentAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> overdraftLimit_;					//get overdraft limit
	return is;
}

const string CurrentAccount::prepareFormattedAccountDetails() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType(getAccountNumber()[0]) << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << getAccountNumber();									//display account number
	os << "\nCREATION DATE:   " << (getCreationDate()).toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << getBalance();	//display balance
	os << "\nOVERDRAFT LIMIT:         \234" << setw(10) << overdraftLimit_; //display overdraft limit
	os << "\nTOTAL AVAILABLE FUNDS:         \234" << setw(10) << maxWithdrawalAllowed();
	return os.str();
}

bool CurrentAccount::canTransferIn(const double& amount) const {
	return true;
}