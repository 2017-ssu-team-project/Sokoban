#include <stdio.h>
#define s 115
#define f 102

int main(void)
{
char ch;

ch = getc();

if(ch==f){
	FILE *sokoban;
	sokoban =fopen("sokoban","w");
}
if(ch==s){
	FILE *sokoban;
	fclose(sokoban);}

	return 0;
	}

