#include <stdio.h>

int main(){
    float a, b;
    int selection;
    printf("Simple calculator. Enter two numbers like 'a b': " );
    scanf("%f %f", &a, &b);
    printf("Select the opration: \n");
    printf("1. Sum\n");
    printf("2. Substraction\n");
    printf("3. Multiplication\n"); 
    printf("4. Division\n"); 

    scanf("%d", &selection);

    if (selection == 1){
        printf("%.2f + %.2f = %.2f", a, b, a + b);
    }
    else if (selection == 2){
        printf("%.2f - %.2f = %.2f", a, b, a - b);
    }
    else if (selection == 3){
        printf("%.2f * %.2f = %.2f", a, b, a * b);
    }
    else {
        printf("%.2f / %.2f = %.2f", a, b, a / b);
    }
}