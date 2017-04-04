#ifndef ChildAccountH
#define ChildAccountH

//---------------------------------------------------------------------------
//ChildAccount: class declaration
//---------------------------------------------------------------------------
#include "SavingsAccount.h"
using namespace std;

class ChildAccount : public SavingsAccount {
public:

	ChildAccount();
	ChildAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& minBalance, const double& minPaidIn, const double& maxPaidIn);
	virtual ~ChildAccount();
	double getMaximumPaidIn() const;
	double getMinimumPaidIn() const;
	virtual double maxWithdrawalAllowed() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual bool canTransferIn(const double& amount) const;
	virtual const string prepareFormattedAccountDetails() const;
private:
	double minimumPaidIn_;
	double maximumPaidIn_;
};

#endif