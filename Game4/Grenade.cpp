#include "stdafx.h"
#include "Bullet.h"
#include "Grenade.h"

Grenade::Grenade()
{
    isFire = false;
    for (int i = 0; i < 36; i++) {
        bullet[i] = new Bullet(L"IceBullet.png");
    }
}

Grenade::~Grenade()
{
    
}

void Grenade::Explosion(Vector2 pos, int Length, float speed)
{
    for (int i = 0; i < 36; i++) {
        bullet[i]->Fire(pos, Vector2(cosf((i * 10) * ToRadian), sinf((i * 10) * ToRadian)), speed);
    }
}

void Grenade::Update()
{
    for (int i = 0; i < 36; i++) {
        bullet[i]->Update();
    }
}

void Grenade::Render()
{
    for (int i = 0; i < 36; i++) {
        bullet[i]->Render();
    }
}
