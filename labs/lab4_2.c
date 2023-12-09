/*Implementați două stive folosind un singur vector.
Trebuie să folosiți operațiile de push si pop
ca să umpleți stivele și să le goliți. 3.5p
*/

/*teoretic, am doua stive puse cap in cap, care functioneza
la capete ca o coada - push/pop dintr-una
la un capat, push/pop din celalat - indeplineste simultan ex 2 si ex 3*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 3
#define MAXSIZE 3

typedef struct Stack
{
    int top;
    int size;
    int capacity;
    int *array;
} STK;

void init_stack_metadata(struct Stack *s1, struct Stack *s2)
{
    s1->capacity = SIZE;
    s1->size = 0;
    s1->top = 0;

    s2->capacity = SIZE;
    s2->size = 0;
    s2->top = 2 * SIZE;
}

void init_stack_data(STK *stack1, STK *stack2)
{
    int *cmn_vector = calloc(2 * SIZE, sizeof(int));

    stack1->array = cmn_vector;
    stack2->array = (cmn_vector + 2 * SIZE);
}

int is_full(struct Stack *sample)
{
    return (sample->size == sample->capacity);
}

int is_empty(struct Stack *sample)
{
    return (0 == sample->size);
}

void push_into_1(int data, struct Stack *struct1)
{
    if (is_full(struct1))
    {
        printf("overflow!\n");
    }

    else
    {
        struct1->top += 1;
        struct1->array[struct1->top] = data;
        struct1->size = struct1->size + 1;
    }
}

void push_into_2(int data, struct Stack *stack2)
{
    if (is_full(stack2))
    {
        printf("overflow!\n");
    }

    else
    {
        stack2->top += -1;
        stack2->size = stack2->size + 1;
        stack2->array[stack2->top] = data;
    }
}

void pop_out_of_1(struct Stack *stack1)
{
    if (is_empty(stack1) == 1)
    {
        printf("nu avem element la care sa dam pop\n");
    }

    else
    {
        stack1->top += -1;
        stack1->size = stack1->size - 1;
    }
}

void pop_out_of_2(struct Stack *stack2)
{
    if (is_empty(stack2) == 1)
    {
        printf("nu avem element la care sa dam pop\n");
    }

    else
    {
        stack2->top += +1;
        stack2->size = stack2->size - 1;
    }
}

int peek(STK *stack)
{
    return (stack->array[stack->top]);
}
int main()
{

    STK Stack1;
    STK Stack2;

    struct Stack *stack1 = &Stack1;
    struct Stack *stack2 = &Stack2;

    init_stack_metadata(stack1, stack2);
    init_stack_data(stack1, stack2);

    push_into_1(1, stack1);
    push_into_1(2, stack1);
    push_into_1(3, stack1);
    printf("rezultat peek in 1:%d \n", peek(stack1));

    push_into_2(4, stack2);
    push_into_2(5, stack2);
    push_into_2(6, stack2);
    printf("rezultat peek in 2:%d \n", peek(stack2));

    for (int i = 0; i < SIZE; i++)
    {
        pop_out_of_1(stack1);
        pop_out_of_2(stack2);
    }

    printf("rezultat peek in 1:%d \n", peek(stack1));
    printf("rezultat peek in 2:%d \n", peek(stack2));

    return 0;
}