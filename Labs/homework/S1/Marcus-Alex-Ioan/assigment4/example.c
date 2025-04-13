#include <stdio.h>

void greet() {
    printf("Hello!\n");
}

int add(int a, int b) {
    return a + b;
}

int main() {
    greet();
    greet();
    int result = add(2, 3);
    printf("%d\n", result);
    return 0;
}
