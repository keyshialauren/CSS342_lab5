#include "Transaction.hpp"
#include "BSTree.hpp"
#include "Account.hpp"
#include <iomanip>

//----------------------------------------------------------------------------
// constructor
Transaction::Transaction(){
   transactionType = ' ';
   amount = 0;
   toAccNum = 0;
   fromAccNum = 0;
   toAcc = 0;
   fromAcc = 0;
}


//----------------------------------------------------------------------------
// contructor
// reads data from file lab5command.txt
Transaction::Transaction(istream& input){
   input >> transactionType;
    
   // check for end of file
   if (input.eof()){
      return; // break out of function
   }

   // buy shares, i.e., deposit funds 
   if (transactionType == 'D'){
      int temp;
      input >> temp;
      fromAccNum = toAccNum = temp / 10;
      fromAcc = toAcc = temp;
      input >> amount;
   // sell shares, i.e., withdraw funds
   } else if (transactionType == 'W'){
      int temp;
      input >> temp;
      fromAccNum = toAccNum = temp / 10;
      fromAcc = toAcc = temp;
      input >> amount;
   // move assets between funds/clients 
   } else if (transactionType == 'M'){
      int temp;
      input >> temp;
      fromAccNum = temp / 10;
      fromAcc = temp;
      input >> amount;
      int temp1;
      input >> temp1;
      toAccNum = temp1 / 10;
      toAcc = temp1;
   // display the history of all transactions of all accounts of a client 
   } else if (transactionType == 'H'){
      input >> fromAccNum;
      toAccNum = toAcc = fromAcc = amount = 0;
   } else {
      char s[60];
      input.getline(s, 60);
   }
}

//----------------------------------------------------------------------------
// destructor
Transaction::~Transaction(){
}

//----------------------------------------------------------------------------
// checkValidTransaction
// check if valid transaction type
// if not valid, print message and return false. Else, return true.
bool Transaction::checkValidTransaction(){
   if (transactionType != 'D' && transactionType != 'W' &&
       transactionType != 'M' && transactionType != 'H'){
      cout << "Unknown transaction type " << "'" << transactionType 
           << "'" << " requested" << endl;
      return false;
   } else {
      return true;
   }
}

//----------------------------------------------------------------------------
// getTransactionType
// get transaction type
char Transaction::getTransactionType(){
   return transactionType; 
}

//----------------------------------------------------------------------------
// getFromAccountNum
// get from account number
int Transaction::getFromAccountNum(){
   return fromAccNum;
}

//----------------------------------------------------------------------------
// getToAccountNum
// get to account number
int Transaction::getToAccountNum(){
   return toAccNum;
}

//----------------------------------------------------------------------------
// getFromAccount
// get from account
int Transaction::getFromAccount(){
   return fromAcc;
}

//----------------------------------------------------------------------------
// getToAccount
// get to account
int Transaction::getToAccount(){
   return toAcc;
}

//----------------------------------------------------------------------------
// getAmount
// get amount
int Transaction::getAmount(){
   return amount;
}

//----------------------------------------------------------------------------
// deposit
// buy shares, i.e., deposit funds 
void Transaction::deposit(BSTree& clientTree){
   Client* tempClient = new Client();              // temporary client
   bool success;
   int clientNum = this->getFromAccountNum();      // gets Account Number
   
   Client toRetrieve(clientNum);
   success = clientTree.retrieve(toRetrieve, tempClient);

   // check if valid
   if (success){ 
      tempClient->history.push_back(this);
      int accountNum = this->getToAccount() % 10;
      // call deposit function
      tempClient->deposit(accountNum, this->getAmount());
   } else {
      cout << "Unknown client ID " << this->getFromAccountNum() <<
      " requested" << endl;
   }
   
   tempClient = nullptr;
   delete tempClient;
}

//----------------------------------------------------------------------------
// withdraw
// sell shares, i.e., withdraw funds 
void Transaction::withdraw(BSTree& clientTree){
   Client* tempClient = new Client();                // temporary client
   bool success;
   int clientNum = this->getFromAccountNum();       // gets Account Number
   
   Client toRetrieve(clientNum);
   success = clientTree.retrieve(toRetrieve, tempClient);
   
   // check if valid
   if (success){
      int accountNum = this->getToAccount() % 10;
      // check for overdrawn
      Account account = tempClient->getAccount(accountNum);
      if(account.getEndingBalance() - this->getAmount() < 0){
         int remainingAmount = this->getAmount() - 
                              account.getEndingBalance();
         // check for other Accounts (money market and bonds)
         for(int x = 0; x < 4; x++){
            if(x != accountNum && remainingAmount != 0){
               // temporary account
               Account tempAcc = tempClient->getAccount(x);
               // when withdrawal can be covered with other account funds
               if(tempAcc.getEndingBalance() - remainingAmount >= 0){
                  tempClient->withdraw(accountNum, 
                                       account.getEndingBalance());
                  for (int y = 0; y <= x; y++){
                     if (y == x){
                        tempClient->withdraw(y, remainingAmount);
                     }
                  }
                  remainingAmount = 0;
                  break;
               } else {
                  remainingAmount -= tempAcc.getEndingBalance();
               }
            }
         }
         // print error message
         if (remainingAmount != 0){
            cout << "Withdrawal not performed on " << 
            ACCTTYPE[this->toAcc % 10] << " fund for client " << 
            this->getFromAccountNum() << endl << "   insufficient funds" 
            << endl;
         }
      } else if (account.getEndingBalance() - this->getAmount() >= 0){
         tempClient->history.push_back(this);
         // call withdraw function
         tempClient->withdraw(accountNum, this->getAmount());
      }
   } else {
      cout << endl << "Withdrawal not performed on " << 
      this->getFromAccountNum() << " for client " << 
      this->getFromAccountNum() << endl << endl;
   }
   tempClient = nullptr;
   delete tempClient;
}

//----------------------------------------------------------------------------
// move
// move assets between funds/clients 
void Transaction::move(BSTree& clientTree){
   Client* temp1 = new Client();                   // from client
   Client* temp2 = new Client();                   // to client
   bool success;
   
   int fromClientNum = this->getFromAccountNum();
   int toClientNum = this->getToAccountNum();
   
   Client toRetrieve1(fromClientNum);              // temporary client
   Client toRetrieve2(toClientNum);                // temporary client
   
   // searches for fromClient
   success = clientTree.retrieve(toRetrieve1, temp1);
   
   if (success){
      // searches for toClient
      success = clientTree.retrieve(toRetrieve2, temp2);
      if (success) {
         int fromAccountNum = this->getFromAccount() % 10;
         int toAccountNum = this->getToAccount() % 10;
         temp1->history.push_back(this);  // add to history
         // withdraw from client
         temp1->withdraw(fromAccountNum, this->getAmount());
         // deposits to client
         temp2->deposit(toAccountNum, this->getAmount());
      } else {
         cout << "Unknown client ID " << this->getFromAccountNum() <<
         " or " << this->getToAccountNum() << " requested" << endl;
      }
   } else {
      cout << "Unknown client ID " << this->getFromAccountNum() << " or " <<
      this->getToAccountNum() << " requested" << endl;
   }
   temp1 = temp2 = nullptr;
   delete temp1;
   delete temp2;
}

//----------------------------------------------------------------------------
// history
// display the history of all transactions of all accounts of a client 
void Transaction::history(BSTree& clientTree){
   Client* temp = new Client();                 // temporary client
   bool success;
   
   // client number
   int fromClientNum = this->getFromAccountNum();
   Client toRetrieve(fromClientNum);
   success = clientTree.retrieve(toRetrieve, temp);
   
   if (success){
      temp->history.push_back(this);
      vector<Transaction*> clientHistory = temp->getHistory();
      cout << endl;
      cout << "History of transactions for client " << temp->getFirstName()
      << " " << temp->getLastName() << ", client ID = " <<
      temp->getAccountNumber() << endl;
      cout << "Type      Amount  Detail" << endl;
      cout << "--------- ------- --------------------------------------"
      << endl;
      for (int i = 0; i < clientHistory.size(); i++) {
         cout << *clientHistory.at(i);
      }
      cout << endl;
   } else {
      cout << "Unknown client ID " << this->getFromAccountNum() <<
      " requested" << endl;
   }
   
   temp = nullptr;
   delete temp;
}

//----------------------------------------------------------------------------
// operator<<
// prints transaction information for an account
ostream& operator<<(ostream& output, const Transaction& toPrint) {
   if (toPrint.transactionType == 'D') {
      output << "deposit" << setw(4) << "$" << setw(7) <<
      toPrint.amount << " into " << ACCTTYPE[toPrint.toAcc % 10] << endl;
      return output;
   } else if (toPrint.transactionType == 'W') {
      output << "withdraw" << setw(3) << "$" << setw(7) <<
      toPrint.amount << " from " << ACCTTYPE[toPrint.toAcc % 10] << endl;
      return output;
   } else if (toPrint.transactionType == 'M') {
      output << "move" << setw(7) << "$" << setw(7) <<
      toPrint.amount << " from " << ACCTTYPE[toPrint.fromAcc % 10] << endl
      << setw(22) << " to " << ACCTTYPE[toPrint.toAcc % 10] <<
      " for client " << toPrint.toAcc / 10 << endl;
      return output;
   } else if (toPrint.transactionType == 'H') {
      output << "history" << endl;
      return output;
   } else {
      return output;
   }
}