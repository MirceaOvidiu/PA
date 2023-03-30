/*Găsiți o pereche de numere într-un vector,
care adunate să dea valoarea unui număr introdus de la tastatură.
Utilizatorul poate să adauge numere de mai multe ori.
Tratați și cazul în care nu găsește nimic.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void getPairs(int *ptr, int count)
{
    int index1, index2;
    int i, j;
    int wanted;
    char addOthers[2];
    int toAdd;
    int found;

    printf("cautam elementele care insumate dau:\n");
    scanf("%d", &wanted);

    for (i = 0; i < count; i++)
    {
        for (j = 1; j < count - i; j++)
        {

            if ((ptr[i] + ptr[i + j]) == wanted)
            {
                index1 = i;
                index2 = i + j;
                printf("perechea v[%d]=%d si v[%d]=%d insumeaza %d \n", index1, ptr[index1], index2, ptr[index2], wanted);
                found = 1;
            }
        }
    }

    if (found == 0)
    {
        printf("nu s-au gasit\n");
    }

    printf("adaugam alte numere?\n");
    scanf("%s", addOthers);

    if (strcmp(addOthers, "y") == 0)
    {
        printf("cate?\n");
        scanf("%d", &toAdd);

        int *added = calloc(toAdd, sizeof(int));

        for (int i = 0; i < toAdd; i++)
        {
            printf("nr adaugat %d:", i + 1);
            scanf("%d", &added[i]);
        }

        int newSize = toAdd + count;
        /// realloc(ptr, count + toAdd); unele valori din ptr sunt nr random din memorie, 
        ///realloc nu a reusit sa aloce nici macar 1 data 

        int *updatedNrs = calloc(newSize, sizeof(int));

        for (int i = 0; i < count; i++)
        {
            updatedNrs[i] = ptr[i];
            updatedNrs[count +i] = added[i];
        }

        printf("acum valorile sunt:\n");
        for (int i = 0; i < newSize; i++)
        {
            printf("%d ", updatedNrs[i] );
        }

        printf("\n");

        getPairs(updatedNrs,newSize);
    }

    else
    {
        return;
    }
}

int main()
{
    int max;
    int count;

    srand(time(0));

    printf("cate numere generam?\n");
    scanf("%d", &count);

    printf("pana la valoarea de: \n");
    scanf("%d", &max);

    int *ptr = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++)
    {
        ptr[i] = (rand() % max) + 1;
    }

    printf("numerele generate sunt:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d ", ptr[i]);
    }

    printf("\n");

    getPairs(ptr, count);

    return 0;
}