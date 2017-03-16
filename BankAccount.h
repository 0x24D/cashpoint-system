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
    ~BankAccount();

	//getter (assessor) functions
    const string getAccountNumber() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
    bool	isEmptyTransactionList() const;

	//other operations
	const string prepareFormattedStatement() const;

    void recordDeposit(double amount);

	double maxWithdrawalAllowed() const;
	bool canWithdraw(double amount) const;
	void recordWithdrawal(double amount);
	void produceAllDepositTransactions(string& str, double& total) const;
	void produceNMostRecentTransactions(const int& num, string& str, double& total) const;

	static const string accountType(char n);
	void readInBankAccountFromFile(const string& fileName);
	void storeBankAccountInFile(const string& fileName) const;
	//functions to put data into and get data from streams
	ostream& putDataInStream(ostream& os) const;
	ostream& putAccountDetailsInStream(ostream& os) const;
	istream& getDataFromStream(istream& is);
	istream& getAccountDataFromStream(istream& is);

	const string prepareFormattedMiniAccountDetails() const;
	const string prepareFormattedTransactionList() const;

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
