#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>  //��ȡ������Ϣ

#include "box_man.h"

POS man;

using namespace std;

//ǽΪ0-�ذ�Ϊ1-����Ŀ��Ϊ2-��ɫΪ3-����Ϊ4-�����غ�Ϊ5
//ͼƬ��ʾ����
IMAGE image[ALL];

//��Ϸ��ͼ
int map[LINE][COLUMN] = {
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,1,1,1,1,1,1,0,0},
	{0,1,4,1,0,2,1,0,2,1,0,0},
	{0,1,0,1,0,1,0,0,1,1,1,0},
	{0,1,0,2,0,1,1,4,1,1,1,0},
	{0,1,1,1,0,3,1,1,1,4,1,0},
	{0,1,2,1,1,4,1,1,1,1,1,0},
	{0,1,0,0,1,0,1,1,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//�ж���Ϸ�Ƿ����
bool isGameOver(){
	for(int i = 0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j] == BOX_DES) return false;
		}
	}
	return true;
}

//��Ϸ����
void gameOverScene(IMAGE *bg){
	putimage(0,0,bg);
	settextcolor(WHITE);
	RECT rec = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	settextstyle(20,0,_T("����"));
	drawtext(_T("��Ϸ����"),&rec,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/**********************************
*�ı���Ϸ��ͼ��ͼ��һ���Ӧ���߲�������ʾ
*   lline - �����ڵ�ͼ��������±�
*	colum - �����ڵ�ͼ��������±�
*	prop - ���ߵ�����
***********************************/
void changeMap(POS *pos,PROPS prop){
	map[pos->x][pos->y] = prop;
	putimage(START_X+pos->y*SIZE,START_Y+pos->x*SIZE,&image[prop]);
}

// ���·���
//void updateScore(){
//	setfillcolor(BLACK);
//	solidrectangle(310,50,410,90);
//	char name[16];
//	sprintf(name,"%d",walk);
//	outtextxy(320,50,name);
//}

//��Ϸ�������,direct->��ǰ������
void gameControl(DIRECTION direct){
	POS next_pos = man;
	POS next_next_pos = man;
	switch(direct){
		case UP:
			next_pos.x--;
			next_next_pos.x-=2;
			//walk++;
			break;
		case DOWN:
			next_pos.x++;
			next_next_pos.x+=2;
			//walk++;
			break;
		case LEFT:
			next_pos.y--;
			next_next_pos.y-=2;
			//walk++;
			break;
		case RIGHT:
			next_pos.y++;
			next_next_pos.y+=2;
			//walk++;
			break;
	}

	//��ǰ���ǵذ�
	if(isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR){
		if(map[man.x][man.y] == BOX_DES){
			changeMap(&man,BOX_DES);
			changeMap(&next_pos,MAN);//С��ǰ��һ��
		}else{
			changeMap(&next_pos,MAN);
			changeMap(&man,FLOOR);
		}
		man = next_pos;
	}else if(isValid(next_pos) && map[next_pos.x][next_pos.y] == BOX){//�˵�ǰ��������
		//�������������ǰ���ǵذ��������ֽĿ�ĵ�
		if(map[next_next_pos.x][next_next_pos.y] == FLOOR){
			if(map[man.x][man.y] == BOX_DES){
				changeMap(&man,BOX_DES);
				changeMap(&next_next_pos,BOX);
				changeMap(&next_pos,MAN);//С��ǰ��һ��
			}else{
				changeMap(&next_next_pos,BOX);
				changeMap(&next_pos,MAN);//С��ǰ��һ��
				changeMap(&man,FLOOR);
			}
			/*if(map[next_next_pos.x][next_next_pos.y] ==BOX){
			}*/
			man = next_pos;
		}else if(map[next_next_pos.x][next_next_pos.y] == BOX_DES){
			changeMap(&next_next_pos,HIT);
			changeMap(&next_pos,MAN);//С��ǰ��һ��
			changeMap(&man,FLOOR);
			man = next_pos;
		}
	}else if(isValid(next_pos) && map[next_pos.x][next_pos.y] == BOX_DES){
		changeMap(&next_pos,MAN);
		changeMap(&man,FLOOR);
		man = next_pos;
		map[man.x][man.y] = BOX_DES;
	}else if(isValid(next_pos) && map[next_pos.x][next_pos.y] == HIT){
		changeMap(&next_next_pos,BOX);
		changeMap(&next_pos,MAN);
		changeMap(&man,FLOOR);
		man = next_pos;
		map[next_pos.x][next_pos.y] = BOX_DES;
	}
}

int main(void){
	IMAGE bg_img;//����һ��ͼƬ����
	//��ʼ������
	cout << "��Ϸ����ֻ���ƶ�40��!" << endl;
	system("pause");
	initgraph(SCREEN_WIDTH,SCREEN_HEIGHT);
	//����ͼƬ������
	loadimage(&bg_img,_T("blackground.bmp"),SCREEN_WIDTH,SCREEN_HEIGHT,true);
	putimage(0,0,&bg_img);//���ص�����

	//���ص���ͼ��
	loadimage(&image[WALL],_T("wall.bmp"),SIZE,SIZE,true);
	loadimage(&image[FLOOR],_T("floor.bmp"),SIZE,SIZE,true);
	loadimage(&image[BOX_DES],_T("des.bmp"),SIZE,SIZE,true);
	loadimage(&image[MAN],_T("man.bmp"),SIZE,SIZE,true);
	loadimage(&image[BOX],_T("box.bmp"),SIZE,SIZE,true);
	loadimage(&image[HIT],_T("box.bmp"),SIZE,SIZE,true);

	//��ͼƬ���ؽ���
	for(int i = 0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j] == MAN){
				man.x = i;
				man.y = j;
			}
			putimage(START_X+j*SIZE,START_Y+i*SIZE,&image[map[i][j]]);
		}
	}

	settextstyle(40,30,_T("�����п�"));
	settextcolor(RED);
	outtextxy(50,50,_T("����: "));
	outtextxy(320,50,"0");

	bool quit = false;

	do{
		//���������������ô_kbhit()��������true
		if(_kbhit()){
			//_getch()��ü������û��ļ�
			char ch = _getch();
			if(ch == KEY_UP){
				gameControl(UP);
			}else if(ch == KEY_DOWN){
				gameControl(DOWN);
			}else if(ch == KEY_LEFT){
				gameControl(LEFT);
			}else if(ch == KEY_RIGHT){
				gameControl(RIGHT);
			}else if(ch == KEY_QUIT){
				quit = true;
			}
			//updateScore();
			if(isGameOver() || walk >= 60){
				Sleep(100);
				gameOverScene(&bg_img);
				quit = true;
			}
		}
		Sleep(100);//���߱����ڴ��˷�
	}while(!quit);

	system("pause");
	//��Ϸ�����ͷ���Դ
	closegraph();
	return 0;
}