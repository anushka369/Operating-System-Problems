#include <stdio.h>
#include <stdlib.h>

void look(int rq[], int n, int head, int dir) 
{
    int seek_time = 0;
    int i, pos = 0;

    for (i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (rq[i] > rq[j]) 
            { 
                int t = rq[i]; rq[i] = rq[j]; 
                rq[j] = t; 
            }
        }
    }

    while (rq[pos] < head)
    {
        pos++;
    }
  
    if (dir) 
    {
        for (i = pos; i < n; i++)
        {
            seek_time += abs(rq[i] - head);
            head = rq[i];
        }
      
        for (i = pos - 1; i >= 0; i--)
        { 
            seek_time += abs(rq[i] - head);
            head = rq[i];
        }
    } 
    
    else 
    {
        for (i = pos - 1; i >= 0; i--)
        { 
            seek_time += abs(rq[i] - head);
            head = rq[i];
        }
      
        for (i = pos; i < n; i++)
        { 
            seek_time += abs(rq[i] - head);
            head = rq[i];
        }
    }
  
    printf("Total Seek Time (LOOK): %d\n", seek_time);
}

int main() 
{
    int n, head, dir, rq[n];
  
    printf("Enter head position, direction (0-L,1-R), number of requests: ");
    scanf("%d %d %d", &head, &dir, &n);
  
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
    { 
        scanf("%d", &rq[i]);
    }

    look(rq, n, head, dir);
    return 0;
}
