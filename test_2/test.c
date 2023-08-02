#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    char ingredient;
    struct node *l_child;
    struct node *r_child;
} NODE;

void init_children(struct node *sample)
{
        sample->l_child = malloc(sizeof(NODE));
        sample->r_child = malloc(sizeof(NODE));

        printf("ingredientele: (charuri despartite de spatiu)");

        scanf("%c %c", &sample->l_child->ingredient, &sample->r_child->ingredient);
        sample->l_child->l_child = NULL;
        sample->l_child->r_child = NULL;
        sample->r_child->l_child = NULL;
        sample->r_child->r_child = NULL;
}

int main()
{   
    NODE *root = malloc(sizeof(NODE));

    printf("ingredientul din root:");
    scanf("%c", &root->ingredient);
    printf("\n");

    root->l_child = NULL;
    root->r_child = NULL;

    init_children(root);

    printf(" suntem la root->l_child :\n");
    init_children(root->l_child);
    getchar();

    printf("suntem la root->r_child \n");
    init_children(root->r_child);

    printf("suntem la root->l_child->l_child \n");
    init_children(root->l_child->l_child);

    printf("suntem la root->l_child->r_child \n");
    init_children(root->l_child->r_child);

    printf("suntem la root->r_child->l_child \n");
    init_children(root->r_child->l_child);

    printf("suntem la root->r_child->r_child \n");
    init_children(root->r_child->r_child);

    printf("suntem la root->l_child->l_child->l_child \n");
    init_children(root->l_child->l_child->l_child);

    printf("suntem la root->l_child->l_child->r_child \n");
    init_children(root->l_child->l_child->r_child);

    printf("suntem la root->l_child->r_child->l_child \n");
    init_children(root->l_child->r_child->l_child);

    printf("suntem la root->l_child->r_child->r_child \n");
    init_children(root->l_child->r_child->r_child);

    printf("suntem la root->r_child->l_child->l_child \n");
    init_children(root->r_child->l_child->l_child);

    printf("suntem la root->r_child->l_child->r_child \n");
    init_children(root->r_child->l_child->r_child);

    printf("suntem la root->r_child->r_child->l_child \n");
    init_children(root->r_child->r_child->l_child);

    printf("suntem la root->r_child->r_child->r_child \n");
    init_children(root->r_child->r_child->r_child);

    return 0;
}
