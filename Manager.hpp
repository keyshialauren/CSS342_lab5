#ifndef MANAGER_H
#define MANAGER_H

#include <queue>
#include "BSTree.hpp"
#include "Transaction.hpp"
 
//-------------------------  class Manager  ----------------------------------
// ADT Manager: Contains BSTree of Client objects
//              Contains STL queue of transactions
//              Builds a collection of client and transactions
//              Runs the business
//
// Assumptions:
//   -- Two .txt files named "lab5command.txt" that stores transactions
//      and "lab5data.txt" that stores client information
//----------------------------------------------------------------------------
class Transaction;

class Manager{
public:
   Manager();                             // constructor
   ~Manager();                            // desctructor
   void buildClientCollection();          // builds BSTree of Clients
   void buildTransactionCollection();     // builds queue of Transactions
   void endOfDayReport();        // prints LOSE report of Client and Account
   void runBusiness();                    // running business activities
   void displayQueueTransactions();
   BSTree clientTree;                     // Client objects

private:
   queue<Transaction*> clientTransactions;   // Transaction objects
};
#endif