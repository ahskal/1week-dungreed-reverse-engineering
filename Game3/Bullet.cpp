#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
    scale.x = 20.0f;
    scale.y = 4.0f;
    isFire = false;
    pivot = OFFSET_L;
}

Bullet::~Bullet()
{
}

void Bullet::Fire(GameObject* shooter, float pressPower)
{
    lifeTime = 3.0f;

    isFire = true;
    SetWorldPos(shooter->GetWorldPos());

    this->pressPower = pressPower;
    fireDir = shooter->GetRight();

    gravityDir = DOWN;
    gravityForce = 0.0f;



}

void Bullet::Fire(Vector2 pos, Vector2 dir, float pressPower)
{
    lifeTime = 3.0f;

    this->pressPower = pressPower;
    isFire = true;
    SetWorldPos(pos);

    rotation.z = atan2f(dir.y, dir.x);
}

void Bullet::Drop(Vector2 pos)
{
    lifeTime = 30.0f;

    isFire = true;
    SetWorldPos(pos);

    //쏘는힘 나아갈방향
    this->pressPower = 0.0f;
    fireDir = Vector2(0, 0);

    gravityDir = DOWN;
    gravityForce = 0.0f;

}

void Bullet::Update()
{
    if (not isFire)
    {
        SetWorldPos(Vector2(-10000.0f, -10000.0f));
    }


    MoveWorldPos(fireDir * DELTA * pressPower);
    rotation.z = atan2f(fireDir.y, fireDir.x);






    //포물선  
    // 
    // gravityForce += 500.0f * DELTA;
    //
    //Vector2 velocity = (fireDir * pressPower
    //    + gravityDir * gravityForce);
    //MoveWorldPos(velocity * DELTA);
    //
    //


    ObRect::Update();

    lifeTime -= DELTA;
    if (lifeTime <= 0.0f)
    {
        isFire = false;
    }


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
