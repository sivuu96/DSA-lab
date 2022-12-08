#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void Algo_Dijkstra(int n, int Graph[][n], int source){
	int min_dist, pre;
	int cost[n][n];
	int d[n], presnt[n];
	int reach[n];
	int c;
	for (int i = 0; i < n; i++){
		d[i] = -1;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (Graph[i][j] != -8)
				cost[i][j] = Graph[i][j];
			else
				cost[i][j] = 99999;
	for (int i = 0; i < n; i++){
		d[i] = cost[source][i];
		presnt[i] = source;
		reach[i] = 0;
	}
	d[source] = 0;
	reach[source] = 1;
	c = 1;
	while (c < n - 1){
		min_dist = 99999;
		for (int i = 0; i < n; i++){
			if (d[i] < min_dist && !reach[i]){
				min_dist = d[i];
				pre = i;
			}
		}
		reach[pre] = 1;
		for (int i = 0; i < n; i++)
			if (!reach[i]){
				if (min_dist + cost[pre][i] < d[i])
				{
					d[i] = min_dist + cost[pre][i];
					presnt[i] = pre;
				}
			}
		c++;
	}
	int max = d[0];
	for (int i = 1; i < n; i++){
		if (max < d[i]){
			max = d[i];
		}
	}
	printf("%d ", source);
	for (int i = 0; i < n; i++){
		if (i != source){
			if (d[i] == 99999){
				printf("INF ");
			}
			else{
				printf("%d ", d[i]);
			}
		}
	}
	printf("\n");
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
void path_dijkstra(int n, int Graph[][n], int source, int end){
	int cost[n][n];
	int reach[n+1];
	int d[n], presnt[n];
	int min_dist, pre;
	int c;
	for (int i = 0; i < n; i++){
		d[i] = -1;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (Graph[i][j] != -8)
				cost[i][j] = Graph[i][j];
			else
				cost[i][j] = 99999;
	for (int i = 0; i < n; i++){
		d[i] = cost[source][i];
		reach[i] = 0;
		presnt[i] = source;
	}
	d[source] = 0;
	reach[source] = 1;
	c = 1;
	while (c < n - 1){	
		pre=0;
		min_dist = 99999;
		for (int i = 0; i < n; i++){
			if (!reach[i]&&d[i] < min_dist ){
				min_dist = d[i];
				pre = i;
			}
		}	
		reach[pre] = 1;
		for (int i = 0; i < n; i++)
			if (!reach[i]){
				if (min_dist + cost[pre][i] < d[i]){
					d[i] = min_dist + cost[pre][i];
					presnt[i] = pre;
				}
			}	
		c++;
	}
	if (d[end] == 99999){
		printf("UNREACHABLE\n");
	}
	else{
		printf("%d\n", d[end]);
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
int main(){
	int n;
	scanf("%d", &n);
	int G[n][n];
	int u;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			G[i][j] = -8;
		}
	}
	int val;
	char space;
	for (int i = 0; i < n; i++){
		scanf("%d", &val);
		scanf("%c", &space);
		while (space != '\n'){
			scanf("%d", &u);
			scanf("%c", &space);
			G[val][u] = -3;
		}
	}
	for (int i = 0; i < n; i++){
		scanf("%d", &val);
		scanf("%c", &space);
		while (space != '\n'){
			scanf("%d", &u);
			scanf("%c", &space);
			for (int j = 0; j < n; j++){
				if (G[val][j] == -3){
					G[val][j] = u;
					break;
				}
			}
		}
	}
	char flag[5];
	int source, dest;
	while (1){
		scanf("%s", flag);
		if (!strcmp(flag, "apsp")){
			scanf("%d", &source);
			Algo_Dijkstra(n, G, source);
		}
		else if (!strcmp(flag, "sssp")){
			scanf("%d", &source);
			scanf("%d", &dest);
			path_dijkstra(n, G, source, dest);
		}
		else if (!strcmp(flag, "stop")){
			return 0;
		}
	}
}