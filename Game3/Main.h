#pragma once

//Ÿ���� ũ�� 

#define TILESIZE 64
//����Ÿ��(������ �ִ� Ÿ��) ũ��
#define TILEX 30
#define TILEY 22

//�� ��ü ����
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

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

enum MAPSCENE
{
	MS_MAIN,
	MS_START,
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


class Main : public Scene
{
private:
	// �÷��� �� Ÿ�ϸ�
	TileMap Tiles[TILESTYLE][TILEX * TILEY];

	// �ӽ� �̹����� ���ϸ�
	// ���콺�� ����Ÿ�Ͽ� �浹������ �ش������� ��Ƶδ� ��
	// Ÿ�Ͽ� �浹������ �ش�Ÿ�Ͽ� �̹��� ���ϸ��� �־��ش�.
	wstring imgAddr;

	// ȭ�� ����
	float scale = 1.0f;

	ObImage* Background;

	bool isDebug;

	int TileStyle = 0;

	//====================================== 
	// ù��° ����
	class Dun_Boss* boss_first;			
	float			Boss_Spawn_Time;

	/** ����*/


	//====================================== 
	// �÷��̾�

	class Player* player;
	float		  hitTimer;	//�ǰݴ��ϰ����� Ÿ�̸�
	float		  B_hitTimer;	//�ǰݴ��ϰ����� Ÿ�̸�

	float timer;

	MAPSCENE scene;

	/** ���� ȭ��*/

	ObRect* startClick;
	ObRect* finishClick;

	ObImage* main;
	ObImage* mainLogo;
	ObImage* mainLogo_bg;
	bool b_mainLogo = true;
	float	mainTIme;				// ���ηΰ� �����ִ� �ð�

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
