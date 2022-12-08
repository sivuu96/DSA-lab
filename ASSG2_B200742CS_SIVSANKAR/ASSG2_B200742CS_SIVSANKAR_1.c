#include <stdio.h>
#include <stdlib.h>
void hashtable(int *t,int n){
    for(int i=0; i<n; i++){
        t[i]=-1;
    }
}
int hashIndex(int id,int m){
    return id%m;
}
int quadIndex(int id,int m,int i,int c1,int c2){
    return ((hashIndex(id,m)+c1*i+c2*i*i)%m);
}
int h2(int k,int m){
    int r=0;
    while(--m){
        int c=0;
        for(int i=2;i<m; i++){
            if(m%i==0){
                c++;
                break;
            }   
        }
        if(c==0){
            r=m;
            break;
        }
    }
    int di=r-(k%r);
    return di;
}
int doubleIndex(int id,int m,int i){
    return((hashIndex(id,m)+i*h2(id,m))%m);
}
void insert(int *ht,int id,char c,int m,int c1,int c2){
    int qi,di;
    int i=hashIndex(id,m);
    if(ht[i]==-1){
        ht[i]=id;
        return;
    }
    else{
        if(c=='a'){
            for(int j=0; j<m; j++){
                qi=quadIndex(id,m,j,c1,c2);
                if(ht[qi]==-1){
                    ht[qi]=id;
                    break;
                }
            }
        }
        else{
            for(int j=0; j<m; j++){
                di=doubleIndex(id,m,j);
                if(ht[di]==-1){
                    ht[di]=id;
                    break;
                }
            }
        }
    }
}
int search(int *ht,int id,char c,int m,int c1,int c2){
    int i=hashIndex(id,m);
    if(ht[i]==id){
        return i;
    }
    if(c=='a'){
        for(int j=0; j<m; j++){
            i=quadIndex(id,m,j,c1,c2);
            if(ht[i]==id){
                return i;
            }
        }
        return -1;
    }
    else{
        for(int j=0; j<m; j++){
            i=doubleIndex(id,m,j);
            if(ht[i]==id){
                return i;    
            }
        }
        return -1;
    }
}
void print(int *ht,int m){
    for(int i=0;i<m;i++){
        if(ht[i]!=-1){
            printf("%d (%d)\n",i,ht[i]);
        }
        else{
            printf("%d ()\n",i);
        }
    }
}
void delete(int *ht,int id,char c,int m,int c1,int c2){
    int i=search(ht,id,c,m,c1,c2);
    ht[i]=-1;
}
int main(){
    char c;
    scanf("%c",&c);
    int m;
    scanf("%d",&m);
    int ht[m];
    hashtable(ht,m);
    int c1,c2;
    if(c=='a'){
        scanf("%d %d",&c1,&c2);
    }
    int id;
    char op;
    while(1){
        scanf("%c",&op);
        switch(op){
            case 'i':
                scanf("%d",&id);
                insert(ht,id,c,m,c1,c2);
                // print(ht,m);
                break;
            case 's':
                scanf("%d",&id);
                int i=search(ht,id,c,m,c1,c2);
                if(i==-1){
                    printf("-1\n");
                }
                else{
                    printf("1\n");
                }
                break;
            case 'd':
                scanf("%d",&id);
                delete(ht,id,c,m,c1,c2);
                // print(ht,m);
                break;
            case 'p':
                print(ht,m);
                break;
            case 't':return 0;
        }
    }
    return 0;
}