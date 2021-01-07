#define SIZE 61  //道具图片像素
#define SCREEN_WIDTH  960 //地图像素
#define SCREEN_HEIGHT 768

//上下左右控制方向  q为退出
#define KEY_UP       'w'
#define KEY_LEFT     'a'
#define KEY_RIGHT    'd'
#define KEY_DOWN     's'
#define KEY_QUIT     'q'


#define LINE    9    //地图数组行
#define COLUMN  12   //列


#define isValid(pos) pos.x>=0 && pos.x<LINE && pos.y>=0 && pos.y<COLUMN


#define START_X 100  //地图起点偏移量
#define START_Y 150

typedef enum _DIRECTION  DIRECTION;
typedef struct _POS		 POS;
typedef enum _PROPS      PROPS;

int walk = 0;

//游戏控制方向
enum _DIRECTION{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct _POS{
	int x;
	int y;
};

//道具定义
enum _PROPS{
	WALL,      //墙
	FLOOR,	   //地板
	BOX_DES,   //箱子目的地
	MAN,	   //角色
	BOX,       //箱子
	HIT,	   //箱子重合
	ALL
};