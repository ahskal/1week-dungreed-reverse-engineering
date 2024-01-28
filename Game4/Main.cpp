#include "stdafx.h"
#include "Bullet.h"
#include"Grenade.h"
#include "Main.h"


Main::Main()
{

	//================================================================================== 스테이지
	{
		Background = new ObImage(L"BGLayer_0 #225474.png");
		Background->scale.x = TILESIZEX;
		Background->scale.y = TILESIZEY;
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				int index = i * TILEX + j;
				Tiles[0][index].rc = new ObRect();
				Tiles[0][index].imgAddr = L"Tile_Ice_W0.png";
				Tiles[0][index].img = new ObImage(Tiles[0][index].imgAddr);

				Tiles[1][index].rc = new ObRect();
				Tiles[1][index].imgAddr = L"Tile_NONE.png";
				Tiles[1][index].img = new ObImage(Tiles[1][index].imgAddr);

				for (int k = 0; k < TILESTYLE; k++) {
					//타일 크기 설정
					Tiles[k][index].rc->scale = Vector2(TILESIZE, TILESIZE);
					Tiles[k][index].img->scale = Vector2(TILESIZE, TILESIZE);

					//타일 간격만큼 좌표 설정
					Tiles[k][index].rc->SetLocalPosX(TILESIZE / 2 - (TILESIZEX) / 2 + j * TILESIZE);
					Tiles[k][index].rc->SetLocalPosY(TILESIZE / 2 - (TILESIZEY) / 2 + i * TILESIZE);

					Tiles[k][index].img->SetLocalPosX(TILESIZE / 2 - (TILESIZEX) / 2 + j * TILESIZE);
					Tiles[k][index].img->SetLocalPosY(TILESIZE / 2 - (TILESIZEY) / 2 + i * TILESIZE);
				}
			}
		}
		load();
		for (int i = 0; i < BULLETMAX2; i++) {
			greande[i] = new Grenade();
		}

	}
	//==================================================================================

	//================================================================================== 플레이어
	{
		player = new Player();
		player->p = new ObRect();
		player->img = new ObImage(L"TAANA0.png");
		player->img->SetParentRT(*player->p);
		for (int i = 0; i < BULLETMAX; i++) {
			player->bullet[i] = new Bullet(L"PB3.png");
			player->bullet[i]->isFilled = false;
		}
		player->bulletIdx = 0;
		player->isGravite = true;
		player->isJump = false;
	}
	//==================================================================================

	Boss = new ObRect();
	BossImage = new ObImage(L"NiflheimIdle0.png");
	BossImage->SetParentRT(*Boss);

	bossimageFream = 0;
	for (int i = 0; i < 4; i++) {
		Ice[i] = new Niflheim_Ice;
		Ice[i]->BB = new ObRect();
		Ice[i]->BB->SetParentRT(*Boss);
		Ice[i]->img = new ObImage(L"IcePillar.png");
		for (int j = 0; j < BULLETMAX; j++) {
			Ice[i]->bullet[j] = new Bullet(L"IceBullet.png");
		}
	}
	for (int i = 0; i < BULLETMAX2; i++) {
		Icicle[i] = new Bullet(L"Icicle.png");
	}
	patron = PT_0;

}

Main::~Main()
{
}
void Main::load()
{
	ifstream fin;
	string file = "TileMap2.map";
	fin.open(file.c_str(), ios::in);

	if (fin.is_open())
	{
		for (int i = 0; i < TILEY * TILEX; i++) {
			int temp;
			string Addr;
			fin >> Addr >> temp;
			Tiles[0][i].imgAddr.assign(Addr.begin(), Addr.end());
			Tiles[0][i].terrain = (TERRAIN)temp;
		}
	}
	fin.close();

	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			int index = i * TILEX + j;
			Tiles[0][index].img->ChangeImg(Tiles[0][index].imgAddr);
		}
	}
	string file2 = "TileMap2.Object";
	fin.open(file2.c_str(), ios::in);

	if (fin.is_open())
	{
		for (int i = 0; i < TILEY * TILEX; i++) {
			int temp;
			string Addr;
			fin >> Addr >> temp;
			Tiles[1][i].imgAddr.assign(Addr.begin(), Addr.end());
			Tiles[1][i].terrain = (TERRAIN)temp;
		}
	}
	fin.close();

	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			int index = i * TILEX + j;
			Tiles[1][index].img->ChangeImg(Tiles[1][index].imgAddr);
		}
	}
}
void Main::Init()
{
	player->p->isFilled = false;
	player->p->scale.x = TILESIZE + 10;
	player->p->scale.y = TILESIZE + 10;
	player->img->scale.x = TILESIZE;
	player->img->scale.y = TILESIZE;
	player->p->SetWorldPos(Vector2(0, -200));
	player->isGravite = true;



	Boss->scale.x = BossImage->imageSize.x * 3 + 10;
	Boss->scale.y = BossImage->imageSize.y * 3 + 10;
	BossImage->scale.x = BossImage->imageSize.x * 3;
	BossImage->scale.y = BossImage->imageSize.y * 3;

	Boss->isFilled = false;;

	for (int i = 0; i < 4; i++) {
		Ice[i]->BB->scale.x = Ice[i]->img->imageSize.x * 2 + 10;
		Ice[i]->BB->scale.y = Ice[i]->img->imageSize.y * 2 + 10;
		Ice[i]->img->scale.x = Ice[i]->img->imageSize.x * 2;
		Ice[i]->img->scale.y = Ice[i]->img->imageSize.y * 2;

		Ice[i]->BB->isFilled = false;
		Ice[i]->isBroken = false;
		Ice[i]->Colcount = 0;
	}



}

void Main::Release()
{
}

void Main::Update()
{
	CAM->scale.x = scale;
	CAM->scale.y = scale;
	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

	ImGui::Text("patron : %d", patron);
	ImGui::Text("World Time : %f", TIMER->GetWorldTime());

	ImGui::Text("player Pos: (%.2f, %.2f)", player->p->GetWorldPivot().x, player->p->GetWorldPivot().y);

	// 보스 이미지 프레임 이미지 프레임값이 변경될때 이미지 변경
	//========================================================== 보스
	{
		switch (bossimageFream)
		{
		case 0: BossImage->ChangeImg(L"NiflheimIdle0.png"); break;
		case 1: BossImage->ChangeImg(L"NiflheimIdle1.png"); break;
		case 2: BossImage->ChangeImg(L"NiflheimIdle2.png"); break;
		case 3: BossImage->ChangeImg(L"NiflheimIdle3.png"); break;
		case 4: BossImage->ChangeImg(L"NiflheimIdle4.png"); break;
		case 5: BossImage->ChangeImg(L"NiflheimIdle5.png"); break;

		default:
			break;
		}
		if (TIMER->GetTick(FreamSwapTime, 0.2f)) {
			bossimageFream++;
		}
		if (bossimageFream == 6) {
			bossimageFream = 0;
		}
	}
	//========================================================== 

	//========================================================== 플레이어
	{
		for (int i = 0; i < BULLETMAX; i++) {
			switch (player->bulletFreamIdx[i])
			{
			case 0: player->bullet[i]->ChangeImg(L"PB1.png"); break;
			case 1: player->bullet[i]->ChangeImg(L"PB2.png"); break;
			case 2: player->bullet[i]->ChangeImg(L"PB3.png"); break;

			default:
				break;
			}
			if (TIMER->GetTick(player->BulletFreamTimer, 0.2f)) {
				player->bulletFreamIdx[i]++;
			}
			if (player->bulletFreamIdx[i] == 3) {
				player->bulletFreamIdx[i] = 0;
			}
		}

		player->p->Update();
		player->img->Update();

		for (int i = 0; i < BULLETMAX; i++) {
			player->bullet[i]->Update();
		}
	}
	//========================================================== 

	//========================================================== 배경
	{
		Background->Update();
		for (int i = 0; i < TILEY * TILEX; i++) {
			if (Tiles[0][i].terrain != TR_BG) {
				Tiles[0][i].rc->Update();
			}
			if (Tiles[1][i].terrain != TR_NONE) {
				Tiles[1][i].rc->Update();
				Tiles[1][i].img->Update();
			}
			Tiles[0][i].img->Update();
		}
	}
	//==========================================================

	//========================================================== 조작
	{
		CAM->position.x = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), player->p->GetWorldPos(), 1.f).x, -(float)(TILESIZEX) / 2 + app.GetHalfWidth(), (float)(TILESIZEX) / 2 - app.GetHalfWidth());
		CAM->position.y = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), player->p->GetWorldPos(), 1.f).y, -(float)(TILESIZEY) / 2 + app.GetHalfHeight(), (float)(TILESIZEY) / 2 - app.GetHalfHeight());

		if (INPUT->KeyDown('1')) {
			patron = PT_0;
		}
		if (INPUT->KeyDown('2')) {
			patron = PT_1;
		}
		if (INPUT->KeyDown('3')) {
			patron = PT_2;
		}
		if (INPUT->KeyDown('4')) {
			patron = PT_3;
		}

		if (INPUT->KeyPress('W')) {
			player->p->MoveWorldPos(UP * 300.f * DELTA);
		}
		if (INPUT->KeyPress('S')) {
			player->p->MoveWorldPos(DOWN * 300.f * DELTA);

		}
		if (INPUT->KeyPress('A')) {
			player->p->MoveWorldPos(LEFT * 300.f * DELTA);
			player->p->rotation.y = PI;

		}
		if (INPUT->KeyPress('D')) {
			player->p->MoveWorldPos(RIGHT * 300.f * DELTA);
			player->p->rotation.y = 0;
		}
		if (INPUT->KeyPress(VK_LBUTTON)) {
			Vector2 MousePos = INPUT->GetWorldMousePos();
			if (TIMER->GetTick(player->BulletTimer, 0.2f)) {
				player->bullet[player->bulletIdx]->Fire(player->p->GetWorldPivot(), MousePos, Vector2(1.5, 0.5), 500.f);
				player->bulletIdx++;
			}
		}
		if (player->bulletIdx == BULLETMAX - 1) {
			player->bulletIdx = 0;
		}

		if (INPUT->KeyDown(VK_SPACE)) {
			player->isJump = true;
			player->jumpPower = 700.f;
			player->Gravite = 10.f;
		}

		if (player->isJump) {
			player->isGravite = false;
			player->jumpPower -= player->Gravite;

			player->p->MoveWorldPos(UP * player->jumpPower * DELTA);
		}

		if (player->isGravite) {

			player->p->MoveWorldPos(DOWN * player->Gravite * 10.f * DELTA);
		}
	}
	//==========================================================

	//if (INPUT->KeyPress(VK_LEFT)) {
	//	Boss->MoveWorldPos(LEFT * 300.f * DELTA);
	//}
	//
	//if (INPUT->KeyPress(VK_RIGHT)) {
	//	Boss->MoveWorldPos(RIGHT * 300.f * DELTA);
	//}
	//
	//if (INPUT->KeyPress(VK_UP)) {
	//	Boss->MoveWorldPos(UP * 300.f * DELTA);
	//}
	//
	//if (INPUT->KeyPress(VK_DOWN)) {
	//	Boss->MoveWorldPos(DOWN * 300.f * DELTA);
	//}
	//CAM->position.x = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), Boss->GetWorldPos(), 1.f).x, -(float)(TILESIZEX) / 2 + app.GetHalfWidth(), (float)(TILESIZEX) / 2 - app.GetHalfWidth());
	//CAM->position.y = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), Boss->GetWorldPos(), 1.f).y, -(float)(TILESIZEY) / 2 + app.GetHalfHeight(), (float)(TILESIZEY) / 2 - app.GetHalfHeight());
	//CAM->position.x = Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), Boss->GetWorldPos(), 1.f).x;
	//CAM->position.y = Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), Boss->GetWorldPos(), 1.f).y;

	for (int i = 0; i < 4; i++) {
		Ice[i]->img->SetWorldPos(Ice[i]->BB->GetWorldPos());
		Ice[i]->img->SetParentRT(*Ice[i]->BB);
		if (not Ice[i]->isBroken) {


			Ice[i]->BB->Update();
			Ice[i]->img->Update();
		}

		for (int j = 0; j < BULLETMAX; j++) {
			Ice[i]->bullet[j]->Update();
		}
	}
	for (int i = 0; i < BULLETMAX2; i++) {
		Icicle[i]->Update();
	}
	for (int i = 0; i < BULLETMAX2; i++) {
		greande[i]->Update();
	}

	Background->Update();
	Boss->Update();
	BossImage->Update();
}

void Main::LateUpdate()
{
	//=================================================== 맵 충돌
	{
		for (int i = 0; i < TILEY * TILEX; i++) {
			if (player->p->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_R) {
				player->p->SetWorldPosX(Tiles[0][i].rc->GetWorldPivot().x - Tiles[0][i].rc->scale.x - 5);
			}
			if (player->p->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_L) {
				player->p->SetWorldPosX(Tiles[0][i].rc->GetWorldPivot().x + Tiles[0][i].rc->scale.x + 5);
			}
			if (player->p->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_B) {
				player->p->SetWorldPosY(Tiles[0][i].rc->GetWorldPivot().y + Tiles[0][i].rc->scale.y + 3.f);
			}
			else if (player->p->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_T) {
				player->p->SetWorldPosY(Tiles[0][i].rc->GetWorldPivot().y - Tiles[0][i].rc->scale.y - 5);
				player->isGravite = false;
				player->Gravite = 10.f;
				player->isJump = false;
			}
			else if (player->jumpPower < -1 && player->p->Intersect(Tiles[1][i].rc) && Tiles[1][i].terrain == TR_FLOOR) {
				//Tiles[1][i].img->color.y = 1.f;
				player->p->SetWorldPosY(Tiles[0][i].rc->GetWorldPivot().y + Tiles[0][i].rc->scale.y);
				player->isGravite = false;
				player->Gravite = 10.f;
				player->isJump = false;
				//Tiles[1][i].img->color.y = 1.f;
			}
			else {
				player->isGravite = true;

				//Tiles[0][i].img->color.x = 0.5f;
				//Tiles[0][i].img->color.y = 0.5f;
				//Tiles[0][i].img->color.z = 0.5f;
			}
		}
	}
	//===================================================

	//=================================================== 고드름
	{
		if (TIMER->GetTick(IcicleTimer, 0.4f)) {
			for (int i = 0; i < BULLETMAX2; i++) {
				if (Icicle[i]->GetIsFire()) continue;
				Vector2 Pos(RANDOM->Int(-10, 10) * (TILESIZE + TILESIZE / 2) * scale, (float)(TILESIZEY) / 2 * scale);
				Icicle[IcicleIdx]->Drop(Pos, Vector2(2, 2), 300.f);
				IcicleIdx++;
				break;
			}
		}
		if (Icicle[IcicleIdx]->GetWorldPos().y < -(float)(TILESIZEY) / 2) {
			Icicle[IcicleIdx]->Release();
		}
		if (IcicleIdx == BULLETMAX2 - 1) {
			IcicleIdx = 0;
		}
	}
	//===================================================

	//===================================================패턴 타이머
	{
		if (TIMER->GetTick(patronTimer, 5.f)) {
			static int last;
			patronNum = RANDOM->Int(0, 2);

			if (last == patronNum)
				patron = PT_1;
			else
				patron = (Patron)patronNum;
			last = patronNum;
		}
	}
	//===================================================

	//=================================================== 1패턴
	{
		if (patron == PT_0) {
			if (Ice[0]->BB->rotation2.z == Ice[1]->BB->rotation2.z) {
				for (int i = 0; i < 4; i++) {
					Ice[i]->BB->rotation.z = 90 * ToRadian;
					Ice[i]->BB->rotation2.z = (90 * i) * ToRadian;
				}
			}
			for (int i = 0; i < 4; i++) {
				Ice[i]->BB->SetParentRT(*Boss);
				Ice[i]->BB->SetLocalPosX(100);
				Ice[i]->BB->SetLocalPosY(0);
				Ice[i]->BB->rotation2.z += 120 * DELTA * ToRadian;
			}
		}
	}
	//=================================================== 

	//=================================================== 2패턴
	{
		if (patron == PT_1) {

			for (int i = 0; i < 4; i++) {
				Ice[i]->BB->DeleteParentRT();
				Ice[i]->BB->SetLocalPos(Vector2(0, 0));
				Ice[i]->BB->rotation2.z = 0;
			}
			Boss->SetWorldPos(Vector2::Lerp(Boss->GetWorldPos(), Vector2(0, 45), 0.03f));
			Ice[0]->BB->SetWorldPos(Vector2::Lerp(Ice[0]->BB->GetWorldPos(), Vector2(400, 250), 0.03f));
			Ice[1]->BB->SetWorldPos(Vector2::Lerp(Ice[1]->BB->GetWorldPos(), Vector2(-400, 250), 0.03f));
			Ice[2]->BB->SetWorldPos(Vector2::Lerp(Ice[2]->BB->GetWorldPos(), Vector2(400, -250), 0.03f));
			Ice[3]->BB->SetWorldPos(Vector2::Lerp(Ice[3]->BB->GetWorldPos(), Vector2(-400, -250), 0.03f));

			if (TIMER->GetTick(patronChangeTimer, 2.5f) && patron == PT_1) {
				patronTimer = 0;
				patron = PT_11;
			}
		}
	}
	//=================================================== 

	//=================================================== 2-1패턴
	{
		if (patron == PT_11) {

			patronTimer -= DELTA / 4;
			for (int i = 0; i < 4; i++) {
				Ice[i]->BB->rotation.z += (RANDOM->Int(0, 10) + 120) * DELTA * ToRadian;
			}

			int ran = RANDOM->Int(0, 3);
			if (TIMER->GetTick(IceTimer, 0.2f)) {
				for (int j = 0; j < BULLETMAX; j++) {
					if (Ice[ran]->bullet[j]->GetIsFire()) continue;

					Ice[ran]->bullet[j]->Fire(Ice[ran]->BB->GetWorldPos(), player->p->GetWorldPivot(), Vector2(1.5f, 1.5f), 100.f);
					break;
				}
			}
		}
	}
	//=================================================== 
	// 
	//=================================================== 3패턴
	{
		if (patron == PT_2) {
			// 이동한 위치로 업데이트
			if (Ice[0]->BB->rotation2.z == Ice[1]->BB->rotation2.z) {
				for (int i = 0; i < 4; i++) {
					Ice[i]->BB->rotation.z = 90 * ToRadian;
					Ice[i]->BB->rotation2.z = (90 * i) * ToRadian;
				}
			}
			for (int i = 0; i < 4; i++) {
				Ice[i]->BB->SetParentRT(*Boss);
				Ice[i]->BB->SetLocalPosX(100);
				Ice[i]->BB->SetLocalPosY(0);
				Ice[i]->BB->rotation2.z += 120 * DELTA * ToRadian;
			}

			Boss->SetWorldPos(Vector2::Lerp(Boss->GetWorldPos(), Vector2(0, 300), 0.03f));

			for (int i = 0; i < BULLETMAX2; i++) {
				ImGui::Text(" i  %d", i);
				if (greande[i]->GetIsFire()) continue;
				if (TIMER->GetTick(greandeTimer, 0.5f)) {
					greande[greandeIdx]->Explosion(Boss->GetWorldPos(), 50, 500.f);
					greandeIdx++;
				}
				break;
			}
			if (greandeIdx == BULLETMAX2 - 1) {
				greandeIdx = 0;
			}
		}
	}
	//=================================================== 

	// 움직이는 패턴인데 랜덤으로 작동이 잘 안됨.
	//=================================================== 4패턴
	{
		if (patron == PT_3) {

			Boss->SetWorldPos(Vector2::Lerp(Boss->GetWorldPos(), Vector2(0, -200), 0.0f));
		}
	}
	//=================================================== 

	//플레이어 총알과 충돌
	for (int i = 0; i < BULLETMAX; i++) {
		if (not player->bullet[i]->GetIsFire()) continue;
		for (int j = 0; j < BULLETMAX; j++) {
			for (int k = 0; k < 4; k++) {
				if (not Ice[k]->bullet[j]->GetIsFire()) continue;
				if (player->bullet[i]->Intersect(Ice[k]->bullet[j])) {
					player->bullet[i]->Release();
					Ice[k]->bullet[j]->Release();
				}
			}
		}
		for (int j = 0; j < BULLETMAX2; j++) {
			if (not Icicle[j]->GetIsFire()) continue;
			if (player->bullet[i]->Intersect(Icicle[j])) {
				player->bullet[i]->Release();
				Icicle[j]->Release();
			}
		}
		for (int j = 0; j < BULLETMAX2; j++) {
			if (not greande[j]->GetIsFire())continue;
			for (int k = 0; k < 36; k++) {
				if (player->bullet[i]->Intersect(greande[j]->bullet[k])) {
					player->bullet[i]->Release();
					greande[j]->bullet[k]->Release();
				}
			}
		}
		//for (int k = 0; k < 4; k++) {
		//	if (not Ice[i]->isBroken) {
		//		if (player->bullet[i]->Intersect(Ice[k]->BB)) {
		//			player->bullet[i]->Release();
		//			Ice[k]->Colcount++;
		//		}
		//	}			
		//	
		//
	}
	for (int i = 0; i < 4; i++) {
		if (Ice[i]->Colcount == 5) {
			Ice[i]->isBroken = true;
		}
	}
	if (Ice[0]->isBroken && Ice[1]->isBroken && Ice[2]->isBroken && Ice[3]->isBroken) {
		patron = PT_3;
	}

}


void Main::Render()
{
	//================================================== //타일 랜더 
	{
		Background->Render();
		for (int i = 0; i < TILEY; i++) {
			for (int j = 0; j < TILEX; j++) {
				int index = i * TILEX + j;
				//Tiles[0][index].rc->Render();
				Tiles[0][index].img->Render();
				if (Tiles[1][index].imgAddr != L"Tile_NONE.png") {
					Tiles[1][index].img->Render();
				}
			}
		}
	}
	//==================================================

	for (int i = 0; i < BULLETMAX2; i++) {
		Icicle[i]->Render();
	}
	Boss->Render();
	BossImage->Render();
	for (int i = 0; i < 4; i++) {
		if (not Ice[i]->isBroken) {
			Ice[i]->BB->Render();
			Ice[i]->img->Render();
		}
		for (int j = 0; j < BULLETMAX; j++) {
			Ice[i]->bullet[j]->Render();
		}
	}
	for (int i = 0; i < BULLETMAX2; i++) {
		greande[i]->Render();
	}
	player->p->Render();
	player->img->Render();
	for (int i = 0; i < BULLETMAX; i++) {
		player->bullet[i]->Render();
	}
}

void Main::ResizeScreen()
{


}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game4");
	app.SetInstance(instance);
	app.InitWidthHeight(1600.0f, 800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}