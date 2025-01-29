#include <stdio.h>
#include <stdlib.h>

void fcfs(int rq[], int n, int head) 
{
    int seek_time = 0;
    for (int i = 0; i < n; i++) 
    {
        seek_time += abs(rq[i] - head);
        head = rq[i];
    }
    printf("Total Seek Time (FCFS): %d\n", seek_time);
}

int main() 
{
    int n, head;
    printf("Enter head position & number of requests: ");
    scanf("%d %d", &head, &n);
    int rq[n];
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) scanf("%d", &rq[i]);
    
    fcfs(rq, n, head);
    return 0;
}
