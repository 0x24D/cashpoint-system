#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------

#include <list>
#include "Transaction.h"
#include <cassert> 	// for assert()
#include <sstream>

class TransactionList {
public:
	void   addNewTransaction(const Transaction&);
    const Transaction newestTransaction() const;
    const  TransactionList olderTransactions() const;
    void   deleteFirstTransaction();
    void   deleteGivenTransaction(const Transaction&);
	void   deleteTransactionsUpToDate(const Date& d);
	void   deleteTransactionsUpToDate(const Date& d, TransactionList& trl);
	int    size() const;
	const TransactionList getAllDepositTransactions() const;
	double getTotalTransactions() const;
	const TransactionList getMostRecentTransactions(const int& num) const;
	const TransactionList getTransactionsForSearchCriterion(const double& a) const;
	const TransactionList getTransactionsForSearchCriterion(const string& title) const;
	const TransactionList getTransactionsForSearchCriterion(const Date& d) const;
	const TransactionList getTransactionsUpToDate(const Date& d) const;
	const TransactionList getTransactionsUpToDate(const Date& d, const TransactionList& trl) const;
	const string toFormattedString() const;		//return transactionlist as a (formatted) string
	ostream& putDataInStream(ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream(istream& is);	//receive TransactionList info from an input stream
	TransactionList getTransactionsHelper(const Date& d, const TransactionList& trl) const;
	void deleteTransactionsHelper(const Date& d, TransactionList& trl) const;
private:
    list<Transaction> listOfTransactions_;	//list of transactions
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const TransactionList&);	//insertion operator
istream& operator>>(istream& is, TransactionList& trl); //extraction operator

#endif

