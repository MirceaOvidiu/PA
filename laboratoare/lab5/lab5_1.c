/*Implementați o funcție ca să verificați că un binary tree este echilibrat
(doi subarbori ai oricărui nod nu au o diferență de nivel mai mare de 1). 3p
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} NODE;

struct node *init_root()
{
    NODE *root = malloc(sizeof(NODE));

    printf("valoarea din root:");
    scanf("%d", &root->data);
    printf("\n");

    root->lchild = NULL;
    root->rchild = NULL;

    return root;
}

void init_children(struct node *sample)
{
    char ans[2];

    printf("ii punem copil stanga(y/n)?");
    scanf("%s", &ans);

    if (strcmp(ans, "y") == 0)
    {
        sample->lchild = malloc(sizeof(NODE));

        printf("de valoarea: ");
        scanf("%d", &sample->lchild->data);
        sample->lchild->lchild = NULL;
        sample->lchild->rchild = NULL;
    }

    printf("ii punem copil dreapta(y/n)?");
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

    if (is_balanced(root) > 0)
        printf("balanced");
    else
        printf("not balanced");

    return 0;
}
