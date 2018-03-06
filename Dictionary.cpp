#include <iostream>
#include "Dictionary.h"
#include <string>

using namespace std;

//default constructor that creates a node of BinaryNode class
template <class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>::BinaryNode(){
  leftPtr = nullptr;
  rightPtr = nullptr;
}

//consturctor that takes parameters key and item
template <class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>::BinaryNode(const KeyType& aKey, const ItemType& anItem){
  key = aKey;
  item = anItem;
  leftPtr = nullptr;
  rightPtr = nullptr;
}

template <class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>::BinaryNode(const KeyType& aKey){
  key = aKey;
  leftPtr = nullptr;
  rightPtr = nullptr;
}

template <class KeyType, class ItemType>
void BinaryNode<KeyType, ItemType>::setKey(const KeyType& aKey){
  key = aKey;
}

template <class KeyType, class ItemType>
KeyType BinaryNode<KeyType, ItemType>::getKey() const{
  return key;
}

template <class KeyType, class ItemType>
void BinaryNode<KeyType, ItemType>::setItem(const ItemType& anItem){
  item = anItem;
}

template <class KeyType, class ItemType>
ItemType& BinaryNode<KeyType, ItemType>::getItem(){
  return item;
}

template <class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* BinaryNode<KeyType, ItemType>::getLeftChildPtr() const{
  return leftPtr;
}

template <class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* BinaryNode<KeyType, ItemType>::getRightChildPtr() const{
  return rightPtr;
}

template <class KeyType, class ItemType>
void BinaryNode<KeyType, ItemType>::setLeftChildPtr(BinaryNode<KeyType, ItemType>* nleftPtr){
  leftPtr = nleftPtr;
}

template <class KeyType, class ItemType>
void BinaryNode<KeyType, ItemType>::setRightChildPtr(BinaryNode<KeyType, ItemType>* nrightPtr){
  rightPtr = nrightPtr;
}

template <class KeyType, class ItemType>
Dictionary<KeyType, ItemType>::Dictionary(){
  container = nullptr;
}

template <class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::recursiveDestructor(BinaryNode<KeyType, ItemType>* root){
  if (root == nullptr){
    return;
  }
  recursiveDestructor(root->getLeftChildPtr());
  recursiveDestructor(root->getRightChildPtr());
  delete root;
}

template <class KeyType, class ItemType>
Dictionary<KeyType, ItemType>::~Dictionary(){
  recursiveDestructor(container);
  }

template <class KeyType, class ItemType>
bool Dictionary<KeyType, ItemType>::IsEmpty() const{
  if (container == nullptr){
    return true;
  }
  else {
    return false;
  }
}


template <class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::clearHelper(BinaryNode<KeyType, ItemType>* root){
BinaryNode<KeyType, ItemType>* curr;
if (root == container) {
	curr = container;
	delete curr;
	container = nullptr;
  }
  else
  if (root != nullptr) {
    clearHelper(root->getLeftChildPtr());
    clearHelper(root->getRightChildPtr());
    delete root;
  }

/*
  if (root->getLeftChildPtr() != nullptr){
    clearHelper(root->getLeftChildPtr());
  }
  if (root->getRightChildPtr() != nullptr){
    clearHelper(root->getRightChildPtr());
  }
  delete root;
*/

}

template <class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::Clear(){
  clearHelper(container);
}

template <class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::sizeHelper(BinaryNode<KeyType, ItemType>* root){
  if (root == nullptr){
    return 0;
  }
  else {
    return (sizeHelper(root->getLeftChildPtr()) + sizeHelper(root->getRightChildPtr()) + 1);
  }
}

template <class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::Size(){
  return sizeHelper(container);
}

template <class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::getHeightHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const{
  if (subTreePtr == nullptr){
    return 0;
  }
  else {
    return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
  }
}
template <class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::Height(){
  return getHeightHelper(container);
}

template <class KeyType, class ItemType>
int Dictionary<KeyType, ItemType>::Count(KeyType searchKey){
  BinaryNode<KeyType, ItemType>* curr = container;  //wants a pointer that holds the boxes
  while (curr != nullptr){
    if (curr->getKey() == searchKey){
      break;
    }
    else
    if (searchKey > curr->getKey()){
      // changed to curr==curr->getRightChildPtr();
      curr=curr->getRightChildPtr();
    }
    else
    if (searchKey < curr->getKey()){
      // changed to curr=curr->getLeftChildPtr();
      curr=curr->getLeftChildPtr();
    }
  }
  if (curr == nullptr){
    return 0;
  }
  else if (curr->getKey() == searchKey){
    return 1;
  }
  return 0;
  // delete curr;
}

template <class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::Remove(const KeyType& searchKey){
  removeHelper(container, searchKey);
}

template <class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::Remove(const KeyType& searchKey){
  BinaryNode<KeyType, ItemType>* root = container;
  BinaryNode<KeyType, ItemType>* curr = container;

  if (curr == nullptr){
    return;
  }

  while (curr!= nullptr){
    if (curr->getKey() == searchKey){
      break;
    }
    else {
      root = curr;
      if (searchKey > curr->getKey()){
        curr=curr->getRightChildPtr();
      }
      else {
        curr=curr->getLeftChildPtr();
      }
    }
  }
  if (curr == nullptr) {
    return;
  }


//scenario 1: leaf node
  if (curr->getRightChildPtr() == nullptr && curr->getLeftChildPtr() == nullptr){
    if (root->getRightChildPtr() == curr){
      root->setRightChildPtr(nullptr);
    }
    else {
      root->setLeftChildPtr(nullptr);
    }
    delete curr;
    //delete root;
    return;
  }

//scenario 2: root w/ 1 child
  if ((curr->getRightChildPtr() != nullptr && curr->getLeftChildPtr() == nullptr) || (curr->getRightChildPtr() == nullptr && curr->getLeftChildPtr() != nullptr)){
    if (curr->getRightChildPtr() != nullptr && curr->getLeftChildPtr() == nullptr){ //has a right child
      if (root->getRightChildPtr() == curr){
        root->setRightChildPtr(curr->getRightChildPtr());
      }
      else {
        root->setLeftChildPtr(curr->getRightChildPtr());
      }
    }
    else { //has a left child
      if (root->getRightChildPtr() == curr){
        root->setRightChildPtr(curr->getLeftChildPtr());
      }
      else {
        root->setRightChildPtr(curr->getLeftChildPtr());
      }
    }
    delete curr;
    delete root;
    return;
  }

//scenario 3: root w/ 2 children
  if (curr->getRightChildPtr() != nullptr && curr->getLeftChildPtr() != nullptr){
    BinaryNode<KeyType, ItemType>* rCurr;
    if(rCurr->getRightChildPtr() == nullptr && rCurr->getLeftChildPtr() == nullptr){ //right child does not have children
      curr->setKey(rCurr->getKey());
      delete rCurr;
      curr->setRightChildPtr(nullptr);
    }
    else { //right child has children
      //right child's children has a right child
      if ((curr->getRightChildPtr())->getRightChildPtr() != nullptr){
        BinaryNode<KeyType, ItemType>* rrCurr;
        curr->setKey(rrCurr->getKey());
        curr->setRightChildPtr(rrCurr->getRightChildPtr());
        delete rrCurr;
      }
      else { //right child's children has a left child aka need to find smallest element in left subtree
        BinaryNode<KeyType, ItemType>* lCurr;
        BinaryNode<KeyType, ItemType>* root_lCurr;
        root_lCurr = curr->getRightChildPtr();
        lCurr = ((curr->getRightChildPtr())->getLeftChildPtr());
        while (lCurr->getLeftChildPtr() != nullptr){
          root_lCurr = lCurr;
          lCurr = lCurr->getLeftChildPtr();
        }
        curr->setKey(lCurr->getKey());
        delete lCurr;
        root_lCurr->setLeftChildPtr(nullptr);
        delete root_lCurr;
      }
    }
    delete curr;
    delete root;
  }
}
 
template <class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* Dictionary<KeyType, ItemType>::search(KeyType searchKey){
BinaryNode<KeyType, ItemType>* curr = container;

 while (curr != nullptr){
  if (curr->getKey() == searchKey){
    break;
  }
  if (searchKey > curr->getKey()){
    curr = curr->getRightChildPtr();
  }
  else if (searchKey < curr->getKey()){
    curr = curr->getLeftChildPtr();
  }
}
if (curr == nullptr){
  return nullptr;
}
if (curr->getKey() == searchKey){
  return curr;
}
//commented out below line
//delete curr;
return nullptr;
}

template <class KeyType, class ItemType>
ItemType& Dictionary<KeyType, ItemType>::operator[](KeyType searchKey){
BinaryNode<KeyType, ItemType>* curr = container;
 if (container==nullptr) {
   container = new BinaryNode<KeyType, ItemType>();
   container->setKey(searchKey);
   return container->getItem();
 }

  //if keytype is already in dictionary
  if (search(searchKey)!=nullptr){
    return search(searchKey)->getItem();
  }
  else {        //keytype not in dictionary and dictionary not empty
    while (curr != nullptr){
        if (curr->getKey() < searchKey){
            if (curr->getRightChildPtr() != nullptr){
              curr = curr->getRightChildPtr();
            }
            else {
              BinaryNode<KeyType, ItemType>* newNode = new BinaryNode<KeyType,ItemType>();
              curr->setRightChildPtr(newNode);
              newNode->setKey(searchKey);
              return newNode->getItem();
            }
        }
        else if (curr->getKey() > searchKey){
          if (curr->getLeftChildPtr() != nullptr){
            curr = curr->getLeftChildPtr();
          }
          else {
              BinaryNode<KeyType, ItemType>* newNode = new BinaryNode<KeyType,ItemType>();
              curr->setLeftChildPtr(newNode);
              newNode->setKey(searchKey);
              return newNode->getItem();
            }
          }
        }
      }
      return search(searchKey)->getItem();
    }


template <class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::travInOrder(BinaryNode<KeyType, ItemType>* root, BinaryNode<KeyType, ItemType>** &temparray, int count){
  if (root == nullptr){
    return;
  }
  else {
    travInOrder(root->getLeftChildPtr(), temparray,count);
    temparray[count]=root;
    count++;
    travInOrder(root->getRightChildPtr(), temparray,count);
  }
}

template <class KeyType, class ItemType>
BinaryNode<KeyType, ItemType>* Dictionary<KeyType, ItemType>::balanceHelper(BinaryNode<KeyType, ItemType>** &temparray, KeyType small, KeyType large){
  if (small > large){
    return nullptr;
  }
  BinaryNode<KeyType, ItemType>* nn = (temparray[(small+large/2)]);
  nn -> setLeftChildPtr(balanceHelper(temparray, small, (small+large)/2-1));
  nn -> setRightChildPtr(balanceHelper(temparray, (small+large)/2-1, large));
  return nn;
}

template <class KeyType, class ItemType>
void Dictionary<KeyType, ItemType>::Balance(){
  BinaryNode<KeyType, ItemType>** temparray = new BinaryNode<KeyType, ItemType>*[Size()];
  travInOrder(container, temparray,0);
  balanceHelper(temparray, 0, Size()-1);
}


int main(){
/*
  Dictionary<char,unsigned short> dict;
  dict['a'] = 30;
  cout << dict['a'] << endl;
  dict['b'] = 40;
  cout << dict['b'] << endl;
  dict['a']+= 10;
  cout << dict['a'] << endl;
*/
  string str="abcedbee";
  //string str="abcd";

      Dictionary<char,unsigned short> dict;

      if(dict.IsEmpty()) cout<<"Empty\n"; // The message should appear on the screen

      for(int i=0; i<str.size(); i++)
      {
          if(dict.Count(str[i])==0) {
            dict[str[i]]=1;
          }
          else {
            dict[str[i]]+=1;
          }
        }

      cout<<"The number of unique letters is "<<dict.Size()<<endl; // Should show 5
      cout<<"The height of the tree is "<<dict.Height()<<endl;     // Should show 4
      cout<<"The letter a happened "<<dict['a']<<" times\n";        //Should show 1
      cout<<"The letter e happened "<<dict['e']<<" times\n\n";      //Should show 3

      dict.Remove('c');
      cout<<"After Remove" <<endl; //debug msg
      cout<<"The number of unique letters is "<<dict.Size()<<endl; // Should show 4
      cout<<"The height of the tree is "<<dict.Height()<<endl;     // Should show 4
      cout<<"something strange here..."<<endl; // debug msg
      cout<<"The letter a happened "<<dict['d']<<" times\n";        //Should show 1
      if(dict.Count('c')==0) cout<<"Now the letter e is absent\n\n"; //This message should appear on the screen

      //dict.Balance();
      cout<<"The height of the tree is "<<dict.Height()<<endl;     // Should show 3

      dict.Clear();
      cout<<"The number of unique letters is "<<dict.Size()<<endl; // Should show 0
      cout<<"The height of the tree is "<<dict.Height()<<endl;     // Should show 0
  return 0;
}
