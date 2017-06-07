#include <stdio.h>


//저장해야 할 것들=============================
char name[]="kmh"; //플레이어 이름
int stage = 2;//현재 스테이지
int gx = 17, gy = 8;//플레이어의 위치

//이동 기록
char move_list [5] = {'h','k','k','l','h'};
int push_list [5] = {0,0,1,0,1};

//저장소 정보
int box_x [20] = {1,2,1,2,1,2,1,2,1,2};
int box_y [20] = {1,1,2,2,3,3,4,4,5,5};

int u = 4;//남은 undo 횟수 
double time = 45.3432;//save시점까지 남은 시간

//현재 맵 상황
char map [13] [22] =
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

};
//=============================

void save_file(void);

//=============================
int main(void)
{
printf("프로그램 저장 중...\n");

        void save_file();

        printf("파일을 열어서 확인 해보자.");

        return 0;
}

void save_file()
{
        /*
         *여기에 save를 하는 문장들을 적으면됨
         */
	
	FILE * ofp = fopen("sokovan.txt","r");
	if(ofp==NULL) {
		puts("파일오픔 실패");
		//return -1;
	}
	
	fprintf(ofp, "u=%d\n",u);
	fprintf(ofp, "stage=%d\n",stage);
	fprintf(ofp, "gx=%d\n",gx);
	fprintf(ofp, "gy=%d\n",gy);
	fprintf(ofp, "time=%f\n",time);


    /*	fprintf(ofp, "name=")                          
                for (int i =0; i<3; i++)
                        {
                                fprintf(ofp, "%c", name [i]);
                        }
                fprintf(ofp, "\n");      */
	
	fprintf(ofp, "move=");
		for (int i =0; i<5; i++)
			{		
				fprintf(ofp, "%c", move_list [i]);
			}	
		fprintf(ofp, "\n");

	fprintf(ofp, "push=");
                for (int i =0; i<5; i++)
                        {
                                fprintf(ofp, "%c", push_list [i]);
                        }
                fprintf(ofp, "\n");

	fprintf(ofp, "box_x=");
                for (int i =0; i<20; i++)
                        {
                                fprintf(ofp, "%d", box_x [i]);
                        }
                fprintf(ofp, "\n");

	fprintf(ofp, "box_y=");
                for (int i =0; i<20; i++)
                        {
                                fprintf(ofp, "%d", box_y [i]);
                        }
                fprintf(ofp, "\n");


	fprintf(ofp, "map=");
		for (int j = 0; j < 13; j++)
		{ 
			for (int i = 0; i < 22; i++)
			{
				fprintf(ofp, "%c", map [j] [i]);
			}	
		fprintf(ofp,"\n");
		}




		fclose(ofp);
		//return 0;

}

