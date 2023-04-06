#include<stdio.h>
char linear_search(int*arr, int size, int ele)
{
   int i;
   for(i=0; i<size; i++)
   {
        if(arr[i] == ele)
            return 1;
   }
   return 0;
}

char binary_search(int*arr, int size, int ele)
{
    int start, end, mid;
    start = 0;
    end = size-1;
    while(start <= end)
    {
        mid = (start+end)/2;
        if(arr[mid] == ele)
        {
            return 1;
        }else if(arr[mid] > ele)
        {
            end = mid - 1;
        }else
        {
            start = mid + 1;
        }
    } 
    return 0;
}