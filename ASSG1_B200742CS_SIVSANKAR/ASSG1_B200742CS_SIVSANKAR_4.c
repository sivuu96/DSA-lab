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
    struct node *parent;
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
void preOrder(node* node){
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}
void remove_spaces(char* s){
    char* d=s;
    do{
        while (*d==' '){
            ++d;
        }
    }while(*s++=*d++);
}
void Search(node *T, node **temp,int s)
{
    if (T==NULL)
    {(*temp)=NULL; return;}
    if(T->data==s)
    {(*temp)=T; return;}
    if(T->left!=NULL)
    {Search(T->left,temp,s);}
    if(T->right!=NULL)
    Search(T->right,temp,s);

}
int ancestor(int *arr,node *p){
    int i=0;
    while(p!=NULL){
        arr[i++]=p->data;
        p=p->parent;
    }
    return i;
}
int depth(node *p,int c){
    while(p->parent!=NULL){
        c++;
        p=p->parent;
    }
    return c;
}
int main(){
    char s[100000];
    scanf("%[^\n]s", s);
    remove_spaces(s);
    node *pa=NULL;
    node *tree=convert(pa,s,1,strlen(s)-2);
    // preOrder(tree)
    // printf("%d",tree->left->left->right->parent->data);
    int x,y;
    scanf("%d %d",&x,&y);
    int ax[10000],ay[10000];
    int ca[10000];
    node *px=NULL;
    node *py=NULL;
    Search(tree,&px,x);
    Search(tree,&py,y);
    int k=0;
    int sx=ancestor(ax,px);
    int sy=ancestor(ay,py);
    for(int i=0;i<sx;i++){
        for(int j=0;j<sy;j++){
            if(ax[i]==ay[j]){
                ca[k++]=ax[i];
            }
        }
    }
    // for(int i=0;i<k;i++){
    //     printf("%d ",ca[i]);
    // }
    int max=0,m;
    for(int i=0;i<k;i++){
        int c=0;
        node *p=NULL;
        Search(tree,&p,ca[i]);
        int n=depth(p,c);
        if(n>max){
            max=n;
            m=ca[i];
        }
    }
    printf("%d",m);
    return 1;
}