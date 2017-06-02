void mapprint()
{
  int s = 0;
  for (int i = 0; i < line[s]; i++)
  {
      for (int j = 0; j < 30; j++)
      {
        printf("%c",arr[s][i][j]);
      }
      printf("\n");
  }
}
