#include <stdio.h>

int main() {
    INT x, y;
    scanf("%d %d", &x, &y);  //normal
    PRINTF("Sum: %d\n", x + y); //YYY
    SCANF("%d", &x);  // ANOTHER
    printf("Next value: %d\n", x);  // Another
    return 0;
}
