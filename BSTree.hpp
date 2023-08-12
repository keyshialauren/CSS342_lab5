#ifndef BSTREE_H
#define BSTREE_H

#include "Client.hpp"

//-------------------------  class BSTree  -----------------------------------
// ADT BSTree: This class is the container for all the Client objects.
// 
// Assumptions:
//   -- Although the tree holds the Clients, it does not know anything
//      about the specifics of the Client's data
//   --  All functionality is through the Object's functions
//----------------------------------------------------------------------------


class BSTree {
public:
   BSTree();             // constructor
   ~BSTree();            // calls makeEmpty which deallocates all memory
   void makeEmpty();     // empties the current tree, deallocates all memory
   
   // insert object into the tree, parameter holds pointer to object
   // to insert
   bool insert(Client*);
   // retrieve object, first parameter is object to retrieve
   // second parameter holds pointer to found object, nullptr if not found
   bool retrieve(const Client&, Client*&) const;
   void display() const;      // displays the contents of a tree to cout
   bool isEmpty() const;      // returns true if tree is empty 
    
private:
   struct Node { // glue that holds data properly
      Client* data;
      Node* right;
      Node* left;
   };
   Node* root;
   
   void makeEmptyHelper(Node*&);        // recursive helper for make empty
   bool insertHelper(Node* &, Client*); // recursive helper for insert
   // recursice helper for retrieve
   bool retrieveHelper(const Client&, Client*&, Node*) const;
   void displayHelper(Node*) const;     // recursive helper for display

};
#endif