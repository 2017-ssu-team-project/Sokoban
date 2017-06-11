#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <termio.h>
#include <string.h>

//=======================

#define maxstage 5 //최고 스테이지, 최종본에서는 5로변경

//=======================

char mapdata [maxstage] [15] [22];//파일로부터 맵데이터를 저장하는 3차원 배열 

char name[10];//플레이어 이름
char map [15] [22];//맵 출력을 위한 배열
int stage; //현재 스테이지를 표현하기 위한 변수
int gx, gy; //게임 상 player의 좌표를 위한 변수
int u;//undo 가능 횟수

//undo 기능을 위한 배열
char move_list [5];
int push_list [5]; 

//저장소 "O"들의 위치
int box_x [20];
int box_y [20];

_Bool status=0; // 게임 실행여부를 나타냄(1은 게임상태, 0은 게임상태 아님)

//시간 측정을 위한 변수들
time_t start_c, end_c;
double timer, save_timer;

//ranking 기능을위한 배열
double rank_time [5] [5];

char rank_name [5] [5] [10];

//======================

void Drawmap(); //맵 상태를 화면에 출력
int getch(); //글자 입력 함수

void move(char); // 위치이동을 위한 함수
void add_history(char);// 이동 기록중 방향을 기록
void add_push(int); //이동 기록중 화물 밀었는가를 기록

void undo(); //undo 되감기를 위한 함수
void display_manual();//command들을 보여주는 함수

void
 rank_input(); //랭킹 등록을 위한 함수
void rank_read(); //랭킹 파일을 읽는 함수
void rank_print();//탱킹 출력하는 함수

void save_file();//상태 저장하는 함수
void load_file();//상태 불러오는 함수
//======================


//........................................
	
int main(void)
{

//0. Analyze map=======
//맵 파일을 읽으면서 오류여부(박스== 저장소) 확인
	
	int i = 0, j = 0, s = 0;
	int boxes=0, storages=0;
	char c = 0;

	//맵 데이터를 ' '로  초기화
	for (s=0; s<maxstage; s++)
	{
		for (j=0; j<13; j++)
		{
			for (i=0; i<22; i++)
			{
				mapdata[s][j][i] = ' ';
			}
		}
	}

	i = j = s = 0;

	FILE *mp = fopen("maps", "r");

	while (fscanf(mp, "%c", &c) != EOF)
	{
		if (c == ' ' || c == '#' || c == '@' || c == '$' || c == 'O')
		{
			mapdata[s][j][i] = c;
			i++;
			
			if (c == '$')
			{
				boxes++;
			}
			else if (c == 'O')

			{
				storages++;
			}
		}
		else if (c == '\n')
		{
			j++;
			i = 0;
		}
		else if (c == 'm')
		{
			s++;

			i = 0, j = -1;

			if (boxes != storages)
			{
				printf("오류 : 스테이지 %d에서의 박스와 저장소의 수가 일치하지 않습니다.", s);
				return 0;
			}
			else
			{
				boxes = 0;
				storages = 0;
			}
		}
	}

	fclose(mp);

//1. Opening===========
//스타트 화면 + 이름 입력 및 저장
	
	system("clear");
	printf("Start....\n");
	printf("input name : ");
	scanf("%s", name);
	
	system("clear");

new_game:

	stage = 0;


//2. Enter stage
//타이머시작
//이동 기록, undo 횟수 초기화

next_stage://클리어 하고나서 stage++을 한 후  다음 단계로 가는 지점

	start_c = time (NULL);
	save_timer = 0;

replay: //goto를 이용한 replay 지점
	
	for (int i = 0; i<5; i++)//이동기록
	{
		move_list [i] = 0;
		push_list [i] = 0;
	}
	u = 5; //undo 가능횟수를 5로 초기화

//3. Print map=======
	
	{
		int i, j;
		int box = 0;

		for (i =0; i<20; i++ ) //박스 정보 초기화
		{
			box_x [i] = 0;
			box_y [i] = 0; 
		}

		for (j = 0; j<15; j++)//게임을 위한 맵 입력
		{
			for (i = 0; i<22; i++)
			{
				map [j] [i] = mapdata [stage] [j] [i];//map data를 현재 map에 배치
				if (map [j] [i] == '@')//플래이어 위치 저장
				{
					gx = i;

					gy = j;
				}
				if (map [j] [i] == 'O')//저장소들의 위치 저장
				{
					box_x [box] = i;
					box_y [box] = j;

					box++;
				}
			}
		}

	}

	Drawmap();

	static char input_char;
		
	if (input_char == 'r')
	{
		printf("r");

	}
	else if (input_char == 'n')
	{
		printf("n");
	}

//4. Game play=======
	
	status = 1;


	while (status == 1)
	{
		
		input_char = getch();
			
		switch (input_char)//커맨드 입력 부분
		{
			//cheat code
			case 'c':
				if (stage != maxstage-1)
				{
					stage++;
					goto next_stage;
				}
				break;
			//status
			case 'a':
				system("clear");
				
        printf("name = %s\n", name);
        printf("stage = %d\n", stage);
        printf("gx = %d, gy = %d\n", gx, gy);

        printf("move_list = ");
        for (i = 0; i<5; i++)
        {
                printf("%c ", move_list [i]);
        }
        printf("\n");

        printf("push_list = ");
        for (i = 0; i<5; i++)
        {
                printf("%d ", push_list [i]);
        }
        printf("\n");


        printf("box_x = ");
        for (i = 0; i<20; i++)
        {
                printf("%d ", box_x[i]);
        }

        printf("\n");

        printf("box_y = ");
        for (i = 0; i<20; i++)
        {
                printf("%d ", box_y [i]);
        }
        printf("\n");

        printf("u = %d\n",u);
        printf("save time = %.f\n", save_timer);

        printf("map =\n");
        for (j = 0; j<13; j++)
        {
                for (i = 0; i<22; i++)
                {
                        printf("%c", map [j] [i]);
                }

                printf("\n");
        }
		input_char = ' ';
		while (input_char != 'a')
		{
			input_char = getch();
		}
		Drawmap();
		break;


			//moving
			case 'h':
				move(input_char);
				break;
			case 'j':
				move(input_char);
				break;
			case 'k':
				move(input_char);
				break;
			case 'l':
				move(input_char);
				break;
			//undo
			case 'u':
				if (u > 0)
				{
					undo();
					u--;
					break;
				}
				else
				{

					Drawmap();
					printf("undo 가능 횟수를 초과 했습니다.");
					break;
				}

			//replay
			case 'r':
				goto replay;
			//new
			case 'n':
				goto new_game;
			//display
			case 'd':
				system("clear");
				printf("   Hello %s\n", name);
				display_manual();
				input_char = ' ';

				while (input_char != 'd')
				{
					input_char = getch();
				}
				
				Drawmap();
				break;
			//top rankings
			case 't':
				rank_print();
				break;
			//save file
			case 's':
				save_file();
				break;
			//file load
			case 'f':
				load_file();
				start_c = time (NULL);
				end_c = time (NULL);
				break;
			//exit
			case 'e':
				save_file();
				system("clear");
				system("clear");
				printf("\nSEE YOU %s....\n\n(Command) e\n", name);
				return 0;				
		}
	}
//5. Game clear!==============
//시간 종료, 랭킹 등록, 다음 스테이지로 이동

	end_c = time (NULL);
   	timer = save_timer + difftime(end_c, start_c);

	printf("  %.fsec\ncongratulation %s!!\n", timer, name);

	rank_input();

	if (stage == maxstage - 1)//최종스테이지면 게임 종료, 아니면 다음 스테이지로
	{
		system("clear");
		printf("\n\n   CONGRATULATION %s!!!", name);
		printf("\n\n   모든 맵을 완수했습니다!!\n\n");
		return 0;
	}
	else
	{
		printf("계속 하려면 y입력...\n ");//y를 입력 하여 넘어가는 형식으로 플레이어에게 여유를 준다.
		input_char = ' ';
		
		while (input_char != 'y')
		{
			input_char = getch();
		}
		stage++;
		goto next_stage;
	}
	//....................
	



}


//=============================



int getch(void)
{

    int ch;

    struct termios buf;
    struct termios save;



    tcgetattr(0, &save);
    buf = save;

    buf.c_lflag&=~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;



    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();

    tcsetattr(0, TCSAFLUSH, &save);


    return ch;

 }


void Drawmap() //이차원 배열 map을 출력
{
	int stagex, stagey;

	system("clear");//이전의 맵상태를 지우고, 새로운 맵상태 출력
	printf("   Hello %s\n", name);
	for (stagey=0; stagey<15; stagey++)
	{
		for (stagex=0; stagex<22; stagex++)
		{
			putchar(map [stagey] [stagex]);
		}
		printf("\n");
	}
	printf("(Command) ");

/*Drawmap()함수의 실행결과 예시 :

  Hello kim
    #####
    #   #
    #$  #
  ###  $###
  #  $  $ #
### # ### #     ######
#   # ### #######  OO#
# $  $             OO#
##### #### #@####  OO#
    #      ###  ######
    ########



(Command)

*/
}


void move(char ch)
{
	int dx, dy;//x변화량과 y변화량

	switch (ch)

	{
		case 'h' :
			dx = -1, dy = 0;
			break;
		case 'j' :
			dx = 0, dy = 1;
			break;

		case 'k' :
			dx = 0, dy = -1;
			break;
		case 'l' :
			dx = 1, dy = 0;
			break;
	}

	if (map [gy+dy] [gx+dx] == '#')//진행방향에 벽이 있다면...

		return;//벽이 있으면 움직임 취소

	else
	{
		if (map [gy+dy] [gx+dx] == '$')//진행방향에 화물이 있다면...
		{
			if (map [gy+2*dy] [gx+2*dx] == '#' || map [gy+2*dy] [gx+2*dx] == '$')//화물 옆에 벽이나 또다른 화물이 있다면 움직임 취소
				return;

	 		else
			{	//화물을 이동하고 push에 1 기록
				map [gy+2*dy] [gx+2*dx] = '$';
				add_push(1);
			}
		}
		else//진행방향에벽x, 화물x. (= 아무것도 없음)
		{	//화물을 이동 하지 않았으므로 push에 0기록
			add_push(0);
		}
				
		
		map [gy+dy] [gx+dx] = '@';//위치 이동
		
		map [gy] [gx] = ' ';// 원래 @의 위치를 빈공간으로 하지만...
		for (int i = 0; i<20; i++)
		{
			if (gx == box_x [i] && gy == box_y [i])//그위치가 원래 저장소의 위치라면 저장소를 보이게 함
				map [gy] [gx] = 'O';
		}
		
		gx += dx, gy+= dy;//좌표도 변경
		Drawmap();
		add_history(ch);//이동 방"   Hello %s\n", name)향  기록

	//클리어 여부를 확인..............................
	//현재 모든 저장소의 위치에 $있다면 status를 0으로 한다.
		for (int i = 0; i<20; i++)
		{	

			char point = map [box_y [i]] [box_x [i]];
			if ((point == '$') || (point == ' ') || (point == '#')) //' '가 있는 이유는 배정되지않은 좌표들은 모두 0,0이기 때문
			{}
			else
				return;
		}

		status = 0;
	//........................................
  	}
	
			
}

void add_history(char ch)
{
	int i,tmp = 0;

	for (i=4; i>0; i--)
	{
		move_list[i] = move_list[i-1];
	}

	move_list [0] = ch;
		
}

void add_push(int n)
{	
	int i, tmp = 0;

	for (i=4; i>0; i--)
	{
		push_list [i] = push_list [i-1];
	}
	
	push_list [0] = n;	
}

void undo()
{
	int dx, dy;
	int tmp, i;

	if (move_list [0] == 0)
		return;//이동 기록이 없으면 undo 안함
	else
	{
		switch (move_list [0])//이동 기록에서 가장 최근 문자를 파악
		{
			case 'h' :
				dx = -1, dy = 0;
				break;
			case 'j' :
				dx = 0, dy = 1;
				break;

			case 'k' :
				dx = 0, dy = -1;
				break;
			case 'l' :
				dx = 1, dy = 0;
				break;
		}
		if (push_list [0] == 1)//최근에 화물을 밀었다면...
		{
			map [gy+dy] [gx+dx] = ' ';//화물도 옮긴다
			
			for (int i = 0; i<20; i++)
			{
				if (gx+dx == box_x [i] && gy+dy == box_y [i])//화물의 위치가 원래 저장소의 위치라면 저장소를 보이게함
					map [gy+dy] [gx+dx] = 'O';
			}
			
			map [gy] [gx] = '$';
		}
		else//최근에 화물을 옮기지 않았다면...
		{		
			map [gy] [gx] = ' ';

			for (int i = 0; i<20; i++)
			{
				if (gx == box_x [i] && gy == box_y [i])//그 위치가 원래 저장소의 위치라면 저장소를 보이게함
					map [gy] [gx] = 'O';
			}
		}
		
		map [gy-dy] [gx-dx] = '@';
		gx -= dx, gy -= dy;
		
		for (i=0; i<4; i++)//이동기록을 하나씩  삭제
		{
			move_list [i] = move_list [i+1];
			push_list [i] = push_list [i+1];
		}
		move_list [4] = 0;
		push_list [4] = 0;

	}
	Drawmap();//맵 출력
	printf("u");
}

void display_manual ()
{
        printf("\nh(왼쪽), j(아래), k(위), l(오른쪽)\n");
        printf("u(undo)\nr(replay)\nn(new)\ne(exit)\n");
        printf("s(save)\nf(file load)\nd(display help)\nt(top))\n");
	printf("\n(Command) d\n계속하려면 'd'입력");
}

void rank_read(void)
{
	int i = 0, j = 0;
	double tmp_time;
	char tmp_name [0];
	FILE *rk = fopen("ranking", "r");

	while(!feof(rk))
	{
		fscanf(rk, "%d / %d / %lf / %s\n", &i, &j, &tmp_time, &tmp_name);

		rank_time [i] [j] = tmp_time;
		strcpy(rank_name [i][j], tmp_name);
	}
	fclose(rk);

	return;

}

void rank_input(void)
{
	int i=0, j=0;
	rank_read();

	for (i = 0; i<5 ; i++)
	{
		if (timer <= rank_time [stage][i])
			break;
	}

	if (timer > rank_time [stage][4])
	{}
	else
	{
		for (j = 3; j >= i; j--)
		{
			rank_time [stage] [j+1] = rank_time [stage] [j];
			strcpy(rank_name[stage] [j+1], rank_name [stage][i]);
		}

		rank_time [stage] [i] = timer;
		strcpy(rank_name [stage] [i], name);

	}

	FILE *rt = fopen("ranking", "w");

	for (i = 0; i<5; i++)
	{

		for (j=0; j<5; j++)
		{
			fprintf(rt, "%d / %d / %f / %s\n", i, j, rank_time[i][j], rank_name[i][j]);
		}
	}

	fclose(rt);
}

void rank_print(void)
{

	rank_read();
	system("clear");
				
	printf("   Hello %s\n", name);


	for (int i=0; i<5; i++)
	{
		printf("map %d\n", i+1);
		for (int j=0; j<5; j++)
		{
			printf("%d. %s   %.f sec\n", j+1, rank_name[i][j], rank_time[i][j]);
		}
		printf("\n");
	}
	printf("(Command) t\n");
				
	char input_char = ' ';

	while ((input_char != 't') && !((input_char >= '1')&&(input_char <='5')))
	{
		input_char = getch();
	}
	if (input_char == 't')
	{
		Drawmap();
		return;
	}
	else if ((input_char >='1') && (input_char <= '5') )
	{
		system("clear");
		printf("   Hello %s\n", name);
		int num;
		num = input_char - '0';

		printf("map %d\n", num);
		for (int i=0; i<5; i++)
		{
			printf("%d. %s   %.f sec\n", i+1, rank_name [num-1][i], rank_time[num-1][i]);
		}
		printf("\n");
		printf("(Command) t %d", num);
		printf("\n계속 하려면 't'입력");
		while (input_char != 't')
		{
			input_char = getch();
		}
		Drawmap();
		return;	
	}
}


void save_file()
{
	end_c = time(NULL);
	save_timer = save_timer + difftime(end_c,start_c);
	FILE *sav = fopen("sokoban", "w");
	
	fprintf(sav, "name=%s\n", name);
	fprintf(sav, "u=%d\n", u);
	fprintf(sav, "stage=%d\n", stage);
	fprintf(sav, "gx=%d\n", gx);
	fprintf(sav, "gy=%d\n", gy);
	fprintf(sav, "time=%lf\n", save_timer);

	fprintf(sav, "move=");
	for (int i=0; i<5; i++)
	{
		fprintf(sav, "%c, ", move_list[i]);
	}
	fprintf(sav, "\n");

	fprintf(sav, "push=");
	for (int i=0; i<5; i++)
	{
		fprintf(sav, "%d, ", push_list[i]);
	}
	fprintf(sav, "\n");

	fprintf(sav, "box_x=");
	for (int i=0; i<20; i++)
	{
		fprintf(sav, "%d, ", box_x[i]);
	}
	fprintf(sav, "\n");

	fprintf(sav, "box_y=");
	for (int i=0; i<20; i++)
	{
		fprintf(sav, "%d, ", box_y[i]);
	}
	fprintf(sav, "\n");

	fprintf(sav, "map=\n");
	for (int j=0; j<13; j++)
	{
		for (int i=0; i<22; i++)
		{
			fprintf(sav, "%c", map[j][i]);
		}
		fprintf(sav, "\n");
	}

	fclose(sav);

	Drawmap();
	printf("s\n");
	return;
}

void load_file()
{
	char c;
	int i,j;
	//..........
	int tmp_y;
	double tmp_time;
	//..........

	FILE *sav = fopen("sokoban", "r");
	
	if (sav==NULL)
	{
	
	Drawmap();
		printf("\n저장된 내용이 없습니다.");
		return;
	}

	fscanf(sav, "name=%s\n", &name);
	fscanf(sav, "u=%d\n", &u);
	fscanf(sav, "stage=%d\n", &stage);
	fscanf(sav, "gx=%d\n", &gx);
	fscanf(sav, "gy=%d\n", &gy);
	fscanf(sav, "time=%lf\n", &save_timer);
	//.........
	tmp_y = gy;
	tmp_time = save_timer;
	//.........

	fscanf(sav, "move=");
	for (i = 0; i<5; i++)
	{
		fscanf(sav, "%c, ", &move_list[i]);
	}
	fscanf(sav, "\n");
	fscanf(sav, "push=");
	for (i = 0; i<5; i++)
	{
		fscanf(sav, "%d, ", &push_list[i]);
	}
	fscanf(sav, "\n");

	fscanf(sav, "box_x");
	for (i=0; i<20; i++)
	{
		fscanf(sav, "%d, ", &box_x[i]);
	}
	fscanf(sav, "\n");

	fscanf(sav, "box_y");
	for (i=0; i<20; i++)
	{
		fscanf(sav, "%d, ", &box_y[i]);
	}
	fscanf(sav, "\n");
	//현재 맵 초기화
	for (j=0; j<13; j++)
	{
		for (i=0; i<22; i++)
		{
			map[i][j] = 0;
		}
	}

	fscanf(sav, "map=\n");

	i=0, j=-3;
	while (fscanf(sav, "%c", &c) != EOF)
	{
		if (c==' ' || c=='#' || c=='@' || c=='O' || c=='$')
		{
			map[j][i] = c;
			i++;
		}
		else if(c=='\n')
		{
			j++;
			i=0;
		}
	}
	fclose(sav);
	//.............
	//저장소 정보를 mapdata를 통해 다시 읽어들어옴
	int box = 0;
	for (i =0; i<20; i++ ) //저장소 정보 초기화
	{
		box_x [i] = 0;
		box_y [i] = 0; 
	}

	for (j = 0; j<15; j++)
	{
		for (i = 0; i<22; i++)
		{
			if (mapdata [stage][j] [i] == 'O')//저장소들의 위치 저장
			{
				box_x [box] = i;
				box_y [box] = j;
				box++;
			}
		}
	}
	//......
	gy = tmp_y;
	save_timer = tmp_time;
	//.......
	
	Drawmap();
	printf("f");
	return;
}
