#ifndef TREE_GUARD
#define TREE_GUARD
#include <stdlib.h>

#define Leaf(v) MakeTree(v, EmptyTree(), EmptyTree())

typedef struct Node Node;
struct Node {
    int val;
    Node* left;
    Node* right;
    int height;
};

typedef Node* Tree;

Tree MakeTree(int v, Tree left, Tree right);
Tree EmptyTree();
int isEmpty(Tree t);
int root(Tree t);
Tree right(Tree t);
Tree left(Tree t);
size_t size(Tree t);
int height(Tree t);
void updateHeight(Tree t);
void display(Tree t);
void printLevel(Tree t, int level);
void freeTree(Tree t);

#endif