/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Fri May  6 10:27:57 2022               *
 * Last Modify:                                        *
 * Comment: 根据课件上的定义创建邻接矩阵图表示时，需要顺序表 *
 *          结构，在此处给出定义                          *
 ******************************************************/
#include "SeqList.h"

void ListInitiate(SeqList *p) {
  p->size = 0;
}

int ListInsert(SeqList *p, int i, DataType x) {
  if ((p->size < MAX_SIZE) && (i >= 0 && i <= p->size)) { // 顺序表未满，且添加位置合理
    for (int j = p->size; j > i; j--)
      p->a[j] = p->a[j - 1];
    p->a[i] = x;
    p->size++; 
    return 1;
  }
  else
    return 0;
}

