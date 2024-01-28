#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"

Player::Player()
{
	hasAxis = true;

	Img = new ObImage(L"TAANA0.png");
	Img->SetParentT(*this);

	bullets = new Bullet * [3];
	bulletAS = new float[3];

	bullets[0] = new Bullet[BULLETMAX1];
	bullets[1] = new Bullet[BULLETMAX2];
	bullets[2] = new Bullet[BULLETMAX3];

	for (int i = 0; i < 3; i++) {
		bulletAS[i] = 0;
	}

	for (int i = 0; i < 200; i++)
	{
		bullets[1][i].scale.x = 20.0f;
		bullets[1][i].scale.y = 10.0f;
	}

	for (int i = 0; i < 10; i++)
	{
		bullets[2][i].scale.x = 50.0f;
		bullets[2][i].scale.y = 40.0f;
	}

	gauge = new ObRect();
	gauge->SetParentT(*this);
	gauge->pivot = OFFSET_L;
	gauge->rotation.z = 90.0f * ToRadian;
	gauge->SetLocalPosY(-10.0f);
	gauge->SetLocalPosX(-50.0f);
	gauge->scale.y = 5.0f;


	gauge2 = new ObRect();
	gauge2->SetParentT(*this);
	gauge2->pivot = OFFSET_L;
	gauge2->rotation.z = 90.0f * ToRadian;
	gauge2->SetLocalPosY(-10.0f);
	gauge2->SetLocalPosX(-55.0f);
	gauge2->scale.y = 5.0f;


	for (int i = 0; i < 4; i++)
	{
		guard[i] = new ObRect();
		guard[i]->SetParentT(*this);
		guard[i]->scale.x = 15.0f;
		guard[i]->scale.y = 15.0f;
	}
	guard[0]->SetLocalPosX(70.0f);
	guard[1]->SetLocalPosX(-70.0f);
	guard[2]->SetLocalPosY(-70.0f);
	guard[3]->SetLocalPosY(70.0f);

	weapon = new ObRect();
	weapon->SetParentRT(*this);
	weapon->isVisible = false;
	weapon->scale.x = 10.0f;
	weapon->scale.y = 120.0f;
	weapon->SetWorldPos(GetWorldPos());
	weapon->SetLocalPosX(20.0f);
	weapon->SetLocalPosY(0.0f);

	weapon2 = new ObRect();
	weapon2->SetParentT(*this);
	weapon2->isVisible = false;
	weapon2->scale.x = 20.0f;
	weapon2->scale.y = 100.0f;
	weapon2->SetWorldPos(GetWorldPos());
	weapon2->SetLocalPosX(35.0f);
	weapon2->SetLocalPosY(35.0f);



	for (int i = 0; i < 4; i++)
	{
		touchOb[i] = new ObRect();
		touchOb[i]->SetParentT(*this);
		touchOb[i]->scale.x = 20.0f;
		touchOb[i]->scale.y = 20.0f;
	}

	touchOb[0]->SetLocalPosX(45.0f);
	touchOb[1]->SetLocalPosX(-45.0f);
	touchOb[2]->SetLocalPosY(-45.0f);
	touchOb[3]->SetLocalPosY(45.0f);

}

Player::~Player()
{
	delete gauge;
	delete gauge2;
	delete weapon;
	delete weapon2;
	for (int i = 0; i < 4; i++)
	{
		delete guard[i];
	}
	for (int i = 0; i < 4; i++)
	{
		delete touchOb[i];
	}
}

void Player::Init(Vector2 spawn)
{
	SetWorldPosX(spawn.x);
	SetWorldPosY(spawn.y);

	scale.x = 48.f;
	scale.y = 48.f;


	Img->scale.x = scale.x;
	Img->scale.y = scale.y;
}

void Player::Control()
{
	// 스택 표기
	ImGui::Text("\n\n\t<<PLAYER>>\n");
	ImGui::Text("player Hp\t\t= %d", hp);
	ImGui::Text("player Damage\t= %d", damage);
	ImGui::Text("\ndashStacks\t\t = %d", dashStacks);

	switch (BulletType)
	{
	case 0:
		damage = 10; break;
	case 1:
		damage = 3; break;
	case 2:
		damage = 30; break;
	default:
		damage = 0; break;
	}

	rotation.z = Utility::DirToRadian(INPUT->GetWorldMousePos() - GetWorldPos());
	//컨트롤 =====================================================================
	{
		if (INPUT->KeyUp('1'))
		{
			BulletType = 0;
		}
		if (INPUT->KeyUp('2'))
		{
			BulletType = 1;
		}
		if (INPUT->KeyUp('3'))
		{
			BulletType = 2;
		}
		if (INPUT->KeyPress('A'))
		{
			MoveWorldPos(LEFT * DELTA * 300);
		}
		if (INPUT->KeyPress('D'))
		{
			MoveWorldPos(RIGHT * DELTA * 300);
		}

		if (INPUT->KeyPress(MK_LBUTTON))
		{

			switch (BulletType) {
			case 0:
				if (TIMER->GetTick(bulletAS[0], 0.4f)) {
					for (int i = 0; i < BULLETMAX1; i++) {
						if (bullets[BulletType][i].GetIsFire()) continue;
						bullets[BulletType][i].Fire(this, pressPower);
						break;
					}
				}break;
			case 1:
				if (TIMER->GetTick(bulletAS[1], 0.2f)) {
					for (int i = 0; i < BULLETMAX2; i++) {
						if (bullets[BulletType][i].GetIsFire()) continue;
						bullets[BulletType][i].Fire(this, pressPower);
						break;
					}
				}break;
			case 2:
				if (TIMER->GetTick(bulletAS[2], 0.5f)) {
					for (int i = 0; i < BULLETMAX3; i++) {
						if (bullets[BulletType][i].GetIsFire()) continue;
						bullets[BulletType][i].Fire(this, pressPower);
						break;
					}
				}break;
			default: break;
			}
		}

		if (INPUT->KeyDown('Q'))
		{
			BulletType = 3;
			isWeaponType1 = false;
			isWeaponType2 = true;
			weapon->isVisible = false;
			weapon2->isVisible = true;
		}

		else if (INPUT->KeyDown('E'))
		{
			BulletType = 3;

			isWeaponType1 = true;
			isWeaponType2 = false;
			weapon->isVisible = true;
			weapon2->isVisible = false;

		}

		//점프
		if (INPUT->KeyDown(VK_SPACE) or INPUT->KeyPress('W'))
		{
			if (not this->GetIsJump() or !isColliding)
			{

				this->Jump(this, UP, JumpPower);
			}
		}
		if (INPUT->KeyPress('S'))
		{
			if (INPUT->KeyDown(VK_SPACE))
			{
				this->downJump(JumpGravityForce);
			}
		}
		if (isWeaponType1 && INPUT->KeyPress(MK_LBUTTON))
		{
			float swingAngle = 20.0f; // 무기 회전

			weapon->rotation.z += swingAngle * DELTA;

		}
	}
	//컨트롤 =====================================================================

	gauge->scale.x = dashStacks * 9.0f;
	gauge2->scale.x = GuardCoolTime * 0.227;

	if (GuardCoolTime >= 199.0f && INPUT->KeyPress(VK_LSHIFT))
	{
		hasGuard = true;
	}
	else if (GuardCoolTime <= 10.0f)  hasGuard = false;

	if (hasGuard)
	{
		const float GUARD_COOLDOWN_RATE = 30.0f;
		GuardCoolTime -= GUARD_COOLDOWN_RATE * DELTA;
		GuardCoolTime = max(GuardCoolTime, 0.0f);
		guard[0]->isVisible = true;
		guard[1]->isVisible = true;
		guard[2]->isVisible = true;
		guard[3]->isVisible = true;
		gauge2->color.x = 0.9f;
		gauge2->color.y = 0.0f;


	}

	else
	{
		guard[0]->isVisible = false;
		guard[1]->isVisible = false;
		guard[2]->isVisible = false;
		guard[3]->isVisible = false;
		GuardCoolTime += 10.0f * DELTA;
		GuardCoolTime = min(GuardCoolTime, 200.0f);
		if (GuardCoolTime == 200.0f)
		{
			gauge2->color.x = 0.0f;
			gauge2->color.y = 0.9f;
		}
	}

	// 대쉬    스택3개   일정시간뒤에 스택 추가
	// 중력가속도 중력수치 조정 필요 
	//KeyDown이 아니라 KeyPress 하면 부드러운 이동이 가능하나 스택-- (하나씩 감소) 가 안되서 다운으로 바꿈
	//가능하면 KeyPress의 스택방식으로 만들 예정.

	if (INPUT->KeyDown(MK_RBUTTON)) {
		if (dashStacks > 0) {
			isDash = true;

			dashStacks--;
		}
		else isDash = false;

		if (isDash) {

			this->Dash(this, GetRight());


			dash = max(dashStacks, 0.0f);
		}
	}

	dashStacks = min(dashStacks, DeshMaxGauge);

	dashRecoverTime += DELTA;
	if (dashRecoverTime >= 1.0f) {
		dashRecoverTime -= 1.0f;
		recoverDash();
	}
}

void Player::Jump(Vector2 pos, Vector2 dir, float Power)
{
	this->JumpPower = Power;
	isDownJump = false;
	isJump = true;
	SetWorldPos(pos);
	rotation.z = atan2f(dir.y, dir.x);

}

void Player::Jump(GameObject* Player, Vector2 dir, float Power)
{
	isJump = true;
	isDownJump = false;
	SetWorldPos(GetWorldPos());

	this->JumpPower = Power;
	JumpDir = UP;
	JumpGravityDir = DOWN;
	JumpGravityForce = 10.0f;

}

void Player::downJump(float Power)
{
	isDownJump = true;
	isJump = true;
	this->JumpPower = Power;
	JumpDir = DOWN;
	JumpGravityDir = DOWN;
	JumpGravityForce = -30.0f;

	Vector2 newPosition = GetWorldPos() + Vector2(0.0f, -100.0f);

	SetWorldPos(newPosition);


}

void Player::Dash(GameObject* Player, Vector2 dir)
{

	isDash = true;

	const float DashDistance = 250.0f; // 대쉬로 이동할 거리

	SetWorldPos(GetWorldPos());

	MoveWorldPos(dir * DashDistance);

	JumpGravityDir = DOWN;
	JumpGravityForce = 500;
	JumpPower = 700;

	isJump = true;

}

void Player::recoverDash()
{
	dashStacks++;
}

void Player::Collision(Dun_Boss* boss)
{
	for (int i = 0; i < BULLETMAX1; i++)
	{
		if (bullets[0][i].Intersect(boss->GetBoss()))
		{
			bullets[0][i].Release();
			boss->hp -= damage;
			boss->ishit_B = true;
		}
	}
	for (int i = 0; i < BULLETMAX2; i++)
	{
		if (bullets[1][i].Intersect(boss->GetBoss()))
		{
			bullets[1][i].Release();
			boss->hp -= damage;
			boss->ishit_B = true;
		}
	}

	for (int i = 0; i < BULLETMAX3; i++)
	{
		if (bullets[2][i].Intersect(boss->GetBoss()))
		{
			bullets[2][i].Release();
			boss->hp -= damage;
			boss->ishit_B = true;
		}
	}
}


void Player::Update()
{
	ObRect::Update();
	gauge->Update();
	gauge2->Update();
	weapon->Update();
	weapon2->Update();
	Img->Update();

	for (int j = 0; j < BULLETMAX1; j++) {
		bullets[0][j].Update();
	}
	for (int j = 0; j < BULLETMAX2; j++) {
		bullets[1][j].Update();
	}
	for (int j = 0; j < BULLETMAX3; j++) {
		bullets[2][j].Update();
	}

	for (int i = 0; i < 4; i++)
	{
		guard[i]->Update();
	}
	for (int i = 0; i < 4; i++)
	{
		touchOb[i]->Update();
	}

	guard[0]->rotation2.z += 0.1f * ToRadian;
	guard[1]->rotation2.z += 0.1f * ToRadian;
	guard[2]->rotation2.z += 0.1f * ToRadian;
	guard[3]->rotation2.z += 0.1f * ToRadian;



	if (not isJump) return;
	//if (hasGravite) {
		JumpGravityForce += 1000.0f * DELTA;
		JumpGravityForce = min(JumpGravityForce, 1000);
	//}
	//else {
		//JumpGravityForce = 0;
	//}
	Vector2 velocity = (JumpDir * JumpPower
		+ JumpGravityDir * JumpGravityForce);
	MoveWorldPos(velocity * DELTA);



	rotation.z = atan2f(velocity.y, velocity.x);

}

void Player::Render()
{
	ObRect::Render();
	Img->Render();
	gauge->Render();
	gauge2->Render();

	for (int j = 0; j < BULLETMAX1; j++) {
		bullets[0][j].Render();
	}
	for (int j = 0; j < BULLETMAX2; j++) {
		bullets[1][j].Render();
	}
	for (int j = 0; j < BULLETMAX3; j++) {
		bullets[2][j].Render();
	}
	for (int i = 0; i < 4; i++)
	{
		guard[i]->Render();
	}
	weapon->Render();
	weapon2->Render();
}



