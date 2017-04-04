#include "ISAAccount.h"

ISAAccount::ISAAccount()
	: SavingsAccount(), maximumYearlyDeposit_(0.0), currentYearlyDeposit_(0.0), endDepositPeriod_(Date::currentDate())
{}
ISAAccount::ISAAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& minBalance, const double& maxYearlyDeposit, const double& currYearlyDeposit, const Date& endOfDepositPeriod)
	: SavingsAccount(acctNum, cD, b, trList, minBalance), maximumYearlyDeposit_(maxYearlyDeposit), currentYearlyDeposit_(currYearlyDeposit), endDepositPeriod_(endOfDepositPeriod)
{}
ISAAccount::~ISAAccount()
{}
double ISAAccount::maxWithdrawalAllowed() const {
	//return borrowable amount
	return (getBalance() - getMinimumBalance());
}
ostream& ISAAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << maximumYearlyDeposit_ << "\n";
	os << currentYearlyDeposit_ << "\n";					
	os << endDepositPeriod_ << "\n";
	return os;
}
istream& ISAAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	SavingsAccount::getAccountDataFromStream(is);
	is >> maximumYearlyDeposit_;					//get maximum Yearly Deposit
	is >> currentYearlyDeposit_;					//get current Yearly Deposit
	is >> endDepositPeriod_;						//get end Deposit Period_
	return is;
}

const string ISAAccount::prepareFormattedAccountDetails() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType(getAccountNumber()[0]) << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << getAccountNumber();									//display account number
	os << "\nCREATION DATE:   " << (getCreationDate()).toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << getBalance();	//display balance
	os << "\nMINIMUM BALANCE:         \234" << setw(10) << getMinimumBalance(); //display minimum balance
	os << "\nMAXIMUM YEARLY DEPOSIT:         \234" << setw(10) << maximumYearlyDeposit_; //display maximum yearly deposit
	os << "\nCURRENT YEARLY DEPSOIT:         \234" << setw(10) << currentYearlyDeposit_; //display minimum balance
	os << "\nEND DEPOSIT PERIOD:         " << endDepositPeriod_; //display end of deposit period
	return os.str();
}

double ISAAccount::getMaximumYearlyDeposit() const{
	return maximumYearlyDeposit_;
}
double ISAAccount::getCurrentYearlyDeposit() const{
	return currentYearlyDeposit_;
}
Date ISAAccount::getEndDepositPeriod() const{
	return endDepositPeriod_;
}

void ISAAccount::updateCurrentYearlyDeposit(const double& a)
{
	currentYearlyDeposit_ += a;
}

bool ISAAccount::canTransferIn(const double& amount) const {
	return ((getMaximumYearlyDeposit() - getCurrentYearlyDeposit()) >= amount);
}