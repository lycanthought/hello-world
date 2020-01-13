

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i, j;

int greatestCommonDivisor(int u, int v)
{
    if (u == v) { return u; }
    int t;
    while (u > 0)
    {
        if (u < v)
        {
            t = u;
            u = v;
            v = t;
        }
        u = u - v;
    }
    return v;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("please enter two integer arguments\n");
    }
    else
    {
        i = atoi(argv[1]);
        j = atoi(argv[2]);
        int array[i][j];
        printf("i = %d, j = %d v = %d\n", i, j, greatestCommonDivisor(i, j));
        for (int a = 0; a < j; a++)
        {
            for (int b = 0; b < i; b++)
            {
                int c = greatestCommonDivisor((a+1), (b+1));
                if (c != 1)
                {
                    c = 0;
                }
                printf("%d ", c);
            }
            printf("\n");
        }
        return 0;
    }
}
