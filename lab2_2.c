/*Realizați un algoritm care să verifice că o listă simplu înlănțuită este palindrom.*/

#include <stdlib.h>
#include <stdio.h>

/// metoda implementata:
// se copiaza lista initiala intr-o alta, se inverseazaa si se compara rezultatele

typedef struct node
{
    int data;
    struct node *next;
} ghe;


/// @brief pentru lejeritate imediat dupa ce introducem datele le copiem in cealalta lista
/// @param head - baza listei initiale 
/// @param head2 - baza listei in care copiem
/// @param nr - nr de elemente
void getData(struct node *head, struct node *head2, int nr)
{
    printf("numarul de elemente: \n");
    scanf("%d", &nr);

    printf("primul element: \n");
    scanf("%d", &head->data);
    head2->data = head->data;

    head->next = NULL;
    head2->next = NULL;

    for (int i = 1; i < nr; i++)
    {
        struct node *current = malloc(sizeof(struct node));
        struct node *current2 = malloc(sizeof(struct node));
        printf("elementul %d: \n", i + 1);
        scanf("%d", &current->data);
        current2->data = current->data;

        head->next = current;
        head2->next = current2;
        current->next = NULL;
        current2->next = NULL;
        head = current;
        head2 = current2;
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

int isPalindrome(struct node *head, struct node *head2)
{
    int isPalindrome;

    while (head != NULL && head2 != NULL)
    {
        if (head->data == head2->data)
        {
            isPalindrome = 1;
        }

        head = head->next;
        head2 = head2->next;
    }

    return isPalindrome;
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
    int isPal;
    struct node *head = malloc(sizeof(struct node));

    /// pointer pentru a face loc pentru copia listei initiale
    struct node *head2 = malloc(sizeof(struct node));

    struct node **head_ref = &head;
    struct node **head2_ref = &head2;

    getData(head, head2, nr);
    printData(head);
    reverseData(head2, head2_ref);
    printData(head2);

    isPal = isPalindrome(head, head2);

    if (isPal == 1)
    {
        printf("este palindrom");
    }

    else
    {
        printf("nu e palindrom");
    }

    return 0;
}