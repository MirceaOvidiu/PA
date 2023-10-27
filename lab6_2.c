#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa, ar fi luat prea mult sa citim
/// stringuri pt numele lor

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} STK;

NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));

    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

GPH *create_graph(int vertices)
{
    int i;

    GPH *graph = malloc(sizeof(GPH));

    graph->vertices = vertices;
    graph->adjacency_lists = malloc(sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STK *create_stack(int capacity)
{
    STK *stack = malloc(sizeof(STK));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(int pushed, STK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushed;
}

void DFS(GPH *graph, STK *stack, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);
    push(vertex_nr, stack);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, stack, connected_vertex);
        }
        temp = temp->next;
    }
}

void insert_edges(GPH *graph, int nr_of_edges, int nr_of_vertices)
{
    int src, dest, i;

    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);

    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe_visited_list(GPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void can_be_reached(GPH *graph, int nr_of_vertices, STK *stack1, STK *stack2)
{
    /// pe scurt luam functionalitatea care e deja pusa in main,
    // si luam 2 cate 2 fiecare nod si aflam daca e sau nu drum intre ele
    // in can_be_reached stocam cu 1 sau 0 daca se poate ajunge la un nod
    // daca nu, adica daca ramane 0, in indexul specific, nu se poate ajunge la
    // acel nod . In functie de indexurile la care este 0, spunem ca nu se poate
    // ajunge la nodurile de acel index

    int *can_be_reached = calloc(5, sizeof(int)); // 0 sau 1 daca poate fi sau nu ajuns

    for (int i = 0; i < nr_of_vertices; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j < 5; j++)
        {
            DFS(graph, stack1, i);

            wipe_visited_list(graph, nr_of_vertices);

            DFS(graph, stack2, j);

            for (int j = 0; j < nr_of_vertices && !ans; j++)
            {
                for (int i = 0; i < nr_of_vertices && !ans; i++)
                {
                    if ((stack1->array[i] == j) && (stack2->array[j] == i))
                    {
                        can_be_reached = 1;
                    }
                }
            }
        }
    }
}

int main()
{

    int nr_of_vertices;
    int nr_of_edges;
    int src, dest;
    int i;
    int vertex_1;
    int vertex_2;
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nr_of_vertices);

    STK *stack1 = create_stack(2 * nr_of_vertices);
    STK *stack2 = create_stack(2 * nr_of_vertices);

    insert_edges(graph, nr_of_edges, nr_of_vertices);

    can_be_reached(graph, nr_of_vertices, stack1, stack2);

    return 0;
}
