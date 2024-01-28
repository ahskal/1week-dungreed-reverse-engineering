#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	player = new Player();
	player->p = new ObRect();
	player->isGravite = true;
	player->isJump = false;


	isDebug = true;;


	player->Gravite = 10.f;

	imgAddr = L"Tile_NONE.png";

	Background = new ObImage(L"BGLayer_0 #225474.png");
	Background->scale.x = TILESIZEX;
	Background->scale.y = TILESIZEY;

	//=====================================================================================================
	if (isDebug) {
		sampleTileRect = new ObRect();
		sampleTileRect->pivot = OFFSET_LB;

		sampleTileRect->scale = Vector2(SAMPLETILEX * SAMPLETILESIZE + SAMPLETILESIZE, SAMPLETILEY * SAMPLETILESIZE + (SAMPLETILESIZE / 4 * SAMPLETILEY));

		sampleTileRect->SetWorldPosX(app.GetHalfWidth() - sampleTileRect->scale.x);
		sampleTileRect->SetWorldPosY(app.GetHalfHeight() - sampleTileRect->scale.y);
		sampleTileRect->isFilled = false;

		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				int index = i * SAMPLETILEX + j;
				for (int k = 0; k < SAMPLELIST; k++)
				{
					SampleTiles[k][index] = new SampleTile;
					SampleTiles[k][index]->rcTile = new ObRect();

					if (k == 0)
					{
						if (index < 9)
						{
							wstring message_w = to_wstring(index) + wstring(L".png");
							SampleTiles[k][index]->imgAddr = L"Tile_BG" + message_w;
							SampleTiles[k][index]->sample = new ObImage(SampleTiles[k][index]->imgAddr);
						}
						else if (index < 31)
						{
							wstring message_w = to_wstring(index - 9) + wstring(L".png");
							SampleTiles[k][index]->imgAddr = L"Tile_W" + message_w;
							SampleTiles[k][index]->sample = new ObImage(SampleTiles[k][index]->imgAddr);
						}
						else
						{
							SampleTiles[k][index]->imgAddr = L"Tile_NONE.png";
							SampleTiles[k][index]->sample = new ObImage(SampleTiles[k][index]->imgAddr);
						}
					}
					else
					{
						if (index < 9)
						{
							wstring message_w = to_wstring(index) + wstring(L".png");
							SampleTiles[k][index]->imgAddr = L"TIle_Ice_BG" + message_w;
							SampleTiles[k][index]->sample = new ObImage(SampleTiles[k][index]->imgAddr);
						}
						else if (index < 30)
						{
							wstring message_w = to_wstring(index - 9) + wstring(L".png");
							SampleTiles[k][index]->imgAddr = L"Tile_Ice_W" + message_w;
							SampleTiles[k][index]->sample = new ObImage(SampleTiles[k][index]->imgAddr);
						}
						else
						{
							SampleTiles[k][index]->imgAddr = L"Tile_NONE.png";
							SampleTiles[k][index]->sample = new ObImage(SampleTiles[k][index]->imgAddr);
						}
					}
					SampleTiles[k][index]->rcTile->scale = Vector2(SAMPLETILESIZE, SAMPLETILESIZE);
					SampleTiles[k][index]->rcTile->SetParentRT(*sampleTileRect);

					SampleTiles[k][index]->rcTile->SetLocalPosX(8 + SAMPLETILESIZE / 2 + (j * SAMPLETILESIZE) + (j * SAMPLETILESIZE / 4));
					SampleTiles[k][index]->rcTile->SetLocalPosY(sampleTileRect->scale.y - 8 - SAMPLETILESIZE / 2 - (i * SAMPLETILESIZE) - (i * SAMPLETILESIZE / 4));

					SampleTiles[k][index]->sample->scale = SampleTiles[k][index]->rcTile->scale;
					SampleTiles[k][index]->sample->SetParentRT(*SampleTiles[k][index]->rcTile);
				}
			}
		}
	}
	//=====================================================================================================
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


}

Main::~Main()
{
}
void Main::save()
{
	ofstream fout;
	string file = "TileMap2.map";

	fout.open(file.c_str(), ios::out);
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			int index = i * TILEX + j;
			string temp;
			temp.assign(Tiles[0][index].imgAddr.begin(), Tiles[0][index].imgAddr.end());

			
			if (temp.find("W18") != string::npos ||
				temp.find("W19") != string::npos ||
				temp.find("W20") != string::npos) {
				Tiles[0][index].terrain = TR_FLOOR;
			}
			else if (temp.find("W21") != string::npos or
				temp.find("Ice_W16") != string::npos) {
				Tiles[0][index].terrain = TR_WALL_B;
			}
			else if (temp.find("W10") != string::npos) {
				Tiles[0][index].terrain = TR_WALL_T;
			}
			else if (temp.find("W12") != string::npos) {
				Tiles[0][index].terrain = TR_WALL_L;
			}
			else if (temp.find("W14") != string::npos) {
				Tiles[0][index].terrain = TR_WALL_R;
			}
			else if (temp.find("W") != string::npos) {
				Tiles[0][index].terrain = TR_WALL;
			}
			else if (temp.find("BG") != string::npos) {
				Tiles[0][index].terrain = TR_BG;
			}
			else {
				Tiles[0][index].terrain = TR_NONE;
			}
			if (fout.is_open())
			{
				string Addr;
				Addr.assign(Tiles[0][index].imgAddr.begin(), Tiles[0][index].imgAddr.end());
				fout << Addr << " " << Tiles[0][index].terrain << endl;
			}
		}
	}
	fout.close();

	string file2 = "TileMap2.Object";
	fout.open(file2.c_str(), ios::out);
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			int index = i * TILEX + j;
			string temp;
			temp.assign(Tiles[1][index].imgAddr.begin(), Tiles[1][index].imgAddr.end());

			if (temp.find("W18") != string::npos ||
				temp.find("W19") != string::npos ||
				temp.find("W20") != string::npos) {
				Tiles[1][index].terrain = TR_FLOOR;
			}
			else {
				Tiles[1][index].terrain = TR_NONE;
			}
			if (fout.is_open())
			{
				string Addr;
				Addr.assign(Tiles[1][index].imgAddr.begin(), Tiles[1][index].imgAddr.end());
				fout << Addr << " " << Tiles[1][index].terrain << endl;
			}
		}
	}
	fout.close();
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
	//=====================================================================================================
	if (isDebug) {

	}
	//=====================================================================================================


	player->p->scale.x = TILESIZE;
	player->p->scale.y = TILESIZE;


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
	ImGui::Text("player Pos: (%.2f, %.2f)", player->p->GetWorldPivot().x, player->p->GetWorldPivot().y);
	//=====================================================================================================
	if (isDebug) {
		ImGui::Text("sample Pos: (%.2f, %.2f)", sampleTileRect->GetWorldPos().x, sampleTileRect->GetWorldPos().y);
		ImGui::Text("sampleType  Pos: %d", SampleType);
		ImGui::Text("sampleStyle Pos: %d", TileStyle);

		if (ImGui::Button("SAVE", ImVec2(50, 50))) {
			save();
		}
		if (ImGui::Button("LOAD", ImVec2(50, 50))) {
			load();
		}

		if (ImGui::Button("TYPE1", ImVec2(100, 50))) {
			SampleType = 0;
		}
		if (ImGui::Button("TYPE2", ImVec2(100, 50))) {
			SampleType = 1;
		}
		if (ImGui::Button("Style1", ImVec2(100, 50))) {
			TileStyle = 0;
		}
		if (ImGui::Button("Style2", ImVec2(100, 50))) {
			TileStyle = 1;
		}

		sampleTileRect->Update();

		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				int index = i * SAMPLETILEX + j;
				for (int k = 0; k < SAMPLELIST; k++)
				{
					//타일 크기 설정
					SampleTiles[k][index]->rcTile->Update();
					SampleTiles[k][index]->sample->Update();
				}
			}
		}
		if (INPUT->KeyPress(VK_LEFT)) {
			CAM->position.x -= 300.f * DELTA;
			sampleTileRect->SetWorldPosX(CAM->position.x + (app.GetHalfWidth() - sampleTileRect->scale.x));
		}
		if (INPUT->KeyPress(VK_RIGHT)) {
			CAM->position.x += 300.f * DELTA;
			sampleTileRect->SetWorldPosX(CAM->position.x + (app.GetHalfWidth() - sampleTileRect->scale.x));
		}
		if (INPUT->KeyPress(VK_UP)) {
			CAM->position.y += 300.f * DELTA;
			sampleTileRect->SetWorldPosY(CAM->position.y + (app.GetHalfHeight() - sampleTileRect->scale.y));
		}
		if (INPUT->KeyPress(VK_DOWN)) {
			CAM->position.y -= 300.f * DELTA;
			sampleTileRect->SetWorldPosY(CAM->position.y + (app.GetHalfHeight() - sampleTileRect->scale.y));
		}
	}
	//=====================================================================================================
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			int index = i * TILEX + j;
			Tiles[0][index].rc->Update();
			Tiles[0][index].img->Update();
			Tiles[1][index].rc->Update();
			Tiles[1][index].img->Update();
		}
	}
	if (not isDebug) {
		CAM->position.x = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), player->p->GetWorldPos(), 1.f).x, -(float)(TILESIZEX) / 2 + app.GetHalfWidth(), (float)(TILESIZEX) / 2 - app.GetHalfWidth());
		CAM->position.y = Utility::Saturate(Vector2::Lerp(Vector2(CAM->position.x, CAM->position.y), player->p->GetWorldPos(), 1.f).y, -(float)(TILESIZEY) / 2 + app.GetHalfHeight(), (float)(TILESIZEY) / 2 - app.GetHalfHeight());
	}

	if (INPUT->KeyPress('W')) {
		player->p->MoveWorldPos(UP * 300.f * DELTA);

	}
	if (INPUT->KeyPress('S')) {
		player->p->MoveWorldPos(DOWN * 300.f * DELTA);

	}
	if (INPUT->KeyPress('A')) {
		player->p->MoveWorldPos(LEFT * 300.f * DELTA);

	}
	if (INPUT->KeyPress('D')) {
		player->p->MoveWorldPos(RIGHT * 300.f * DELTA);

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
	player->p->Update();
	Background->Update();

}

void Main::LateUpdate()
{
	if (isDebug) {
		Vector2 mousePos = Vector2(INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y);
		for (int i = 0; i < SAMPLETILEY; i++) {
			for (int j = 0; j < SAMPLETILEX; j++) {
				int index = i * SAMPLETILEX + j;
				if (SampleTiles[SampleType][index]->rcTile->Intersect(mousePos)) {
					if (INPUT->KeyDown(VK_LBUTTON)) {
						imgAddr = SampleTiles[SampleType][index]->imgAddr;
					}
				}
			}
		}

		for (int i = 0; i < TILEY; i++) {
			for (int j = 0; j < TILEX; j++) {
				int index = i * TILEX + j;
				for (int k = 0; k < TILESTYLE; k++) {
					if (Tiles[k][index].rc->Intersect(mousePos)) {
						if (INPUT->KeyPress(VK_LBUTTON)) {
							Tiles[TileStyle][index].imgAddr = imgAddr;
							Tiles[TileStyle][index].img->ChangeImg(imgAddr);
						}
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < TILEY * TILEX; i++) {
			for (int k = 0; k < TILESTYLE; k++) {

	

				if (player->p->Intersect(Tiles[k][i].rc) && Tiles[k][i].terrain == TR_WALL) {
					Tiles[k][i].img->color.x = 1.f;
					player->p->SetWorldPosY(Tiles[k][i].rc->GetWorldPivot().y + Tiles[k][i].rc->scale.y);
					player->isGravite = false;
					player->Gravite = 10.f;
					player->isJump = false;
					
				}

				else if (player->jumpPower < -1 &&player->p->Intersect(Tiles[k][i].rc) && Tiles[k][i].terrain == TR_FLOOR) {
					Tiles[k][i].img->color.y = 1.f;
					player->p->SetWorldPosY(Tiles[k][i].rc->GetWorldPivot().y + Tiles[k][i].rc->scale.y);
					player->isGravite = false;
					player->Gravite = 10.f;
					player->isJump = false;
					Tiles[k][i].img->color.y = 1.f;
				}
				else {
					player->isGravite = true;

					Tiles[k][i].img->color.x = 0.5f;
					Tiles[k][i].img->color.y = 0.5f;
					Tiles[k][i].img->color.z = 0.5f;
				}
			}
		}

	}



}

void Main::Render()
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
	player->p->Render();

	//=====================================================================================================
	if (isDebug) {
		sampleTileRect->Render();
		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				int index = i * SAMPLETILEX + j;
				//타일 크기 설정
				//SampleTiles[SampleType][index]->rcTile->Render();
				SampleTiles[SampleType][index]->sample->Render();
			}
		}
	}
	//=====================================================================================================

}

void Main::ResizeScreen()
{


}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.0f, 800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}