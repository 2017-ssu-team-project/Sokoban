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

//undo 기능을 위한 배열
char move_list [5];
int push_list [5]; 

//저장소 "O"들의 위치
int box_x [20];
int box_y [20];

_Bool status=0; // 게임 실행여부를 나타냄(1은 게임상태, 0은 게임상태 아님)

//======================

void Drawmap(); //맵 상태를 화면에 출력
int getch(); //글자 입력 함수
void move(char); // 위치이동을 위한 함수
void add_history(char);// 이동 기록중 방향을 기록
void add_push(int); //이동 기록중 화물 밀었는가를 기록
void undo(); //undo 되감기를 위한 함수

//======================

//예비 맵 (나중에 삭제)..............
const char mapdata [maxstage] [13] [22] =
{
	{
		"    #####             ",
		"    #   #             ",
		"    #   #             ",
		"  ###   ###           ",
		"  #       #           ",
		"### # ### #     ######",
		"#   # ### #######    #",
		"#             @$   O #",
		"##### #### # ####    #",
		"    #      ###  ######",
		"    ########          "
	},

	{
		"############          ",
		"#    #     ###        ",
		"#    #       #        ",
		"#    # ####  #        ",
		"# O  $ @ ##  #        ",
		"#    # #    ##        ",
		"###### ##    #        ",
		"  #          #        ",
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


//3. Enter stage
//타이머시작
//이동 기록, undo 횟수 초기화

replay: //goto를 이용한 replay 지점
	
	for (int i = 0; i<5; i++)//이동기록
	{
		move_list [i] = 0;
		push_list [i] = 0;
	}
	int u = 5; //undo 가능횟수를 5로 초기화

//4. Print map=======
	
	{
		int i, j;
		int box = 0;

		for (i =0; i<20; i++ ) //박스 정보 초기화
		{
			box_x [i] = 0;
			box_y [i] = 0; 
		}

		for (j = 0; j<13; j++)//게임을 위한 맵 입력
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

//5. Game play=======
	
	status = 1;

	int input_char;

	while (status == 1)
	{
		
		input_char = getch();
			
		switch (input_char)//커맨드 입력 부분
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
		}
	}
//6. Game clear!==============
//시간 종료, 랭킹 등록, 다음 스테이지로 이동
	printf("congratulation %s!!\n", name);

	if (stage == maxstage - 1)//최종스테이지면 게임 종료, 아니면 다음 스테이지로
	{
		system("clear");
		printf("You win!!");
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
		goto replay;
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
	for (stagey=0; stagey<13; stagey++)
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
			dx = 0, dy = -1;
			break;
		case 'k' :
			dx = 0, dy = 1;
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
		add_history(ch);//이동 방향  기록

	//클리어 여부를 확인..............................
	//현재 모든 저장소의 위치에 $있다면 status를 0으로 한다.
		for (int i = 0; i<6; i++)
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
				dx = 0, dy = -1;
				break;
			case 'k' :
				dx = 0, dy = 1;
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
		
		for (i=0; i<4; i++)//이동기록을 하나 삭제
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

