#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stack{
    int top;
    char arr[100000];
}stack;
typedef struct node{
    char *id;
    int reward;
    struct node * left;
    struct node * right;
}node;
node *createnode(char *id, int r){
    node *new=(node *)malloc(sizeof(node));
    new->id=id;
    new->reward=r;
    new->left=NULL;
    new->right=NULL;
    return new;
}
void push(stack* stack, char item){
    stack->arr[++stack->top] = item;
}
char employee_month[1000][1000];
int num = 0;
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
    int c1=0,c2=0;
    int j=f;
    char *id=(char *)malloc(sizeof(char)*100);
    char *r=(char *)malloc(sizeof(char)*100000);
    // char id[100],r[100000];
    while(s[j]!=')'&&s[j]!='('&&j<=l){
        if(s[j]==' '){
            j++;
            while(s[j]!=' '){
                r[c2++]=s[j];
                j++;
            }
            break;
        }
        else{
            id[c1++]=s[j];
            j++;
        }
    }
    int re=atoi(r);
    // printf("%d\n",re);
    // printf("%s",id);
    node *root=createnode(id,re);
    if(s[f+c1+c2+2]=='('){
        i=findex(s,f+c1+c2+2,l);
    }
    if(i!=-1){
        root->left=convert(s,f+c1+c2+4,i-2);
        root->right=convert(s,i+4,l-2);
    }
    return root;
}
node  *read_and_store(char *s,int l){
    return convert(s,2,l-3);
}
void print_employees(node *root){
    if (root == NULL)
        return;
 
    print_employees(root->left);
 
    print_employees(root->right);
 
    printf("%s ", root->id);
}
void find_employees(struct node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    else
    {
        find_employees(tree->left);
        find_employees(tree->right);
        // printf("%s ", tree->data);

        int a = 0, b = 0;
        if (tree->left == NULL)
        {
            a = 0;
        }
        else
        {
            a = tree->left->reward;
        }

        if (tree->right== NULL)
        {
            b = 0;
        }
        else
        {
            b = tree->right->reward;
        }
        if ((a+b)>=tree->reward && tree->reward != 0)
        {
            strcpy(employee_month[num], tree->id);
            num++;
        }
    }
}

int main(){
    char s[100000];
    scanf("%[^\n]s", s);
    int l=strlen(s);
    node *tree=read_and_store(s,l);
    print_employees(tree);
    find_employees(tree);
    printf("\n");
    for(int i=0;i<num;i++){
        printf("%s ",employee_month[i]);
    }
    return 0;

}