#include <stdio.h>
#include <stdlib.h>

void Hanoi(int nr_of_disks, char from_tower, char to_tower, char aux_tower)
{
    if (nr_of_disks == 1)
    {
        printf("\n mutam discul 1: %c -> %c", from_tower, to_tower);
        return;
    }

    Hanoi(nr_of_disks - 1, from_tower, aux_tower, to_tower);

    printf("\n mutam discul %d: %c -> %c", nr_of_disks, from_tower, to_tower);

    Hanoi(nr_of_disks - 1, aux_tower, to_tower, from_tower);
}

int main()
{
    int nr_of_disks = 4;

    Hanoi(nr_of_disks, 'a', 'b', 'c');

    return 0;
}