#include <stdio.h>
#include <stdlib.h>

void sstf(int rq[], int n, int head) 
{
    int seek_time = 0;
    int visited[n];
  
    for (int i = 0; i < n; i++) 
    {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++) 
    {
        int min = 9999, index = -1;
      
        for (int j = 0; j < n; j++) 
        {
            if (!visited[j] && abs(rq[j] - head) < min) 
            {
                min = abs(rq[j] - head);
                index = j;
            }
        }
      
        visited[index] = 1;
        seek_time += min;
        head = rq[index];
    }
  
    printf("Total Seek Time (SSTF): %d\n", seek_time);
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

    sstf(rq, n, head);
    return 0;
}
