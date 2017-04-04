#ifndef CurrentAccountH
#define CurrentAccountH

//---------------------------------------------------------------------------
//CurrentAccount: class declaration
//---------------------------------------------------------------------------
#include "BankAccount.h"
using namespace std;

class CurrentAccount : public BankAccount {
public:
	CurrentAccount();
	CurrentAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& overdraftLimit);
	virtual ~CurrentAccount();
	double getOverdraftLimit() const;
	virtual double maxWithdrawalAllowed() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual bool canTransferIn(const double& amount) const;
	virtual const string prepareFormattedAccountDetails() const;
private:
	double overdraftLimit_;
};
#endif