#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

typedef struct {
  char name[10];
  int score;
}STU;


int cmp_int(void *px, void *py) {
  return *((int*)px) - *((int*)py);
}

int cmp_int_rev(void *px, void *py) {
  return *((int*)py) - *((int*)px);
}


int cmp_float(void *px, void *py) {
  return *((float*)px) - *((float*)py);
}


void swap(void *px, void *py, int sz) {
  unsigned char buff[sz];
  memcpy(buff, px, sz);
  memcpy(px, py, sz);
  memcpy(py, buff, sz);
}



void print_float(void *pf) {
  printf("%f ", *(float*)pf);
}


void print_stu(void *pu) {
  printf("Name: %s, Score: %d\n", ((STU*)pu)->name, ((STU*)pu)->score);
}

int cmp_stu(void *psx, void *psy) {
  return ((STU*)psx)->score > ((STU*)psy)->score;
}

int cmp_stu_name(void *psx, void *psy) {
  return strcmp(((STU*)psx)->name , ((STU*)psy)->name);
}


// 冒泡排序函数  
void bubbleSort(void *arr, int n, int sz,  int (*cmp)(void *, void *), void (*swap)(void *, void *, int)) {
  int i, j;
  for (i = 0; i < n-1; i++) { // 外层循环，控制排序的轮数
    for (j = 0; j < n-i-1; j++) { // 内层循环，控制每轮比较的次数
      // 如果当前元素大于下一个元素，则交换它们
      if (cmp(arr + j*sz, arr + (j+1)*sz))
	swap(arr + j*sz, arr + (j+1)*sz, sz);
    }
  }
}  
  
// 打印数组函数  
void printArray(int arr[], int size) {  
    int i;  
    for (i = 0; i < size; i++)  
        printf("%d ", arr[i]);  
    printf("\n");  
}  

// 打印数组函数  
void printArray_v2(void *arr, int n, int sz, void (*print)(void *)) {  
    int i;  
    for (i = 0; i < n; i++)  
      print(arr+i*sz);
    printf("\n");  
}  

// 打印数组函数  
void printArrayF(float arr[], int size) {  
    int i;  
    for (i = 0; i < size; i++)  
        printf("%f ", arr[i]);  
    printf("\n");  
}  


// 主函数  
int main() {  
    int arr[] = {64, 34, 25, 12, 22, 11, 90};  
    float arr_f[] = {64.64, 34.34, 25, 12, 22, 11, 90};
    STU stu[3] = {{"zhang", 88}, {"wang", 77}, {"li", 99}};
    int n = sizeof(arr)/sizeof(arr[0]);  
    int fn = sizeof(arr_f)/sizeof(arr_f[0]);  
    //bubbleSort(arr, n);  
    // bubbleSort_v2(arr_f, n, sizeof(float), cmp_float, swap);  
    //bubbleSort_v2(stu, 3, sizeof(STU), cmp_stu, swap);  
    bubbleSort(stu, 3, sizeof(STU), cmp_stu_name, swap);  
    printf("Sorted array: \n");  
    //printArrayF(arr_f, n);
    printArray_v2(stu, 3, sizeof(STU), print_stu);
    return 0;  
}
