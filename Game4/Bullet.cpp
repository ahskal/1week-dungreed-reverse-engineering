#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	scale.x = 20.0f;
	scale.y = 20.0f;
	isFire = false;
	pivot = OFFSET_L;

	img = nullptr;
	hasImage = false;
	isGravite = false;
}

Bullet::Bullet(wstring imgAddr)
{
	img = new ObImage(imgAddr);
	isFire = false;
	pivot = OFFSET_N;
	hasImage = true;
	isFilled = false;
	hasAxis = false;
}

Bullet::~Bullet()
{
	delete img;
}
void Bullet::Fire(Vector2 pos, Vector2 dir, float pressPower) {
	
	this->scale.x = 30.f;
	this->scale.y = 30.f;

	this->pressPower = pressPower;
	SetWorldPos(pos);
	//fireDir = shooter->GetRight();
	rotation.z = atan2(dir.y, dir.x);

	if (hasImage) {
		this->scale.x = img->imageSize.x * 1.5f + 10;
		this->scale.y = img->imageSize.y * 1.5f + 10;
		img->scale.x = img->imageSize.x * 1.5f;
		img->scale.y = img->imageSize.y * 1.5f;

		img->rotation.z = atan2f(dir.y, dir.x);
		img->SetWorldPos(pos);
	}

	isFire = true;


}
void Bullet::Fire(Vector2 pos, Vector2 pos2, Vector2 scale, float pressPower, bool gravite)
{
	this->scale.x = 30.f;
	this->scale.y = 30.f;

	this->pressPower = pressPower;
	Distance = pos2 - pos;
	rotation.z = atan2f(Distance.y, Distance.x);
	isGravite = gravite;
	SetWorldPos(pos);
	if (hasImage) {
		this->scale.x = img->imageSize.x * scale.x + 10;
		this->scale.y = img->imageSize.y * scale.y + 10;
		img->scale.x = img->imageSize.x * scale.x;
		img->scale.y = img->imageSize.y * scale.y;

		img->rotation.z = atan2f(Distance.y, Distance.x);
		img->SetWorldPos(pos);
	}

	isFire = true;
}

void Bullet::Drop(Vector2 pos, Vector2 scale, float pressPower, bool gravite)
{
	if (hasImage) {
		this->scale.x = img->imageSize.x * scale.x + 10;
		this->scale.y = img->imageSize.y * scale.y + 10;
		img->scale.x = img->imageSize.x * scale.x;
		img->scale.y = img->imageSize.y * scale.y;

		img->rotation.z = atan2f(DOWN.y, DOWN.x);
		img->SetWorldPos(pos);
	}

	isGravite = gravite;
	this->pressPower = pressPower;
	rotation.z = atan2f(DOWN.y, DOWN.x);

	SetWorldPos(pos);

	isFire = true;
}



//void Bullet::Fire(GameObject* shooter, float pressPower)
//{
//    lifeTime = 10.0f;
//    scale.x = pressPower * 0.1f;
//    scale.y = scale.x * 0.2f;
//    isFire = true;
//    SetWorldPos(shooter->GetWorldPos());
//
//    this->pressPower = pressPower;
//    fireDir = shooter->GetRight();
//
//    gravityDir = DOWN;
//    gravityForce = 0.0f;
//
//
//    fireDir = shooter->GetRight();
//    rotation.z = atan2f(shooter->GetRight().y, shooter->GetRight().x);
//}
//
//void Bullet::Fire(Vector2 pos, Vector2 dir, float pressPower)
//{
//    lifeTime = 10.0f;
//    scale.x = 20;
//    scale.y = 5;
//    this->pressPower = pressPower;
//    isFire = true;
//    SetWorldPos(pos);
//    fireDir = shooter->GetRight();
//    rotation.z = atan2f(dir.y, dir.x);
//}
//
//void Bullet::Drop(Vector2 pos)
//{
//    lifeTime = 30.0f;
//    scale.x = 20;
//    scale.y = 5;
//    isFire = true;
//    SetWorldPos(pos);
//
//    쏘는힘 나아갈방향
//    this->pressPower = 0.0f;
//    fireDir = Vector2(0, 0);
//
//    gravityDir = DOWN;
//    gravityForce = 0.0f;
//    rotation.z = atan2f(DOWN.y, DOWN.x);
//}

void Bullet::Update()
{
	if (not isFire) return;
	if (isGravite)
	{
		gravityForce += 500.0f * DELTA;

		Vector2 velocity = (fireDir * pressPower
			+ gravityDir * gravityForce);
		MoveWorldPos(velocity * DELTA);
		rotation.z = atan2f(velocity.y, velocity.x);

	}
	else {
		Vector2 velocity = (fireDir * pressPower);
		MoveWorldPos(GetRight() * DELTA * pressPower);
		if (hasImage)
			img->MoveWorldPos(img->GetRight() * DELTA * pressPower);
	}



	ObRect::Update();
	if (hasImage)
		img->Update();
	//lifeTime -= DELTA;
	//if (lifeTime <= 0.0f)
	//{
	//    isFire = false;
	//}


	//이동후 화면 벗어남 체크
	/*if (0.0f > GetWorldPos().x or GetWorldPos().x > 800.0f or
		0.0f > GetWorldPos().y or GetWorldPos().y > 600.0f)
	{
		isFire = false;
	}*/
}

void Bullet::Render()
{
	if (not isFire) return;

	ObRect::Render();
	if (hasImage)
		img->Render();
}

bool Bullet::Touch(GameObject* target)
{
	if ((GetWorldPos() - target->GetWorldPos()).Length() <
		7 + target->scale.x * 0.5f)
	{
		return true;
	}

	return false;
}

void Bullet::ChangeImg(wstring file)
{
	img->ChangeImg(file);
}
