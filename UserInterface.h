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

    void	showProduceBalanceOnScreen(double bal) const;
    void	showDepositOnScreen(bool auth, double deposit) const;
    void	showWithdrawalOnScreen(bool auth, double withdrawal) const;
    void	showStatementOnScreen(const string&) const;
	void	showMiniStatementOnScreen(const bool& isEmpty, const double& total, const string& str) const;
	void	showDepositOnScreen(bool, const string&, double) const;

private:
    //support functions
	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu() const;
    int		readInCommand() const;
    double	readInPositiveAmount() const;
	int		readInPositiveNumber() const;
};

#endif
