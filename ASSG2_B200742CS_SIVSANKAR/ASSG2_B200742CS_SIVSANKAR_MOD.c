#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef struct node{
    char *word;
    int s;
    struct node *next;
}node;
node *createnode(char *word){
    node *temp=(node *)malloc(sizeof(node));
    temp->word=word;
    temp->next=NULL;
    return temp;
}
// void insert(node **head,node *new){
//     node *temp=*head;
//     if(temp==NULL){
//         (*head)=new;
//     }
//     else{
//         while(temp->next!=NULL){
//             temp=temp->next;
//         }
//         temp->next=new;
//     }
// }
int hashfn(char *s,int n,int l){
    
}
int main(){
    int n,l,i,sum;
    scanf("%d",&n);
    getchar();
    node *h[n];
    char c;
    while(1){
        scanf("%c",&c);
        getchar();
        char *name=(char *)malloc(sizeof(char)*2000);
        node *new;
        switch(c){
            case 'i':
                scanf("%s",name);
                getchar();
                new=createnode(name);
                
                l=strlen(name);
                
                sum=0;
                for(int i=0;i<l;i++){
                    if(name[i]<97){
                    sum+=((name[i]-64)*pow(3,i));
                    }
                    else{
                    sum+=((name[i]-97)*pow(3,i));
                    }
                }
                i=sum%n;
                printf("%d",i);
                // insert(&h[i],new);
                node *tmp=h[i];
                while(tmp!=NULL){
                    tmp=tmp->next;
                }
                tmp=new;
                printf("6");
                break;
            case 'd':
                scanf("%s",name);
                getchar();
                l=strlen(name);
                sum=0;
                for(int i=0;i<l;i++){
                    if(name[i]<97){
                    sum+=((name[i]-64)*pow(3,i));
                    }
                    else{
                    sum+=((name[i]-97)*pow(3,i));
                    }
                }
                node *temp=h[i];
                node *prev=NULL;
                if(temp!=NULL){
                    while(strcmp(name,temp->word)!=0){
                        prev=temp;
                        temp=temp->next;
                    }
                    if(temp!=NULL){
                        prev->next=temp->next;
                    }
                }
                break;
            case 'p':
                for(i=0;i<n;i++){
                    node *temp=h[i];
                    if(temp==NULL ||temp->next==NULL){
                        continue;
                    }
                    else{
                        printf("-1\n");
                        break;
                    }
                }
                if(i==n){
                    printf("1\n");
                }
                break;
            case 't':
                return 1;
        }
    }
}



