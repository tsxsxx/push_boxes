#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>  //获取键盘信息

#include "box_man.h"

POS man;

using namespace std;

//墙为0-地板为1-箱子目的为2-角色为3-箱子为4-箱子重合为5
//图片表示数组
IMAGE image[ALL];

//游戏地图
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

//判断游戏是否结束
bool isGameOver(){
	for(int i = 0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j] == BOX_DES) return false;
		}
	}
	return true;
}

//游戏结束
void gameOverScene(IMAGE *bg){
	putimage(0,0,bg);
	settextcolor(WHITE);
	RECT rec = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	settextstyle(20,0,_T("宋体"));
	drawtext(_T("游戏结束"),&rec,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/**********************************
*改变游戏地图视图中一格对应道具并重新显示
*   lline - 道具在地图数组的行下标
*	colum - 道具在地图数组的列下标
*	prop - 道具的类型
***********************************/
void changeMap(POS *pos,PROPS prop){
	map[pos->x][pos->y] = prop;
	putimage(START_X+pos->y*SIZE,START_Y+pos->x*SIZE,&image[prop]);
}

// 更新分数
//void updateScore(){
//	setfillcolor(BLACK);
//	solidrectangle(310,50,410,90);
//	char name[16];
//	sprintf(name,"%d",walk);
//	outtextxy(320,50,name);
//}

//游戏方向控制,direct->人前进方向
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

	//人前方是地板
	if(isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR){
		if(map[man.x][man.y] == BOX_DES){
			changeMap(&man,BOX_DES);
			changeMap(&next_pos,MAN);//小人前进一格
		}else{
			changeMap(&next_pos,MAN);
			changeMap(&man,FLOOR);
		}
		man = next_pos;
	}else if(isValid(next_pos) && map[next_pos.x][next_pos.y] == BOX){//人的前方是箱子
		//两种情况，箱子前面是地板或者是相纸目的地
		if(map[next_next_pos.x][next_next_pos.y] == FLOOR){
			if(map[man.x][man.y] == BOX_DES){
				changeMap(&man,BOX_DES);
				changeMap(&next_next_pos,BOX);
				changeMap(&next_pos,MAN);//小人前进一格
			}else{
				changeMap(&next_next_pos,BOX);
				changeMap(&next_pos,MAN);//小人前进一格
				changeMap(&man,FLOOR);
			}
			/*if(map[next_next_pos.x][next_next_pos.y] ==BOX){
			}*/
			man = next_pos;
		}else if(map[next_next_pos.x][next_next_pos.y] == BOX_DES){
			changeMap(&next_next_pos,HIT);
			changeMap(&next_pos,MAN);//小人前进一格
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
	IMAGE bg_img;//定义一个图片背景
	//初始化布局
	cout << "游戏人物只能移动40步!" << endl;
	system("pause");
	initgraph(SCREEN_WIDTH,SCREEN_HEIGHT);
	//加载图片做背景
	loadimage(&bg_img,_T("blackground.bmp"),SCREEN_WIDTH,SCREEN_HEIGHT,true);
	putimage(0,0,&bg_img);//加载到界面

	//加载道具图标
	loadimage(&image[WALL],_T("wall.bmp"),SIZE,SIZE,true);
	loadimage(&image[FLOOR],_T("floor.bmp"),SIZE,SIZE,true);
	loadimage(&image[BOX_DES],_T("des.bmp"),SIZE,SIZE,true);
	loadimage(&image[MAN],_T("man.bmp"),SIZE,SIZE,true);
	loadimage(&image[BOX],_T("box.bmp"),SIZE,SIZE,true);
	loadimage(&image[HIT],_T("box.bmp"),SIZE,SIZE,true);

	//用图片加载界面
	for(int i = 0;i<LINE;i++){
		for(int j=0;j<COLUMN;j++){
			if(map[i][j] == MAN){
				man.x = i;
				man.y = j;
			}
			putimage(START_X+j*SIZE,START_Y+i*SIZE,&image[map[i][j]]);
		}
	}

	settextstyle(40,30,_T("华文行楷"));
	settextcolor(RED);
	outtextxy(50,50,_T("步数: "));
	outtextxy(320,50,"0");

	bool quit = false;

	do{
		//如果键盘有输入那么_kbhit()函数返回true
		if(_kbhit()){
			//_getch()获得键盘所敲击的键
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
		Sleep(100);//休眠避免内存浪费
	}while(!quit);

	system("pause");
	//游戏结束释放资源
	closegraph();
	return 0;
}