/*Realizați un algoritm care să verifice că o listă simplu înlănțuită este palindrom.*/

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int data;
    struct node *next;
} ghe;

void getData(struct node *head, int nr)
{
    printf("numarul de elemente: \n");
    scanf("%d", &nr);

    printf("primul element: \n");
    scanf("%d", &head->data);

    head->next = NULL;

    for (int i = 1; i < nr; i++)
    {
        struct node *current = malloc(sizeof(struct node));
        printf("elementul %d: \n", i + 1);
        scanf("%d", &current->data);

        head->next = current;
        current->next = NULL;
        head = current;
    }
}

void reverseData(struct node *head, struct node **head_ref)
{

    struct node *prev = NULL;
    struct node *current = *head_ref;
    struct node *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

void printData(struct node *head)
{

    printf("datele sunt: ");

    while (head != NULL)
    {
        printf(" %d |", head->data);
        head = head->next;
    }
}

int main()
{
    int nr;
    struct node *head = malloc(sizeof(struct node));
    struct node **head_ref = &head;

    getData(head, nr);
    printData(head);
    reverseData(head, head_ref);
    printData(head);

    return 0;
}