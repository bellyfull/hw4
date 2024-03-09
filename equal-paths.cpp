// #ifndef RECCHECK
// //if you want to add any #includes like <iostream> you must do them here (before the next endif)
// #include <iostream>
// #endif

// #include "equal-paths.h"
// using namespace std;


// // You may add any prototypes of helper functions here
// int checkEqual(Node * node, int depth = 0);

// bool equalPaths(Node * root)
// {
//     if (root == NULL) { return true; } // if theres no root

//     int result = checkEqual(root);
//     return result != -1;
// }

// int checkEqual(Node* node, int depth) {
//   if (node == NULL) { // base case
//     return depth; // if root does not exist, then will return -1
//   }
//   if (node->left == NULL && node->right == NULL) { // is a leaf 
//     return depth+1; // single root will have depth = 0
//   }
//   int leftDepth = -1;
//   int rightDepth = -1;
//   //recursing down one level
//   if (node->left != NULL) {
//     leftDepth = checkEqual(node->left, depth+1); // adding onto level and checking if child is a leaf
//   } else {
//     leftDepth = depth +1;
//   }
//   if (node->right !=NULL) {
//     rightDepth = checkEqual(node->right, depth+1); 
//   } else {
//     rightDepth = depth +1;
//   }

//   if (node->left == NULL || node->right == NULL) {
//     return -1;
//   }

//   if (leftDepth == rightDepth) {
//     return leftDepth;
//   }
//   else if (leftDepth != rightDepth) {
//     return -1;
//   }
// }

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
    if (root == NULL) { return true; } // if theres no root
    
    int result = checkEqual(root);
    return result != -1;
}

int checkEqual(Node* node, int depth) {
  if (node == NULL) { // base case
    return depth; // if root does not exist, then will return -1
  }
  if (node->left == NULL && node->right == NULL) { // is a leaf 
    return depth+1; // single root will have depth = 0
  }
  int leftDepth = -2;
  int rightDepth = -2;
  //recursing down one level
  if (node->left != NULL) {
    leftDepth = checkEqual(node->left, depth+1); // adding onto level and checking if child is a leaf
  }
  if (node->right != NULL) {
    rightDepth = checkEqual(node->right, depth+1); 
  }
  if (node->left == NULL || node->right == NULL) {
    return max(leftDepth,rightDepth);
  }
  
  if (leftDepth == rightDepth) {
    return leftDepth;
  }
  else if (leftDepth != rightDepth) {
    return -1;
  }

}