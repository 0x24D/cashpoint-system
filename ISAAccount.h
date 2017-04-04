#ifndef ISAAccountH
#define ISAAccountH

//---------------------------------------------------------------------------
//ISAAccount: class declaration
//---------------------------------------------------------------------------
#include "SavingsAccount.h"
using namespace std;


class ISAAccount : public SavingsAccount {
public:
	ISAAccount();
	ISAAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList, const double& minBalance, const double& maxYearlyDeposit, const double& currYearlyDeposit, const Date& endOfDepositPeriod);
	virtual ~ISAAccount();
	double getMaximumYearlyDeposit() const;
	double getCurrentYearlyDeposit() const;
	Date getEndDepositPeriod() const;
	virtual double maxWithdrawalAllowed() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	virtual bool canTransferIn(const double& amount) const;
	virtual const string prepareFormattedAccountDetails() const;
private:
	double maximumYearlyDeposit_;
	double currentYearlyDeposit_;
	Date endDepositPeriod_;
	void updateCurrentYearlyDeposit(const double& a);
};

#endif