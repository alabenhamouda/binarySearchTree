#ifndef GUARD_BST
#define GUARD_BST

#include "tree.h"

void insert(Tree* tp, int v);
Tree search(Tree t, int v);
int getAndRemoveSmallestNode(Tree* tp);
void delete(Tree *tp, int v);
int isbst(Tree t);
int allBigger(Tree t, int v);
int allSmaller(Tree t, int v);
void displaySorted(Tree t);
void sortInArr(Tree t, int* arr, int* i);
Tree makeBalancedTree(int* arr, int n);
Tree rebalance(Tree t);
void rightRotate(Tree* tp);
void leftRotate(Tree* tp);
Tree avl_insert(Tree* tp, int v);
void avl_delete(Tree *tp, int v);

#endif