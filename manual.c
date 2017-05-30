int manual()
  {
   char manual[200] = {0,};//파일을 읽을 때 사용할 임시 공간
   FILE *mu = fopen("manual.txt", "r");
   fread(manual, sizeof(manual), 1, mu);
   printf("%s\n", manual);
   fclose(mu);
   return 0;
  }
