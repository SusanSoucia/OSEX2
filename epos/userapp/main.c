/*
 * vim: filetype=c:fenc=utf-8:ts=4:et:sw=4:sts=4
 */
#include <inttypes.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <sys/mman.h>
#include <syscall.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "graphics.h"
#include <string.h>

extern void *tlsf_create_with_pool(void* mem, size_t bytes);
extern void *g_heap;

/**
 * GCC insists on __main
 *    http://gcc.gnu.org/onlinedocs/gccint/Collect2.html
 */
void __main()
{
    size_t heap_size = 32*1024*1024;
    void  *heap_base = mmap(NULL, heap_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
	g_heap = tlsf_create_with_pool(heap_base, heap_size);
}

/*
结构体定义
*/
struct passArg{
    int* array;
    int size;
    int lEdge;
};

void bubbleSort(int arr[], int size);
void selectionSort(int arr[], int size);
void insertionSort(int arr[],int size);
void quickSort(int arr[], int low, int high);
int findpivot(int arr[], int low, int high);
int partition(int arr[], int low,int high,int pivot);
void swap(int arr[],int low,int high);
int* createArray(int size);
void printArray(int arr[], int size);
void drawArray(int arr[], int size,int lEdge);
void successMark(int x,int y);

/**
 * 新线程所执行的函数
 */
void taskfoo(void *pv)
{
    printf("task #%d: I'm a new thread(pv=0x%08x)!\r\n",
            task_getid(), pv);
    //传参
    struct passArg *args = (struct passArg *)pv;
    bubbleSort(args->array, args->size);
    successMark((args->lEdge+args->lEdge+200)/2,500);
    task_exit(0);
    }

void taskfoo1(void *pv)
{
    printf("task #%d: I'm a new thread(pv=0x%08x)!\r\n",
            task_getid(), pv);
    //传参
    struct passArg *args = (struct passArg *)pv;
    selectionSort(args->array, args->size);
    successMark((args->lEdge+args->lEdge+200)/2,500);
    task_exit(0);
    }

void taskfoo2(void *pv)
{
    printf("task #%d: I'm a new thread(pv=0x%08x)!\r\n",
            task_getid(), pv);
    //传参
    struct passArg *args = (struct passArg *)pv;
    insertionSort(args->array, args->size);
    successMark((args->lEdge+args->lEdge+200)/2,500);
    task_exit(0);
    }

void taskfoo3(void *pv)
{
    printf("task #%d: I'm a new thread(pv=0x%08x)!\r\n",
            task_getid(), pv);
    //传参
    struct passArg *args = (struct passArg *)pv;
    quickSort(args->array,0,args->size-1);
    successMark((args->lEdge+args->lEdge+200)/2,500);
    task_exit(0);
    }


//////////////////////////此处用于定义排序及作图的函数
void drawArray(int arr[], int size,int lEdge)
{
    int i;
    for (i = 0; i < size; i++)
    {   
        line(lEdge,i,200+lEdge,i,RGB(0, 0, 0));
        line(lEdge,i,lEdge+arr[i]/8,i,RGB(0, 0, 255));
    }
}

void successMark(int x,int y)
{   
    int i;
    int j;
    for (i=x ; i < x+10; i++)
    {
        for (j=y ; j < y+10; j++)
        {
            setPixel(i,j,RGB(0,255,0));
        }
    }
}

/*
排序函数
*/
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
                drawArray(arr,size,0);
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
        drawArray(arr,size,200);
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
            drawArray(arr,size,400);
        }
        arr[j + 1] = key;
    }
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


/////////////////////////
int* createArray(int size)
{
    int* arr = (int*)malloc(size * sizeof(int));
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = rand() % 1000;
    }
    return arr;
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}
/////////////////////////



/**
 * 第一个运行在用户模式的线程所执行的函数
 */
void main(void *pv)
{
    int tid_foo;int tid_foo2;int tid_foo3;int tid_foo4;
    printf("task #%d: I'm the first user task(pv=0x%08x)!\r\n",
            task_getid(), pv);

    //TODO: Your code goes here
    //list_graphic_modes();
    srand(time(NULL));
    int randomnum = rand()%681; //随机数范围限制在0~680，便于作图
    int kinds = 4;  //要显示的种类数

    init_graphic(0x115);
    int xLength = g_graphic_dev.XResolution;
    int yLength = g_graphic_dev.YResolution;
    int i;

    for (i =0;i<kinds;i++){     //分界线
        int x0 = i*xLength/kinds;
        line(x0,0,x0,yLength,RGB(255, 0, 0));
    }


    //定义数组
    int* arr = createArray(randomnum);
    struct passArg arg1; struct passArg arg2;
    struct passArg arg3; struct passArg arg4;
    arg1.array = (int*)malloc(randomnum * sizeof(int));
    arg2.array = (int*)malloc(randomnum * sizeof(int));
    arg3.array = (int*)malloc(randomnum * sizeof(int));
    arg4.array = (int*)malloc(randomnum * sizeof(int));
    arg1.size = randomnum; arg2.size = randomnum;
    arg3.size = randomnum; arg4.size = randomnum;
    arg1.lEdge = 0; arg2.lEdge = 200;
    arg3.lEdge = 400; arg4.lEdge = 600;
    memcpy(arg1.array,arr,sizeof(int)*randomnum);
    memcpy(arg2.array,arr,sizeof(int)*randomnum);
    memcpy(arg3.array,arr,sizeof(int)*randomnum);
    memcpy(arg4.array,arr,sizeof(int)*randomnum);

    sleep(2);

    //printf("randomnum = %d\n", randomnum);
    //printf("xLength = %d, yLength = %d\n", xLength, yLength);

    unsigned char*stack_foo;
    unsigned char*stack_foo1;
    unsigned char*stack_foo2;
    unsigned char*stack_foo3;
    unsigned int stack_size = 1024*1024;
    stack_foo= (unsigned char*)malloc(stack_size);
    stack_foo1 = (unsigned char*)malloc(stack_size);
    stack_foo2 = (unsigned char*)malloc(stack_size);
    stack_foo3 = (unsigned char*)malloc(stack_size);
    time_t t0 = time(NULL);
    tid_foo = task_create(stack_foo+stack_size,&taskfoo,(void*)&arg1);
    tid_foo2 = task_create(stack_foo1+stack_size,&taskfoo1,(void*)&arg2);
    tid_foo3 = task_create(stack_foo2+stack_size,&taskfoo2,(void*)&arg3);
    tid_foo4 = task_create(stack_foo3+stack_size,&taskfoo3,(void*)&arg4);
    task_wait(tid_foo,NULL);
    time_t t1 = time(NULL);
    task_wait(tid_foo2,NULL);
    time_t t2 = time(NULL);
    task_wait(tid_foo3,NULL);
    time_t t3 = time(NULL);
    task_wait(tid_foo4,NULL);
    time_t t4 = time(NULL);
    sleep(2);
    exit_graphic();
    printf("bubbleSort time: %d\n",t1-t0);
    printf("selectionSort time: %d\n",t2-t0);  
    printf("insertionSort time: %d\n",t3-t0);
    printf("quickSort time: %d\n",t4-t0);

    while(1)
    ;
    task_exit(0);

}

