#include <stdio.h>
#include <math.h>

void calcSquareRoot(double a, double b, double c) {
    double discriminating = pow(b, 2) - 4 * a * c;


    double real_root, img_root;

    // test if larger than zero (two roots)
    if (discriminating > 0) {
        double root1 = (-b + sqrt(discriminating)) / (2 * a);
        double root2 = (-b - sqrt(discriminating)) / (2 * a);

        printf("As raizes sao: %.2f e %.2f\n", root1, root2);

    } else if (discriminating  == 0) {
        double root = -b / (2 * a);
        printf("Tem uma raiz dupla: %.2f\n", root);

    } else {
        real_root = -b / (2 * a);
        img_root = sqrt(-discriminating ) / (2 * a);
        printf("Tem raizes complexas: %.2f+%.4fi e %.2f-%.4fi\n", real_root, img_root, real_root, img_root);
    }
}

int main() {
    double a, b, c;
    printf("Introduza o valor de a: ");
    scanf("%lf", &a);
    printf("Introduza o valor de b: ");
    scanf("%lf", &b);
    printf("Introduza o valor de c: ");
    scanf("%lf", &c);

    calcSquareRoot(a, b, c);

    return 0;
}