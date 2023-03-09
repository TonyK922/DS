#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 20

//创建一个小顶堆,size代表的是实际元素的个数
typedef struct MinHeap {
    int size;
    int data[MAX_SIZE];
} heap;

//初始化：数组0位置要空着
void init(heap* h ) {
    h->size = 0;
}

//插入元素x 
int insert(heap* h, int x) {
	int flag = 1;
    if (h->size == MAX_SIZE) {
        printf("heap is full!");
        flag = 0;
    }
    int i;
    h->size++;
    for (i = h->size; i >= 1; i /= 2) {
        if(x < h->data[i / 2]) {
            h->data[i] = h->data[i/2];
        } else {
            break;
        }
    }
    h->data[i] = x;
    return flag;
}

//删除最小元素，在小顶堆即意味着删除根节点
int deleteMin(heap* h) {
    int child;
    int result = h->data[1];
    h->data[1] = h->data[h->size];
    h->size--;
    int i = 1;
    int temp = h->data[1];
    for (i = 1; 2 * i <= h->size; i = child) {
        child = 2 * i;
        if (child != h->size && h->data[child] > h->data[child+1]) {
			//如果左子节点非最后元素且>右子节点,则右子节点最小
            child++;
        }
        if (temp > h->data[child]) {
			//如果temp大于当前元素的最小子节点，则将最小子节点赋值给父节点，否则跳出
            h->data[i] = h->data[child];
        } else {
            break;
        }
    }
    h->data[i] = temp;//将缓冲区值赋给当前游标
    return result;
}

//堆排序
void heap_sort(int a[], int n) {
    int i;
    heap* h = (heap*)malloc(sizeof(heap));//给堆指针分配空间
    init(h);//初始化堆
    for (i = 0; i < n; i++) {//将数组的元素依次插入堆
        insert(h, a[i]);
    }
    for (i = 0; i < n; i++) {
        a[i] = deleteMin(h);
    }
}
//遍历数组
void traverse_array(int a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
}

//主函数测试 
int main() {
    int a[] = {10,7,2,5,1};
    int n = sizeof(a) / sizeof(int);
    traverse_array(a, n);
    heap_sort(a, n);
    traverse_array(a, n);
}