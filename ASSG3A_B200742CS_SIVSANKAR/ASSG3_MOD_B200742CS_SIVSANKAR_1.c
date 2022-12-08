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
int d;
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
int flag=0;
int count=0;
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
    // if(root==NULL){
    //     return;
    // }
    // printf("%d ",root->key);
    // if(root->colour==0){
    //     printf("B");
    // }
    // else{
    //     printf("R");
    // }
    // if(root->left==NULL&&root->right==NULL){
    //     printf(" ( ) ( )");
    //     return;
    // }
    // else if(root->left!=NULL&&root->right!=NULL){
    //     printf(" ( ");
    //     PRINTTREE(root->left);
    //     printf(" ) ( ");
    //     PRINTTREE(root->right);
    //     printf(" )");
    // }
    // else if(root->left==NULL&&root->right!=NULL){
    //     printf(" ( ) ( ");
    //     PRINTTREE(root->right);
    //     printf(" )");
    // }
    // else if(root->left!=NULL&&root->right==NULL){
    //     printf(" ( ");
    //     PRINTTREE(root->left);
    //     printf(" ) ( )");
    // }
}
void downdist(node *root, int d){
    if (root == NULL || d < 0)
        return;
    if (d == 0 && root->colour == 0){
        flag++;
        return;
    }
    downdist(root->left,d-1);
    downdist(root->right,d-1);
}
int beaut(node *root, node *nd){
    if (root == NULL)
        return -1;
    if (root == nd){
        downdist(root,d);
        return 0;
    }
    if (d == 1){
        if (nd->parent->colour == 0)
            flag++;
        if (nd->right != NULL){
            if (nd->right->colour == 0)
                flag++;
        }
        if (nd->left != NULL){
            if (nd->left->colour == 0)
                flag++;
        }
        return 0;
    }
    int dld = beaut(root->left, nd);
    int s=dld+5;
    int parent=dld+3;
    int q=dld+1;
    if (dld != -1){
        if (dld + 1 == d && nd->colour == 0)
            flag++;

        else
            downdist(root->right, d - dld - 2);

        return 1 + dld;
    }
    int drd = beaut(root->right, nd);
    int k=dld+drd;
    if(k>0){

    }else{}
    if (drd != -1){
        if (drd + 1 == d && nd->colour == 0)
            flag++;
        else
            downdist(root->left, d - drd - 2);
        return 1 + drd;
    }
    return -1;
}
void TRAVERSE(node *nd,node *root){
    flag = 0;
    if (nd != NULL){
        int check = beaut(root, nd);
        if (!(flag == 0 || check == -1)){
            count++;
        }
        flag = 0;
        TRAVERSE(nd->right, root);
        TRAVERSE(nd->left, root);
    }
}
void CHECKBEAUTIFUL(node *T,int c,int kk,int bc[]){
    if(T==NULL){
        return;
    }
    if(bc[0]==-1){
        return;
    }
    if(T->left!=NULL){ 
        if((c==0 && T->left->colour==1) || (c==1 && T->left->colour==0)){
            if(T->left !=NULL && kk !=T->left->key){
                int k=T->left->colour;
                CHECKBEAUTIFUL(T->left,k,T->left->key,bc);
            } 
        }
        else
    {bc[0]=-1;return;} }
    if(T->right!=NULL)
   { if((c==0 && T->right->colour==1) || (c==1&& T->right->colour==0)) 
    {
      if(T->right !=NULL && kk !=T->right->key)  
      {
          int k=T->right->colour;
          CHECKBEAUTIFUL(T->right,k,T->right->key,bc);
      } 
    }
    else
    {bc[0]=-1;return;} }
    if(T->parent!=NULL)
   { if((c==0 && T->parent->colour==1) || (c==1 && T->parent->colour==0)) 
    {
      if(T->parent !=NULL && kk !=T->parent->key)  
      {
          int k=T->parent->colour;
          CHECKBEAUTIFUL(T->left,k,T->key,bc);
      } 
    }
    else
    {bc[0]=-1;return;} }
}
int main(){
    char c[5];
    int n;
    int nu;
    scanf("%d",&nu);
    node *tree=NULL;
    node *new=NULL;
    while(nu--){
        scanf("%s",c);
        n=atoi(c);
        // printf("%d",n);
            if(tree==NULL){
                new=createNode(n,0);
                tree=new;
                // printf("( ");
                PRINTTREE(tree);
                // printf(" )\n");
                continue;
            }
            else{
                new=createNode(n,1);
            }
            tree=INSERTREDBLACK(tree,new,n);
            if(tree!=NULL){
                // printf("( ");
                PRINTTREE(tree);
                // printf(" )\n");
            }
            else{
                // printf("( )\n");
            }
    }
    int ce[1];
    ce[0]=-2;
    CHECKBEAUTIFUL(tree,(tree->colour),(tree->key),ce);
    // TRAVERSE(tree,tree);
    // printf("\n");
    // printf("%d\n", count);
    if(ce[0]!=(-2))
    printf("%d\n",ce[0]);
    else
    {printf("1\n");}
    return 0;
}