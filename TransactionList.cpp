#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction(const Transaction& tr) {
    listOfTransactions_.push_front(tr);
}
const Transaction TransactionList::newestTransaction() const {
    return (listOfTransactions_.front());
}
const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist(*this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
    listOfTransactions_.pop_front();
}
void TransactionList::deleteGivenTransaction(const Transaction& tr) { //TODO: never called
    //listOfTransactions_.deleteOne(tr);
}
//void TransactionList::deleteTransactionsUpToDate(const Date& d){
//	TransactionList temp(*this);
//	TransactionList ret;
//	while (temp.size() > 0){
//		if (!((temp.newestTransaction()).getDate() < d))
//			ret.addNewTransaction(temp.newestTransaction());
//		temp.deleteFirstTransaction();
//	}
//	(*this) = ret;
//}

void TransactionList::deleteTransactionsUpToDate(const Date& d){
	TransactionList ret(*this);
	deleteTransactionsHelper(d, ret);
	(*this) = ret;
}

int TransactionList::size() const {
    return (listOfTransactions_.size());
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
	return total;
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

const TransactionList TransactionList::getTransactionsForSearchCriterion(const double& a) const{
	TransactionList temp(*this);
	TransactionList ret;
	while (temp.size() > 0){
		if ((temp.newestTransaction()).getAmount() == a)
			ret.addNewTransaction(temp.newestTransaction());
		temp.deleteFirstTransaction();
	}
	return ret;
}

const TransactionList TransactionList::getTransactionsForSearchCriterion(const string& title) const{
	TransactionList temp(*this);
	TransactionList ret;
	while (temp.size() > 0){
		if ((temp.newestTransaction()).getTitle() == title)
			ret.addNewTransaction(temp.newestTransaction());
		temp.deleteFirstTransaction();
	}
	return ret;
}
const TransactionList TransactionList::getTransactionsForSearchCriterion(const Date& d) const{
	TransactionList temp(*this);
	TransactionList ret;
	while (temp.size() > 0){
		if ((temp.newestTransaction()).getDate() == d)
			ret.addNewTransaction(temp.newestTransaction());
		temp.deleteFirstTransaction();
	}
	return ret;
}

//const TransactionList TransactionList::getTransactionsUpToDate(const Date& d) const{
//	TransactionList temp(*this);
//	TransactionList ret;
//	while (temp.size() > 0){
//		if ((temp.newestTransaction()).getDate() < d)
//			ret.addNewTransaction(temp.newestTransaction());
//		temp.deleteFirstTransaction();
//	}
//	return ret;
//}

const TransactionList TransactionList::getTransactionsUpToDate(const Date& d) const{
	TransactionList trl(*this);
	return getTransactionsHelper(d, trl);
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
		listOfTransactions_.push_back(aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}

//recursion helpers

TransactionList TransactionList::getTransactionsHelper(const Date& d, const TransactionList& trl) const{
	if (trl.size() == 0)
		return trl;
	else{
		TransactionList ret = getTransactionsHelper(d, trl.olderTransactions());
		if ((trl.newestTransaction().getDate()) < d)
			ret.addNewTransaction(trl.newestTransaction());
		return ret;
	}
}

void TransactionList::deleteTransactionsHelper(const Date& d, TransactionList& trl) const{
	TransactionList ret;
	if (trl.size() == 0)
		return;
	else{
		Date tranDate = trl.newestTransaction().getDate();
		while (!(tranDate < d)){
			ret.addNewTransaction(trl.newestTransaction());
			trl.deleteFirstTransaction();
			tranDate = trl.newestTransaction().getDate();
			//tranDate = (trl.olderTransactions()).newestTransaction().getDate();
		}
		trl.deleteFirstTransaction();
		deleteTransactionsHelper(d, trl);
		while (ret.size() != 0){
			trl.addNewTransaction(ret.newestTransaction());
			ret.deleteFirstTransaction();
		}
	}
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