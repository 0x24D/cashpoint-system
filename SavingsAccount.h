#ifndef SavingsAccountH
#define SavingsAccountH

//---------------------------------------------------------------------------
//SavingsAccount: class declaration
//---------------------------------------------------------------------------
#include "BankAccount.h"
using namespace std;


class SavingsAccount : public BankAccount {
public:
	SavingsAccount();
	SavingsAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& minBalance);
	virtual ~SavingsAccount();
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	double getMinimumBalance() const;
	virtual const string prepareFormattedAccountDetails() const;
private:
	double minimumBalance_;
};

#endif