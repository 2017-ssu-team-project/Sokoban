int manual()  {  
  int i = 0;   char manual[150] = {0,};//파일을 읽을 때 사용할 임시 공간  
               FILE *mu = fopen("manual.txt", "r"); 
               while (fgets(manual, sizeof(manual), mu) != NULL)  
               {     printf("%s", manual);   }  
               fclose(mu);   return 0;  }
