#include <stdio.h>

int binsearch(int value, int values[], int size);

int main(void)
{
    int arr[9];
    int i, index;
    
    for(i = 0; i < 9; i++)
        arr[i] = i;

    index = binsearch(4, arr, 9);

    printf("%d\t%d\n", index, arr[index]);
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while(low < high) {
        mid = (low+high) / 2;
        if(x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }

    if(v[low] == x)
        return low;

    return -1;
}