#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override; // returns AVLNode pointers
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item) override; // TODO
    virtual void remove(const Key& key) override;  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    
    AVLNode<Key, Value>* insertNode (AVLNode<Key,Value>* node, const std::pair<const Key, Value>& new_item);
    int height(AVLNode<Key,Value>* node);
    void findBalance(AVLNode<Key,Value>* node);
    AVLNode<Key, Value>* balancer(AVLNode<Key,Value>* node);
    AVLNode<Key, Value>* fixRight(AVLNode<Key,Value>* node);
    AVLNode<Key, Value>* fixLeft(AVLNode<Key,Value>* node);
    AVLNode<Key, Value>* fixzigzagLR(AVLNode<Key,Value>* node);
    AVLNode<Key, Value>* fixzigzagRL(AVLNode<Key,Value>* node);
    AVLNode<Key,Value>* findNode(AVLNode<Key,Value>* node, const Key& key);
    void removeNode(AVLNode<Key,Value>* node);
    AVLNode<Key,Value>* predecessor(AVLNode<Key,Value>* node);
    void removeFix(AVLNode<Key,Value>* node, int diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    //AVLNode<Key, Value>* 
    this->root_ = insertNode(static_cast<AVLNode<Key, Value>*>(this->root_), new_item);
  //calling on root

}


template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::insertNode(AVLNode<Key,Value>* node, const std::pair<const Key, Value>& new_item) {
  if (node == NULL) { //base case: reach empty position, inserting new node as a leaf 
    return new AVLNode<Key,Value>(new_item.first, new_item.second, NULL); // empty tree -> inserting will remain balance
  }
  // trickling down to find the right position its order should be in 
  //recursive call to find right spot
  // root's children are called as new root parameter in recursive call
  // calls findbalance to calculate the balance of each node
  //calls balancer to make balanced 
  if (new_item.first < node->getKey()) { // new node is smaller than root -> node is now left child
    
    // if (node->getLeft() == NULL) {
    //   node->setLeft(new AVLNode<Key,Value>(new_item.first, new_item.second, node));
    //   node = node->getLeft();
    // }
    // else {
    //   return insertNode(node->getLeft(), new_item);
    // }
    AVLNode<Key,Value>* leftChild = insertNode(node->getLeft(), new_item);
    node->setLeft(leftChild);
    leftChild->setParent(node);
    
    // node->setLeft(insertNode(node->getLeft(), new_item));
    // node->updateBalance(-1);
  }

  else if (new_item.first > node->getKey()) { // new node is greater than root -> node is now right child
    // node->setRight(insertNode(node->getRight(), new_item));
    // node->updateBalance(1);

    // if (node->getRight() == NULL) {
    //   node->setRight(new AVLNode<Key,Value>(new_item.first, new_item.second, node));
    //   node = node->getRight();
    // }
    // else {
    //    return insertNode(node->getRight(), new_item);
    // }
    AVLNode<Key,Value>* rightChild = insertNode(node->getRight(), new_item);
    node->setRight(rightChild);
    rightChild->setParent(node);
  }


  else {
    node->setValue(new_item.second); // key is found., no insertions made, update value
    // return node; // returns the node of the key with updated value
  }
 
  findBalance(node); // called after insertion to make sure new balance is accurate
  return balancer(node);

}

template<class Key, class Value>
void AVLTree<Key,Value>::findBalance(AVLNode<Key,Value>* node) {
  // calculates balance based on heights of left and right subtrees
  if (node != NULL) {
    int leftHeight = height(node->getLeft());
    int rightHeight = height(node->getRight());
    node->setBalance(leftHeight - rightHeight);
  }
}

template<class Key, class Value>
int AVLTree<Key,Value>::height(AVLNode<Key,Value>* node) {
  // calculates height of tallest tree either from left or right
  //used to calculate balance
  if (node == NULL) {
    return 0;
  }
  int lHeight = height(node->getLeft());
  int rHeight = height(node->getRight());

  int maxHeight;
  if(lHeight > rHeight) {
    maxHeight = lHeight;
  }
  else {
    maxHeight = rHeight;
  }
  int total = 1+maxHeight;
  return total;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::balancer(AVLNode<Key,Value>* node) {

  findBalance(node);

  if (node->getBalance() < -1) { // right-heavy
    if (node->getRight()->getBalance() <=0) {
      return fixLeft(node);
    }
    else if (node->getRight()->getBalance()>0) {
      node->setRight(fixRight(node->getRight()));
      return fixLeft(node);
    }
  }
  else if (node->getBalance()>1) { // left-heavy
    if (node->getLeft()->getBalance()>=0) {
      return fixRight(node);
      
    }
    else if (node->getLeft()->getBalance()<0) {
      node->setLeft(fixLeft(node->getLeft()));
      return fixRight(node);
    }

  }

  return node;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::fixRight(AVLNode<Key,Value>* y) {
  // right rotation
  AVLNode<Key,Value>* x = y->getLeft();
  AVLNode<Key,Value>* z = x->getRight();

  x->setRight(y);
  y->setLeft(z);

  // y->updateBalance(1);
  // x->updateBalance(-1);

// update parent pointers
  x->setParent(y->getParent());
  y->setParent(x);
  if (z) {
    z->setParent(y);
  }

  if (y==this->root_) {
    this->root_ = x;
  }

  findBalance(y);
  findBalance(x);

  return x;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::fixLeft(AVLNode<Key,Value>* x) {
  // left rotation
  AVLNode<Key,Value>* y = x->getRight();
  AVLNode<Key,Value>* z = y->getLeft();

  y->setLeft(x);
  x->setRight(z);

  y->setParent(x->getParent());
  x->setParent(y);
  if (z) {
    z->setParent(x);
  }

  if (x == this->root_) {
    this->root_ = y;
  }

  findBalance(y);
  findBalance(x);

  return y;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::fixzigzagLR(AVLNode<Key,Value>* node) {
  // handle left-right zig zag
  node->setLeft(fixLeft(node->getLeft()));
  return fixRight(node);
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::fixzigzagRL(AVLNode<Key,Value>* node) {
  // handle right-left zig zag
  node->setRight(fixRight(node->getRight()));
  return fixLeft(node);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
  AVLNode<Key,Value>* removingNode = findNode(static_cast<AVLNode<Key, Value>*>(this->root_), key);
  if (!removingNode) {
    return;
  }
  removeNode(removingNode);
}

template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::findNode(AVLNode<Key,Value>* node, const Key& key) 
{
    // TODO
  if (node == NULL || node->getKey() == key) {
    return node;
  }
  
  if (node->getKey() < key) {
    return findNode(node->getRight(), key); // moving to iterator's right child if it is too small for the node
  }

  else if (node->getKey() > key) {
    return findNode(node->getLeft(), key);
  }

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeNode(AVLNode<Key,Value>* node)
{
    // TODO

  if (node == NULL) {
    return;
  }

  // after nodeswap, the deleting node will have 0 or 1 child at most. so there isn't a need to call removeNode() again
   if (node->getLeft()!= NULL && node->getRight() != NULL) {
    AVLNode<Key,Value>* pred = predecessor(node);
    if ( pred == NULL) {
      std::cout<<"node or pred is null";
      return;
    }
    nodeSwap(node, pred);

    // std::cout << "recursing w pred";

   }

  AVLNode<Key, Value>* parent = node->getParent();
  int diff = 0;

  // removingNode is a leaf
   if (node->getLeft() == NULL && node->getRight() == NULL) {
    if (node == this->root_) {
      this->root_ = NULL;
    }
    else if (node == node->getParent()->getLeft()) { // is left child
      node->getParent()->setLeft(NULL);
      diff = 1;
    }
    else if (node == node->getParent()->getRight()){ // is right child
      node->getParent()->setRight(NULL);
      diff = -1;
    }

    delete node;
  }
  
  // removingNode has one child
  else if (node->getLeft() == NULL || node->getRight() == NULL) {
    AVLNode<Key,Value>* child;
    if (node->getLeft() == NULL) { // if left is empty, right is full
      child = node->getRight();
    }
    else if (node->getRight() == NULL) {
      child = node->getLeft();
    }

  // assigning child 


    if (node == this->root_) {
      this->root_ = child;
      if (this->root_ != NULL) {
        this->root_->setParent(NULL);
      } 
    }
    else {
      // if (node->getRight() == NULL) {
      if (node == parent->getLeft()) {
        parent->setLeft(child);
        diff = 1;
      }
      else {
        parent->setRight(child);
        diff = -1;
      }
      if (child != NULL) {
        child->setParent(node->getParent());
      }
    }
    delete node;
  }

  //removingNode has two children
  //  else {
  //   AVLNode<Key,Value>* pred = predecessor(node);
  //   if ( pred == NULL) {
  //     std::cout<<"node or pred is null";
  //     return;
  //   }

  //   // std::cout << "before swap: node= " << node->getValue() << " pred=" << pred->getValue();
  //   nodeSwap(node, pred);
  //   // std::cout << "swapped";
  //   // std::cout << "after swap: node= " << node->getValue() << " pred=" << pred->getValue();

  //   // if (pred == node) {
  //   //   std::cout <<"pred is same as original node";
  //   //   return;
  //   // }

  //   // std::cout << "recursing w pred";
  //   removeNode(node);
  //   // std::cout <<"returned from recursive call w pred";
  //  }

  // while (parent != NULL) {
  //   parent = balancer(parent);
  //   parent = parent->getParent();
  // }
  // if (parent != NULL) {
    removeFix(parent, diff);
  // }
  // else {
  //   if (this->root_ != NULL) {
  //     removeFix(static_cast<AVLNode<Key, Value>*>(this->root_), 0);
  //   }
  // }
}



template<class Key, class Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key,Value>* node, int diff) {
  if (node == NULL) {
    return;
  }

  AVLNode<Key, Value>* k = node->getParent();
  int difference = 0;
  if (k != NULL) {
    if (node == k->getLeft()) {
      difference = 1;
    }
    else {
      difference = -1;
    }
  }


  node->setBalance(node->getBalance() + diff);
  AVLNode<Key, Value>* balancedNode = balancer(node);

  if (k != NULL) {
    if (node == k->getLeft()) {
      k->setLeft(balancedNode);
    }
    else {
      k->setRight(balancedNode);
    }
  }


  if (difference !=0 && k != NULL) {
    removeFix(k, difference);
  }
  
}


template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key,Value>::predecessor(AVLNode<Key,Value>* node) {
  Node<Key,Value>* pred = BinarySearchTree<Key, Value>::predecessor(node);
  return static_cast<AVLNode<Key,Value>*>(pred);
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
