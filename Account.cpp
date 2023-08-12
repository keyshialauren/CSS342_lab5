#include "Account.hpp"

//----------------------------------------------------------------------------
// Constructor
Account::Account(){
   accountName = " ";
   accountNumber = 0;
   startingBalance = 0;
   endingBalance = 0;
}        

//----------------------------------------------------------------------------
// Destructor
Account::~Account(){
}

//----------------------------------------------------------------------------
// getStartingBalance
// Returns value startingBalance
int Account::getStartingBalance() const{
   return startingBalance;
}   

//----------------------------------------------------------------------------
// getEndingBalance
// Returns value endingBalance
int Account::getEndingBalance() const{
   return endingBalance;
}

//----------------------------------------------------------------------------
// getAccount
Account* Account::getAccount() {
    return this;
}


//----------------------------------------------------------------------------
// setStartingBalance
// Set startingBalance externally
void Account::setStartingBalance(int balance){
   startingBalance = balance;
}

//----------------------------------------------------------------------------
// setEndingBalance
// Set endingBalance externally
void Account::setEndingBalance(int balance){
   endingBalance = balance;
}

//----------------------------------------------------------------------------
// setAccountNumber
// Set accountNumber externally
void Account::setAccountNumber(int num){
   accountNumber = num;
}

//----------------------------------------------------------------------------
// setAccountName
// Set accountName externally
void Account::setAccountName(string name){
   accountName = name;
}

//----------------------------------------------------------------------------
// deposit
// Increase currentBalance by param amount
void Account::deposit(int deposit){
   endingBalance += deposit;
}

//----------------------------------------------------------------------------
// withdraw
// Decrease currentBalance by param amount
// Error checked by User object (overdrawn verification)
void Account::withdraw(int withdraw){
   endingBalance -= withdraw;
}

//----------------------------------------------------------------------------
// operator<<
ostream& operator<<(ostream& output, const Account& toPrint) {
   output << toPrint.startingBalance;
   return output;
}