#Given P a process that calculates the greatest common divisor (gcd) of two numbers. 
#Using a suitable structure of such processes, write a program that determines the gcd of N given numbers.

#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int N, i, result;

    printf("Enter how many numbers: ");
    scanf("%d", &N);

    if (N < 2) {
        printf("Need at least two numbers to compute GCD.\n");
        return 1;
    }

    int numbers[N];

    
    printf("Enter %d numbers: ", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }

    result = numbers[0];

    for (i = 1; i < N; i++) {
        result = gcd(result, numbers[i]);
    }

    printf("The GCD of the given numbers is: %d\n", result);

    return 0;
}
