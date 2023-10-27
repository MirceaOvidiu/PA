#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct om
{
    char name[10];
    char hobby[10];
    struct om *next;

} PERS;

void enter_Data(PERS *p, PERS *q, int n)
{
    printf("nr. de persoane:\n");
    scanf("%d", &n);

    printf("numele primului:");
    gets(p->name);
    getchar();

    printf("hobby-ul primului:\n");
    gets(p->hobby);
    getchar();

    for (int i = 0; i < n; i++)
    {
        q = malloc(sizeof(PERS));

        printf("numele persoanei %d:", i + 2);
        gets(q->name);
        getchar();

        printf("hobby-ul persoanei %d:", i + 2);
        gets(q->hobby);
        getchar();

        p->next = q;
        p = q;
        q = NULL;
    }
}

void print_Data(PERS *p, PERS *q)
{
    for (; p != NULL; p = q)
    {
        printf("numele in ordinea hobby-urilor: %s \n", p->name);
    }
}

void sort_Data(PERS *p, PERS *q)
{
    for (; p != NULL; p = q)
    {
        if (strcmp(p->hobby, p->next->hobby) > 0)
        {
            strcpy(q->name, p->name);
            strcpy(q->hobby, p->hobby);

            strcpy(p->name, p->next->name);
            strcpy(p->hobby, p->next->hobby);

            strcpy(p->next->name, q->name);
            strcpy(p->next->hobby, q->hobby);
        }
    }
}

int main()
{
    PERS *p, *q;

    int n;
    p = malloc(sizeof(PERS));
    p->next = NULL;

    enter_Data(p, q, n);
    sort_Data(p, q);
    print_Data(p, q);

    return 0;
}