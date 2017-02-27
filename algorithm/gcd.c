#include <stdio.h>

int Gcd(unsigned int a, unsigned int b)
{
    int temp;
    while(b > 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main()
{
    unsigned int a, b;
    int result;
    printf("please input two numbers.\n");
    scanf("%d", &a);
    scanf("%d", &b);
    result = Gcd(a, b);
    printf("result is %d.\n", result);
    return 0;
}