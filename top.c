int top()
{
  char ranking[200] = {0,};//파일을 읽을 때 사용할 임시 공간
  FILE *rk = fopen("ranking.txt", "r");
  fread(ranking, sizeof(ranking), 1, rk );
  printf("%s\n", ranking);
  fclose(rk);
  return 0;
}
