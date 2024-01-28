#pragma once

//타일의 크기 

#define TILESIZE 64
//샘플타일(보여서 넣는 타일) 크기
#define TILEX 30
#define TILEY 22

//맵 전체 길이
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
	//블럭 타입
	TERRAIN terrain;
	// 충돌체
	ObRect* rc;
	// 이미지
	ObImage* img;
	// 이미지의 파일명
	wstring imgAddr;
};


class Main : public Scene
{
private:
	// 플레이 할 타일맵
	TileMap Tiles[TILESTYLE][TILEX * TILEY];

	// 임시 이미지의 파일명
	// 마우스가 샘플타일에 충돌했을때 해당정보를 담아두는 곳
	// 타일에 충돌했을때 해당타일에 이미지 파일명을 넣어준다.
	wstring imgAddr;

	// 화면 배율
	float scale = 1.0f;

	ObImage* Background;

	bool isDebug;

	int TileStyle = 0;

	//====================================== 
	// 첫번째 보스
	class Dun_Boss* boss_first;			
	float			Boss_Spawn_Time;

	/** 보스*/


	//====================================== 
	// 플레이어

	class Player* player;
	float		  hitTimer;	//피격당하고나서의 타이머
	float		  B_hitTimer;	//피격당하고나서의 타이머

	float timer;

	MAPSCENE scene;

	/** 시작 화면*/

	ObRect* startClick;
	ObRect* finishClick;

	ObImage* main;
	ObImage* mainLogo;
	ObImage* mainLogo_bg;
	bool b_mainLogo = true;
	float	mainTIme;				// 메인로고 보여주는 시간

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
