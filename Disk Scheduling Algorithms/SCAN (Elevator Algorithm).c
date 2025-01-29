#include <stdio.h>
#include <stdlib.h>

void scan(int rq[], int n, int head, int disk_size, int dir) 
{
    int seek_time = 0, i, pos = 0;
    rq[n++] = head;
    rq[n++] = (dir == 1) ? disk_size - 1 : 0;
    
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
  
    printf("Total Seek Time (SCAN): %d\n", seek_time);
}

int main() 
{
    int n, head, disk_size, dir, rq[n];
  
    printf("Enter disk size, head position, direction (0-L,1-R), requests: ");
    scanf("%d %d %d %d", &disk_size, &head, &dir, &n);
  
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &rq[i]);
    }

    scan(rq, n, head, disk_size, dir);
    return 0;
}
