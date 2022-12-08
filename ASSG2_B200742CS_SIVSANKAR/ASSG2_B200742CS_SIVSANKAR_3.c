#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tsize 128
typedef struct node{
    char *fname;
    char *lname;
    struct node *left;
    struct node *right;
    int age;
}node;
typedef struct value{
    char *name1;
    char *name2;
    int age;
    struct value* next;
}v;
node *createnode(char fn[], char ln[],int age){
    node *temp=(node *)malloc(sizeof(node));
    temp->fname=fn;
    temp->lname=ln;
    temp->age=age;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
int hashfn(char *ln,int s){
    for(int i=0;i<strlen(ln);i++){
        s+=ln[i];
    }
    return (s%tsize);
}
void INSERTDATA(node **head,node *new){
    if((*head)==NULL){
        (*head) = new;
     
    }
    else{
        if((*head)->age>new->age){
            INSERTDATA(&((*head)->left),new);
        }
        else if((*head)->age<new->age){
            INSERTDATA(&((*head)->right),new);
        }
    }
}
void inorder(struct node* node)
{
    if (node == NULL)
        return;
 
    inorder(node->left);
 
    printf("%s %s %d\n", node->fname,node->lname,node->age);
    inorder(node->right);
}
v *create(char *fname, char *lname,int age){
    v* temp =(v *)malloc(sizeof(v));
    temp->name1=fname;
    temp->name2=lname;
    temp->age=age;
    temp->next=NULL;
    return temp;
}
void insert(v** head,v* new){
    
    if((*head)==NULL){
        (*head) = new;
    }
    else{
        v*temp=*head;
        while(temp->next!=NULL){
            (temp)=((temp)->next);
        }
        (temp)->next=new;
    }
}
int search(v *head,char *fn,char *ln){
    v* temp =head;
    while(temp!=NULL){
        if(strcmp(temp->name1,fn)==0&&strcmp(temp->name2,ln)==0){
            return temp->age;
        }
        else{
            temp=temp->next;
        }
    }
    return 0;

}
void print(v *head){
    v* temp =head;
    while(temp!=NULL){
        printf("%s %s %d\n",temp->name1,temp->name2,temp->age);
        temp=temp->next;
    }
}
void PRINTRELATIVES(node *head,int k){
    if(head->age!=k){
        printf("%s %s %d\n",head->fname,head->lname,head->age);
        if(head->age<k){
            PRINTRELATIVES(head->right,k);
        }
        else{
            PRINTRELATIVES(head->left,k);
        }
    }
    else{
        printf("%s %s %d\n",head->fname,head->lname,head->age);
        return;
    }
}
int main(){
    node *arr[tsize];
    for(int i=0; i<tsize; i++){
        arr[i]=NULL;
    }
    char c;
    v* head = NULL;
    while(1){
        scanf("%c",&c);
        getchar();
        int age;
        char *fn=(char *)malloc(sizeof(char)*2000);
        char *ln=(char *)malloc(sizeof(char)*2000);
        
        node *new=NULL;
        v *a=NULL;
        switch(c){
            case 'i':
                scanf("%s",fn);
                scanf("%s",ln);
                scanf("%d",&age);
                getchar();
                new=createnode(fn,ln,age);
                a=create(fn,ln,age);
                // printf("6");
                int s=0;
                int i=hashfn(ln,s);
                // printf("%d",i);
                INSERTDATA(&arr[i],new);
                insert(&head,a);
                // print(head);
                // printf("%d",i);
                // inorder(arr[i]);
                // printf("%s %d\n",arr[i]->fname,arr[i]->age);
                break;
            case 'p':
                scanf("%s",fn);
                getchar();
                scanf("%s",ln);
                getchar();
                int sum=0;
                int in=hashfn(ln,sum);
                int flag=search(head,fn,ln);
                // printf("%d\n",flag);
                if(flag){
                    PRINTRELATIVES(arr[in],flag);
                }
                else{
                    printf("-1\n");
                }
                break;
            case 't':
                return 1;
        }
    }
    return 0;
}