#include "Manager.hpp"
 
//-----------------------------  Main  ---------------------------------------
// Main method for the program.
// It calls functions from the Manager class to run the business, including
// building the client and transaction collection and producing a report. 
// ---------------------------------------------------------------------------
 
int main(){
   Manager lose;
   lose.buildClientCollection();
   lose.buildTransactionCollection();
   lose.runBusiness();  
   lose.endOfDayReport();

   return 0;
}