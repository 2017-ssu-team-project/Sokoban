#include <stdio.h>
#include <stdlib.h>
int manual();
int main(void)
{
 manual();
 return 0;
}
int manual()
  {
    int i = 0;
   char arr[150] = {0,};//파일을 읽을 때 사용할 임시 공간
   FILE *mu = fopen("manual.txt", "r");
   for(i = 0; i <= 300; i++)
   {
     fscanf(mu,"%c",&arr[i]);
     printf("%c", arr[i]);
     if (arr[i] == '/')
          break;
   }
   fclose(mu);
   return 0;
  }
