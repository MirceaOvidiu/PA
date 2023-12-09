#include <stdio.h>
#include <stdlib.h>

#define LINES 6
#define COLS 6

typedef struct Cell
{
    int line;
    int column;
} CELL;

int **generate_initial_labyrinth()
{
    int **labyrinth = malloc(LINES * sizeof(int *));

    /*  **labyrinth pentru a evita undefined behaviour, dar
    tot  exited with code=3221226356 apare la run  */

    for (int i = 0; i < LINES; i++)
    {
        labyrinth[i] = malloc(COLS * sizeof(int));
        for (int j = 0; j < COLS; j++)
        {
            labyrinth[i][j] = 1; // 1 pt celule libere
        }
    }

    // 0 pentru cele blocate
    labyrinth[0][1] = 0;
    labyrinth[2][1] = 0;
    labyrinth[2][3] = 0;
    labyrinth[3][1] = 0;
    labyrinth[3][4] = 0;
    labyrinth[4][4] = 0;

    return labyrinth;
}

int **generate_final_labyrinth(int **initial_labyrinth)
{
    int **solved = malloc(LINES * sizeof(int *));

    for (int i = 0; i < LINES; i++)
    {
        solved[i] = malloc(COLS * sizeof(int));
        memcpy(solved[i], initial_labyrinth[i], COLS * sizeof(int));
        // cauzeaza warning de
        // implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
        // dar din moment ce am inclus stlib, nu pricep de ce apare
    }

    return solved;
}

void display_labyrinth(int **labyrinth, int **solved)
{
    for (int i = 0; i < LINES; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (solved[i][j] == 9)
                printf("X");
            else if (labyrinth[i][j] == 0)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int correct_move(int **labyrinth, int column, int line)
{
    if (column >= 0 && column < COLS && line >= 0 && line < LINES && labyrinth[line][column] == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int move(int **labyrinth, int column, int row, int **solved, CELL *finish)
{
    if (column == finish->column && row == finish->line)
    {
        solved[row][column] = 1;
        return 1;
    }

    if (correct_move(labyrinth, column, row))
    {
        solved[row][column] = 9;

        if (move(labyrinth, column + 1, row, solved, finish))
        {
            return 1;
        }

        if (move(labyrinth, column, row + 1, solved, finish))
        {
            return 1;
        }

        solved[row][column] = 0;
        return 0;
    }
    return 0;
}

int solve(int **labyrinth, int **solved, CELL *start, CELL *finish)
{
    if (!move(labyrinth, start->column, start->line, solved, finish))
    {
        printf("No path found.\n");
        return 0;
    }

    labyrinth[finish->line][finish->column] = 9;

    return 1;
}

void free_labyrinth(int **labyrinth)
{
    for (int i = 0; i < LINES; i++)
    {
        free(labyrinth[i]);
    }
    free(labyrinth);
}

int main()
{
    int **labyrinth = generate_initial_labyrinth();
    int **solved = generate_final_labyrinth(labyrinth);

    for (int i = 0; i < LINES; i++)
    {
        solved[i] = malloc(COLS * sizeof(int));
    }

    CELL *start = malloc(sizeof(CELL));
    start->line = 0;
    start->column = 0;

    CELL *finish = malloc(sizeof(CELL));
    finish->column = 5;
    finish->line = 5;

    printf("Initial Labyrinth:\n");
    display_labyrinth(labyrinth, solved);

    printf("\nLabyrinth Solution:\n");

    if (solve(labyrinth, solved, start, finish))
    {
        display_labyrinth(labyrinth, solved);
    }

    free_labyrinth(labyrinth);
    free_labyrinth(solved);
    free(start);
    free(finish);

    return 0;
}