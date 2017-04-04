#include "ChildAccount.h"

ChildAccount::ChildAccount()
	: SavingsAccount(), minimumPaidIn_(0.0), maximumPaidIn_(0.0)
{}
ChildAccount::ChildAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& minBalance, const double& minPaidIn, const double& maxPaidIn)
	: SavingsAccount(acctNum, cD, b, trList, minBalance), minimumPaidIn_(minPaidIn), maximumPaidIn_(maxPaidIn)
{}
ChildAccount::~ChildAccount()
{}
double ChildAccount::getMaximumPaidIn() const {
	return maximumPaidIn_;
}

double ChildAccount::getMinimumPaidIn() const {
	return minimumPaidIn_;
}

double ChildAccount::maxWithdrawalAllowed() const {
	//return borrowable amount
	return (0.0);
}

ostream& ChildAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << minimumPaidIn_ << "\n";
	os << minimumPaidIn_ << "\n";
	return os;
}

istream& ChildAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	SavingsAccount::getAccountDataFromStream(is);
	is >> minimumPaidIn_;
	is >> maximumPaidIn_;
	return is;
}

const string ChildAccount::prepareFormattedAccountDetails() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType(getAccountNumber()[0]) << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << getAccountNumber();									//display account number
	os << "\nCREATION DATE:   " << (getCreationDate()).toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << getBalance();	//display balance
	os << "\nMINIMUM BALANCE:         \234" << setw(10) << getMinimumBalance(); //display minimum balance
	os << "\nMINIMUM PAID IN:         \234" << setw(10) << minimumPaidIn_; //display minimum balance
	os << "\nMAXIMUM PAID IN:         \234" << setw(10) << maximumPaidIn_; //display minimum balance
	return os.str();
}

bool ChildAccount::canTransferIn(const double& amount) const {
	return (maximumPaidIn_ >= amount);
}