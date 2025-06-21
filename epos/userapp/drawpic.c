#include "graphics.h"
//#include <stddef.h>    // NULL

struct timespec delay = {
    .tv_sec  = 0,
    .tv_nsec = 1000 * 1000L
};

void nanosleep_delay() {
    nanosleep(&delay, NULL);
}

// 画条形图函数：参数意义同原来代码
void drawBar(int barSize, int length, int lEdge, int upHead, COLORREF r) {
    int i;
    int drawLength = length / 4;  // 根据原代码计算条宽

    for (i = 0; i < barSize; i++) {
        line(lEdge, upHead + i, lEdge + 300, upHead + i, RGB(0, 0, 0));
    }

    for (i = 0; i < barSize; i++) {
        if (i%barSize==0)
            line(lEdge, upHead + i, lEdge + drawLength, upHead + i, RGB(0,255,0));
        else
            line(lEdge, upHead + i, lEdge + drawLength, upHead + i, r);
    }
    nanosleep_delay();
    return;
}


// 初始绘制数组
void drawArr(int* arr, int arrSize, int lEdge, COLORREF color) {
    int i;
    
    for (i = 0; i < arrSize; i++) {
        drawBar(5, arr[i], lEdge, i * 5, color);
    }
    return;
}

// 新增：高亮显示条形图的函数
void highlightBar(int barSize, int length, int lEdge, int upHead, COLORREF highlightColor, COLORREF originalColor) {
    // 用高亮色绘制
    drawBar(barSize, length, lEdge, upHead, highlightColor);
    // 延时一会，让用户能看出高亮效果
    nanosleep_delay();
    nanosleep_delay();
    nanosleep_delay();
    // 操作完成后恢复原色
    drawBar(barSize, length, lEdge, upHead, originalColor);
}

// 交换两个元素并进行高亮提示，注意更新交换前后的状态显示
void drawSwap(int* arr, int firstIndex, int secIndex, int lEdge, COLORREF originalColor) {
    // 交换操作
    int temp = arr[firstIndex];
    arr[firstIndex] = arr[secIndex];
    arr[secIndex] = temp;

    // 计算条形图中的顶部位置，假设每个条间隔为 5 像素
    int upHead1 = firstIndex * 5;
    int upHead2 = secIndex * 5;

    // 高亮正在交换的两个元素, 可选使用不同高亮颜色
    COLORREF highlightColor1 = RGB(255, 255, 0); // 黄色
    COLORREF highlightColor2 = RGB(0, 255, 255); // 青色

    // 先对第一个位置进行高亮，然后恢复原色
    highlightBar(5, arr[firstIndex], lEdge, upHead1, highlightColor1, originalColor);
    // 再对第二个位置进行高亮
    highlightBar(5, arr[secIndex], lEdge, upHead2, highlightColor2, originalColor);
}

void drawBoundary(int lEdge, int upHead,int size,COLORREF color) {
    // 画出边界线
    int i;
    for(i = 0;i < size; i++) {
        line(lEdge + i, upHead, lEdge + i, upHead + 600, color);
    }
}