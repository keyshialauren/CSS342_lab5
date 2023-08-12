#include "Client.hpp"
#include "Transaction.hpp"
#include <iomanip>

//----------------------------------------------------------------------------
// Constructor
Client::Client(){
   firstName = " ";
   lastName = " ";
   accountNumber = 0;
   accounts = 0;    
}

//----------------------------------------------------------------------------
// Constructor 
// Takes in account number as param
Client::Client(int num){
   firstName = " ";
   lastName = " ";
   accountNumber = num;
   accounts = new Account[10];
}

//----------------------------------------------------------------------------
// Constructor
// Ttakes in a file as param
Client::Client(istream& input){
   int balance;
   input >> lastName >> firstName >> accountNumber;
   accounts = new Account[10];           // set up the user accounts

   // check for end of file
   if (input.eof()){
      return;                            // break out of function
   }

   // set up the accounts 
   for (int i = 0; i < 10; i++) {
      input >> balance;
      accounts[i].setAccountName(ACCTTYPE[i]);               // accountName
      accounts[i].setAccountNumber(accountNumber * 10 + i);  // accountNumber
      accounts[i].setStartingBalance(balance);          // startingBalance
      accounts[i].setEndingBalance(balance);            // endingBalance
   }
}
//----------------------------------------------------------------------------
// Destructor
Client::~Client(){
   delete [] accounts;
}

//----------------------------------------------------------------------------
// getAccount
Account Client::getAccount(int accountNum) {
   return accounts[accountNum];
}

//----------------------------------------------------------------------------
// getFirstName
// returns first name
string Client::getFirstName(){
   return firstName;
}

//----------------------------------------------------------------------------
// getLastName
// returns last name
string Client::getLastName(){
   return lastName;
}

//----------------------------------------------------------------------------
// getAccountNumber
// returns account number
int Client::getAccountNumber(){
   return accountNumber;
}

//----------------------------------------------------------------------------
// deposit
void Client::deposit(int accountNum, int ammount) {
   accounts[accountNum].deposit(ammount);
}

//----------------------------------------------------------------------------
// withdraw
void Client::withdraw(int accountNum, int ammount) {
   accounts[accountNum].withdraw(ammount);
}

//----------------------------------------------------------------------------
// getHistory
vector<Transaction*> Client::getHistory() {
   return history;
}

//----------------------------------------------------------------------------
// operator<
// less than operator
bool Client::operator<(const Client& other) const{
   return (accountNumber < other.accountNumber);
}

//----------------------------------------------------------------------------
// operator>
// greater than operator
bool Client::operator>(const Client& other) const{
   return (accountNumber > other.accountNumber);
}

//----------------------------------------------------------------------------
// operator==
// equality operator
bool Client::operator==(const Client& other) const{
   return (accountNumber == other.accountNumber);
}

//----------------------------------------------------------------------------
// operator!=
// equality operator
bool Client::operator!=(const Client& other) const{
   return (accountNumber != other.accountNumber);
}

//----------------------------------------------------------------------------
// operator<<
ostream& operator<<(ostream& output, const Client& toPrint){
   output << toPrint.accountNumber << "  " << toPrint.firstName << " "
          << toPrint.lastName << endl << "Initial Balances:";
   for (int i = 0; i < 10; i++) {
      output << setw(7) << toPrint.accounts[i].getStartingBalance();
   }
   output << endl << "Final Balances:  ";
   for (int i = 0; i < 10; i++) {
      output << setw(7) << toPrint.accounts[i].getEndingBalance();
   }
   output << endl << endl;
   return output;
}