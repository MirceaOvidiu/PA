/// SPT folosind dijkstra

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10
#define SIZE 12

typedef struct Graph
{
    int nr_of_vertices;
    int nr_of_edges;
    int *adjacency_matrix;
} GPH;

typedef struct Edge
{
    int source;
    int destination;
    int edge_value;
} EDGE;

GPH *init_graph(int nr_of_vertices)
{
    GPH *graph = malloc(sizeof(struct Graph));

    graph->nr_of_vertices = nr_of_vertices;
    graph->nr_of_edges = 0;

    return graph;
}

int *read_csv(FILE *input, GPH *graph)
{
    GPH *aux_graph = malloc(sizeof(GPH));
    aux_graph->nr_of_edges = 0;
    aux_graph->nr_of_vertices = 0;

    if (input == NULL)
    {
        printf("input file not found\n");
        exit(1);
    }

    char buffer[BUFFER_SIZE];

    int *matrix = calloc(SIZE * SIZE, sizeof(int));

    char *sp;

    while (fgets(buffer, BUFFER_SIZE, input) != NULL)
    {
        EDGE *temp_in = malloc(sizeof(struct Edge));

        sp = strtok(buffer, ",");
        temp_in->source = atoi(sp);

        sp = strtok(NULL, ",");
        temp_in->destination = atoi(sp);

        sp = strtok(NULL, ",");
        temp_in->edge_value = atoi(sp);

        if (temp_in->edge_value != 0)
            graph->nr_of_edges++;

        matrix[SIZE * (temp_in->destination - 1) + (temp_in->source - 1)] = temp_in->edge_value;

        free(temp_in);
    }

    graph->adjacency_matrix = matrix;

    return matrix;
}

int min_distance(int *dist, int *visited, GPH *graph)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < graph->nr_of_vertices; v++)
    {
        if (visited[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
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

void print_solution(int *dist, int n)
{
    printf("vertex:  distanta de la sursa:\n");
    for (int i = 0; i < n; i++)
        printf("%d \t %d\n", i, dist[i]);
}

void dijkstra(GPH *graph, int src)
{
    int *dist = malloc(graph->nr_of_vertices * sizeof(int));
    int *in_spt = calloc(graph->nr_of_vertices, sizeof(int));
    int *prev = calloc(graph->nr_of_vertices, sizeof(int));

    for (int i = 0; i < graph->nr_of_vertices; i++)
    {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[src] = 0;

    for (int i = 0; i < graph->nr_of_vertices - 1; i++)
    {
        int u = min_distance(dist, in_spt, graph);

        in_spt[u] = 1;

        for (int v = 0; v < graph->nr_of_vertices; v++)
        {
            if (!in_spt[v] && graph->adjacency_matrix[u * SIZE + v] && dist[u] != INT_MAX && dist[u] + graph->adjacency_matrix[u * SIZE + v] < dist[v])
            {
                dist[v] = dist[u] + graph->adjacency_matrix[u * SIZE + v];
                prev[v] = u;
            }
        }
    }

    print_solution(dist, graph->nr_of_vertices);

    printf("\nsi pathurile pentru fiecare:\n");

    for (int i = 0; i < graph->nr_of_vertices; i++)
    {
        printf("%d: ", i);
        print_path(prev, i);
        printf("\n");
    }
}

int main()
{
    FILE *input = fopen("input_graf1_undirected.csv", "r");

    GPH *graph = init_graph(SIZE);

    int *adjacency_matrix = read_csv(input, graph);

    dijkstra(graph, 0);

    fclose(input);

    return 0;
}