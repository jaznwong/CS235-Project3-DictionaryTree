#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>

using namespace std;

//all items have keys (integers, string, whatever) but they must be comparable (operations ==, !=, >, <, >=, <=)
//dictionary has two data types -- keytypes and itemtype
//keytype -> type of the key
//itemtype -> type of the item
template <class KeyType, class ItemType>
class BinaryNode {
private:
  KeyType key; //data portion of KeyType
  ItemType item; //data portion of ItemType
  BinaryNode<KeyType, ItemType> *leftPtr; //Pointer to left child
  BinaryNode<KeyType, ItemType> *rightPtr; //pointer to right child
public:
  BinaryNode();
  BinaryNode(const KeyType& aKey, const ItemType& anItem);
  BinaryNode(const KeyType& aKey);

  void setKey(const KeyType& aKey);
  KeyType getKey() const;

  void setItem(const ItemType& anItem);
  ItemType& getItem();

  BinaryNode<KeyType, ItemType>* getLeftChildPtr() const;
  BinaryNode<KeyType, ItemType>* getRightChildPtr() const;

  void setLeftChildPtr(BinaryNode<KeyType, ItemType>* nleftPtr);
  void setRightChildPtr(BinaryNode<KeyType, ItemType>* nrightPtr);
}; //end BinaryNode




template <class KeyType, class ItemType>
class Dictionary {
private:
  BinaryNode<KeyType, ItemType>* container;
protected:
  void recursiveDestructor(BinaryNode<KeyType, ItemType>* root);
  void clearHelper(BinaryNode<KeyType, ItemType>* root);
  int sizeHelper(BinaryNode<KeyType, ItemType>* root);
  int getHeightHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const;
  BinaryNode<KeyType, ItemType>* findSmallest(BinaryNode<KeyType, ItemType>* root);
  void removeHelper(BinaryNode<KeyType, ItemType>* root, KeyType searchKey);
  void travInOrder(BinaryNode<KeyType, ItemType>* root, BinaryNode<KeyType, ItemType>** &temparray, int count);
  BinaryNode<KeyType, ItemType>* balanceHelper(BinaryNode<KeyType, ItemType>** &temparray, KeyType small, KeyType large);
  BinaryNode<KeyType, ItemType>* search(KeyType searchKey);
  //BinaryNode<KeyType, ItemType>* insertNode(BinaryNode<KeyType, ItemType>* node,KeyType searchKey);
public:
  //contructor that sets up an empty container
  Dictionary();
  //destructor
  ~ Dictionary();
  //returns true if container is empty
  bool IsEmpty() const;
  //empties container
  void Clear();
  //returns the number of items stored in container
  int Size();
  //returns height of binary search tree
  int Height();
  //returns 1 if an item with a given key exists in the container and 0 otherwise.
  int Count(KeyType searchKey);

  //returns the reference to the item with the given key; if container does not have the item, it creates a new item and assigns it the given key
  ItemType& operator[](KeyType searchKey); //given return type and parameters
  //removes the item with the specified key from the container
  void Remove(const KeyType& searchkey);
  //function that rearranges the tree to make it balanced
  //**note this will need a temporary storage (only use dynamically allocated array)
  void Balance();
};

#endif
