/*#problem 12
Compute the sum of an array of numbers using divide et impera method: a process splits the array in two sub-arrays and gives them to two other child processes to compute their sums, then adds the results obtained. The child processes use the same technique (split, etc. …).*/

#include <stdio.h>
#include <stdlib.h>

//functie pt a calcula suma din array cu divide et impera
int sumaArray(int arr[], int start, int end) {
    if (start == end) {
        return arr[start];
    } else {
        int mid = (start + end) / 2;
        //impartim array-ul in 2 parti si calculam suma recursiv pt fiecare parte 
        int leftSum = sumArray(arr, start, mid);
        int rightSum = sumArray(arr, mid + 1, end);
        // returnam suma totala a array-ului
        return leftSum + rightSum;
    }
}

int main() {
    int n;
    printf("enter the nr of elements in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("memory allocation failed\n");
        return 1;
    }

    printf("enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int arraySum = sumaArray(arr, 0, n - 1);
    printf("sum of the array elements: %d\n", arraySum);

    free(arr);
    return 0;
}
