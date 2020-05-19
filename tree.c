#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
// Constructor
Tree MakeTree(int v, Tree left, Tree right){
    Node* root = (Node*) malloc(sizeof(*root));
    root->val = v;
    root->left = left;
    root->right = right;
    updateHeight(root);
    return root;
}
// Contructor for empty trees
Tree EmptyTree(){
    return NULL;
}

int isEmpty(Tree t){
    return t == NULL;
}

int root(Tree t){
    if(!isEmpty(t))
        return t->val;
}

Tree right(Tree t){
    if(!isEmpty(t))
        return t->right;
}

Tree left(Tree t){
    if(!isEmpty(t))
        return t->left;
}

size_t size(Tree t){
    if(isEmpty(t))
        return 0;
    return 1 + size(left(t)) + size(right(t));
}

int max(int h1, int h2){
    if(h1 > h2)
        return h1;
    return h2;
}

int height(Tree t){
    if(isEmpty(t))
        return -1;
    return t->height; 
}

void updateHeight(Tree t){
    if(!isEmpty(t))
        t->height = 1 + max(height(left(t)), height(right(t)));
}

void printLevel(Tree t, int level){
    if(!isEmpty(t)){
        if(level == 0)
            printf("%d ", root(t));
        else{
            printLevel(left(t), level - 1);
            printLevel(right(t), level - 1);
        }
    }
}

void display(Tree t){
    int h = height(t);
    int i;
    for(i = 0; i <= h; i++){
        printLevel(t, i);
        printf("\n");
    }
}

void freeTree(Tree t){
    if(!isEmpty(t)){
        freeTree(left(t));
        freeTree(right(t));
        free(t);
    }
}