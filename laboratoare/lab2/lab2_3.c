/*Realizați o listă dublu înlănțuită în care să căutați un element și să îl ștergeți. */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int key;
    struct node *prev;
    struct node *next;
} da;

void insertFirst(struct node *head, struct node *last)
{
    printf("data de adaugat:");
    scanf("%d", &head->key);

    head->prev = NULL;
    head->next = NULL;
    last = head;
}

void insertAfter(struct node *last)
{

    struct node *link = malloc(sizeof(struct node));

    printf("data de adaugat:");
    scanf("%d", &link->key);

    link->next = last->next;

    last->next = link;

    link->prev = last;

    if (link->next != NULL)
        link->next->prev = link;
}

void insertLast(struct node **head_ref)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    struct node *last = *head_ref;

    printf("data de adaugat:");
    scanf("%d", &new_node->key);

    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;

    new_node->prev = last;

    return;
}

struct node *delete(int key, struct node *head)
{

    struct node *current = head;
    struct node *previous = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    while (current->key != key)
    {

        if (current->next == NULL)
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

        current->prev->next = current->next;
    }
}

void display(struct node *head)
{
    struct node *ptr = head;

    printf("\n[ ");

    while (ptr != NULL)
    {
        printf("(%d) ", ptr->key);
        ptr = ptr->next;
    }

    printf(" ]");
}

int main()
{
    struct node *head = malloc(sizeof(struct node));
    struct node *last;

    int i = 0;
    int removeMe;

    insertFirst(head, last);
    insertAfter(head);
    insertAfter(head->next);
    insertLast(&head);

    display(head);

    printf("\n");
    printf("ce data eliminam?\n");
    scanf("%d", &removeMe);

    delete (removeMe, head);
    printf("au ramas:\n");
    display(head);

    return 0;
}