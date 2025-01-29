#include <stdio.h>
#include <stdlib.h>

void cscan(int rq[], int n, int head, int disk_size) 
{
    int seek_time = 0, i, pos = 0;
    rq[n++] = head;
    rq[n++] = disk_size - 1;
    rq[n++] = 0;
    
    for (i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (rq[i] > rq[j]) 
            { 
                int t = rq[i]; rq[i] = rq[j]; rq[j] = t; 
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
  
    head = 0;
  
    for (i = 0; i < pos; i++) 
    {
        seek_time += abs(rq[i] - head);
        head = rq[i];
    }

    printf("Total Seek Time (C-SCAN): %d\n", seek_time);
}

int main() 
{
    int n, head, disk_size, rq[n];
  
    printf("Enter disk size, head position, number of requests: ");
    scanf("%d %d %d", &disk_size, &head, &n);
  
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &rq[i]);
    }

    cscan(rq, n, head, disk_size);
    return 0;
}
