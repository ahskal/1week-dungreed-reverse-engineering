#include "stdafx.h"

Dun_Sphere::Dun_Sphere()
{
	Img_sphere = new ObImage(L"BossBullet001.png");
	Img_sphere->SetParentRT(*this);

	scale.x = 0.0f;
	scale.y = 0.0f;
	isFire = false;
	//hasAxis = true;
}

Dun_Sphere::~Dun_Sphere()
{
}

void Dun_Sphere::Fire(Vector2 pos, Vector2 dir, float pressPower)
{
	lifeTime = 3.0f;
	scale.x = 50.0f;
	scale.y = 50.0f;

	Img_sphere->scale.x = 50.0f;
	Img_sphere->scale.y = 50.0f;

	this->pressPower = pressPower;
	isFire = true;
	SetWorldPos(pos);
	//fireDir = shooter->GetRight();
	rotation.z = atan2f(dir.y, dir.x);
}

void Dun_Sphere::Update()
{
	if (not isFire) return;
	MoveWorldPos(GetUp() * pressPower * DELTA);

	ObCircle::Update();
	Img_sphere->Update();

	lifeTime -= DELTA;
	if (lifeTime <= 0.0f)
	{
		isFire = false;
	}
}

void Dun_Sphere::Render()
{
	if (not isFire) return;

	ObCircle::Render();
	Img_sphere->Render();
}

bool Dun_Sphere::Touch(GameObject* target)
{
	return false;
}
