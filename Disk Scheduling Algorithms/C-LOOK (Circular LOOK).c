#include <stdio.h>
#include <stdlib.h>

void clook(int rq[], int n, int head) 
{
    int seek_time = 0, i, pos = 0;
  
    for (i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (rq[i] > rq[j]) 
            { 
                int t = rq[i]; 
                rq[i] = rq[j];
                rq[j] = t; 
            }
        }
    }

    while (rq[pos] < head)
    { 
        pos++;
    }

    for (i = pos; i < n; i++)
    { 
        seek_time += abs(rq[i] - head);
        head = rq[i];
    }

    for (i = 0; i < pos; i++)
    { 
        seek_time += abs(rq[i] - head);
        head = rq[i];
    }

    printf("Total Seek Time (C-LOOK): %d\n", seek_time);
}

int main() 
{
    int n, head, rq[n];
  
    printf("Enter head position & number of requests: ");
    scanf("%d %d", &head, &n);
  
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
    { 
        scanf("%d", &rq[i]);
    }

    clook(rq, n, head);
    return 0;
}
