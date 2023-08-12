#ifndef ACCT_H
#define ACCT_H
#include <iostream>
using namespace std;
 
//-------------------------  class Account  ----------------------------------
// ADT Account: Object containing account balance information and unique
//              account number
//
// Assumptions:
//   -- A LOSE account is a 5-digit number based on the account number 
//      with the last digit representing one of the ten possible kinds of 
//      accounts 
// ---------------------------------------------------------------------------
 
class Account{
   friend ostream& operator<<(ostream&, const Account&);

public:
   Account();                         // Constructor
   ~Account();                        // Destructor
 
   int getStartingBalance() const;   // Returns value startingBalance
   int getEndingBalance() const;     // Returns value of currentBalance
   Account* getAccount();            // Returns pointer of account
   void setStartingBalance(int);     // Set startingBalance externally
   void setEndingBalance(int);       // Set endingBalance externally
   void setAccountNumber(int);       // Set accountNumber externally
   void setAccountName(string);      // Set accountName externally

   // Increase currentBalance by param amount
   void deposit(int);

   // Decrease currentBalance by param amount
   void withdraw(int);
 
private:
   int startingBalance;
   int endingBalance;
   int accountNumber;
   string accountName;
 
};
#endif
