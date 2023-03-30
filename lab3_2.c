/*Creati un vector cu 10000 de valori random. Să se afișeze timpul de rulare al fiecărui algoritm și care a fost cel mai performant.
Notă: s-ar putea ca datele sa fie prea puține și timpul de rulare  să dea mereu 0, în acest caz măriți vectorul.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct sortDetails
{
    char sortName[8];
    double runTime;
} SORT;

int cmp_func(int *a, int *b)
{
    return (a - b);
}

int cmp_func2(double *a, double *b)
{
    return (a - b);
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swap2(int a, int b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}

void structSwap(struct sortDetails *a, struct sortDetails *b)
{
    struct sortDetails temp;
    temp.runTime = a->runTime;
    a->runTime = b->runTime;
    b->runTime = temp.runTime;

    strcpy(&temp.sortName, a->sortName);
    strcpy(a->sortName, b->sortName);
    strcpy(b->sortName, &temp.sortName);
}

void quickSort(int *p, int cmp_func)
{
    qsort(p, 1000000, sizeof(int), cmp_func);
}

void bubbleSort(int *p)
{
    int n = 100000;
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j] > p[j + 1])
                swap(&p[j], &p[j + 1]);
        }
}

void insertSort(int *p)
{
    int n = 100000;
    int temp;
    for (int i = 1; i < n; i++)
    {
        temp = p[i];
        int j = i - 1;

        while (j >= 0 && p[j] > temp)
        {
            p[j + 1] = p[j];
            j = j - 1;
        }
        p[j + 1] = temp;
    }
}

void selectSort(int *p)
{
    int n = 100000;
    int i, j, min;

    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (p[j] < p[min])
                min = j;
        }
        if (min != i)
        {
            swap(&p[min], &p[i]);
        }
    }
}

void merge(int *p, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = p[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = p[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            p[k] = L[i];
            i++;
        }
        else
        {
            p[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        p[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        p[k] = R[j];
        j++;
        k++;
    }
}

void runTimeSort(struct sortDetails *p)
{
    int n = 5;
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].runTime > p[j + 1].runTime)
            {
                structSwap(&p[j], &p[j + 1]);
            }
        }
}

void mergeSort(int *p, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(p, l, m);
        mergeSort(p, m + 1, r);

        merge(p, l, m, r);
    }
}

int main()
{
    double neededTimes[5];
    srand(time(0));

    int *p1 = calloc(100000, sizeof(int));
    int *p2 = calloc(100000, sizeof(int));
    int *p3 = calloc(100000, sizeof(int));
    int *p4 = calloc(100000, sizeof(int));
    int *p5 = calloc(100000, sizeof(int));

    for (int i = 0; i < 100000; i++)
    {
        p1[i] = (rand() % 10);
    }

    for (int i = 0; i < 100000; i++)
    {
        p2[i] = (rand() % 10);
    }
    for (int i = 0; i < 100000; i++)
    {
        p2[i] = (rand() % 10);
    }
    for (int i = 0; i < 100000; i++)
    {
        p3[i] = (rand() % 10);
    }
    for (int i = 0; i < 100000; i++)
    {
        p4[i] = (rand() % 10);
    }

    struct sortDetails *base = calloc(5, sizeof(struct sortDetails));
    strcpy(base->sortName, "bubble");
    strcpy((base + 1)->sortName, "merge");
    strcpy((base + 2)->sortName, "insert");
    strcpy((base + 3)->sortName, "quick");
    strcpy((base + 4)->sortName, "select");

    clock_t begin1 = clock();
    bubbleSort(p1);
    clock_t end1 = clock();
    neededTimes[0] += (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("bubblesort pentru 10^6 elemente random a luat:%Lf\n", neededTimes[0]);

    clock_t begin2 = clock();
    mergeSort(p2, 0, 99999);
    clock_t end2 = clock();
    neededTimes[1] += (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("mergesort pentru 10^6 elemente random a luat:%Lf  \n", neededTimes[1]);

    clock_t begin3 = clock();
    insertSort(p3);
    clock_t end3 = clock();
    neededTimes[2] += (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("insertsort pentru 10^6 elemente random a luat:%Lf \n", neededTimes[2]);

    clock_t begin4 = clock();
    quickSort(p4, cmp_func);
    clock_t end4 = clock();
    neededTimes[3] += (double)(end4 - begin4) / CLOCKS_PER_SEC;
    printf("quicksort pentru 10^6 elemente random a luat:%Lf \n", neededTimes[3]);

    clock_t begin5 = clock();
    selectSort(p5);
    clock_t end5 = clock();
    neededTimes[4] += (double)(end5 - begin5) / CLOCKS_PER_SEC;
    printf("selectsort pentru 10^6 elemente random a luat:%Lf \n", neededTimes[4]);

    for (int i = 0; i < 5; i++)
    {
        (base + i)->runTime = neededTimes[i];
    }

    runTimeSort(base);

    printf("in ordinea crescatoare a performantei algoritmii s-au clasat: \n");

    for (int i = 0; i < 5; i++)
    {
        printf("%ssort cu runtime de %Lf \n", (base + i)->sortName, (base + i)->runTime);
    }

    printf("deci cel mai performant de data aceasta a fost %ssort",base->sortName);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);

    return 0;
}