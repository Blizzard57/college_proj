#include<stdlib.h>
#include<stdio.h>
struct node{
    int key, sum;
    struct node *left, *right;
};

struct node *newNode(int item){
    struct node *temp =(struct node *)malloc(sizeof(struct node));
    temp->key = item;
    //temp->sum = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert(struct node* node, int key) { 
    if (node == NULL) return newNode(key); 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);    
    return node; 
} 

void inorder(struct node *root){
    if (root != NULL){
        inorder(root->left);
        printf("key : %d sum : %d\n", root->key,root->sum);
        inorder(root->right);
    }
}

int sum(struct node *node){
    if(node == NULL)
        return 0;
    int val=node->key;
    node->key = sum(node->left) + sum(node->right);
    return node->key + val;
}

void summing(struct node *root){
     if (root != NULL){
         summing(root->left);
         root->sum=sum(root);
         summing(root->right);
     }
 }


int main(){
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30); 
    insert(root, 20); 
    summing(root);
    inorder(root);
    printf("**%d\n",sum(root->left));
}