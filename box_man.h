#define SIZE 61  //����ͼƬ����
#define SCREEN_WIDTH  960 //��ͼ����
#define SCREEN_HEIGHT 768

//�������ҿ��Ʒ���  qΪ�˳�
#define KEY_UP       'w'
#define KEY_LEFT     'a'
#define KEY_RIGHT    'd'
#define KEY_DOWN     's'
#define KEY_QUIT     'q'


#define LINE    9    //��ͼ������
#define COLUMN  12   //��


#define isValid(pos) pos.x>=0 && pos.x<LINE && pos.y>=0 && pos.y<COLUMN


#define START_X 100  //��ͼ���ƫ����
#define START_Y 150

typedef enum _DIRECTION  DIRECTION;
typedef struct _POS		 POS;
typedef enum _PROPS      PROPS;

int walk = 0;

//��Ϸ���Ʒ���
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

//���߶���
enum _PROPS{
	WALL,      //ǽ
	FLOOR,	   //�ذ�
	BOX_DES,   //����Ŀ�ĵ�
	MAN,	   //��ɫ
	BOX,       //����
	HIT,	   //�����غ�
	ALL
};