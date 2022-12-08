#include <stdio.h>
#include <stdlib.h>
typedef struct edges{
    int u;
    int v;
    int w;
} edges;
typedef struct graph{
    int V;
    int E;
    edges *edge;
}graph;
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
int bellmanford_algo(graph *grph, int start, int n, int m);
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
  
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
  
        // vert_swap the found minimum element with the first element
        //swap(&arr[min_idx], &arr[i]);
    }
}
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)     
 
       // Last i elements are already in place  
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              //swap(&arr[j], &arr[j+1]);
              j++;
              i++;
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */
    int L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}
int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}
int main(){
    graph *grph = (graph *)malloc(sizeof(graph));
    int n, m;
    scanf("%d %d", &n, &m);
    //scanf("%d", &m);
    //grph=NULL;
    grph->V = n;
    grph->E = m;
    grph->edge = (edges *)malloc(m * sizeof(edges));
    int x, y, z;
    for (int i = 0; i < m; i++){
        scanf("%d %d %d", &x, &y, &z);
        //scanf("%d", &y);;
        grph->edge[i].v = y;
        grph->edge[i].w = z;
        grph->edge[i].u = x;
    }
    int output = bellmanford_algo(grph, 0, n, m);
    printf("%d\n", output);
    return 0;
}
int bellmanford_algo(graph *grph, int start, int n, int m){
    int j, i, w, v, u;
    int setup[n];
    for(int i=0;i<n;i++){
        setup[i] =0;
    }
    int totEdj = grph->E;
    int totVer = grph->V;
    int d[totVer];
    int p[totVer];
    for (i = 0; i < totVer; i++){
        p[i] = 0;
        d[i] = 99999; // Sentinel value denoting huge positive number
    }
    d[start] = 0;
    for(int i=0;i<n;i++){
        setup[i]++;
    }
    for (i = 1; i <= totVer - 1; i++){
        for (j = 0; j < totEdj; j++){
            v = grph->edge[j].v;
            w = grph->edge[j].w;
            u = grph->edge[j].u;
            if (d[v] > d[u] + w && d[u] != 99999){
                p[v] = u;
                d[v] = d[u] + w;
            }
        }
    }
    for (i = 0; i < totEdj; i++){
        v = grph->edge[i].v;
        w = grph->edge[i].w;
        u = grph->edge[i].u;
        if (d[v] > d[u] + w&&d[u] != 99999){
            return 1;
        }
    }
    for(int i=0;i<n;i++){
        setup[i]--;
    }
    for (i = 0; i < m; i++){
        int val;
        val = d[grph->edge[i].u] + grph->edge[i].w;
        if (val<d[grph->edge[i].v]){
            return 1;
        }
    }
    return -1;
    for(int i=0;i<n;i++){
        setup[i]--;
        i++;
    }
}
void display(int *arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}