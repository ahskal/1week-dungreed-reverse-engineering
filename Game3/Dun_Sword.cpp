#include "stdafx.h"

/*
Bullet_Dun::Bullet_Dun()
{
	Im_sword = new ObImage(L"BossSword.png");
	Im_sword->SetParentRT(*this);

	isFilled = false;
	scale.x = 0.0f;
	scale.y = 0.0f;
	isFire = false;
	hasAxis = true;
}

Bullet_Dun::~Bullet_Dun()
{
}

void Bullet_Dun::Init(GameObject* player, int i)
{
	//fireDir = player->GetWorldPos() - GetWorldPos();
	//rotation.z = atan2f(fireDir.y, fireDir.x);
	//lifeTime = 2.5f;
	//scale.x = 35.0f;
	//scale.y = 400.0f;
	//
	//Im_sword->scale.x = 35.0f;
	//Im_sword->scale.y = 400.0f;
	//isFire = true;
	//SetWorldPos(Vector2((-300.0f + i * 100), 450.0f));
	//fireDir = player->GetWorldPos() - GetWorldPos();
	lifeTime = 2.5f;
	scale.x = 35.0f;
	scale.y = 400.0f;

	Im_sword->scale.x = 100.0f;
	Im_sword->scale.y = 400.0f;
	fireDir = DOWN;
	rotation.z = atan2f(fireDir.y, fireDir.x);
}

void Bullet_Dun::Fire(GameObject* player, int i)
{
	//if (isFire == false) return;
	//rotation.z = atan2f(fireDir.y, fireDir.x);
	//fireDir = player->GetWorldPos() - GetWorldPos();

	lifeTime = 2.5f;
	scale.x = 35.0f;
	scale.y = 400.0f;
	
	Im_sword->scale.x = 100.0f;
	Im_sword->scale.y = 400.0f;
	isFire = true;
	SetWorldPos(Vector2((-300.0f + i * 100), 450.0f));
	fireDir = player->GetWorldPos() - GetWorldPos();
	
	//rotation.z = atan2f(fireDir.y, fireDir.x);
	//MoveWorldPos(GetUp() * DELTA);
	//
	//lifeTime -= DELTA;
	//if (lifeTime <= 0.0f)
	//{
	//	isFire = false;
	//}
}

void Bullet_Dun::Move(GameObject* player, int i)
{
	if (isFire == false) return;

	rotation.z = atan2f(fireDir.y, fireDir.x) + PI * 0.5f;
	MoveWorldPos(GetUp() * DELTA * 1000.0f);
}

void Bullet_Dun::Update()
{
	ObRect::Update();

	Im_sword->Update();

	lifeTime -= DELTA;
	if (lifeTime <= 0.0f)
	{
		isFire = false;
	}
}

void Bullet_Dun::Render()
{
	if (not isFire) return;

	ObRect::Render();
	Im_sword->Render();
}

bool Bullet_Dun::Touch(GameObject* target)
{
	return false;
}*/

Dun_Sword::Dun_Sword()
{
	Img_sword = new ObImage(L"BossSword.png");
	Img_sword->SetParentRT(*this);

	scale.x = 0.0f;
	scale.y = 0.0f;
	isFire = false;
	hasAxis = false;
	//pivot = OFFSET_L;
}

Dun_Sword::~Dun_Sword()
{
}

void Dun_Sword::Fire(Vector2 pos, Vector2 dir, float pressPower)
{
	lifeTime = 3.0f;
	scale.x = 35.0f;
	scale.y = 300.0f;

	Img_sword->scale.x = 100.0f;
	Img_sword->scale.y = 300.0f;
	this->pressPower = pressPower;
	isFire = true;
	SetWorldPos(pos);
	//fireDir = shooter->GetRight();
	rotation.z = atan2f(dir.y, dir.x) + PI * 1.5f;
}

void Dun_Sword::Update()
{
	if (not isFire) return;
	MoveWorldPos(GetUp() * pressPower * DELTA);

	ObRect::Update();
	Img_sword->Update();

	lifeTime -= DELTA;
	if (lifeTime <= 0.0f)
	{
		isFire = false;
	}
}

void Dun_Sword::Render()
{
	if (not isFire) return;

	ObRect::Render();
	Img_sword->Render();
}

bool Dun_Sword::Touch(GameObject* target)
{
	if ((GetWorldPos() - target->GetWorldPos()).Length() <
		7 + target->scale.x * 0.5f)
	{
		return true;
	}

	return false;
}
