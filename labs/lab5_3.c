/*Implementați o funcție care să găsească cel mai apropiat strămoș comun al două noduri dintr-un arbore binar. 3p
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 6
#define MAXSIZE 6

int top = -1;
int stack[6];

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} NODE;

NODE *init_root()
{
    NODE *root = malloc(sizeof(NODE));
    printf("initializam root cu valoarea:\n");
    scanf("%d", &root->data);
    root->lchild = NULL;
    root->rchild = NULL;
}

int is_Empty()
{
    if (top == -1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int is_Full()
{
    if (top == MAXSIZE)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int peek()
{
    return stack[top];
}

int pop()
{
    int data;

    if (!is_Empty())
    {
        data = stack[top];
        top += -1;

        return data;
    }

    else
    {
        printf("empty stack\n");
    }
}

void push(int data)
{
    if (!is_Full())
    {
        top += 1;
        stack[top] = data;
    }

    else
    {
        printf("stack overflow\n");
    }
}

void insert_children(NODE *sample)
{
    char ans[2];

    printf("punem lchild(y/n)?");
    scanf("%s", &ans);

    if (strcmp(ans, "y") == 0)
    {
        sample->lchild = malloc(sizeof(NODE));

        printf("de valoarea: ");
        scanf("%d", &sample->lchild->data);
        sample->lchild->lchild = NULL;
        sample->lchild->rchild = NULL;
    }
    else
        sample->lchild == NULL;

    printf("punem rchild(y/n)?");
    scanf("%s", &ans);

    if (strcmp(ans, "y") == 0)
    {
        sample->rchild = malloc(sizeof(NODE));

        printf("de valoarea: ");
        scanf("%d", &sample->rchild->data);
        sample->rchild->lchild = NULL;
        sample->rchild->rchild = NULL;
    }

    else
        sample->rchild == NULL;
}

void push_back(int **arr, int *size, int value)
{
    int *temp = realloc(*arr, (*size + 1) * sizeof(int));
    if (temp != NULL)
    {
        *arr = temp;
        (*arr)[*size] = value;
        (*size)++;
    }
}

bool hasPath(NODE *root, int searched)
{

    if (!root)
        return false;

    push(root->data);

    if (root->data == searched)
        return true;

    if (hasPath(root->lchild, searched) ||
        hasPath(root->rchild, searched))
        return true;

    pop();
    return false;
}

void printPath(NODE *root, int searched, int path[])
{
    if (hasPath(root, searched))
    {
        for (int i = 0; i < sizeof(stack) / sizeof(int) - 2; i++)
        {

            printf("%d ", stack[i]);
            path[i] = stack[i];
        }
    }

    else
        printf("nu s-a gasit path");
}

int main()
{
    NODE *root = init_root(0);

    int path1[5];
    int path2[5];

    insert_children(root);

    insert_children(root->lchild);

    insert_children(root->lchild->lchild);

    printPath(root, 5, path1);
    printf("\n");

    top = -1;

    for (int i = 0; i < 6; i++)
    {
        stack[i] = 0;
    }

    printPath(root, 6, path2);
    printf("\n");

    for (int i = 4; i > 0; i--)
    {
        if (path1[i] == path2[i])
        {
            printf("LCA = %d", path1[i]);
            break;
        }
    }

    return 0;
}