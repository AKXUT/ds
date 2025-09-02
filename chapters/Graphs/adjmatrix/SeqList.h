/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Fri May  6 10:51:27 2022                *
 * Last Modify:                                        *
 * Comment: 根据课件上的定义创建邻接矩阵图表示时，需要顺序表 *
 *          结构，在此处给出定义                          *
 ******************************************************/
#ifndef Seq_L
#define Seq_L

#define MAX_SIZE 50
typedef char DataType;

typedef struct {
  int size;
  DataType a[MAX_SIZE];
} SeqList;

void ListInitiate(SeqList *p);
int ListInsert(SeqList *p, int i, DataType x);
#endif
