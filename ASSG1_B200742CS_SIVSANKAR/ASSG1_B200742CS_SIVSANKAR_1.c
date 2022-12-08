#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    struct node* parent;
}node;
typedef struct queue{
struct node * arr[100];
int front;
int rear;
}Q;
node *create_node(int n){
    node *temp=(node*)malloc(sizeof(node));
    temp->key = n;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}
int height(node* t){
    if (t == NULL)
        return 0;
    else {
        int lh = height(t->left);
        int rh = height(t->right);
        if (lh > rh){
            return (lh+1 );
        }
        else{
            return (rh+1);
        }
    }
}
void position(node **t, int i,int h,node *new){
    if(h==1){
        (*t)->left=new;
        new->parent=(*t);
        return;
    }
    else{
        
    }

}
// void inorder(struct node* node)
// {
//     if (node == NULL)
//         return;
 
//     /* first recur on left child */
//     inorder(node->left);
 
//     /* then print the data of node */
//     printf("%d ", node->key);
 
//     /* now recur on right child */
//     inorder(node->right);
// }
void levelordert(node **t,node *new){
    int h=height(*t);
    for(int i=1;i<=h;i++){
        position(t,i,h,new);
    }

}
node *INSERT(node **T,node *new){
    
}
void print(node *p){
    if(p==NULL)
        {   printf("(");
           printf(")");
            return;
        }
        printf("(");
        printf("%d",p->key);
    print(p->left);
    print(p->right);
    printf(")");
}
int main(){
    node *bt=(node*)malloc(sizeof(node));
    bt=NULL;
    int n;
    char c;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':scanf("%d",&n);
            node *new=create_node(n);
            bt=INSERT(bt,new);      
            // printf("%d",bt->key);  
            // inorder(bt);                    
            break;
            case 'p':print(bt);
            break;
            case 'e':return 1;
        }
    }
}