/*************************************************
 * Created by David on Wed Sep 17 17:07:18 2025  *
 *************************************************/

#include <stdio.h>

// 枚举类型，表示 9 种运算符
typedef enum {
  PLUS, MINUS, STAR, SLASH, LPAREN, RPAREN, HASH, OPERATOR_COUNT
} Operator;

// 运算符优先级表
int precedence[OPERATOR_COUNT][OPERATOR_COUNT] = {
  { '>', '>', '<', '<', '<', '>', '>'},  // '+'  
  { '>', '>', '<', '<', '<', '>', '>'},  // '-'  
  { '>', '>', '>', '>', '<', '>', '>'},  // '*'  
  { '>', '>', '>', '>', '<', '>', '>'},  // '/'  
  { '<', '<', '<', '<', '<', '=', 'N'},  // '('  
  { '>', '>', '>', '>', 'N', '>', '>'},  // ')'  
  { '<', '<', '<', '<', '<', 'N', '='},  // '#'
};

// 根据运算符号查找它在优先级表中的位置
int get_operator_index(char op) {
  switch (op) {
    case '+': return PLUS;
    case '-': return MINUS;
    case '*': return STAR;
    case '/': return SLASH;
    case '(': return LPAREN;
    case ')': return RPAREN;
    case '#': return HASH;
    default: return -1;  // 无效运算符
  }
}

// 比较两个运算符号的优先级关系
int compare_precedence(char op1, char op2) {
  int op1_index = get_operator_index(op1);
  int op2_index = get_operator_index(op2);

  if (op1_index == -1 || op2_index == -1) {
    printf("运算符不正确\n");
    return -2;  // -2 表示无效运算符
  }

  if (precedence[op1_index][op2_index] == '>')       return 1;  // op1 级别高
  else if (precedence[op1_index][op2_index] == '<')  return -1; // op1 级别低
  else                                               return 0;  // op1 和 op2 级别相等
  
}

int main() {

  char op1, op2;
  
  // 提示用户输入
  printf("输入第一个运算符: ");
  scanf("%c", &op1);  
  printf("输入第二个运算符: ");
  scanf(" %c", &op2);

  // 比较结果
  int result = compare_precedence(op1, op2);
  
  if (result == 1) {
    printf("运算符 '%c' 优先级高于 '%c'.\n", op1, op2);
  } else if (result == -1) {
    printf("运算符 '%c' 优先级低于 '%c'.\n", op1, op2);
  } else if (result == 0) {
    printf("运算符 '%c' 和 '%c' 级别相等\n", op1, op2);
  } else {
    printf("无效比较\n");
  }

  return 0;
}
