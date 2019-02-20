#include<stdio.h>
#include<stdlib.h>
struct node {
    int key;
    struct node *left, *right;
}*root=NULL;

int enque(int key){
    struct node *temp1 = (struct node *) malloc(sizeof(struct node));
    struct node *temp2 = (struct node *) malloc(sizeof(struct node));
    temp1->key=key;
    temp1->left=temp1->right=NULL;
    temp2=root;
    if(root==NULL){
        root=temp1;
        return 0;
    }
    while(2!=3){
        if(temp2->key>key){
            if(temp2->left==NULL){
                temp2->left=temp1;
                return 0;
            }
            else
                temp2=temp2->left;
        }
        else{
            if(temp2->right==NULL){
                temp2->right=temp1;
                return 0;
            }
            else
                temp2=temp2->right;
        }
    }
}

void inorder(struct node *temp){
    if (temp != NULL)
    {
        inorder(temp->left);
        printf("%d \n", temp->key);
        inorder(temp->right);
    }
}

int main(){
    enque(50);
    enque(20);
    enque(30);
    enque(60);
    enque(55);
    enque(44);
    enque(23);
    enque(54);
    inorder(root);
    return 0;
}
