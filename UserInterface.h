#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Date.h"
#include "Time.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class UserInterface {
public:
    void	showWelcomeScreen() const;
    void	showByeScreen() const;

	int		readInCardIdentificationCommand() const;
	int		readInAccountProcessingCommand() const;

	void	showErrorInvalidCommand() const;
    void	wait() const;
	const string	readInCardToBeProcessed() const;
    void	showValidateCardOnScreen(int validCode, const string& cardNum) const;
	void	showCardOnScreen(const string& cardSt) const;
	const string  readInAccountToBeProcessed() const;
	void	showValidateAccountOnScreen(int valid, const string& acctNum) const;

    double	readInWithdrawalAmount() const;
    double	readInDepositAmount() const;
	int		readInNumberOfTransactions() const;
	int		readInCommand() const; //TODO: using instead of readInSearchCommand()
	double	readInAmount() const;
	string  readInTitle() const;
	Date	readInDate() const;
	Date	readInValidDate(const Date& cd) const;
	bool	readInConfirmDeletion() const;
	double	readInTransferAmount() const;

    void	showProduceBalanceOnScreen(double bal) const;
    void	showDepositOnScreen(bool auth, double deposit) const;
    void	showWithdrawalOnScreen(bool auth, double withdrawal) const;
    void	showStatementOnScreen(const string&) const;
	void	showMiniStatementOnScreen(const bool& isEmpty, const double& total, const string& str) const;
	void	showDepositOnScreen(bool, const string&, double) const;
	void	showNoTransactionsOnScreen() const;
	void	showSearchMenu() const;
	void	showMatchingTransactionsOnScreen(const double& a, const int& n, const string& str) const;
	void	showMatchingTransactionsOnScreen(const string& title, const int& n, const string& str) const;
	void	showMatchingTransactionsOnScreen(const Date& date, const int& n, const string& str) const;
	void	showTransactionsUpToDateOnScreen(const bool& isEmpty, const Date& d, const int& n, const string& str) const;
	void	showDeletionOfTransactionsUpToDateOnScreen(const int& n, const Date& d, const bool& deletionConfirmed) const;
	void	showFundsAvailableOnScreen(const bool& isEmpty, const string& mad, const double& m) const;
	void	showTransferOnScreen(const bool& trOutOK, const bool& trInOK, const double& transferAmount) const;

private:
    //support functions
	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu() const;
    //made readInCommand public
    double	readInPositiveAmount() const;
	int		readInPositiveNumber() const;
};

#endif
