#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "bst.h"

void insert(Tree* tp, int v){
    Tree t = *tp;
    if(isEmpty(t))
        *tp = Leaf(v);
    else if(v < root(t)){
        insert(&(t->left), v);
        updateHeight(t);
    }
    else if(v > root(t)){
        insert(&(t->right), v);
        updateHeight(t);
    }
    else
        printf("Error\n");
}

Tree search(Tree t, int v){
    if(isEmpty(t))
        return EmptyTree();
    if(v < root(t))
        return search(left(t), v);
    if(v > root(t))
        return search(right(t), v);
    return t;
}

int getAndRemoveSmallestNode(Tree* tp){
    Tree t = *tp;
    if(!isEmpty(t)){
        if(!isEmpty(left(t))){
            int ret = getAndRemoveSmallestNode(&(t->left));
            updateHeight(t);
            return ret;
        }
        int ret = root(t);
        *tp = right(t);
        free(t);
        return ret;
    }
}

void delete(Tree *tp, int v){
    Tree t = *tp;
    if(!isEmpty(t)){
        if(v < root(t))
            delete(&(t->left), v);
        else if (v > root(t))
            delete(&(t->right), v);
        else {
            if(isEmpty(left(t))){
                *tp = right(t);
                free(t);
            }
            else if (isEmpty(right(t))){
                *tp = left(t);
                free(t);
            }
            else {
                t->val = getAndRemoveSmallestNode(&(t->right));
            }
        }
        updateHeight(*tp);
    }
}

int allSmaller(Tree t, int v){
    if(isEmpty(t))
        return 1;
    if(root(t) > v)
        return 0;
    return allSmaller(right(t), v);
}

int allBigger(Tree t, int v){
    if(isEmpty(t))
       return 1; 
    if(root(t) < v)
        return 0;
    return allBigger(left(t), v);
}

int isbst(Tree t){
    if(isEmpty(t))
        return 1;
    return isbst(left(t)) && isbst(right(t)) && 
            allSmaller(left(t), root(t)) && allBigger(right(t), root(t));
}

void displaySorted(Tree t){
    if(!isEmpty(t)){
        display(left(t));
        printf("%d ", root(t));
        display(right(t));
    }
}

void sortInArr(Tree t, int* arr, int* i){
    if(!isEmpty(t)){
        sortInArr(left(t), arr, i);
        arr[(*i)++] = root(t);
        sortInArr(right(t), arr, i);
    }
}

Tree makeBalancedTree(int* arr, int n){
    if(n > 0){
        return MakeTree(arr[n/2], makeBalancedTree(arr, n/2), 
        makeBalancedTree(arr + n/2 + 1, (n&1 ? n/2 : n/2 - 1)));
    }
    else{
        return EmptyTree();
    }
}

Tree rebalance(Tree t){
    int n = size(t);
    int *arr = malloc(n * sizeof(int));
    int i = 0;
    sortInArr(t, arr, &i);
    return makeBalancedTree(arr, n);
}

void rightRotate(Tree* tp){
    Tree t = *tp;
    if(!isEmpty(t) && !isEmpty(left(t))){
        Tree lr = right(left(t));
        left(t)->right = t;
        *tp = left(t);
        t->left = lr;
        updateHeight(right(*tp));
        updateHeight(*tp);
    }
}

void leftRotate(Tree* tp){
    Tree t = *tp;
    if(!isEmpty(t) && !isEmpty(right(t))){
        Tree rl = left(right(t));
        right(t)->left = t;
        *tp = right(t);
        t->right = rl;
        updateHeight(left(*tp));
        updateHeight(*tp);
    }
}

Tree avl_insert(Tree* tp, int v){
    Tree t = *tp;
    if(isEmpty(t)){
        *tp = Leaf(v);
        return EmptyTree();
    }
    if(v < root(t)){
        Tree x = avl_insert(&(t->left), v);
        updateHeight(t);
        Tree y = left(t);
        if(height(left(t)) - height(right(t)) >= 2){
            if(x == left(y)){
                rightRotate(tp);
            }
            else{
                leftRotate(&(t->left));
                rightRotate(tp);
            }
        }
        return left(t);
    }
    else if (v > root(t)){
        Tree x = avl_insert(&(t->right), v);
        updateHeight(t);
        Tree y = right(t);
        if(height(right(t)) - height(left(t)) >= 2){
            if(x == right(y)){
                leftRotate(tp);
            }
            else {
                rightRotate(&(t->right));
                leftRotate(tp);
            }
        }
        return right(t);
    }
}

void avl_delete(Tree *tp, int v){
    Tree t = *tp;
    if(!isEmpty(t)){
        if(v < root(t)){
            avl_delete(&(t->left), v);
            updateHeight(t);
            if(height(right(t)) == height(left(t)) + 2){
                if(height(right(right(t))) == height(left(t)) + 1){
                    leftRotate(tp);
                }
                else {
                    rightRotate(&(t->right));
                    leftRotate(tp);
                }
            }
        }
        else if (v > root(t)){
            avl_delete(&(t->right), v);
            updateHeight(t);
            if(height(left(t)) == height(right(t)) + 2){
                if(height(left(left(t))) == height(right(t)) + 1){
                    rightRotate(tp);
                }
                else {
                    leftRotate(&(t->left));
                    rightRotate(tp);
                }
            }
        }
        else{
            if(isEmpty(left(t))){
                *tp = right(t);
                free(t);
            }
            else if (isEmpty(right(t))){
                *tp = left(t);
                free(t);
            }
            else {
                t->val = getAndRemoveSmallestNode(&(t->right));
                updateHeight(t);
            }
        }
    }
}