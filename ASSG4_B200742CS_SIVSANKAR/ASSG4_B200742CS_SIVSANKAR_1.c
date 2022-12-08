#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node{
    int k;
    int d;
    struct node *child;
    struct node *sibling;
    struct node *parent;
}node;
void DECREASEKEY(node **Heap, int a, int bb);
node* MergeUni(node* pt1,node* pt2);
void PCHILD(node *Heap);
void UNION(node **Heap,node *uni);
void EXTRACTMIN(node **Heap);

void MAKEHEAP(node **HEAP, int key){
    (*HEAP)=(node*)malloc(sizeof(node));
    (*HEAP)->d=0;
    (*HEAP)->k=key;
    (*HEAP)->child=NULL;
    (*HEAP)->parent=NULL;
    (*HEAP)->sibling=NULL;
}
int Makelink(node* Heap,node* uni){
    Heap->parent = uni;
    Heap->sibling = uni->child;
    uni->child = Heap;
    uni->d++;
}
void INSERT(node **Heap, int key){
    node *t;
    MAKEHEAP(&t,key);
    UNION(&(*Heap),t);
}
void UNION(node **Heap,node *uni){
    if (*Heap == NULL && uni == NULL){
        return;
    }
    node *crnt = MergeUni(*Heap, uni);
    node* ipp = crnt;
    node* prvus = NULL;
    node* nxt = ipp->sibling;
    while (nxt != NULL){
        if ((ipp->d != nxt->d) || ((nxt->sibling != NULL) && (nxt->sibling)->d == ipp->d)){
            prvus = ipp;
            ipp = nxt;
        }
        else{
            if (ipp->k > nxt->k){
                if (prvus == NULL)
                    crnt = nxt;
                else
                    prvus->sibling = nxt;
                Makelink(ipp, nxt);
                ipp = nxt;
            }
            else{
                ipp->sibling = nxt->sibling;
                Makelink(nxt, ipp);
            }
        }
        nxt = ipp->sibling;
    }
    *Heap=crnt;
}
void PCHILD(node *Heap){
    if(Heap==NULL){
        return;
    }
    else{
        printf("%d ",Heap->k);
        if(Heap->sibling!=NULL){
            printf("%d ",Heap->sibling->k);
        }
        PCHILD(Heap->child);
        return;
    }  
}
node* MergeUni(node* pt1,node* pt2){
    if (pt2 == NULL){
        return pt1;
    }
    if (pt1 == NULL){
        return pt2;
    }
    node* crnt = NULL;
    if (pt2->d < pt1->d)
        crnt = pt2;
    else if (pt2->d >= pt1->d)
        crnt = pt1;
    while (pt1 != NULL && pt2 != NULL){
        if(pt1->d == pt2->d){
            node* sibling = pt1->sibling;
            pt1->sibling = pt2;
            pt1 = sibling;
        }
        else if (pt2->d > pt1->d){
            pt1 = pt1->sibling;
        }
        else{
            node* sibling = pt2->sibling;
            pt2->sibling = pt1;
            pt2 = sibling;
        }
    }
    return crnt;
}
node *SEARCH(struct node *Heap, int key){
    if (Heap == NULL){
        return NULL;
    }
    if (Heap->k == key){
        return Heap;
    }
    node* get = SEARCH(Heap->child, key);
    if (get != NULL){
        return get;
    }
    return SEARCH(Heap->sibling, key);
}
void PHEAP(struct node *Heap){
    if(Heap!=NULL){
        printf("%d ",Heap->k);
        PCHILD(Heap->child);
        PHEAP(Heap->sibling);
    }
    else{
        return;
    }
}
node *MINIMUM(struct node *Heap){
    if (Heap==NULL){
        return NULL;
    }
    node *mini = Heap;
    node *prvus = NULL;
    int sm = Heap->k;
    node *ipp = Heap;
    while (ipp->sibling != NULL){
        if ((ipp->sibling)->k < sm){
            prvus = ipp;
            mini = ipp->sibling;
            sm = (ipp->sibling)->k;
        }
        ipp = ipp->sibling;
    }
    node *t;
    MAKEHEAP(&t,sm);
    return t;
}
void EXTRACTMIN(node **Heap){
    if (Heap == NULL){
        return;
    }
    node* crnt = (*Heap);
    node* nxt = crnt->sibling;
    node *min = NULL;
    node* prev = NULL;
   
    MAKEHEAP(&min, MINIMUM(*Heap)->k);
    while (nxt != NULL){
        if (crnt->k == min->k){
            break;
        }
        prev = crnt;
        crnt = nxt;
        nxt = nxt->sibling;
    }
    if (prev != NULL){
        prev->sibling = nxt;
    }
    else{
        (*Heap) = nxt;
    }
    crnt->sibling = NULL;
    node* te = crnt;
    crnt = crnt->child;
    free(te);
    node* t = NULL;
    t=(node*)malloc(sizeof(node));
    t->parent = NULL;
    t = crnt;
    nxt = NULL;
    prev = NULL;
    while (crnt != NULL){
        nxt=crnt->sibling;
        crnt->sibling=prev;
        prev=crnt;
        crnt=nxt;
    }
    t=prev;
    UNION(&*Heap, t);
}
void DECREASEKEY(node **Heap, int a, int bb){
    node* get=SEARCH(*Heap, a);
    if (get==NULL){
        return;
    }
    else{
        get->k=(a-bb);
        node* parent=get->parent;
        while (parent!=NULL&&get->k<parent->k){
            int a[1],b[1];
            b[0]=parent->k;
            a[0]=get->k;
            parent->k=a[0];
            get->k=b[0];
            get=parent;
            parent=parent->parent;
        }
    }
}
void DELETE(node **Heap, int data){
    if (*Heap != NULL){
        node *t=SEARCH(*Heap, data);
        if (t == NULL){
            printf("-1\n");
            return;
        }
        else{
            printf("%d\n", data);
        }
        DECREASEKEY(&(*Heap), data, 10000);
        return EXTRACTMIN(&*Heap);
    }
    else{
        printf("-1\n");
        return;
    }
}
int main(){
    int n;
    int neg;
    char ch;
    node *sma=NULL;
    node *Heap=NULL;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':
                getchar();
                scanf("%d",&n);
                INSERT(&Heap,n);
                break;
            case 'm':
                sma=MINIMUM(Heap);
                if(sma==NULL){
                    printf("-1\n");
                }
                else{
                    printf("%d\n",(sma)->k);
                }
                break;
            case 'd':
                getchar();
                scanf("%d",&n);
                DELETE(&Heap,n);
                break;
            case 'x':
                sma=MINIMUM(Heap);
                if(sma!=NULL){
                    printf("%d\n",(sma)->k);
                    EXTRACTMIN(&Heap);
                }
                else{
                    printf("-1\n");
                }                      
                break;
            case 'p':
                PHEAP(Heap);
                printf("\n");
                break;
            case 'e': return 0;
            case 'r':
                getchar();
                scanf("%d",&n);
                scanf("%d",&neg);
                sma=SEARCH(Heap,n);
                if(sma!=NULL){
                    printf("%d\n",n-neg);
                    DECREASEKEY(&Heap,n,neg);}
                else{
                    printf("-1\n");
                }
                break;
        }
    }
}
