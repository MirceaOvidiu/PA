/*Implementați o funcție prin care să verificați
 că un binary tree este binary search tree. 3p*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} NODE;

NODE *init_root(int data)
{
    NODE *root = malloc(sizeof(NODE));
    root->data = data;
    printf("root = %d\n", data);
    root->lchild = NULL;
    root->rchild = NULL;
}

NODE *new_node(int data)
{
    NODE *sample = malloc(sizeof(NODE));

    sample->data = data;
    sample->lchild = NULL;
    sample->rchild = NULL;

    return sample;
}

NODE *bst_insert(NODE *sample, int data)
{
    if (data < sample->data)
    {
        sample->lchild = bst_insert(sample->lchild, data);
    }

    else
    {
        sample->rchild = bst_insert(sample->rchild, data);
    }

    return sample;
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
}

int isBSTUtil(struct node *sample, int min, int max)
{
    if (sample == NULL)
        return 1;
    if (sample->data < min || sample->data > max)
        return 0;
    return isBSTUtil(sample->lchild, min, sample->data - 1) &&
           isBSTUtil(sample->rchild, sample->data + 1,
                     max);
}

int isBST(struct node *sample)
{
    return (isBSTUtil(sample, INT_MIN, INT_MAX));
}

void display(NODE *root)
{
    if (root != NULL)
    {
        display(root->lchild);
        printf("| %d ", root->data);
        display(root->rchild);
    }
}

int main()
{
    NODE *root = init_root(40);

    insert_children(root);
    printf("copii pentru root-lchild\n");
    insert_children(root->lchild);
    printf("\n");
    printf("copii pentru root->rchild\n");
    insert_children(root->rchild);

    if (isBST(root))
        printf("e BST");
    else
        printf("nu e BST");

    return 0;
}