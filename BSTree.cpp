#include "BSTree.hpp"

//----------------------------------------------------------------------------
// constructor
BSTree::BSTree(){
   root = nullptr;
}

//----------------------------------------------------------------------------
// destructor
// calls makeEmpty()
BSTree::~BSTree(){
   makeEmpty();
}

//----------------------------------------------------------------------------
// makeEmpty
void BSTree::makeEmpty(){
   // base case = tree is empty
   if (root == nullptr){
      return;
   }

   // call recursive helper
   makeEmptyHelper(root);
}

//----------------------------------------------------------------------------
// makeEmptyHelper
void BSTree::makeEmptyHelper(Node* &current){
   // base case = node is nullptr
   if (current == nullptr){
      return;
   }

   // recursive calls
   makeEmptyHelper(current->left);              // traverse left subtree
   makeEmptyHelper(current->right);             // traverse right subtree

   delete current->data;
   current->data = nullptr;
   delete current;
   current = nullptr;
}

//----------------------------------------------------------------------------
// insert
bool BSTree::insert(Client* toInsert){
   // call recursive helper
   return insertHelper(root, toInsert);
}

//----------------------------------------------------------------------------
// insertHelper
bool BSTree::insertHelper(Node* &current, Client* toPtr){
   if(current == nullptr){
      current = new Node;                         // creates new node
      current->data = toPtr;
      current->left = current->right = nullptr;
      return true;
   }
   
   // recursive calls
   // traverse left subtree
   if (*toPtr < *current->data){
      return insertHelper(current->left, toPtr);
   // traverse right subtree
   } else if (*toPtr > *current->data){
      return insertHelper(current->right, toPtr);
   }
   return false;
}

//----------------------------------------------------------------------------
// retrieve
bool BSTree::retrieve(const Client& toRetrieve, Client* &ptrClient) const{
   // base case = tree is empty
   if (root == nullptr) {
      return false;
   }
    
   // if root is the target
   if (*root->data == toRetrieve) {
      ptrClient = root->data;
      return true;
   }
    
   // call recursive helper
   return retrieveHelper(toRetrieve, ptrClient, root);
}

//----------------------------------------------------------------------------
// retrieveHelper
bool BSTree::retrieveHelper(const Client& toRetrieve, Client* &ptrClient,
                            Node* current) const{
   // base case = client is null
   if (current == nullptr) {
      return false;
   }
   
   // base case = the node is object
   if (*current->data == toRetrieve){
      ptrClient = current->data;
      return true;
   }

   // recursive calls
   // traverse left subtree
   if (toRetrieve < *current->data){
      if (current->left != nullptr){
         return retrieveHelper(toRetrieve, ptrClient, current->left);
      }
   // traverse right subtree
   } else if (toRetrieve > *current->data){
      if (current->right != nullptr){
         return retrieveHelper(toRetrieve, ptrClient, current->right);
      }
   }
   return false;
}

//----------------------------------------------------------------------------
// display
void BSTree::display() const{
   // base case = empty tree
   if (root == nullptr) {
      return;
   }
    
   // call recursive helper
   return displayHelper(root);
}

//----------------------------------------------------------------------------
// displayHelper
void BSTree::displayHelper(Node* current) const{
   if (current == nullptr) {
      return;
   }

   // prints in order traversal (left, root, right)
   displayHelper(current->left);
   cout << *current->data;                   // traverse left subtree
   displayHelper(current->right);            // traverse right subtree
}

//----------------------------------------------------------------------------
// isEmpty()
bool BSTree::isEmpty() const{
   if (root == nullptr) {
      return true;
   } else {
      return false;
   }
}

