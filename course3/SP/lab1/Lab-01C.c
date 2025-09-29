#include <stdio.h>

int main() {
    int x, k;
    printf("enter x: ");
    scanf("%d", &x);
    if (x < 100) {
        printf("error.\n");
        return 1;
    }
    k = (x / 100) % 10;
    printf("third num: %d\n", k);
    getchar();
    return 0;
}