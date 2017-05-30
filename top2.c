int top2(int t)
{
   char ranking[200] = {0,};//파일을 읽을 때 사용할 임시 공간
   FILE *rk;
  if (t == 1)
      {rk = fopen("ranking1.txt", "r");
      fread(ranking, sizeof(ranking), 1, rk );
      printf("%s\n", ranking);
      fclose(rk);}
  if (t == 2)
      {rk = fopen("ranking2.txt", "r");
      fread(ranking, sizeof(ranking), 1, rk );
      printf("%s\n", ranking);
      fclose(rk);}
  if (t == 3)
      {rk = fopen("ranking3.txt", "r");
      fread(ranking, sizeof(ranking), 1, rk );
      printf("%s\n", ranking);
      fclose(rk);}
  if (t == 4)
      {rk = fopen("ranking4.txt", "r");
      fread(ranking, sizeof(ranking), 1, rk );
      printf("%s\n", ranking);
      fclose(rk);}
  if (t == 5)
      {rk = fopen("ranking5.txt", "r");
      fread(ranking, sizeof(ranking), 1, rk );
      printf("%s\n", ranking);
      fclose(rk);}
  return 0;
  }
