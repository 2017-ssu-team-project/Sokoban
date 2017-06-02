#include <stdio.h>
#include <stdlib.h>
int readmap();
int main(void)
{
 readmap();
 return 0;
}
void readmap()
{
  int s = 0, i = 0, j = 0;
  char a = 0;
  char arr[5][30][30] = {0,}, line[s] = {0,};//파일을 읽을 때 사용할 임시 공간
  FILE *mp = fopen("map.txt", "r");
  while (fscanf(mp, "%c", &a)!= EOF) {
    fscanf(mp,"%c",&a);
    arr[s][i][j] = a;
    if (a == ' ' || a == '#' || a == '@' || a == '$')
      j++;
    else if (a == '\n')
      i++;
      j = 0;
    else if (a == 'm' || a == 'e')
      line[s] = i;
      s++;
      i = 0; ,j = 0;
   }
   fclose(mu);
   return 0;
  }
