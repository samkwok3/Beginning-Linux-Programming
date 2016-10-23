#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>
int main()
{
    int nrows, ncolumns;
    setupterm(NULL, fileno(stdout), (int *)0);
    nrows = tigetnum("lines");
    ncolumns = tigetnum("cols");
    printf("This terminal has %d columns and %d rows\n", ncolumns, nrows);

    char *cup;
    cup = tigetstr("cup");
    printf("clear num:%s\n", cup);
    tputs(tparm(cup, 1, 3), 1, putchar);

    exit(0);
}
