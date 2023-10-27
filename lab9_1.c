/*1. Realizați algoritmul fibonacci recursiv și iterativ (n=10). 2p*/

#include <stdlib.h>
#include <stdio.h>

void fib_it(int n)
{
    int i = 1;
    int current = 1;
    int next = 1;
    int temp;

    printf("%d ", current);

    while (i < n)
    {
        int temp = current;
        current = next;
        next = next + temp;
        printf("%d ", current);
        i++;
    }
}

int fib_rec(int current, int next, int n)
{
    if (n == 0)
    {
        return current;
    }

    else
    {
        int temp = current;
        current = next;
        next = next + temp;
        printf("%d ", current);

        return fib_rec(current, next, n - 1);
    }
}

int main(void)
{
    int nr_termeni;

    printf("sa se afiseze cati termeni din seria fibonacci?");
    scanf("%d", &nr_termeni);

    printf("iterativ: ");
    fib_it(nr_termeni);

    printf("\nrecursiv: ");
    fib_rec(0, 1, nr_termeni);

    return 0;
}