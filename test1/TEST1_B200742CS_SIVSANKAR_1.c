#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node{
    char *word;
    struct node *next;
}node;
node *createnode(char *word){
    node *temp=(node *)malloc(sizeof(node));
    temp->word=word;
    temp->next=NULL;
    return temp;
}
int find_hash1(char *w,int n,int l){
    if(l==1){
        return ((2*w[0])%n);
    }
    else{
        return (((w[0]+w[1]+w[l-2]+w[l-1])/l)%n);
    }
}
int find_hash2(char *w,int n,int l){
    int s=0;
    for(int i=0;i<l;i++){
        s+=w[i];
    }
    return ((s/l)%n);
}
int length_of_chain(node *head,int c){
    node *temp=head;
    while(temp!=NULL){
        c++;
        temp=temp->next;
    }
    return c;
}
void insert(node **head,node *new){
    node *temp=*head;
    if(temp==NULL){
        (*head)=new;
    }
    else{
        while(temp!=NULL){
            temp=temp->next;
        }
        temp=new;
    }
}
void store_word(node **h,int n,int l,char *w,node *new,int clen){
    int hi=find_hash1(w,n,l);
    int gi=find_hash2(w,n,l);
    if(length_of_chain(h[hi],clen)>length_of_chain(h[gi],clen)){
        insert(&h[gi],new);
    }
    else if(length_of_chain(h[hi],clen)<length_of_chain(h[gi],clen)){
        insert(&h[hi],new);
    }
    else{
        insert(&h[hi],new);
    }
}
void print_table(node **h,int n){
    for(int i=0;i<n;i++){
        node *temp=h[i];
        if(temp==NULL){
            printf("NULL\n");
            continue;
        }
        else{
            while(temp!=NULL){
                printf("%s ",temp->word);
                temp=temp->next;
            }
            printf("\n");
        }
    }
}
int main(){
    int n;
    scanf("%d",&n);
    getchar();
    char s[500];
    scanf("%[^\n]s",s);
    node *h[n];
    for(int i=0; i<n; i++){
        h[i]=NULL;
    }
    char words[10000][100];
    int c=0;
    for(int i=0;i<strlen(s);i++){
        int j=0;
        while(s[i]!=' '){
            words[c][j++] = s[i];
            i++;
        }
        words[c][j++] = '\0';
        c++;
    }
    node *new=NULL;
    for(int i=0;i<c;i++){
        char *w=(char *)malloc(sizeof(char)*100);
        w=words[i];
        new=createnode(w);
        int l=strlen(w);
        int clen=0;
        store_word(h,n,l,w,new,clen);
    }
    print_table(h,n);
    return 0;
}