//시험용... 완성본 아님...

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <termio.h>

//=======================

#define maxstage 2 //최고 스테이지, 최종본에서는 5로변경

//=======================

char name[0];//플레이어 이름
char map [13] [22];//맵 출력을 위한 배열
int stage; //현재 스테이지를 표현하기 위한 변수
int gx, gy; //게임 상 player의 좌표를 위한 변수
char move_list [5]={0}; // undo기능을 위한 배열
_Bool status=0; // 게임 실행여부를 나타냄(1은 게임상태, 0은 게임상태 아님)

//======================

void Drawmap();
int getch();
void move(char);
void add_history(char);
void undo();

//======================

//예비 맵 (나중에 삭제)..............
const char mapdata [maxstage] [13] [22] =
{
	{
		"    #####             ",
		"    #   #             ",
		"    #$  #             ",
		"  ###  $###           ",
		"  #  $  $ #           ",
		"### # ### #     ######",
		"#   # ### #######  OO#",
		"# $  $             OO#",
		"##### #### #@####  OO#",
		"    #      ###  ######",
		"    ########          "
	},
	{
		"############          ",
		"#OO  #     ###        ",
		"#OO  # $  $  #        ",
		"#OO  #$####  #        ",
		"#OO    @ ##  #        ",
		"#OO  # #  $ ##        ",
		"###### ##$ $ #        ",
		"  # $  $ $ $ #        ",
		"  #    #     #        ",
		"  ############        ",
		"                      "
	}
};
//........................................
	
int main(void)
{

//1. Opening===========
//스타트 화면 + 이름 입력 및 저장

	printf("Start....\n");
	printf("input name : ");
	scanf("%s", name);
	
	system("clear");
	
	stage = 0;

//2. Map read=========
//파일로 부터 맵 읽어오기


//3. Enter stage========
//타이머시작

replay: //goto를 이용한 replay 지점

//4. Print map=======

	
	{
		int i, j;

		for (j = 0; j<13; j++)
		{
			for (i = 0; i<22; i++)
			{
				map [j] [i] = mapdata [stage] [j] [i];
				if (map [j] [i] == '@')
				{
					gx = i;
					gy = j;
				}
			}
		}

	}
		Drawmap();

//5. Game play=======
	
	status = 1;

	int u = 5;//undo 가능횟수
	int input_char;

	while (status = 1)
	{
		while (1)
		{
			input_char = getch();
			
			switch (input_char)
			{
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
					undo();
					break;
				//replay
				case 'r':
					goto replay;
			}
		}
	}


}

//=============================

//...................
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
//.....................


void Drawmap()
{
	int stagex, stagey;

	system("clear");
	printf("   Hello %s\n", name);
	for (stagey=0; stagey<13; stagey++)
	{
		for (stagex=0; stagex<22; stagex++)
		{
			putchar(map [stagey] [stagex]);
		}
		printf("\n");
	}
	printf("(Command) ");
}

void move(char ch)
{
	int dx, dy;

	switch (ch)
	{
		case 'h' :
			dx = -1, dy = 0;
			break;
		case 'j' :
			dx = 1, dy = 0;
			break;
		case 'k' :
			dx = 0, dy = -1;
			break;
		case 'l' :
			dx = 0, dy = 1;
			break;
	}

	if (map [gy+dy] [gx+dx] == '#')
		return;
	else
	{
		if (map [gy+dy] [gx+dx] == '$')
		{
			if (map [gy+2*dy] [gx+2*dx] == '#' || map [gy+2*dy] [gx+2*dx] == '$')
				return;
			else
			{
				map [gy+2*dy] [gx+2*dx] = '$';
			}
		}
				
		
		
		map [gy+dy] [gx+dx] = '@';
		map [gy] [gx] = ' ';
		gx += dx, gy+= dy;
		Drawmap();
		add_history(ch);
		
  	}
				
}

void add_history(char ch)
{
}


void undo()
{
	Drawmap();
	printf("u");
}

