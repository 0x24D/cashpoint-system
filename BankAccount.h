#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"

#include <fstream>
using namespace std;


class BankAccount {
public:
    //constructors & destructor
	BankAccount();
    BankAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList);
    virtual ~BankAccount();

	//getter (assessor) functions
    const string getAccountNumber() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
    bool	isEmptyTransactionList() const;
	//other operations
	const string prepareFormattedStatement() const;
    void recordDeposit(double amount);
	void recordTransferOut(const double& amount, const string& tAN);
	void recordTransferIn(const double& amount, const string& aAN);
	virtual double maxWithdrawalAllowed() const = 0;
	bool canWithdraw(double amount) const;
	void recordWithdrawal(double amount);
	void recordDeleteTransactionsUpToDate(const Date& d);
	void produceAllDepositTransactions(string& str, double& total) const;
	void produceNMostRecentTransactions(const int& num, string& str, double& total) const;
	template <typename T>
	void produceTransactionsForSearchCriterion(const T& t, int& n, string& str) const{
		TransactionList trl(transactions_.getTransactionsForSearchCriterion(t));
		n = trl.size();
		str = trl.toFormattedString();
	}
	void produceTransactionsUpToDate(const Date& d, int& n, string& str) const;
	static const string accountType(char n);
	void readInBankAccountFromFile(const string& fileName);
	void storeBankAccountInFile(const string& fileName) const;
	//functions to put data into and get data from streams
	ostream& putDataInStream(ostream& os) const;
	virtual ostream& putAccountDetailsInStream(ostream& os) const = 0;
	istream& getDataFromStream(istream& is);
	virtual istream& getAccountDataFromStream(istream& is) = 0;
	bool canTransferOut(const double& amount) const;
	virtual bool canTransferIn(const double& amount) const = 0;
	const string prepareFormattedMiniAccountDetails() const;
	const string prepareFormattedTransactionList() const;
	virtual const string prepareFormattedAccountDetails() const;
private:
    //data items
    string accountNumber_;
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;
	//support functions
	void updateBalance(double amount);
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator

#endif
