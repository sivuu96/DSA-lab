#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
}node;
node *createnode(int n){
    node *new=(node *)malloc(sizeof(node));
    new->data = n;
    new->right=NULL;
    new->left=NULL;
    new->parent=NULL;
    return new;
}
void insert(node **T,node *new){
    if((*T)==NULL){
        (*T) = new;
    }
    else{
        new->parent=(*T);
        if(new->data<(*T)->data){
            insert(&((*T)->left),new);
        }
        else{
            insert(&((*T)->right),new);
        }
    }
}
int level(node *t,int k,int r){
    if(t==NULL){
        return 0;
    }
    if(t->data==k){
        return r;
    }
    int rl=level(t->left,k,++r);
    if(rl!=0){
        return rl;
    }
    return level(t->right,k,++r);
}
node* getMinKey(node* cur){
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}
node* getMaxKey(node* cur){
    while (cur->right != NULL) {
        cur = cur->right;
    }
    return cur;
}
int getMinVal(node* cur){
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur->data;
}
int getMaxVal(node* cur){
    while (cur->right != NULL) {
        cur = cur->right;
    }
    return cur->data;
}
node *search(node *tree,int key){
    if(tree==NULL){
        return NULL;
    }
    else if(tree->data==key){
        return tree;
    }
    else if(tree->data>key){
        search(tree->left,key);
    }
    else{
        search(tree->right,key);
    }
}
void successor(node *t,int n,node *suc){
    if(t==NULL){
        return;
    }
    if(suc->right!=NULL){
        node *temp=getMinKey(suc->right);
        printf("%d\n",temp->data);
        return;
    }
    else{

    node *pa=suc->parent;
    while(pa!=NULL&&suc==pa->right){
        suc=pa;
        if(pa->parent!=NULL){
            pa=pa->parent;
        }
        else{
            printf("-1\n");
            return;
        }
    }
    printf("%d\n",pa->data);
    return;
    }
    printf("-1\n");
}
void predecessor(node *t,int n,node *pre) {
    if(t==NULL) return;
    if(pre->left!=NULL){
        node *temp=getMaxKey(pre->left);
        printf("%d\n",temp->data);
        return;
    }
    else{

    node *pa=pre->parent;
    while(pa!=NULL&&pre==pa->left){
        pre=pa;
        if(pa->parent!=NULL){
            pa=pa->parent;
        }
        else{
            printf("-1\n");
            return;
        }
    }
    printf("%d\n",pa->data);
    return;
    }
    printf("-1\n");
}
void delete(node **T,int n,node *del){
    if((*T)==NULL){
        return;
    }
    else if(del->left==NULL&&del->right==NULL){
        del=del->parent;
        if(del->right->data==n){
            del->right=NULL;
        }
        else{
            del->left=NULL;
        }
    }
    else if(del->left==NULL){
        del->data=del->right->data;
        del->right=NULL;
    }
    else if(del->right==NULL){
        del->data=del->left->data;
        del->left=NULL;
    }
    else{
        node *next=getMinKey(*T);
        int v=next->data;
        del->data=v;
        delete(T,v,next);
    }
}
void postorder(node *root){
    if(root==NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}
int addition(int a,int b){
    return a+b;
}
void inorder(node *root){
    if(root==NULL) return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}
void preorder(node* node){
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}
int main(){
    char ch;
    int n;
    int mini,maxi;
    node *bst=(node *)malloc(sizeof(node));
    bst=NULL;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'a':
                scanf("%d",&n);
                node *new=createnode(n);
                insert(&bst,new);
                // preorder(bst);
                break;
            case 'd':
                scanf("%d",&n);
                node *del=search(bst,n);
                if(del==NULL){
                    printf("-1\n");
                }
                else{
                    printf("%d\n",del->data);
                    delete(&bst,n,del);
                    // preorder(bst);
                }
                break;
            case 's':
                scanf("%d",&n);
                node *item=search(bst,n);
                if(item!=NULL){
                    printf("1\n");
                }
                else{
                    printf("-1\n");
                }
                break;
            case 'l':
                scanf("%d",&n);
                node *f=search(bst,n);
                if(f!=NULL){
                    int d=level(bst,n,0);
                    printf("%d\n",d);
                }
                else{
                    printf("-1\n");
                }
                break;
            case 'm':
                mini=getMinVal(bst);
                printf("%d\n",mini);
                break;
            case 'x':
                maxi=getMaxVal(bst);
                printf("%d\n",maxi);
                break;
            case 'u':
                scanf("%d",&n);
                node *suc=search(bst,n);
                if(suc!=NULL){
                    successor(bst,n,suc);
                }
                else{
                    printf("-1\n");
                }
                break;
            case 'r':
                scanf("%d",&n);
                node *pre=search(bst,n);
                if(pre!=NULL){
                    predecessor(bst,n,pre);
                }   
                else{
                    printf("-1\n");
                }
                break;
            case 'i':
                inorder(bst);
                printf("\n");
                break;
            case 'p':
                preorder(bst);
                printf("\n");
                break;
            case 't':
                postorder(bst);
                printf("\n");
                break;
            case 'e':
                return 1;
        }
    }
}