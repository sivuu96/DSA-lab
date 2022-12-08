#include <stdio.h>
#include <stdlib.h>
// void callNode(int n){
//     scanf("%d", &n);
//     return;
// }
void adjlist(int n,int am[][n]){
    for(int i=0; i<n; i++){
        printf("%d ", i);
        for(int j=0; j<n; j++){
            if(am[i][j]==1){
                printf("%d ",j);
            }
        }
        printf("\n");
    }
}
int main(){
    int n;
    scanf("%d", &n);
    int am[n][n];
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            scanf("%d", &am[i][j]);
        }
    }
    adjlist(n,am);
    return 0;
}