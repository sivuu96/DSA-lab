#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node{
    char *word;
    struct node *next;
}node;
int index(int n,int k){
    return ((n*n)%k);
}
node *createnode(char *word){
    node *temp=(node *)malloc(sizeof(node));
    temp->word=word;
    temp->next=NULL;
    return temp;
}
int notDup(node *arr[],int hi,char *w){
    node *temp=arr[hi];
    // if(temp->next!=NULL){
    //     printf("%s",temp->next->word);
    // }
    while(temp!=NULL&&(strcmp(temp->word,w))!=0){
        // printf("%s..",temp->word);
        temp=temp->next;
    }
    if(temp==NULL){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    int k;
    scanf("%d",&k);
    getchar();
    char s[500];
    scanf("%[^\n]s",s);
    node *arr[k];
    for(int i=0; i<k; i++){
        arr[i]=NULL;
    }
    char words[500][500];
    int c=0;
    for(int i=0;i<strlen(s);i++){
        int j=0;
        while(s[i]!=' '){
            words[c][j++] = s[i];
            i++;
        }
        c++;
    }
    // for(int i=0;i<c;i++){
    //     printf("%s..",words[i]);
    // }
    for(int i=0;i<c;i++){
        char *w=words[i];
        int hi=index(strlen(w),k);
        node *temp=NULL;
        temp=arr[hi];
        node *new=NULL;
        new=createnode(w);
        if(temp==NULL){
            arr[hi]=new;
        }
        else{
            // printf("%d ",notDup(arr,hi,w));
            // printf("%s ",temp->word);
            if(notDup(arr,hi,w)){
                while(temp->next!=NULL){
                    temp=temp->next;
                }
                temp->next=new;
            }
        }
    }
    // printf("%s",arr[1]->next->next->word);
    for(int i=0;i<k; i++){
        node *temp=arr[i];
        if(temp==NULL){
            printf("%d:null",i);
        }
        else{
            printf("%d:",i);
            while(temp!=NULL){
                if(temp->next!=NULL){
                    printf("%s-",temp->word);
                }
                else{
                    printf("%s",temp->word);
                }
                temp=temp->next;
            }
        }
        printf("\n");
    }
    return 0;
}