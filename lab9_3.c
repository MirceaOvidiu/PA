/*3. Realizați un program de afișare a unui vector folosind un algoritm recursiv. 2p*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int display_element(int *base, int nr_of_elements, int current)
{
    if (current < nr_of_elements)
    {
        printf("%d ", base[current]);

        current = current + 1;

        return display_element(base, nr_of_elements, current);
    }
}

int main()
{
    int nr_of_elements;
    printf("cate elemente sa fie in vector?");
    scanf("%d", &nr_of_elements);

    int *base = calloc(nr_of_elements, sizeof(int));

    srand(time(0));

    for (int i = 0; i < nr_of_elements; i++)
    {
        base[i] = (rand() % 11);
    }

    display_element(base, nr_of_elements, 0);
}