#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int arrayProduct(int arr[], int start, int end) {
    if (start == end) {
        // cand nu are decat unelement arrrayu
        return arr[start];
    } else {
        int mid = (start + end) / 2;

        int leftChild = fork();

        if (leftChild == 0) {
            int leftProduct = arrayProduct(arr, start, mid);
            _exit(leftProduct); // dai exit cu valorea produsului
        } else if (leftChild > 0) {
            // in parinte
            int rightChild = fork();
            if (rightChild == 0) {
                int rightProduct = arrayProduct(arr, mid + 1, end);
                _exit(rightProduct); 
            } else if (rightChild < 0) {
                perror("fork");
                return -1;
            }

            int leftProduct, rightProduct;
            waitpid(leftChild, &leftProduct, 0);
            waitpid(rightChild, &rightProduct, 0);

            return WEXITSTATUS(leftProduct) * WEXITSTATUS(rightProduct);
        } else {
            perror("fork");
            return -1;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3,5};

    int n = sizeof(arr) / sizeof(arr[0]);

    int product = arrayProduct(arr, 0, n - 1);

    printf("Product of the array: %d\n", product);

    return 0;
}
