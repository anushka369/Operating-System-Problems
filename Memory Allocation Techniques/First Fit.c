#include <stdio.h>

void firstFit(int b[], int m, int p[], int n) 
{
    int alloc[n];
    for (int i = 0; i < n; i++)
    {
        alloc[i] = -1;
    }

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (b[j] >= p[i]) 
            {
                alloc[i] = j;
                b[j] -= p[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) 
    {
        if (alloc[i] != -1)
        {
            printf("Process %d allocated to block %d\n", i+1, alloc[i]+1);
        }
          
        else
        {
            printf("Process %d not allocated\n", i+1);
        }
    }
}

int main() 
{
    int b[] = {100, 500, 200, 300, 600};
    int p[] = {212, 417, 112, 426};
    int m = sizeof(b) / sizeof(b[0]);
    int n = sizeof(p) / sizeof(p[0]);

    firstFit(b, m, p, n);

    return 0;
}
