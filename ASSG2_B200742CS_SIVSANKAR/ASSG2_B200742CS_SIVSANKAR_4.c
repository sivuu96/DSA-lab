#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define tsize 1000
int first(char *s,int l) {
    if(l>=3){
        return (((s[0]+s[1]+s[2])%26)%10);
    }
    else if(l>=2){
        return (((s[0]+s[1])%26)%10);
    }
    else{
        return (((s[0])%26)%10);
    }
}
int second(char *s,int l) {
    if(l>=5){
        return (((s[0]+s[2]+s[4])%26)%10);
    }
    else if(l>=3){
        return (((s[0]+s[2])%26)%10);
    }
    else{
        return (((s[0])%26)%10);
    }
}
int third(char *s,int l){
    if(l>=9){
        return (((s[0]+s[4]+s[8])%26)%10);
    }
    else if(l>=5){
        return (((s[0]+s[4])%26)%10);
    }
    else{
        return (((s[0])%26)%10);
    }
}
void INSERTDATA(char **arr,char *s,int l){
    int fd=first(s,l);
    int sd=second(s,l);
    int td=third(s,l);
    int index=fd*100+sd*10+td;
    // printf("%d",index);
    arr[index]=s;
}
void SEARCH(char ** arr,int i){
    if(arr[i]==NULL){
        printf("NOT FOUND\n");
    }
    else{
        printf("%s\n",arr[i]);
    }
}
void DELETE(char ** arr,int i){
    arr[i]=NULL;
}
int main(){
    char c;
    char *arr[tsize];
    for(int i=0; i<tsize; i++){
        arr[i]=NULL;
    }
    while(1){
        scanf("%c",&c);
        char *s=(char*)malloc(sizeof(char)*tsize);
        char *rn=(char*)malloc(sizeof(char)*4);
        char *hn=(char*)malloc(sizeof(char)*3);
        switch(c){
            case 'i':
                scanf("%s",s);
                getchar();
                int l=strlen(s);
                INSERTDATA(arr,s,l);
                break;
            case 's':
                scanf("%s",rn);
                getchar();
                hn[0]=rn[1];
                hn[1]=rn[2];
                hn[2]=rn[3];
                int i=atoi(hn);
                SEARCH(arr,i);
                break;
            case 'd':
                scanf("%s",rn);
                getchar();
                hn[0]=rn[1];
                hn[1]=rn[2];
                hn[2]=rn[3];
                int di=atoi(hn);
                DELETE(arr,di);
                break;
            case 't':
                return 1;
        }
    }
    return 0;
}