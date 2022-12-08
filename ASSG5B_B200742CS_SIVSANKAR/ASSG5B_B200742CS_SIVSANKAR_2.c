#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>
//KRUSKAL ALGORITHM Setting
typedef struct krusk_node{
    int vlu;
    int weight;
    struct krusk_node *link;
}krusk_node;
typedef struct krusk_vert{
    int u;
    int v;
    int w;
    struct krusk_vert *link;
}krusk_vert;
typedef struct s_node{
    int vlu;
    int flag;
    int weight;
    char clr;
}s_node;
typedef struct edge{
    int u;
    int v;
    int w;
}edge;
typedef struct ver{
    int vertx1;
    int vertx2;
}ver;
typedef struct graph{
    int nvtx;
    s_node *vertex;
    struct krusk_node **AdjList;
}graph;
edge adjMat[1000][1000];
int n;
int went[1000],s[1000];
ver hp[1000];
int h_index[1000],sh;

void CREATE_KRUSK_NODES(krusk_vert **K, int u, int v, int weight){
    (*K) = (struct krusk_vert*)malloc(sizeof(struct krusk_vert));
    (*K)->v = v;
    (*K)->w = weight;
    (*K)->link = NULL;
    (*K)->u = u;
}
int reperet(graph *G, int key){
    return G->vertex[key].flag;
}
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
krusk_vert* INSERT_KRUSK(krusk_vert *kruNode, int u, int v, int w){
    if(kruNode != NULL){
        if(kruNode->w <= w){     
            kruNode->link = INSERT_KRUSK(kruNode->link, u, v, w);
            return kruNode;
        }
        else{
            krusk_vert *NodeKrus;
            CREATE_KRUSK_NODES(&NodeKrus, u, v, w);
            NodeKrus->link = kruNode;
            return NodeKrus;     
        }
    }
    else{
        krusk_vert *nk;
        CREATE_KRUSK_NODES(&nk,u, v, w);
        return nk;
    }
}
void CreateKruskGraph(struct graph **G,int key){
    *G = (struct graph*)malloc(sizeof(graph));
    (*G)->vertex = malloc(key * sizeof(s_node));
    (*G)->AdjList = malloc(key * sizeof(krusk_node*));
    (*G)->nvtx = key;
    for( int i = 0; i < key; i++){
        (*G)->vertex[i].vlu = i;
        (*G)->vertex[i].flag = -1;
        (*G)->vertex[i].clr = 'w';
        (*G)->vertex[i].weight = 99999;
        (*G)->AdjList[i] = NULL;
    }
}
void CreateKruskAdj(krusk_node **K, int n){
    if(n != -1){
        *K = (krusk_node *)malloc(sizeof(krusk_node));
        (*K)->vlu = n;
        (*K)->weight = 0;
        (*K)->link = NULL;
    }
    else{
        (*K)= NULL;
    }
}
krusk_node* KruskInsertAdj(krusk_node *vert1, krusk_node *vert2){
    if(vert1 != NULL){
        vert1->link = KruskInsertAdj(vert1->link, vert2);
        return vert1;
    }
    else{
        return vert2;
    }
}

graph* KruskUnionGraph(graph *G, int u, int v){
    int i;
    for(i = 0; i < G->nvtx; i++){
        if(G->vertex[i].flag == v){
            G->vertex[i].flag = u;
        }
    }
    return G;
}
void kruskMinSpanTCal(graph *G, long int *s){
    int i, u, v;
    long int sum=(*s);
    krusk_vert *O = NULL;
    for(i = 0; i < G->nvtx; i++){
        G->vertex[i].weight = 99999;
        G->vertex[i].flag = i;
        G->vertex[i].clr = 'w';
        krusk_node *pr = G->AdjList[i];
        while(pr != NULL){
            O = INSERT_KRUSK(O, i, pr->vlu, pr->weight);
            pr = pr->link;
        }
    }
    while(O != NULL){
        u = O->u;
        v = O->v;
        if(reperet(G, u) != reperet(G, v)){
            s[0] += O->w;
            sum += O->w;
            G = KruskUnionGraph(G, reperet(G, u), reperet(G, v));
        }
        O = O->link;
    }
}
//PRIMS ALGORITHM STAGING
int RIGHTCHILD(int key){ 
    return ((2*key)+2);
}
int LEFTCHILD(int key){ 
    return ((2*key)+1); 
}
int PARENT(int key){ 
    return ((key-1)/2); 
}
void vert_swap(ver *x,ver *y){
    ver t = *x;
    *x = *y;
    *y = t;
    int tem = h_index[x->vertx2];
    h_index[x->vertx2] = h_index[y->vertx2];
    h_index[y->vertx2] = tem;
}
void Prim_decrease(int x,int w){
    int i = h_index[x];
    if(hp[i].vertx1 > w){
        hp[i].vertx1 = w;
        while(i!=0 && hp[PARENT(i)].vertx1 > hp[i].vertx1){
            vert_swap(&hp[PARENT(i)],&hp[i]);
            i = PARENT(i);
        }
    }
}

void Prim_insert(struct ver x){
    h_index[x.vertx2] = sh; 
    hp[sh] = x;
    int i = sh;
    sh++;
    while(i!=0 && hp[PARENT(i)].vertx1 > hp[i].vertx1){
        vert_swap(&hp[PARENT(i)],&hp[i]);
        i = PARENT(i);
    }
}
void Heapify(int i) { 
    int sm = i;
    int r = RIGHTCHILD(i); 
    int l = LEFTCHILD(i); 
         
    if (hp[l].vertx1 < hp[i].vertx1 && l < sh) {

        sm = l; 
    }
    if (hp[r].vertx1 < hp[sm].vertx1 && r < sh) {
        sm = r; 

    }
    if (sm != i) { 
        vert_swap(&hp[i], &hp[sm]); 
        Heapify(sm); 
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
ver EXTRACT_MIN() { 
    ver root = hp[0]; 
    if (sh <= 0) 
        return root; 
    if (sh == 1) { 
        sh--; 
        return hp[0]; 
    } 
    hp[0] = hp[sh-1]; 
    sh--; 
    Heapify(0);   
    return root; 
} 
void INSERTDATA(char **arr,char *s,int l){
    int fd=first(s,l);
    int sd=second(s,l);
    int td=third(s,l);
    int index=fd*100+sd*10+td;
    // printf("%d",index);
    arr[index]=s;
}
int main(){
    char ch;
    scanf("%c",&ch);
    int digit;
    switch(ch){
        case 'a':
            getchar();
            scanf("%d", &n);
            graph *G ;
            CreateKruskGraph(&G,n);    
            int i;
            int key;
            int chmm;
            digit = getchar();
            for(i = 0; i < n; i++){
                krusk_node *K = NULL;
                key = -1;
                while(1){
                    digit = getchar();
                    if(digit == 10){
                        //wew
                        CreateKruskAdj(&K,key);
                        G->AdjList[i] = KruskInsertAdj(G->AdjList[i], K);
                        break;
                    }
                    else if(digit == ' '){
                        CreateKruskAdj(&K,key);
                        G->AdjList[i] = KruskInsertAdj(G->AdjList[i],K);
                        key = -1;
                        chmm = 1;
                    }
                    else{
                        if(key == -1){
                            key = 0;
                        }
                        key = key * 10 + ( (int)digit - 48 );
                    }
                }
            }
            for(i = 0; i < n; i++){
                krusk_node *present = G->AdjList[i];
                key = -99999;
                chmm = 1;
                while(1){
                    digit = getchar();
                    if(digit == ' '){
                        present->weight = chmm * key;
                        key = -99999;
                        chmm = 1;
                        present = present->link;
                    }
                    else if(digit == '-'){
                        chmm = -1;
                    }
                    else if(digit == 10){
                        if(key != -99999){
                            present->weight = chmm * key;
                        }
                        chmm = 1;
                        break;
                    }
                    else{
                        if(key == -99999)
                            key = 0;
                        key = key * 10 + ( (int)digit - 48 );
                    }
                }
            }
            long int Sum_k[1];
            int bbb=0;
            Sum_k[bbb] = bbb;
            kruskMinSpanTCal(G,Sum_k);
            printf("%ld\n", Sum_k[0]);
            return 0;
    
        case 'b':
            getchar();
            scanf("%d",&n);
            digit = '\0';
            digit = getchar();
            for(int i=0;i<n;i++){
                digit = getchar();
                if(digit=='\n') 
                    continue;
                int value = digit - '0';
                while(digit!='\n'){
                    digit = getchar();
                    if(digit == ' '||digit == '\n'){
                        adjMat[i][s[i]].u = i;
                        adjMat[i][s[i]].v = value;
                        value = 0;
                        s[i]++;
                    }
                    else 
                        value = value*10 + digit - '0';         
                }
            }
            for(int i=0;i<n;++i){
                for(int j=0;j<s[i];++j){
                    int w;
                    scanf("%d",&w);
                    adjMat[i][j].w = w;;
                }   
            }
            ver temp ;
            long long PRIM_MIN_SPAN = 0;
            temp.vertx2 = 0;  
            temp.vertx1 = 0;
            Prim_insert(temp);
            for(int i=1;i<n;++i){
                temp.vertx2 = i;
                temp.vertx1 = 99999;
                Prim_insert(temp);
            }
            while(sh){
                temp = hp[0];
                EXTRACT_MIN();
                
                if(went[temp.vertx2])
                    continue;
                went[temp.vertx2] = 1;
                PRIM_MIN_SPAN += temp.vertx1;
                for(int i=0;i<s[temp.vertx2];++i){
                    edge x = adjMat[temp.vertx2][i]; 
                    
                    if(!went[x.v]) 
                        Prim_decrease(x.v,x.w);
                }
            }
            printf("%lld\n",PRIM_MIN_SPAN);
            return 0;
    }
}
