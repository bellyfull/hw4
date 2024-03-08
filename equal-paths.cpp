#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int checkEqual(Node * node, int depth = 0);

bool equalPaths(Node * root)
{
    // Add your code below
    // if (root == NULL) { return true; } // if theres no root
    // if (root->left && root->right == NULL) { return true; } // if it has no leaves

    int result = checkEqual(root);
    return result != -1;
}

int checkEqual(Node* node, int depth) {
  if (node == NULL) { // base case
    return depth-1; // if root does not exist, then will return -1
  }
  if (node->left == NULL && node->right == NULL) { // is a leaf 
    return depth; // single root will have depth = 0
  }
  //recursing down one level
  int leftDepth = checkEqual(node->left, depth+1); // adding onto level and checking if child is a leaf
  int rightDepth = checkEqual(node->right, depth+1); 
  
  if (leftDepth != rightDepth) {
    return -1;
  }
}
