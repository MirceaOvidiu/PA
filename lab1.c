#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    char name[10];
    char surname[10];
    char hschool[10];
    char city[10];
    char hobbies[3][10];
} PERSON;

void enter_data(PERSON *ptr)
{
    printf("prenumele:\n");
    gets(ptr->surname);
    getchar();

    printf("numele:\n");
    gets(ptr->name);
    getchar();

    printf("liceul:\n");
    gets(ptr->hschool);
    getchar();

    printf("orasul:\n");
    gets(ptr->city);
    getchar();

    for (int i = 0; i < 3; i++)
    {
        printf("hobby-ul %d:\n", i + 1);
        gets(ptr->hobbies[i]);
        getchar();
    }
}

int cmp_func(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}

void sort_data(int cmp_func, PERSON *ptr)
{
    void *base = ptr->hobbies;

    qsort(base, 3, 10, cmp_func);
}

void print_data(PERSON *ptr)
{

    printf("numele %s prenume %s, din %s, a invatat la %s \n", ptr->surname, ptr->name, ptr->city, ptr->hschool);

    printf("are hobby-urile: %s %s si %s:", ptr->hobbies[0], ptr->hobbies[1], ptr->hobbies[2]);
}

int main()
{
    PERSON *ptr;
    ptr = malloc(sizeof(PERSON));

    enter_data(ptr);
    sort_data(cmp_func,ptr);
    print_data(ptr);

    return 0;
}
