#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
    printf("%d\n", strcmp(av[1], av[2]));
}