#pragma once

//Ÿ���� ũ�� 

#define TILESIZE 32
//����Ÿ��(������ �ִ� Ÿ��) ũ��
#define SAMPLETILESIZE 48

//Ÿ���� ����
//#define TILEX 30
//#define TILEY 22

#define TILEX 36
#define TILEY 18


//�� ��ü ����
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ� (����Ÿ��)
#define SAMPLETILEX 3
#define SAMPLETILEY 12

#define SAMPLELIST 2
#define TILESTYLE 2

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
struct SampleTile {
	// �浹ü
	ObRect* rcTile;
	// �̹���
	ObImage* sample;
	// �̹����� ���ϸ�
	wstring imgAddr;
};

struct Player {
	ObRect* p;
	float jumpPower;
	float Gravite;
	bool isGravite;
	bool isJump;
};

class Main : public Scene
{
private:

	SampleTile* SampleTiles[SAMPLELIST][SAMPLETILEX * SAMPLETILEY];
	ObRect* sampleTileRect;
	//SampleTile SampleTiles2[SAMPLETILEX * SAMPLETILEY];
	// �÷��� �� Ÿ�ϸ�
	TileMap Tiles[TILESTYLE][TILEX * TILEY];

	// �ӽ� �̹����� ���ϸ�
	// ���콺�� ����Ÿ�Ͽ� �浹������ �ش������� ��Ƶδ� ��
	// Ÿ�Ͽ� �浹������ �ش�Ÿ�Ͽ� �̹��� ���ϸ��� �־��ش�.
	wstring imgAddr;

	// ȭ�� ����
	float scale = 1.0f;

	ObImage* Background;

	

	Player* player;

	bool isDebug;
	int SampleType = 0;
	int TileStyle = 0;


public:
	Main();
	~Main();

	void save();
	void load();

	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
