#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    int h;
}node;
node *create_node(int k){
    node *new=(node *)malloc(sizeof(node));
    new->key=k;
    new->left=NULL;
    new->right=NULL;
    new->h=1;
    return new;
}
node *LEFTROTATE(node *root){
    node *nr = root->right;
    node *temp = nr->left;
    nr->left = root;
    root->right = temp;
    return nr;
}
node *RIGHTROTATE(node *root)
{
    node *nr = root->left;
    node *t = nr->right;
    nr->right = root; 
    root->left = t;
    return nr;
}
int Height(node *root){
    if (root == NULL){
        return 0;
    }
    int lefth = Height(root->left);
    int righth = Height(root->right);
    if (lefth > righth)
        return (lefth + 1);
    else
        return (righth + 1);
}
int GETBALANCE(node *root){
    int l,r;
    l=Height(root->left);
    r=Height(root->right);
    return (l-r);
}
node *getMin(node *root){
    while(root->right!=NULL){
        root=root->right;
    }
    return root;
}
void INSERT(node **root, node *temp){
    if((*root)==NULL){ 
        (*root)=temp;
    }
    if(temp->key>(*root)->key){ 
        INSERT(&(*root)->right, temp); 
    }
    else if(temp->key<(*root)->key){ 
        INSERT(&(*root)->left,temp); 
    }
    int b=GETBALANCE(*root);

    if(b>1&&temp->key<(*root)->left->key){
        (*root)=RIGHTROTATE(*root);
        return;
    }
    else if(b<-1&&temp->key>(*root)->right->key){
        (*root)=LEFTROTATE(*root);
        return;
    }
    else if(b>1&&temp->key>(*root)->left->key){
        (*root)->left=LEFTROTATE((*root)->left);
        (*root)=RIGHTROTATE(*root);
        return;
    }
    else if(b<-1&&temp->key<(*root)->right->key){
        (*root)->right=RIGHTROTATE((*root)->right);
        (*root)=LEFTROTATE(*root);
        return;
    }
}
void DELETENODE(node **root,int num){
    node *temp=NULL;
    if((*root)== NULL){
        return;
    }
    if(num>(*root)->key){
        DELETENODE(&((*root)->right),num);
    }
    else if(num<(*root)->key){
        DELETENODE(&((*root)->left),num);
    }
    else{
        if((*root)->left==NULL||(*root)->right==NULL){
            if((*root)->right==NULL&&(*root)->left!=NULL){
                temp=(*root)->left;
            }
            else if((*root)->right!=NULL&&(*root)->left==NULL){
                temp=(*root)->right;
            }
            if(temp!=NULL){
                (*root)=temp;
            }
            else{
                temp=(*root);
                (*root)=NULL;
            }
        }
        else{
            temp=getMin((*root)->right);
            (*root)->key=temp->key;
            DELETENODE(&(*root)->right,temp->key);
        }
    }
    if((*root)== NULL){
        return;
    }
    int b=GETBALANCE(*root);
    if(b>1&&GETBALANCE((*root)->left)>=0){
        RIGHTROTATE((*root));
        return;
    }
    else if(b<-1&&GETBALANCE((*root)->right)<=0){
        LEFTROTATE(*root);
        return;
    }
    else if(b>1&&GETBALANCE((*root)->left)<0){
        (*root)->left=LEFTROTATE((*root)->left);
        (*root)=RIGHTROTATE(*root);
        return;
    }
    else if(b<-1&&GETBALANCE((*root)->right)>0){
        (*root)->right=RIGHTROTATE((*root)->right);
        (*root)=LEFTROTATE(*root);
        return;
    }
}
node *SEARCH(node *root,int n){
    if((root)==NULL){
        return NULL;
    }
    if(root->key==n){
        return root;
    }
    else if(root->key>n){
        SEARCH(root->left,n);
    }
    else if(root->key<n){
        SEARCH(root->right,n);
    }
}
void PRINTTREE(node *root){
    if(root==NULL){
        return;
    }
    printf("%d",root->key);
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
    char c;
    int n,bal;
    node *temp=NULL;
    node *root=NULL;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                getchar();
                scanf("%d",&n);
                temp=create_node(n);
                INSERT(&root,temp);
                break;
            case 'd':
                getchar();
                scanf("%d",&n);
                temp=SEARCH(root,n);
                if(temp==NULL){
                    printf("FALSE\n");
                }
                else{
                    printf("%d\n",n);
                }
                DELETENODE(&root,n);
                break;
            case 's':
                getchar();
                scanf("%d",&n);
                temp=SEARCH(root,n);
                if(temp==NULL){
                    printf("FALSE\n");
                }
                else{
                    printf("TRUE\n");
                }
                break;
            case 'b':
                getchar();
                scanf("%d",&n);
                temp=SEARCH(root,n);
                if(temp==NULL){
                    printf("FALSE\n");
                }
                else{
                    bal=GETBALANCE(temp);
                    printf("%d\n",bal);
                }
                break;
            case 'p':
                getchar();
                printf("( ");
                PRINTTREE(root);
                printf(" )\n");
                break;
            case 'e':
                return 0;
        }
    }
}
