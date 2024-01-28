#include "stdafx.h"

Dun_Laser::Dun_Laser()
{
	Img_laserFirst	= new ObImage(L"SkellBossLaserHead0.png");
	//Img_laserFirst->SetParentT(*this);
	Img_laserSecond	= new ObImage(L"SkellBossLaserBody0.png");
	//Img_laserSecond->SetParentT(*this);
	Img_laserThird	= new ObImage(L"SkellBossWeaponLaserHead0.png");
	//Img_laserThird->SetParentT(*this);


	scale.x = 0.0f;
	scale.y = 0.0f;
	delayTime = 1.0f;
	isFire = false;
	isturn = true;
	//if (isturn) pivot = OFFSET_R;
	//else pivot = OFFSET_L;
}

Dun_Laser::~Dun_Laser()
{
}

void Dun_Laser::Fire(Vector2 pos)
{
	//isturn = not isturn;	//Fire 함수 호출될때마다 손방향 바꾸기
	isturn = not isturn;

	lifeTime = 0.5f;
	delayTime = 1.0f;
	SetWorldPos(pos);
	scale.x = 1110.0f;
	scale.y = 50.0f;

	Img_laserFirst->SetWorldPos(Vector2(480.0f, pos.y));
	Img_laserSecond->SetWorldPos(Vector2(0.0f, pos.y));
	Img_laserThird->SetWorldPos(Vector2(-480.0f, pos.y));

	Img_laserFirst->scale.x = 150.0f;
	Img_laserFirst->scale.y = 200.0f;
	Img_laserSecond->scale.x = 810.0f;
	Img_laserSecond->scale.y = 200.0f;
	Img_laserThird->scale.x = 150.0f;
	Img_laserThird->scale.y = 200.0f;
	this->pressPower = pressPower;
	isFire = true;
}

void Dun_Laser::Update()
{
	ImGui::Text("Img_laserSecond pos.y = % d", (int)Img_laserSecond->GetWorldPos().y);
	ImGui::Text("delayTime = %.2f", delayTime);
	if (not isFire) return;
	//MoveWorldPos(GetUp() * 1500.0f * DELTA);

	ObRect::Update();
	Img_laserFirst	->Update();
	Img_laserSecond	->Update();
	Img_laserThird	->Update();
	
	//delayTime -= DELTA;
	//if (delayTime <= 0.0f)
	//{
	//	isturn = not isturn;
	//}

	lifeTime -= DELTA;
	if (lifeTime <= 0.0f)
	{
		isFire = false;
	}
}

void Dun_Laser::Render()
{
	if (not isFire) return;

	Img_laserFirst	->Render();
	Img_laserSecond	->Render();
	Img_laserThird	->Render();
	ObRect::Render();
}

bool Dun_Laser::Touch(GameObject* target)
{
	return false;
}
