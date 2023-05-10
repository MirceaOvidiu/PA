#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 7
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
    int edge_nr = 0;

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

void display_adj_matrix(int *adjacency_matrix, FILE *output)
{
    printf("matricea de adiacenta a grafului este:\n");
    fprintf(output, "matricea de adiacenta a grafului este:\n");

    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            printf("%d ", adjacency_matrix[j * SIZE + i]);
            fprintf(output, "%d ", adjacency_matrix[j * SIZE + i]);
        }

        printf("\n");
        fprintf(output, "\n");
    }
}

int cmp_func(EDGE *a, EDGE *b)
{
    return a->edge_value - b->edge_value;
}

int find(int parent[], int node)
{
    if (parent[node] == -1)
    {
        return node;
    }

    return find(parent, parent[node]);
}

void union_nodes(int parent[], int node1, int node2)
{
    int parent_node1 = find(parent, node1);
    int parent_node2 = find(parent, node2);

    parent[parent_node1] = parent_node2;
}

int compare_edges(const void *a, const void *b)
{
    EDGE *edge_a = (EDGE *)a;
    EDGE *edge_b = (EDGE *)b;

    return edge_a->edge_value - edge_b->edge_value;
}

void kruskal(GPH *graph, FILE *output)
{
    // Allocate memory for visited array
    int *visited = calloc(SIZE, sizeof(int));

    // Allocate memory for edges array
    EDGE *edges = malloc(graph->nr_of_edges * sizeof(EDGE));

    // Copy edges from adjacency matrix to edges array
    int k = 0;

    for (int i = 0; i < graph->nr_of_vertices; i++)
    {
        for (int j = 0; j < graph->nr_of_vertices; j++)
        {
            if (*(graph->adjacency_matrix + i * graph->nr_of_vertices + j) != 0)
            {
                (edges + k)->source = i;
                (edges + k)->destination = j;
                (edges + k)->edge_value = *(graph->adjacency_matrix + i * graph->nr_of_vertices + j);
                k++;
            }
        }
    }

    // Sort edges array in ascending order of edge value
    qsort(edges, graph->nr_of_edges, sizeof(EDGE), cmp_func);

    int parent[SIZE];

    // Initialize parent array
    for (int i = 0; i < SIZE; i++)
    {
        parent[i] = -1;
    }

    int total_weight = 0;

    printf("MST folosind kruskal: \n");
    fprintf(output, "MST folosind kruskal: \n");

    for (int i = 0; i < graph->nr_of_edges; i++)
    {
        int source = (edges + i)->source;
        int dest = (edges + i)->destination;
        int edge_value = (edges + i)->edge_value;

        int parent_src = find(parent, source);
        int parent_dest = find(parent, dest);

        if (parent_src != parent_dest)
        {
            printf("%d -> %d\n", source, dest);
            fprintf(output, "%d -> %d\n", source, dest);
            total_weight += edge_value;
            union_nodes(parent, parent_src, parent_dest);
        }
    }

    // Print the total weight of the MST
    printf("Total weight of MST: %d\n", total_weight);
    fprintf(output, "Total weight of MST: %d\n", total_weight);

    // Free memory
    free(visited);
    free(edges);
}

void prim(GPH *graph, FILE *output)
{
    int min_edge;
    int location = 0;
    int src, dest;
    int total_weight = 0;
    int *matrix = graph->adjacency_matrix;

    printf("MST folosind prim: \n");
    fprintf(output, "MST folosind prim: \n");

    // cautam muchia cu valoarea minima pentru a incepe de la ea
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (graph->adjacency_matrix[i * SIZE + j] != 0)
            {
                if (min_edge < graph->adjacency_matrix[i * SIZE + j])
                {
                    continue;
                }

                else
                {
                    if (graph->adjacency_matrix[i * SIZE + j] < min_edge)
                    {
                        min_edge = graph->adjacency_matrix[SIZE * i + j];
                        src = j;
                        dest = i;
                    }
                }
            }
        }
    }

    total_weight += min_edge;

    printf("muchia %d->%d cu valoarea %d\n", src, dest, min_edge);

    int *visited = calloc(SIZE, sizeof(int));

    visited[src] = 1;
    visited[dest] = 1;

    while (1)
    {
        min_edge = INT_MAX;
        for (int i = 0; i < SIZE; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < SIZE; j++)
                {
                    if (!visited[j] && matrix[i * SIZE + j] != 0 && matrix[i * SIZE + j] < min_edge)
                    {
                        min_edge = matrix[i * SIZE + j];
                        src = i;
                        dest = j;
                    }
                }
            }
        }

        // break cand toate nodurile sunt vizitate
        if (min_edge == INT_MAX)
            break;

        // adaugam muchia cu val minima in MST
        visited[dest] = 1;
        total_weight += min_edge;

        fprintf(output, "muchia%d<->%d cu valoarea %d\n", src + 1, dest + 1, min_edge);
        printf("muchia %d<->%d cu valoarea %d\n", src + 1, dest + 1, min_edge);
    }
    printf("Costul MST-ului: %d\n", total_weight);
    fprintf(output, "Costul MST-ului: %d\n", total_weight);

    free(visited);
    free(matrix);
}

int main()
{
    FILE *import_file = fopen("import.csv", "rt");
    /// fisierul csv contine contine informatii despre muchiile
    /// grafului sub forma : sursa, destinatie, costul muchiei
    FILE *export_file = fopen("export.csv", "wt");

    GPH *graph = init_graph(12);

    read_csv(import_file, graph);

    fclose(import_file);

    display_adj_matrix(graph->adjacency_matrix, export_file);

    prim(graph, export_file);

    kruskal(graph, export_file);

    fclose(export_file);

    return 0;
}
