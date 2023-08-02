/// knapsck

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR_OBJ 5
#define CAPACITY 15
#define BUFFER_SIZE 10

typedef struct Object
{
    int weight;
    int value;
} OBJ;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void read_objects(FILE *input_file, OBJ *objects)
{
    int i = 0;
    char buffer[BUFFER_SIZE];
    char *sp;

    while (fgets(buffer, BUFFER_SIZE, input_file) != NULL && i < NR_OBJ)
    {
        sp = strtok(buffer, ",");
        (objects + i)->weight = atoi(sp);

        sp = strtok(NULL, ",");
        (objects + i)->value = atoi(sp);

        i += 1;
    }
}

int bktr(OBJ *objects, int capacity, int nr_of_objects)
{
    if (nr_of_objects == 0 || capacity == 0)
        return 0;

    OBJ current_item = objects[nr_of_objects - 1];

    int current_weight = current_item.weight;
    int current_value = current_item.value;

    if (current_weight > capacity)
        return bktr(objects, capacity, nr_of_objects - 1);

    int include_current = current_value + bktr(objects, capacity - current_weight, nr_of_objects - 1);
    int exclude_current = bktr(objects, capacity, nr_of_objects - 1);

    return max(include_current, exclude_current);
}

int main()
{
    FILE *infile = fopen("input.csv", "rt");
    OBJ *objects = calloc(NR_OBJ, sizeof(OBJ));
    int capacity = CAPACITY;
    int nr_of_obj = NR_OBJ;
    int max_value = 0;

    read_objects(infile, objects);

    for (int i = 0; i < NR_OBJ; i++)
    {
        printf("Obiectul %d: valoare:%d greutate:%d\n", i + 1, (objects + i)->value, (objects + i)->weight);
    }

    max_value = bktr(objects, capacity, nr_of_obj);
    printf("valoarea maxima: %d\n", max_value);

    return 0;
}