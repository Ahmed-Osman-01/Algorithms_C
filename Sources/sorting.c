#include<stdio.h>
#include<stdlib.h>
#include "../Headers/common.h"

/*
 This is the range of the sorted pivot elements using 3-way partition in quick sort
 (min) is the start index
 (max) is the end index
*/
typedef struct range
{
    u16 min;
    u16 max;
}range;

void merge(s32*, u16, u16, u16, u16);
u16 partition(s32*, u16, u16, u16);
range partition_3(s32*, u16, u16, u16);
void swap(s32*, s32*);
void print_arr(s32*, u16);


void selection_sort(s32*arr, u16 size)
{
    int i, j;
    for(i=0; i<size-1; i++)
    {
        for(j=i+1; j<size; j++)
        {
            if(arr[i] > arr[j])
            {
                // swap elements
                arr[i] = arr[i] + arr[j];
                arr[j] = arr[i] - arr[j];
                arr[i] = arr[i] - arr[j];
            }
        }
    }
}

void bubble_sort(s32 *arr, u16 size)
{
    int i, j;
    for(i=0; i<size-1;i++)
    {
        for(j=0; j<size-1-i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                arr[j] = arr[j] + arr[j+1];
                arr[j+1] = arr[j] - arr[j+1];
                arr[j] = arr[j] - arr[j+1];
            }
        }
    }
}


void iterative_merge_sort(s32 *arr, u16 arr_size)
{
    u16 list_size,i,low,mid,high;

    /* starting with lists of size 2 and multiplty the size by 2 in each iteration
        this is to replace the recursion so we have to do bottom up approach */
    for(list_size=2; list_size<=arr_size; list_size = list_size*2)
    {
        /* divide the array into smaller lists of sizes 2, 4, 6...etc and sort these lists using merge */
        for(i=0; i+list_size-1 < arr_size; i = i+list_size)
        {
            low = i;
            high = i+list_size-1;
            mid = (low+high)/2;
            merge(arr, low, mid, high, list_size);
        }
    }
        /*IF THE SIZE OF THE ARR IS NOT 2, 4, 8, 16...ETC WE HAVE TO DO ONE EXTRA MERGE*/
        if(list_size/2 < arr_size)
            merge(arr, 0, (list_size/2)-1, arr_size-1, arr_size);
}

/* Merge part in the merge sort algorithm
    @param arr Array to be sorted
    @param low The start index of the array
    @param mid The middle index of the array
    @param high The end index of the array
    @param size The size of the array */
void merge(s32 *arr, u16 low, u16 mid, u16 high, u16 size)
{
    /* Temporarly array to store the new sorted elements in it */
    s32 tmp_arr[size];
    /* index of the left list , right list and temp array */
    u16 left_list_current, right_list_current, tmp_arr_current;
    left_list_current = low; right_list_current = mid+1; tmp_arr_current = 0;

    /* as long as there are elements in both the left list and right list remaning to be sorted */
    while(left_list_current <= mid && right_list_current <= high)
    {
        if(arr[left_list_current] > arr[right_list_current])
            tmp_arr[tmp_arr_current++] = arr[right_list_current++];
        else
            tmp_arr[tmp_arr_current++] = arr[left_list_current++];
    }

    /* after one of the lists has no more elements, add the rest of the elements of the other list
        in the temp arr */
    for(; left_list_current<=mid; left_list_current++)
        tmp_arr[tmp_arr_current++] = arr[left_list_current];
    for(; right_list_current<=high; right_list_current++)
        tmp_arr[tmp_arr_current++] = arr[right_list_current];
    
    /* copy the elements of the temp array in the original array
        reuse the left_list_current instead of creating new variable */
    for(left_list_current = 0; left_list_current < size; left_list_current++)
        arr[left_list_current + low] = tmp_arr[left_list_current];
}



void iterative_quick_sort(s32 *arr, u16 size)
{
    
    s32 stack[size];
    u16 stack_pointer = 0, left = 0, right = size - 1;
    s16 p, pivot, rnd;
    stack[stack_pointer++] = left;
    stack[stack_pointer++] = right;
    while(stack_pointer != 0)
    {
        right = stack[--stack_pointer];
        left = stack[--stack_pointer];
        rnd = rand() % (right - left + 1) + left;
        pivot = arr[rnd];
        swap(&arr[left], &arr[rnd]);
        p = partition(arr, left, right, pivot);
        
        if(!(p-1 <= left))
        {
            stack[stack_pointer++] = left;
            stack[stack_pointer++] = p-1;
        }
        if(!(p+1 >= right))
        {
            stack[stack_pointer++] = p+1;
            stack[stack_pointer++] = right;
        }
    }

}

u16 partition(s32 *arr, u16 left, u16 right, u16 pivot)
{
    u16 i;
    s16 j = left-1;
    for(i = left; i <= right; i++)
    {
        if(arr[i] <= pivot)
        {   
            swap(&arr[i], &arr[++j]);
        }
    }
    swap(&arr[left], &arr[j]);
    return j;
}

// uses the 3-way partition to solve the problem of semi sorted arrays
void iterative_quick_sort_3(s32 *arr, u16 size)
{
    /* custom stack to push and pop the first and last index of the array to work on to replace the
        recursion */
    s32 stack[size];
    u16 stack_pointer = 0, left = 0, right = size - 1; // start and end of the array
    /* rnd -> random index */
    s16 pivot, rnd;
    /* custom data type to store the start and end of elements equal to pivot */
    range p;

    stack[stack_pointer++] = left;
    stack[stack_pointer++] = right;

    /* while the stack is not empty */
    while(stack_pointer != 0)
    {   /* pop the end and start of the array */
        right = stack[--stack_pointer];
        left = stack[--stack_pointer];

        /* get random index in the range of the new array */
        rnd = rand() % (right - left + 1) + left;
        pivot = arr[rnd];

        /* put the pivot element as the first element in the new array*/
        swap(&arr[left], &arr[rnd]);

        p = partition_3(arr, left, right, pivot);

        /* if the left side of the pivot elements is MORE than one element then push the 
            left side in the stack as a new array */
        if(!(p.min - 1 <= left))
        {
            stack[stack_pointer++] = left;
            stack[stack_pointer++] = p.min - 1;
        }
        /* same as with the left side but with the right side */
        if(!(p.max + 1 >= right))
        {
            stack[stack_pointer++] = p.max + 1;
            stack[stack_pointer++] = right;
        }
    }

}

/* 
    3-Way partition returning the index of the ragne of the elements equal to the pivot element
    (######=======&&&&&)   
    , # -> smaller than pivot
    , = -> equal to pivot
    , & -> bigger than pivot
    @param arr Array to be sorted
    @param left Starting index of the array to be sorted
    @param right Ending index of the array to be sorted
    @param pivot The current pivot element that needs to be positioned in the right index
 */
range partition_3(s32 *arr, u16 left, u16 right, u16 pivot)
{

    u16 i = left;
    /*  j -> last index of smaller than area + 1
        k -> first index of bigger than area  - 1*/
    s16 j = left, k = right;
    
    while(i <= k)
    {   /* if the current element equals the pivot then increament i only */
        if(arr[i] == pivot)
        {
            i++;
        }
        /* if the current element is smaller than  the pivot element then swap them then increament the size of
           smaller than area and i */
        else if(arr[i] < pivot)
        {
            swap(&arr[i++], &arr[j++]);
        }
        /* if the current element is bigger than the pivot then swap them then increase the size of
           bigger than area by decreamenting k only */
        else if(arr[i] > pivot)
        {
            swap(&arr[i], &arr[k--]);
        }   
    }
    /* Add the j and k to the custom data type range then return it */
    range pivot_range = {j, k};
    return pivot_range;
}

// UTILITY FUNCTION
void swap(s32 *a, s32 *b)
{
    s32 temp = *a;
    *a = *b;
    *b = temp;
}



