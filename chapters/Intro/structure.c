/*************************************************
 * Created by David on Thu Sep  4 16:31:42 2025  *
 *************************************************/


#include <stdio.h>
typedef struct {
  int id;
  char name[10];
  int score;
}STU ;

int main()
{
  STU s3={1,"zhang", 95}, s4={2, "wang", 98};
  STU *p = &s4;

  printf("%d\t%s\t%d\n", s3.id, s3.name, s3.score);
  printf("%d\t%s\t%d\n", (*p).id, (*p).name, (*p).score);
  printf("%d\t%s\t%d\n", p->id, p->name, p->score);


  return 0;
}
