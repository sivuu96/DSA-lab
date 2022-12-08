#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    int data;
    struct node * left;
    struct node * right;
    struct node *parent;
}node;
typedef struct stack{
    int top;
    char arr[100000];
}stack;
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
node *convert(node *pa,char *s,int f,int l){
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
    root->parent=pa;
    pa=root;
    if(f+c<=l&&s[f+c]=='('){
        i=findex(s,f+c,l);    
    
    }
    if(i!=-1){
        root->left=convert(pa,s,f+c+1,i-1);
        root->right=convert(pa,s,i+2,l-1);
    }
    return root;
}
void remove_spaces(char* s){
    char* d=s;
    do{
        while (*d==' '){
            ++d;
        }
    }while(*s++=*d++);
}
void Search(node *T, node **temp,int s){
    if (T==NULL)
    {(*temp)=NULL; return;}
    if(T->data==s)
    {(*temp)=T; return;}
    if(T->left!=NULL)
    {Search(T->left,temp,s);}
    if(T->right!=NULL)
    Search(T->right,temp,s);
}
// void preOrder(node* node){
//     if (node == NULL)
//         return;
//     printf("%d ", node->data);
//     preOrder(node->left);
//     preOrder(node->right);
// }
int traverse(node *l,node *r,int d,int sum,int i){
    if((l != NULL||r != NULL)&&i<d){
        i++;
        sum=l->data+r->data+sum;
        traverse(l->left,l->right,d,sum,i);
        i=1;
        traverse(r->left,r->right,d,sum,i);
    }
    return sum;
}
int traverseP(node *p,node *l,node *r,int d,int sum,int i){

}
int findid(node *p,int d,int sum){
    int i=0;
    sum=traverse(p->left,p->right,d,sum,i);
    i=0;
    // node* templ,*tempr;
    // sum=traverseP(p->parent,templ,tempr,d,sum,i);
    return sum;
}
int main(){
    char s[100000];
    scanf("%[^\n]s", s);
    remove_spaces(s);
    node *pa=NULL;
    node *tree=convert(pa,s,1,strlen(s)-2);
    // preOrder(tree);
    int id,d;
    scanf("%d %d",&id,&d);
    node* se=NULL;
    Search(tree,&se,id);
    int sum=0;
    int f=findid(se,d,sum)+id;
    printf("%d",f);
}