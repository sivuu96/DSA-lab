#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int key;
    struct node* left;
    struct node* right;
}node;
node *create_node(int k){
    node *new=(node *)malloc(sizeof(node));
    new->key=k;
    new->left=NULL;
    new->right=NULL;
    return new;
}
void INSERT(node **root, node *temp){
    if((*root)==NULL){ 
        (*root)=temp;
        return;
    }
    if(temp->key>(*root)->key){ 
        INSERT(&(*root)->right, temp); 
    }
    else if(temp->key<(*root)->key){ 
        INSERT(&(*root)->left,temp); 
    }
}
void inorder(node* node){
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ",node->key);
    inorder(node->right);
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
void isAVL(node *root, int *flag){
    int b;
    if (root==NULL){
        return;
    }
    isAVL(root->left,flag);
    b=GETBALANCE(root);
    if(b!= 0 && b!= 1 && b!=-1){
        (*flag)++;
    }
    isAVL(root->right,flag);
}
int main(){
    char c;
    int n;
    node *temp=NULL;
    node *root=NULL;
    int flag=0;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                getchar();
                scanf("%d",&n);
                temp=create_node(n);
                INSERT(&root,temp);
                // inorder(root);
                break;
            case 'c':
                isAVL(root,&flag);
                // printf("%d\n",flag);
                if(flag){
                    printf("0\n");
                }
                else{
                    printf("1\n");
                }
                flag=0;
                break;
            case 't':
                return 0;
        }
    }
}