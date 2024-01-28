#pragma once
#pragma once
#pragma once
#pragma once


//Ÿ���� ũ��
#define TILESIZE 64
//����Ÿ��(������ �ִ� Ÿ��) ũ��

//Ÿ���� ����
#define TILEX 36
#define TILEY 18

//�� ��ü ����
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

#define TILESTYLE 2

#define BULLETMAX 50
#define BULLETMAX2 15

enum TERRAIN
{
	TR_NONE,
	TR_WALL,
	TR_WALL_T,
	TR_WALL_L,
	TR_WALL_R,
	TR_WALL_B,
	TR_FLOOR,
	TR_BG,
};

struct TileMap {
	//�� Ÿ��
	TERRAIN terrain;
	// �浹ü
	ObRect* rc;
	// �̹���
	ObImage* img;
	// �̹����� ���ϸ�
	wstring imgAddr;
};

struct Player {
	ObRect* p;
	ObImage* img;
	float jumpPower;
	float Gravite;
	bool isGravite;
	bool isJump;
	Bullet* bullet[BULLETMAX];
	ObImage* bulletImg[BULLETMAX];
	int bulletFreamIdx[BULLETMAX];
	int bulletIdx;

	float BulletTimer = 0;
	float BulletFreamTimer = 0;
};

struct Niflheim_Ice {
	ObRect* BB;
	Bullet* bullet[BULLETMAX];
	ObImage* img;
	bool isBroken;
	int Colcount;
};

enum Patron {
	PT_0,
	PT_1,
	PT_2,
	PT_3,

	PT_11,

};

class Main : public Scene
{
private:
	// ȭ�� ����
	float scale = 1.0f;

	// �÷��� �� Ÿ�ϸ�
	TileMap Tiles[TILESTYLE][TILEX * TILEY];
	ObImage* Background;

	// ��帧
	class Bullet* Icicle[BULLETMAX2];
	float IcicleTimer = 0;
	int IcicleIdx = 0;
	
	// ������ ź 
	class Grenade* greande[BULLETMAX2];
	float greandeTimer = 0;
	int greandeIdx = 0;

	Player* player;

	ObRect* Boss;
	ObImage* BossImage;
	int bossimageFream = 0;
	float FreamSwapTime = 0;
	Patron patron;
	float patronTimer = 0;

	float patronChangeTimer = 0;

	Niflheim_Ice* Ice[4];
	float IceTimer = 0;

	Vector2 Pos;

	

	bool isDebug;
	int SampleType = 0;
	int TileStyle = 0;

	int patronNum;


public:
	Main();
	~Main();

	void load();

	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
