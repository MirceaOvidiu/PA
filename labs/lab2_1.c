/*Realizați un program care să șteargă duplicatele dintr-o listă simplu înlănțuită nesortată.*/

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int data;
    struct node *next;
} ghe;

void getData(struct node *head, int nr)
{
    printf("numarul de date: \n");
    scanf("%d", &nr);

    printf("prima data: \n");
    scanf("%d", &head->data);

    head->next = NULL;

    for (int i = 1; i < nr; i++)
    {
        struct node *current = malloc(sizeof(struct node));
        printf("data cu nr: %d: \n", i + 1);
        scanf("%d", &current->data);

        head->next = current;
        current->next = NULL;
        head = current;
    }
}

void swap(struct node *a, struct node *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

struct node *delete(int data, struct node *head)
{
    struct node *current = head;
    struct node *previous = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    while (current->data != data)
    {
        if (current->data == data)
        {
            return NULL;
        }

        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (current == head)
    {
        head = head->next;
    }

    else
    {
        previous->next = current->next;
    }

    return current;
}

void printData(struct node *head)
{

    printf("datele sunt: ");

    while (head != NULL)
    {
        printf(" %d |", head->data);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    int nr;
    int i = 0;
    struct node *head = malloc(sizeof(struct node));

    getData(head, nr);
    printData(head);
    
    struct node *p = head;
    for (; p->next != NULL; p = p->next)
    {

        if (p->data == p->next->data)
        {
            delete (p->data, head);
        }
    }

    printData(head);

    return 0;
}