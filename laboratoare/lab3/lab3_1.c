/*Se dau următorii vectori
25 1 44 56 100 9 2
6, 5, 3, 2, 8, 10, 9
100 67 34 22 15 10 2
Să se sorteze cei trei vectori crescător utilizând toți algoritmii prezentați în laborator.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
}

void printValues(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" | %d | ", v[i]);
    }

    printf("\n");
}

void insertSort(int v[], int n)
{
    int temp;
    for (int i = 1; i < n; i++)
    {
        temp = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > temp)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = temp;
    }
}

void selectSort(int v[], int n)
{
    int i, j, min;

    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (v[j] < v[min])
                min = j;
        }
        if (min != i)
        {
            swap(&v[min], &v[i]);
        }
    }
}

void merge(int v[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = v[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = v[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int v[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(v, l, m);
        mergeSort(v, m + 1, r);

        merge(v, l, m, r);
    }
}

int separe(int v[], int low, int high)
{
    int pivot;
    pivot = v[high];

    int i, j;
    i = low - 1;

    for (j = low; j <= high - 1; j++)
    {
        if (v[j] < pivot)
        {
            i++;
            swap2(v[i], v[j]);
        }
    }

    swap2(v[i + 1], v[high]);

    return (i + 1);
}

void quickSort(int v[], int low, int high)
{
    int sepIndex;

    if (low < high)
    {
        sepIndex = separe(v, low, high);

        quickSort(v, low, sepIndex - 1);

        quickSort(v, sepIndex + 1, high);
    }
}

int main()
{

    int V1[7] = {25, 1, 44, 56, 100, 9, 2};
    int V2[7] = {6, 5, 3, 2, 8, 10, 9};
    int V3[7] = {100, 67, 34, 22, 15, 10, 2};

    int n = sizeof(V1) / sizeof(int);
    int choice;
    char which[8];

    printf("cu ce le sortam:");
    gets(which);

    if (strcmp(which, "quick") == 0)
    {
        quickSort(V1, 0, 6);
        printValues(V1, n);

        quickSort(V2, 0, 6);
        printValues(V2, n);

        quickSort(V3, 0, 6);
        printValues(V3, n);
    }

    if (strcmp(which, "bubble") == 0)
    {
        bubbleSort(V1, n);
        printValues(V1, n);

        bubbleSort(V2, n);
        printValues(V2, n);

        bubbleSort(V3, n);
        printValues(V3, n);
    }

    if (strcmp(which, "insert") == 0)
    {
        insertSort(V1, n);
        printValues(V1, n);

        insertSort(V2, n);
        printValues(V2, n);

        insertSort(V3, n);
        printValues(V3, n);
    }

    if (strcmp(which, "merge") == 0)
    {
        mergeSort(V1, 0, n - 1);
        printValues(V1, n);

        mergeSort(V2, 0, n - 1);
        printValues(V2, n);

        mergeSort(V3, 0, n - 1);
        printValues(V3, n);
    }

    if (strcmp(which, "select") == 0)
    {
        selectSort(V1, n);
        printValues(V1, n);

        selectSort(V2, n);
        printValues(V2, n);

        selectSort(V3, n);
        printValues(V3, n);
    }

    return 0;