
#include <stdio.h>

int main(void) {
    double p;

    printf("Enter parallel fraction (0 to 1): ");
    if (scanf("%lf", &p) != 1 || p < 0 || p > 1) {
        printf("Invalid fraction.\n");
        return 1;
    }

    printf("\nProcessors\tTheoretical speedup\n");
    for (int n = 1; n <= 16; n++) {
        double speedup = 1.0 / ((1.0 - p) + p / n);
        printf("%d\t\t%.4f\n", n, speedup);
    }
    return 0;
}

