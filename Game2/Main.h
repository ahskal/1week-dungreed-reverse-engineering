#pragma once

//타일의 크기 

#define TILESIZE 32
//샘플타일(보여서 넣는 타일) 크기
#define SAMPLETILESIZE 48

//타일의 갯수
//#define TILEX 30
//#define TILEY 22

#define TILEX 36
#define TILEY 18


//맵 전체 길이
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋 (샘플타일)
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
	//블럭 타입
	TERRAIN terrain;
	// 충돌체
	ObRect* rc;
	// 이미지
	ObImage* img;
	// 이미지의 파일명
	wstring imgAddr;
};
struct SampleTile {
	// 충돌체
	ObRect* rcTile;
	// 이미지
	ObImage* sample;
	// 이미지의 파일명
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
	// 플레이 할 타일맵
	TileMap Tiles[TILESTYLE][TILEX * TILEY];

	// 임시 이미지의 파일명
	// 마우스가 샘플타일에 충돌했을때 해당정보를 담아두는 곳
	// 타일에 충돌했을때 해당타일에 이미지 파일명을 넣어준다.
	wstring imgAddr;

	// 화면 배율
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
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
