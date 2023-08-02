#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    char ingredient;
    struct node *lchild;
    struct node *rchild;
} NODE;

struct node *init_root()
{
    NODE *root = malloc(sizeof(NODE));

    printf("ingredientul din root:");
    scanf("%d", &root->ingredient);
    printf("\n");

    root->lchild = NULL;
    root->rchild = NULL;

    return root;
}

void init_children(struct node *sample)
{
        sample->lchild = malloc(sizeof(NODE));

        printf("de valoarea: ");
        scanf("%d", &sample->lchild->ingredient);
        sample->lchild->lchild = NULL;
        sample->lchild->rchild = NULL;

        sample->rchild = malloc(sizeof(NODE));
        printf("de valoarea: ");
        scanf("%d", &sample->rchild->ingredient);
        sample->rchild->lchild = NULL;
        sample->rchild->rchild = NULL;
}

int is_balanced(NODE *root)
{
    if (root == NULL)
        return 0;

    int lh, rh;

    lh = is_balanced(root->lchild);
    if (lh == -1)
        return -1;

    rh = is_balanced(root->rchild);
    if (rh == -1)
        return -1;

    if (abs(lh - rh) > 1)
        return -1;

    else
    {
        return lh > rh ? lh + 1 : rh + 1;
    }
}

int main()
{
    struct node *root = init_root();

    init_children(root);
    printf(" suntem la: root->lchild :\n");
    init_children(root->lchild);

    printf("suntem la: root->rchild \n");
    init_children(root->rchild);

    printf("suntem la root->lchild->lchild \n");
    init_children(root->lchild->lchild);


    return 0;
}
