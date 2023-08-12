#include "Manager.hpp"
#include "Transaction.hpp"
#include <iostream>
#include <fstream>

//----------------------------------------------------------------------------
// Constructor
Manager::Manager(){
} 

//----------------------------------------------------------------------------
// Destructor                       
Manager::~Manager(){
}

//----------------------------------------------------------------------------
// buildClientCollection
// builds BSTree of Clients
void Manager::buildClientCollection(){
   ifstream infile("lab5data.txt");  // open lab5data.txt file
   // check for successful open
   if (!infile){                  
      cout << "File could not be opened." << endl;
   }
   // loop through file until eof()
   for (;;){
      Client* toInsert = new Client(infile);       // create client object

      // check for end of file
      if (infile.eof()){
         delete toInsert;                         // delete client object
         break;
      }

      bool success = clientTree.insert(toInsert);  // insert client to tree
      
      // check for successful insert
      if (!success){
         delete toInsert;                          // delete client object
      }
      toInsert = nullptr;
      delete toInsert;
   }
}

//----------------------------------------------------------------------------
// buildTransactionCollection
// builds queue of Transactions
void Manager::buildTransactionCollection(){
   ifstream infile("lab5command.txt");  // open lab5command.txt file
   
   // check for successful open
   if (!infile){                  
      cout << "File could not be opened." << endl;
   }

   // loop through file until eof()
   for (;;){
      // create client object
      Transaction* toInsert = new Transaction(infile);

      // check for end of file
      if (infile.eof()){
         delete toInsert;                             // delete client object
         toInsert = nullptr;
         break;
      }

      // check for valid transaction type
      bool success = toInsert->checkValidTransaction();

      // check for successful insert
      if (!success){
         delete toInsert;                          // delete client object
      }

      // insert transaction to queue
      clientTransactions.push(toInsert);
      toInsert = nullptr;
      delete toInsert;
   }

}

//----------------------------------------------------------------------------
// endOfDayReport
// prints LOSE report of Client and Account
void Manager::endOfDayReport(){
   cout << endl << "REPORT" << endl << endl;
   clientTree.display();  // BSTree display member function call
}

//----------------------------------------------------------------------------
// runBusiness
// running all of the business activity
void Manager::runBusiness(){
   // loops until queue is empty
   while (!clientTransactions.empty()){
      Transaction* transaction;                 // transaction to be processed
      transaction = clientTransactions.front(); // gets the transaction
      clientTransactions.pop();                 // dequeue the transaction
      
      switch (transaction->getTransactionType()){
         case 'D':
            transaction->deposit(clientTree);
            break;
         case 'W':
            transaction->withdraw(clientTree);
            break;
         case 'M':
            transaction->move(clientTree);
            break;
         case 'H':
            transaction->history(clientTree);
            break;
         // invalid transaction type
         default:
            break;
   }
   transaction = nullptr;
   delete transaction;
   }
}