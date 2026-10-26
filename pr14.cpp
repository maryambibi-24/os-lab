
#include <stdio.h>

int main(void) {
    double p;

    printf("Enter parallel fraction p (0 to 1): ");
    if (scanf("%lf", &p) != 1 || p < 0 || p > 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("N\tAmdahl\t\tGustafson\n");
    for (int n = 1; n <= 8; n++) {
        double amdahl = 1.0 / ((1.0 - p) + p / n);
        double gustafson = n - (1.0 - p) * (n - 1);
        printf("%d\t%.4f\t\t%.4f\n", n, amdahl, gustafson);
    }
    return 0;
}

