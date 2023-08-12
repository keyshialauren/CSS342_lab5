#ifndef TRANS_H
#define TRANS_H
#include "Client.hpp"
#include <iostream>
using namespace std;

//-----------------------  class Transaction  --------------------------------
// ADT Transaction: Object containing transaction information
// 
// Assumptions:
//   -- The format (number and types of input items) of the transaction
//      is correct.
//   -- When there is insufficient fund, The desired amount (only the partial 
//      amount needed to cover the withdrawal) is moved to that money market 
//      account.  Bond accounts are handled similarly. No other types of 
//      accounts are handled in this manner. 
// ---------------------------------------------------------------------------
class BSTree;

class Transaction{
   friend ostream& operator<<(ostream&, const Transaction&);

public:
   Transaction();              // constructor
   Transaction(istream&);      // constructor, reads from file
   ~Transaction();             // destructor
    
   bool checkValidTransaction();      // check if valid transaction type
   char getTransactionType();         // get transaction type
   int getFromAccountNum();           // get from account number
   int getToAccountNum();             // get to account number
   int getFromAccount();              // get from account
   int getToAccount();                // get to account
   int getAmount();                   // get amount

   void deposit(BSTree&);             // deposit
   void withdraw(BSTree&);            // withdraw
   void move(BSTree&);                // move
   void history(BSTree&);             // history
 
private:
   char transactionType; 
   int amount;
   int fromAccNum;                   // sending client
   int toAccNum;                     // receiving client
   int fromAcc;                      // sending account  
   int toAcc;                        // receiving account
};
#endif
