// mySort.c
# include "mySort.h"

void bubbleSort(int arr[], int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int size)
{
    int i, j, minIndex;
    for (i = 0; i < size - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void insertionSort(int arr[],int size)
{

    int i, j, key;
    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            drawArray(arr,size,340);
        }
        arr[j + 1] = key;
    }
}

void mergeSort(int arr[], int l, int r)
{
    //Todo
}

void quickSort(int arr[], int low, int high)
{
    if (high <= low)
        return;
    int pivotindex = findpivot(arr, low, high);
    swap(arr, pivotindex, high);
    int k = partition(arr, low - 1, high, arr[high]);
    swap(arr, k, high);
    quickSort(arr, low, k - 1);
    quickSort(arr, k + 1, high);
}

inline int findpivot(int arr[], int low, int high)  //快速排序返回轴值
{
    return (low + high) / 2;
}

inline int partition(int arr[], int low,int high,int pivot) //快速排序划分
{
    do
    {
        while (arr[++low] < pivot);
        while ((low < high) && (pivot < arr[--high]));
        swap(arr, low, high);
    } while (low < high);
    return low;
}

inline void swap(int arr[],int low,int high)    //快速排序交换
{
    int temp = arr[low];
    arr[low] = arr[high];
    arr[high] = temp;

    drawArray(arr,high,600);
}
