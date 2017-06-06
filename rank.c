void rankread()
{
  float time1;
  char name[20]; // 처음 이름을 입력한 name
  time1 = a; // 기록된 시간을 time1에 넣음
  FILE *rk = fopen("ranking.txt","w");
  fprintf(rk, "1. %s   %d\n", name, time1);
  fclose(rk);
}
void rankprint()
{
  int i, j, p = 0;
  char rankname [5][5][], n[20];
  int ranktime[5][5];
  FILE *rk = fopen("ranking.txt","r");
  fscanf(rk, "%s %s  %d", &n, &rankname[i][j], &ranktime[i][j]);//n은 1. 버리기

      for (p = 0; p < i; p++)
        if (number[i] > nember[i+1])
        {
          tmp = number[i];
          number[i] = number[i+1];
          number[i+1] = tmp;
        }// 이배열을 어떻게 적용할지..
          for (int i = 0; i <= 5; i++)
            {
              printf("map %d\n", i+1);
              for (int j =1; j < 5; j++)
              {
                printf("%s    %d\n",rankname[i][j], ranktime[i][j]);
              }
              printf("\n");
            }

}
