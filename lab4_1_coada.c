#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Queue
{
    int head;
    int tail;
    int size;
    int capacity;
    int *array;
};

struct Queue *generate_Queue(int capacity)
{
    struct Queue *q = malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->size = 0;
    q->head = q->size;

    q->tail = capacity - 1;
    q->array = (int *)calloc(q->capacity, sizeof(int));

    return q;
}

int is_full(struct Queue *q)
{
    return (q->size == q->capacity);
}

int is_empty(struct Queue *q)
{
    return (0 == q->size);
}

void enqueue(int data, struct Queue *q)
{
    if (is_full(q))
    {
        printf("overflow!\n");
    }

    else
    {
        q->tail += -1;
        q->array[q->tail] = data;
        q->size = q->size + 1;
    }
}

void dequeue(struct Queue *q)
{
    if (is_empty(q))
    {
        printf("nu avem element la care sa dam dequeue\n");
    }

    else
    {

        int data = q->array[q->head];
        q->head = q->head + 1;
    }
}

int peek(struct Queue *q)
{
    return (q->array[q->head]);
}

int main()
{
    struct Queue *q = generate_Queue(5);

    enqueue(1, q);
    enqueue(2, q);
    enqueue(3, q);
    enqueue(4, q);

    dequeue(q);

    printf("in varf se afla: %d\n", peek(q));

    return 0;
}
