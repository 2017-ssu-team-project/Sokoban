/*소스코드*/
#include <stdio.h>


//=============================
char name[]={0}; //플레이어 이름
int stage;//현재 스테이지
int gx, gy;//플레이어의 위치

//이동 기록
char move_list [5] = {0};
int push_list [5] = {0};

//저장소 정보
int box_x [20] = {0};
int box_y [20] = {0};

int u;//남은 undo 횟수
double time;//save시점까지 남은 시간

//현재 맵 상황
char map [13] [22] = {0};
//=============================

void load_file(void);

//=============================
int main(void)
{
        int i,j;

        printf("파일을 로드 합니다...\n");

        load_file();

        //이 아래는 데이터가 제대로 load가 됐는지 확인하기 위해 출력 하는 것

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
                printf("%d", push_list [i]);
        }
        printf("\n");

        printf("box_x = ");
        for (i = 0; i<20; i++)
        {
                printf("%d", box_x[i]);
        }
        printf("\n");

        printf("box_y = ");
        for (i = 0; i<20; i++)
        {
                printf("%d", box_y [i]);
        }
        printf("\n");

        printf("u = %d\n",u);
        printf("time = %f\n", time);

        printf("map =\n");
        for (j = 0; j<13; j++)
        {
                for (i = 0; i<22; i++)
                {
                        printf("%c", map [j] [i]);
                }
                printf("\n");
        }
        return 0;
}

void load_file()
{
        /*
         *여기에 load를 하는 문장들을 적으면됨
         */

	FILE *ofp = fopen("save","r");


	fscanf(ofp, "u=%d\n",&u);
        fscanf(ofp, "stage=%d\n",&stage);
        fscanf(ofp, "gx=%d\n",&gx);
        fscanf(ofp, "gy=%d\n",&gy);
        fscanf(ofp, "time=%f\n",&time);
        fscanf(ofp, "name=%s\n", name);

        fscanf(ofp, "move=");
                for (int i =0; i<5; i++)
                        {
                                fscanf(ofp, "%c", &move_list [i]);
                        }
                fscanf(ofp, "\n");

        fscanf(ofp, "push=");
                for (int i =0; i<5; i++)
                        {
                                fscanf(ofp, "%d", &push_list [i]);
                        }
                fscanf(ofp, "\n");

        fscanf(ofp, "box_x=");
                for (int i =0; i<20; i++)
                        {
                                fscanf(ofp, "%d, ", &box_x [i]);
                        }
                fscanf(ofp, "\n");

        fscanf(ofp, "box_y=");
                for (int i =0; i<20; i++)
                        {
                                fscanf(ofp, "%d, ", &box_y [i]);
                        }
                fscanf(ofp, "\n");

	
	fscanf(ofp, "map=");
                for (int j = 0; j < 13; j++)
                {
                        for (int i = 0; i < 22; i++)
                        {
                                fscanf(ofp, "%c", &map [j] [i]);
                        }
                fscanf(ofp,"\n");
                }




                fclose(ofp);
                return;





}

