#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction(const Transaction& tr) {
    listOfTransactions_.addInFront(tr);
}
const Transaction TransactionList::newestTransaction() const {
    return (listOfTransactions_.first());
}
const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist(*this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
    listOfTransactions_.deleteFirst();
}
void TransactionList::deleteGivenTransaction(const Transaction& tr) {
    listOfTransactions_.deleteOne(tr);
}
int TransactionList::size() const {
    return (listOfTransactions_.length());
}

const TransactionList TransactionList::getAllDepositTransactions() const{
	TransactionList temp(*this);
	TransactionList ret;

	while (temp.size() > 0){
		if (temp.newestTransaction().getAmount() >= 0)
			ret.addNewTransaction(temp.newestTransaction());
		temp.deleteFirstTransaction();
	}
	return ret;
}

double TransactionList::getTotalTransactions() const{
	TransactionList temp(*this);
	double total(0.0);
	while (temp.size() > 0){
		total += temp.newestTransaction().getAmount();
		temp.deleteFirstTransaction();
	}
	return total; // TODO: NOT FINISHED
}

const TransactionList TransactionList::getMostRecentTransactions(const int& num) const{
	TransactionList temp(*this);
	TransactionList ret;
	for (int i = 0; i < num; i++)
		if (temp.size() != 0){
			ret.addNewTransaction(temp.newestTransaction());
			temp.deleteFirstTransaction();
		}
	return ret;
}

const string TransactionList::toFormattedString() const {
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os_transactionlist << tempTrList.newestTransaction().toFormattedString() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return (os_transactionlist.str());
}

ostream& TransactionList::putDataInStream(ostream& os) const {
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return os;
}
istream& TransactionList::getDataFromStream(istream& is) {
//read in (unformatted) transaction list from input stream
	Transaction aTransaction;
	is >> aTransaction;	//read first transaction
	while (is) 	//while not end of file
	{
		listOfTransactions_.addAtEnd(aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const TransactionList& aTransactionList) {
    return (aTransactionList.putDataInStream(os));
}
istream& operator>>(istream& is, TransactionList& aTransactionList) {
	return (aTransactionList.getDataFromStream(is));
}
