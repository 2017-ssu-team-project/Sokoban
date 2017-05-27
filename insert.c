#include <stdio.h>
int main (void)
{
	//배열을 초기화 한다
	int number[10] = {92, 30, 42, 27, 35, 65, 77, 85, 48, 50};
	int i,j,insert,pos;
	
	//정렬전 출력
	printf("정렬전 : \n");
	
	for (i=0; i <10; i++)
	{
		printf("%d ", number[i]);
	}
	
	//삽입 정렬
	for (i=0; i<11; i++)
	{
		//삽입 할 값 지정
		insert = number[i];
		
		pos = i-1;

		//삽입하기에 적절한 위치를 찾아 가는 과정
		while (pos>=0 && number[pos] > insert)
		{
			number[pos+1] = number [pos];
			pos--;
			//삽입 값보다 큰 값들은 한 칸 씩 밀려난다.
		}
		
		number[pos+1] = insert;//적절한 위치에 삽입 값 배정
	}

	//정렬 후의 결과를 출력
	printf("\n정렬 후 : \n");
	for (i=0; i<10; i++)
		printf("%d ", number[i]);
	printf("\n");


return 0;
}
