#include <stdio.h>

void bestFit(int b[], int m, int p[], int n) 
{
    int alloc[n];
    for (int i = 0; i < n; i++)
    {
        alloc[i] = -1;
    }

    for (int i = 0; i < n; i++) 
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) 
        {
            if (b[j] >= p[i]) 
            {
                if (bestIdx == -1 || b[bestIdx] > b[j])
                {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) 
        {
            alloc[i] = bestIdx;
            b[bestIdx] -= p[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
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

    bestFit(b, m, p, n);

    return 0;
}
