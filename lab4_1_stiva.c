#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 8
#define MAXSIZE 10

int top = -1;
int stack[SIZE];

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



int main()
{

    push(1);
    push(2);
    push(3);
    push(4);
    pop();

    printf("la varf se afla:%d", peek());

    return 0;
}