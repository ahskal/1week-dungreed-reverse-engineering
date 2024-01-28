#include "stdafx.h"
#include "Player.h"
#include "Main.h"

Main::Main()
{
	/** ==============추가할 부분==============*/
	main = new ObImage(L"Main.png");
	mainLogo = new ObImage(L"MainLogo.png");
	mainLogo_bg = new ObImage(L"TownSky_Xmas.png");

	startClick = new ObRect();
	finishClick = new ObRect();
	startClick->isFilled = false;
	finishClick->isFilled = false;
	/** ==============추가할 부분==============*/

	player = new Player();

	imgAddr = L"Tile_NONE.png";
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

	boss_first = new Dun_Boss();
}

Main::~Main()
{

	delete mainLogo_bg;
	delete startClick;
	delete finishClick;
}
void Main::load()
{
	ifstream fin;
	string file = "TileMap.map";
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
	string file2 = "TileMap.Object";
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
	player->Init(Vector2(0, -360));
	player->isFilled = false;
	player->color = Color(0.5, 0, 0);
	hitTimer = 0.0f;
	B_hitTimer = 0.0f;

	boss_first->Init(Vector2(0.0f, 150.0f));

	/** ==============추가할 부분==============*/
	scene = MS_MAIN;
	mainTIme = 0.0f;

	main->scale.x = 1600.0f;
	main->scale.y = 800.0f;
	mainLogo_bg->scale.x = 1600.0f;
	mainLogo_bg->scale.y = 800.0f;
	mainLogo->scale.x = 800.0f;
	mainLogo->scale.y = 400.0f;

	main->SetWorldPos(Vector2(0, 0));
	mainLogo_bg->SetWorldPos(Vector2(0, 0));
	mainLogo->SetWorldPos(Vector2(0, 0));

	startClick->SetWorldPos(Vector2(0, -120.0f));
	finishClick->SetWorldPos(Vector2(0, -230.0f));

	startClick->scale.x = 190.0f;
	startClick->scale.y = 55.0f;

	finishClick->scale.x = 100.0f;
	finishClick->scale.y = 50.0f;
	/** ==============추가할 부분==============*/


}



void Main::Release()
{
}

void Main::Update()
{
	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

	ImGui::SliderFloat("Cam Scale", &scale, 0.0f, 2.0f);
	ImGui::Text("Winsize Pos: (%.2f, %.2f)", app.GetWidth(), app.GetHeight());
	CAM->scale.x = scale;
	CAM->scale.y = scale;
	ImGui::Text("Selected Values: (%.2f, %.2f)", CAM->scale.x, CAM->scale.y);
	ImGui::Text("Mouse Pos: (%.2f, %.2f)", INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y);
	ImGui::Text("cam Pos: (%.2f, %.2f)", CAM->position.x, CAM->position.y);
	//ImGui::Text("player Pos: (%.2f, %.2f)", player->p->GetWorldPivot().x, player->p->GetWorldPivot().y);


	/** ==============추가할 부분==============
	* if 부분만 추가 하고
	else if 부분은 그대로*/
	if (scene == MS_MAIN)
	{
		main->Update();
		mainLogo->Update();
		mainLogo_bg->Update();

		startClick->Update();
		finishClick->Update();
	}
	else if (scene == MS_START)
	{
		if (player->hp <= 0) ImGui::Text("\n\n\tPLAYER LOSE");
		else if (boss_first->hp <= 0) ImGui::Text("\n\n\tPLAYER WIN");
		else ImGui::Text("\n\n\tPLAYING\n\n");

		if (player->ishit)
		{
			player->color = Color(0.7f, 0, 0);
			if (TIMER->GetTick(hitTimer, 2.0f))
			{
				player->ishit = false;
			}
		}
		else player->color = Color(0.3f, 0.3f, 0.3f);
		if (boss_first->ishit_B)
		{
			boss_first->GetBoss()->color = Color(0.7f, 0, 0);
			if (TIMER->GetTick(B_hitTimer, 0.2f))
			{
				boss_first->ishit_B = false;
			}
		}
		else boss_first->GetBoss()->color = Color(1.0f, 1.0f, 1.0f);


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

		if (not isDebug) {
			CAM->position.x = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), player->GetWorldPos(), 1.f).x, -(float)(TILESIZEX) / 2 + app.GetHalfWidth(), (float)(TILESIZEX) / 2 - app.GetHalfWidth());
			CAM->position.y = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), player->GetWorldPos(), 1.f).y, -(float)(TILESIZEY) / 2 + app.GetHalfHeight(), (float)(TILESIZEY) / 2 - app.GetHalfHeight());
		}

		Background->Update();
		if (player->hp > 0 and boss_first->hp > 0)
		{
			player->Control();
			Boss_Spawn_Time += DELTA;
			boss_first->Action(player, Boss_Spawn_Time);

			player->Update();
			boss_first->Update();
		}

	}

}

void Main::LateUpdate()
{
	if (scene == MS_MAIN)
	{
		if (startClick->Intersect(INPUT->GetWorldMousePos()))
		{
			startClick->color = Color(1.0f, 0, 0);
			if (INPUT->KeyUp(VK_LBUTTON))
			{
				scene = MS_START;
			}
		}
		else startClick->color = Color(1, 1, 1);
		if (finishClick->Intersect(INPUT->GetWorldMousePos()))
		{
			finishClick->color = Color(1.0f, 0, 0);
			if (INPUT->KeyUp(VK_LBUTTON))
			{
				PostQuitMessage(0);
			}
		}
		else finishClick->color = Color(1, 1, 1);
	}
	else if (scene == MS_START)
	{
		for (int i = 0; i < TILEY * TILEX; i++) {

			for (int k = 0; k < 7; k++) {
				if (boss_first->GetSword(k)->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL)
				{
					Tiles[0][i].img->color.x = 1.f;
					boss_first->GetSword(k)->Release();
				}

			}

			if (player->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_R) {
				player->SetWorldPosX(Tiles[0][i].rc->GetWorldPivot().x - Tiles[0][i].rc->scale.x - 5);
			}
			if (player->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_L) {
				player->SetWorldPosX(Tiles[0][i].rc->GetWorldPivot().x + Tiles[0][i].rc->scale.x + 5);
			}
			if (player->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_B) {
				player->SetWorldPosY(Tiles[0][i].rc->GetWorldPivot().y + Tiles[0][i].rc->scale.y + 3.f);
			}
			if (player->Intersect(Tiles[0][i].rc) && Tiles[0][i].terrain == TR_WALL_T) {
				player->SetWorldPosY(Tiles[0][i].rc->GetWorldPivot().y - Tiles[0][i].rc->scale.y - 5.f);
			}

			for (int k = 0; k < TILESTYLE; k++) {

				if (player->Intersect(Tiles[k][i].rc) && Tiles[k][i].terrain == TR_FLOOR) {
					player->SetWorldPosY(Tiles[k][i].rc->GetWorldPivot().y + Tiles[k][i].rc->scale.y - 5.f);
					Tiles[k][i].img->color.y = 1.f;
				}
				else {
					//player->isGravite = true;

					Tiles[k][i].img->color.x = 0.5f;
					Tiles[k][i].img->color.y = 0.5f;
					Tiles[k][i].img->color.z = 0.5f;
				}
			}
		}



		/** 플레이어 - 보스 패턴 충돌 (플레이어 hp 차감)*/
		if (not player->ishit)
		{
			/** 플레이어 - 검 충돌*/
			for (int i = 0; i < 7; i++)
			{
				if (boss_first->GetSword(i)->Intersect(player))
				{
					player->hp -= boss_first->GetDamage();
					player->ishit = true;
					break;
				}
			}
			/** 플레이어 - 구체 충돌*/
			for (int i = 0; i < 30; i++)
			{
				if (boss_first->GetSphereT(i)->Intersect(player))
				{
					player->hp -= boss_first->GetDamage();
					player->ishit = true;
					break;
				}
				if (boss_first->GetSphereB(i)->Intersect(player))
				{
					player->hp -= boss_first->GetDamage();
					player->ishit = true;
					break;
				}
				if (boss_first->GetSphereR(i)->Intersect(player))
				{
					player->hp -= boss_first->GetDamage();
					player->ishit = true;
					break;
				}
				if (boss_first->GetSphereL(i)->Intersect(player))
				{
					player->hp -= boss_first->GetDamage();
					player->ishit = true;
					break;
				}
			}
			/** 플레이어 - 레이저 충돌*/
			if (boss_first->GetLaser()->Intersect(player))
			{
				player->ishit = true;
				player->hp -= boss_first->GetDamage();
			}
		}
		/** 플레이어 총알 - 보스 충돌 (보스 hp 차감)*/
		if (not boss_first->ishit_B)
		{
			player->Collision(boss_first);
		}
	}
}

void Main::Render()
{

	if (scene == MS_MAIN)
	{
		if (b_mainLogo)
		{
			mainLogo_bg->Render();
			mainLogo->Render();
		}
		else
		{
			main->Render();
			startClick->Render();
			finishClick->Render();
		}
		if (TIMER->GetTick(mainTIme, 2.0f))
		{
			b_mainLogo = false;
		}
	}
	else if (scene == MS_START)
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
		if (player->hp > 0 and boss_first->hp > 0)
		{
			boss_first->Render();

			player->Render();
		}
	}
}
void Main::ResizeScreen()
{


}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game3");
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