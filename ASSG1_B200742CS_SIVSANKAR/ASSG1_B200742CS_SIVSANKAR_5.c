#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stack{
    int top;
    char arr[100000];
}stack;
typedef struct node{
    int data;
    struct node * left;
    struct node * right;
}node;
node *createnode(int key){
    node *new=(node *)malloc(sizeof(node));
    new->data = key;
    new->left=NULL;
    new->right=NULL;
    return new;
}
void push(stack* stack, char item){
    stack->arr[++stack->top] = item;
}
void pop(stack* stack){
    stack->top--;
}
int isEmpty(stack* stack){
    return stack->top == -1;
}
int findex(char *s,int nf,int nl){
    stack *okda=(stack*)malloc(sizeof(stack));
    okda->top=-1;
    push(okda,s[nf]); 
    for(int i=nf+1;i<=nl;i++){
        if(s[i]=='('){
            push(okda,s[i]);
        }
        else if(s[i]==')'){
            if(okda->arr[0]=='('){
                pop(okda);
            }
            if(isEmpty(okda)){
                return i;
            }
        }
    }
    return -1;
}
node *convert(char *s,int f,int l){
    if(f>l){
        return NULL;
    }
    int i=-1;
    int c=0;
    int j=f;
    char *t=malloc(7*sizeof(char));
    while(s[j]!=')'&&s[j]!='('&&j<=l){
        t[c++]=s[j];
        j++;
    }
    int v=atoi(t);
    node *root=createnode(v);
    if(f+c<=l&&s[f+c]=='('){
        i=findex(s,f+c,l);    
    
    }
    if(i!=-1){
        root->left=convert(s,f+c+1,i-1);
        root->right=convert(s,i+2,l-1);
    }
    return root;
}
// void preOrder(node* node){
//     if (node == NULL)
//         return;
//     printf("%d ", node->data);
//     preOrder(node->left);
//     preOrder(node->right);
// }
void remove_spaces(char* s){
    char* d=s;
    do{
        while (*d==' '){
            ++d;
        }
    }while(*s++=*d++);
}
int flag(node *tree, node *temp){
    if (tree!=NULL){
        if (flag(tree->left,temp)!=2){
            return 0;
        }
        if (temp!=NULL && temp->data>= tree->data){
            return 0;
        }
        temp=tree;
        return flag(tree->right, temp);
    }
    return 2;
}
int sizeTree(node *bst){
    if (bst != NULL){
        return(sizeTree(bst->right)+sizeTree(bst->left)+1);
    }
    else{
        return 0;
    }
}
node *bst(node *tree){
    node *temp = NULL;
    if(flag(tree, temp)==2){
       return tree;
    }
    else if(flag(tree->left, temp)==2){
        return tree->left;
    }
    else if(flag(tree->right, temp)==2){
        return tree->right;
    }
}
int main(){
    char s[100000];
    scanf("%[^\n]s", s);
    remove_spaces(s);
    node *tree=convert(s,1,strlen(s)-2);
    // preOrder(tree);
    node *btree=bst(tree);
    int out=sizeTree(btree);
    printf("%d",out);
    return 1;
}