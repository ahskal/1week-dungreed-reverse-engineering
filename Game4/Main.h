#pragma once
#pragma once
#pragma once
#pragma once


//타일의 크기
#define TILESIZE 64
//샘플타일(보여서 넣는 타일) 크기

//타일의 갯수
#define TILEX 36
#define TILEY 18

//맵 전체 길이
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
	//블럭 타입
	TERRAIN terrain;
	// 충돌체
	ObRect* rc;
	// 이미지
	ObImage* img;
	// 이미지의 파일명
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
	// 화면 배율
	float scale = 1.0f;

	// 플레이 할 타일맵
	TileMap Tiles[TILESTYLE][TILEX * TILEY];
	ObImage* Background;

	// 고드름
	class Bullet* Icicle[BULLETMAX2];
	float IcicleTimer = 0;
	int IcicleIdx = 0;
	
	// 퍼지는 탄 
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
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
