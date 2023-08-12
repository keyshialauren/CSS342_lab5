#ifndef CLIENT_H
#define CLIENT_H
#include "Account.hpp"
using namespace std;
 
//--------------------------  class Client  ----------------------------------
// ADT Client: Object containing unique Client information
//             Stores Account object containing the 10 account types
// 
// Assumptions:
//   -- Each client has 10 accounts
// ---------------------------------------------------------------------------
 
#include <iostream>
#include <vector>

const string ACCTTYPE[] = {"Money Market", "Prime Money Market",
                           "Long-Term Bond", "Short-Term Bond", 
                           "500 Index Fund", "Capital Value Fund", 
                           "Growth Equity Fund", "Growth Equity Fund",
                           "Value Fund", "Value Stock Index"};

class Transaction;

class Client{
   friend ostream& operator<<(ostream&, const Client&);

public:
   Client();                          // Constructor
   Client(int);                       // Constructor that takes in accountnum
   Client(istream&);                  // Constructor that takes in a file 
   ~Client();                         // Destructor

   Account getAccount(int);            // getAccount
   string getFirstName();              // returns first name
   string getLastName();               // returns last name
   int getAccountNumber();             // returns account number
   void deposit(int, int);             // deposit
   void withdraw(int, int);            // withdraw

   vector<Transaction*> history;       // holds history of transactions
   vector<Transaction*> getHistory();  // getHistory
   
   // operators
   bool operator<(const Client&) const;   // less than operator
   bool operator>(const Client&) const;   // greater than operator
   bool operator==(const Client&) const;  // equality operator
   bool operator!=(const Client&) const;  // non-equality operator

private:
   string firstName;
   string lastName;
   int accountNumber;
   Account* accounts;               // pointer to 10 account types
};
#endif