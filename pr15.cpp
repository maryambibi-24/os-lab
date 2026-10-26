
#include <stdio.h>

int main(void) {
    int n;
    double speedup;

    printf("Enter processor count N (N > 1): ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        printf("N must be greater than 1.\n");
        return 1;
    }

    printf("Enter measured speedup: ");
    if (scanf("%lf", &speedup) != 1 || speedup <= 0) {
        printf("Invalid speedup.\n");
        return 1;
    }

    double serial = (1.0 / speedup - 1.0 / n) / (1.0 - 1.0 / n);

    printf("Processor count: %d\n", n);
    printf("Measured speedup: %.4f\n", speedup);
    printf("Estimated serial fraction: %.4f (%.2f%%)\n",
           serial, serial * 100);

    if (serial < 0 || serial > 1)
        printf("Warning: result is outside 0..1; measurement/model may not fit.\n");

    return 0;
}

