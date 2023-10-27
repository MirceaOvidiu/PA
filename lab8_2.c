/// SPT folosind Bellman - Ford

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10
#define INF 999

typedef struct Edge
{
    int source;
    int destination;
    int weight;
} EDGE;

typedef struct Graph
{
    int nr_of_vertices;
    int nr_of_edges;
    struct Edge *edges;
} GPH;

GPH *init_graph(int nr_of_vertices, int nr_of_edges)
{
    GPH *graph = malloc(sizeof(GPH));

    graph->nr_of_edges = nr_of_edges;
    graph->nr_of_vertices = nr_of_vertices;

    graph->edges = malloc(nr_of_edges * sizeof(EDGE));

    return graph;
}

void read_csv(FILE *input, GPH *graph)
{
    int edge_nr = 0;
    int i = 0;

    if (input == NULL)
    {
        printf("input file not found\n");
        exit(1);
    }

    char buffer[BUFFER_SIZE];

    char *sp;

    while (fgets(buffer, BUFFER_SIZE, input) != NULL && i < graph->nr_of_edges)
    {
        sp = strtok(buffer, ",");
        (graph->edges + i)->source = atoi(sp);

        sp = strtok(NULL, ",");
        (graph->edges + i)->destination = atoi(sp);

        sp = strtok(NULL, ",");
        (graph->edges + i)->weight = atoi(sp);

        i++;
    }
}

void display_distances(int *to_display, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("pana la %d: ", i);
        printf("%d ", to_display[i]);
        printf("\n");
    }

    printf("\n");
}

void print_edges(GPH *graph)
{
    printf("muchiile sunt:\n");

    for (int i = 0; i < graph->nr_of_edges; i++)
    {
        printf("%d->%d cost %d \n", ((graph->edges) + i)->source,
               ((graph->edges) + i)->destination,
               ((graph->edges) + i)->weight);
    }
}

void print_path(int *prev, int dest)
{
    if (prev[dest] == -1)
    {
        printf("%d", dest);
        return;
    }

    print_path(prev, prev[dest]);
    printf(" -> %d", dest);
}

void bellman_ford(GPH *graph, int start)
{
    int src, dest, wt;

    // int distances and predecessors
    int *distances = calloc(graph->nr_of_vertices, sizeof(int));
    int *prev = calloc(graph->nr_of_vertices, sizeof(int));

    for (int i = 0; i < graph->nr_of_vertices; i++)
    {
        distances[i] = INF;
        prev[i] = -1;
    }

    distances[start] = 0;

    /// relax edges nr_of_vertices - 1 times
    for (int i = 1; i <= graph->nr_of_vertices; i++)
    {
        for (int j = 0; j < graph->nr_of_edges; j++)
        {
            src = ((graph->edges) + j)->source;
            dest = ((graph->edges) + j)->destination;
            wt = ((graph->edges) + j)->weight;

            if (distances[src] != INF && distances[dest] > distances[src] + wt)
            {
                distances[dest] = distances[src] + wt;
                prev[dest] = src;
            }
        }
    }

    /// check for negative cycle
    for (int i = 0; i < graph->nr_of_vertices; i++)
    {
        src = ((graph->edges) + i)->source;
        dest = ((graph->edges) + i)->destination;
        wt = ((graph->edges) + i)->weight;

        if (distances[src] != INF && distances[dest] > distances[src] + wt)
        {
            printf("ciclu negativ!\n");
        }
    }

    printf("\n");

    display_distances(distances, graph->nr_of_vertices);

    printf("si pathurile pentru fiecare:\n");

    for (int i = 0; i < graph->nr_of_vertices; i++)
    {
        printf("%d: ", i);
        print_path(prev, i);
        printf("\n");
    }
}

int main()
{
    int nr_of_vertices;
    int nr_of_edges;

    FILE *input = fopen("input_graf0_directed.csv", "r");

    GPH *graph = init_graph(10, 14);

    read_csv(input, graph);

    print_edges(graph);

    bellman_ford(graph, 0);

    free(graph);
    fclose(input);
}