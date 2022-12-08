#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    int key;
    int colour;
    struct node* left;
    struct node* right;
    struct node* parent;
}node;
node *createNode(int n,int c){
    node *new=(node *)malloc(sizeof(node));
    new->key=n;
    new->left=NULL;
    new->right=NULL;
    new->parent=NULL;
    new->colour=c;
    return new;
}
void INSERT(node **t,node *new,int n){
    if((*t)==NULL){
        (*t)=new;
        return;
    }
    new->parent=(*t);
    if(n<(*t)->key){
        INSERT(&((*t)->left),new,n);
    }
    else if(n>(*t)->key){
        INSERT(&((*t)->right),new,n);
    }
}
void RIGHTROTATE(node *T,node *temp){
    node* new = temp->left;
    temp->left = new->right;
    if (temp->left!=NULL){
        temp->left->parent = temp;
    }
    new->parent = temp->parent;
    if (temp->parent==NULL){
        T = new;
    }
    else if (temp == temp->parent->left){
        temp->parent->left = new;
    }
    else{
        temp->parent->right = new;
    }
    new->right = temp;
    temp->parent = new;
}
void LEFTROTATE(node *T,node *temp){
    node* new= temp->right;
    temp->right = new->left;
    if (temp->right!=NULL){
        temp->right->parent=temp;
    }
    new->parent = temp->parent;
    if (temp->parent==NULL){
        T = new;
    }
    else if (temp == temp->parent->left){
        temp->parent->left = new;
    }
    else{
        temp->parent->right = new;
    }
    new->left = temp;
    temp->parent = new;
}
node *INSERTREDBLACK(node *T,node *new,int n){
    INSERT(&T,new,n);
    while(new!=T&& new!=NULL && new->parent !=NULL && new->parent->parent !=NULL && new->parent->colour==1&&new->colour!=0){
        node *temp=NULL;
        if(new->parent==new->parent->parent->right){
            temp=new->parent->parent->left;
        }
        else{
            temp=new->parent->parent->right;
        }
        if(temp!=NULL&&temp->colour==1){
            temp->colour=0;
            new->parent->colour=0;
            new->parent->parent->colour=1;
            new=new->parent->parent;
        }
        else{
            if(new->parent==new->parent->parent->left&&new==new->parent->left){
                int i=new->parent->colour;
                new->parent->colour=new->parent->parent->colour;
                new->parent->parent->colour=i;
                RIGHTROTATE(T,new->parent->parent);
            }
            else if(new->parent==new->parent->parent->right&&new==new->parent->right){
                int i=new->parent->colour;
                new->parent->colour=new->parent->parent->colour;
                new->parent->parent->colour=i;
                LEFTROTATE(T,new->parent->parent);
            }
            else if(new->parent==new->parent->parent->left&&new==new->parent->right){
                int i=new->colour;
                new->colour=new->parent->parent->colour;
                new->parent->parent->colour=i;
                LEFTROTATE(T,new->parent);
                RIGHTROTATE(T,new->parent);
            }
            else if(new->parent==new->parent->parent->right&&new==new->parent->left){
                int i=new->colour;
                new->colour=new->parent->parent->colour;
                new->parent->parent->colour=i;
                RIGHTROTATE(T,new->parent);
                
                LEFTROTATE(T,new->parent);
                
            }
        }
    }
    while(T->parent!=NULL){
        T=T->parent;
    }
    T->colour=0;
    return T;
}
void PRINTTREE(node *root){
    if(root==NULL){
        return;
    }
    printf("%d ",root->key);
    if(root->colour==0){
        printf("B");
    }
    else{
        printf("R");
    }
    if(root->left==NULL&&root->right==NULL){
        printf(" ( ) ( )");
        return;
    }
    else if(root->left!=NULL&&root->right!=NULL){
        printf(" ( ");
        PRINTTREE(root->left);
        printf(" ) ( ");
        PRINTTREE(root->right);
        printf(" )");
    }
    else if(root->left==NULL&&root->right!=NULL){
        printf(" ( ) ( ");
        PRINTTREE(root->right);
        printf(" )");
    }
    else if(root->left!=NULL&&root->right==NULL){
        printf(" ( ");
        PRINTTREE(root->left);
        printf(" ) ( )");
    }
}
int main(){
    char c[5];
    int n;
    node *tree=NULL;
    node *new=NULL;
    while(1){
        scanf("%s",c);
        n=atoi(c);
        // printf("%d",n);
        if(c[0]!='t'){
            if(tree==NULL){
                new=createNode(n,0);
                tree=new;
                printf("( ");
                PRINTTREE(tree);
                printf(" )\n");
                continue;
            }
            else{
                new=createNode(n,1);
            }
            tree=INSERTREDBLACK(tree,new,n);
            if(tree!=NULL){
                printf("( ");
                PRINTTREE(tree);
                printf(" )\n");
            }
            else{
                printf("( )\n");
            }
        }
        else{
            return 0;
        }
    }
}