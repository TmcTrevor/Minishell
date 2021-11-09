#include "stdio.h"

int main(int argc, char **av)
{
    int i;

    i = 0;
    while (av[i])
    {
        printf("%s\n", av[i]);
        i++;
    }
    return (0);
}