#include<stdio.h>
#include<stdlib.h>
#include "../Headers/common.h"
#include "../Headers/searching.h"
#include "../Headers/sorting.h"
#define arr_size 12

void test_sorting_algo(s32*, u16, void (*algo)(s32*, u16));
void print_arr(s32*, u16);
int main()
{
    s32 arr[arr_size] = {3,5,7,1,8,6,10,5,19,2,3};
    s32 sorted_arr[arr_size] = {1,2,4,5,7,8,9,12};
    s32 ele;
    

    // THIS SHOUD PRINT ARRAY BEOFRE AND AFTER BEING SORTED
    test_sorting_algo(arr, arr_size, &iterative_quick_sort);    
   
    return 1;
}

void test_sorting_algo(s32 *arr, u16 size, void (*algo)(s32*, u16))
{
    printf("Before: ");
    print_arr(arr, arr_size);
    algo(arr, size);
    printf("After: ");
    print_arr(arr, size);
}

void print_arr(s32 *arr, u16 size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}