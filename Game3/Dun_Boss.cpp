#include "stdafx.h"

Dun_Boss::Dun_Boss()
{
	HB_Head = new ObCircle();
	HB_Head->hasAxis = false;
	idle = new ObImage(L"SkellBossIdle0.png");
	Img_rightHand = new ObImage(L"SkellBossRightHandIdle0.png");
	Img_rightHand->SetParentT(*HB_Head);
	Img_leftHand = new ObImage(L"SkellBossLeftHandIdle0.png");
	Img_leftHand->SetParentT(*HB_Head);

	for (int i = 0; i < SWORDMAX; i++)
	{
		HB_sword[i] = new Dun_Sword();
	}

	for (int i = 0; i < SPHEREMAX; i++)
	{
		HB_sphereT[i] = new Dun_Sphere();
		HB_sphereT[i]->SetParentT(*HB_Head);

		HB_sphereB[i] = new Dun_Sphere();
		HB_sphereB[i]->SetParentT(*HB_Head);

		HB_sphereR[i] = new Dun_Sphere();
		HB_sphereR[i]->SetParentT(*HB_Head);

		HB_sphereL[i] = new Dun_Sphere();
		HB_sphereL[i]->SetParentT(*HB_Head);
	}
	HB_laser = new Dun_Laser();

	state = STATE::NONE;
	isdead = false;
	ishit_B = false;
}

Dun_Boss::~Dun_Boss()
{
	for (int i = 0; i < SWORDMAX; i++)
	{
		delete HB_sword[i];
	}

	for (int i = 0; i < SPHEREMAX; i++)
	{
		delete HB_sphereT[i];
		delete HB_sphereB[i];
		delete HB_sphereR[i];
		delete HB_sphereL[i];
	}

	delete idle;

	delete HB_laser;
	delete HB_Head;
	delete Img_rightHand;
	delete Img_leftHand;
}

void Dun_Boss::Init(Vector2 spawn)
{
	/** 보스 외형 초기값*/
	HB_Head->SetWorldPosX(spawn.x);
	HB_Head->SetWorldPosY(spawn.y);
	HB_Head->scale.x = 370.0f;
	HB_Head->scale.y = 370.0f;
	HB_Head->isFilled = false;

	idle->SetWorldPosX(spawn.x - 40.0f);
	idle->SetWorldPosY(spawn.y + 35.0f);
	idle->scale.x = 400.0f;
	idle->scale.y = 400.0f;

	Img_rightHand->SetLocalPos(Vector2(650.0f, -300.0f));
	Img_rightHand->scale.x = 200.0f;
	Img_rightHand->scale.y = 300.0f;

	Img_leftHand->SetLocalPos(Vector2(-650.0f, -300.0f));
	Img_leftHand->scale.x = 200.0f;
	Img_leftHand->scale.y = 300.0f;
	/** 보스 외형 초기값*/

	for (int i = 0; i < SWORDMAX; i++)
	{
		HB_sword[i]->isFilled = false;
	}
	for (int i = 0; i < SPHEREMAX; i++)
	{
		HB_sphereT[i]->isFilled = false;
		HB_sphereB[i]->isFilled = false;
		HB_sphereR[i]->isFilled = false;
		HB_sphereL[i]->isFilled = false;
	}
	HB_laser->isFilled = false;

	/* 보스 스텟*/
	hp = 500;
	damage = 1;
	random = 0;
	attackCoolT = 0.0f;
	delayST = 0.0f;
}

void Dun_Boss::Action(GameObject* player, int time)
{
	ImGui::Text("\n\n\t<<BOSS>>\n");
	ImGui::Text("Boss State(Pattern)\t= %d", (int)state);
	ImGui::Text("random\t\t\t\t = %d", random);

	ImGui::Text("attackCoolTimer\t\t= %d", (int)attackCoolT);

	ImGui::Text("\n\nBoss HP\t\t= %d", hp);
	ImGui::Text("Boss Damage\t= %d", damage);

	if (!isdead)
	{
		if (time < 3.0f) Change_State(STATE::IDLE);
		else if (TIMER->GetTick(attackCoolT, 3.0f))
		{
			random = RANDOM->Int(11, 40);

			if ((random >= 11 and random <= 20) and state != STATE::ATTACK1)
			{
				Change_State(STATE::ATTACK1);
			}
			else if ((random >= 21 and random <= 30) and state != STATE::ATTACK2)
			{
				Change_State(STATE::ATTACK2);
			}
			else if ((random >= 31 and random <= 40) and state != STATE::ATTACK3)
			{
				Change_State(STATE::ATTACK3);
			}
			else
			{
				Change_State(STATE::IDLE);
			}
		}
		Attack(player);
	}
	else
	{
		state = STATE::DEATH;
	}
}

void Dun_Boss::Attack(GameObject* player)
{
	if (state == STATE::IDLE)
	{
		for (int i = 0; i < SWORDMAX; i++)
		{
			HB_sword[i]->Release();
		}
		for (int i = 0; i < SPHEREMAX; i++)
		{
			HB_sphereT[i]->Release();
			HB_sphereB[i]->Release();
			HB_sphereR[i]->Release();
			HB_sphereL[i]->Release();
		}
		HB_laser->Release();
	}
	if (state == STATE::ATTACK1)
	{
		damage = 10.0f;
		if (TIMER->GetTick(delayST, 0.2f))
		{
			for (int i = 0; i < SWORDMAX; i++)
			{
				if (not HB_sword[i]->GetIsFire())
				{
					Vector2 spawn = Vector2(HB_Head->GetWorldPos().x, HB_Head->GetWorldPos().y + 200.0f);
					Vector2 target = player->GetWorldPos();

					HB_sword[i]->Fire(spawn, target - spawn, 800.0f);
					break;
				}
			}
		}
	}
	if (state == STATE::ATTACK2)
	{
		damage = 20.0f;
		if (TIMER->GetTick(delayST, 0.05f))
		{
			for (int i = 0; i < SPHEREMAX; i++)
			{
				if (not HB_sphereT[i]->GetIsFire())
				{
					Vector2 spawn = Vector2(HB_Head->GetWorldPos().x, HB_Head->GetWorldPos().y + 50.0f); // 생성위치
					float seta = i * 6.0f * ToRadian;	// 각도
					Vector2 target = spawn + +Vector2(cosf(seta), sinf(seta)) * 100.0f; // 날아갈 위치
					HB_sphereT[i]->Fire(spawn, target - spawn, 900.0f);

					break;
				}
			}
			for (int i = 0; i < SPHEREMAX; i++)
			{
				if (not HB_sphereB[i]->GetIsFire())
				{
					Vector2 spawn = Vector2(HB_Head->GetWorldPos().x, HB_Head->GetWorldPos().y - 50.0f); // 생성위치
					float seta = (i * 6.0f + 180.0f) * ToRadian;	// 각도
					Vector2 target = spawn + +Vector2(cosf(seta), sinf(seta)) * 100.0f; // 날아갈 위치
					HB_sphereB[i]->Fire(spawn, target - spawn, 900.0f);

					//HB_sphereB[i]->Fire(Vector2(HB_Head->GetWorldPos().x, HB_Head->GetWorldPos().y - 50.0f), LEFT, 100.0f);
					break;
				}
			}
			for (int i = 0; i < SPHEREMAX; i++)
			{
				if (not HB_sphereR[i]->GetIsFire())
				{
					Vector2 spawn = Vector2(HB_Head->GetWorldPos().x + 50.0f, HB_Head->GetWorldPos().y); // 생성위치
					float seta = (i * 6.0f + 270.0f) * ToRadian;	// 각도
					Vector2 target = spawn + +Vector2(cosf(seta), sinf(seta)) * 100.0f; // 날아갈 위치
					HB_sphereR[i]->Fire(spawn, target - spawn, 900.0f);

					//HB_sphereR[i]->Fire(Vector2(HB_Head->GetWorldPos().x + 50.0f, HB_Head->GetWorldPos().y), DOWN, 100.0f);
					break;
				}
			}
			for (int i = 0; i < SPHEREMAX; i++)
			{
				if (not HB_sphereL[i]->GetIsFire())
				{
					Vector2 spawn = Vector2(HB_Head->GetWorldPos().x - 50.0f, HB_Head->GetWorldPos().y); // 생성위치
					float seta = (i * 6.0f + 90.0f) * ToRadian;	// 각도
					Vector2 target = spawn + +Vector2(cosf(seta), sinf(seta)) * 100.0f; // 날아갈 위치
					HB_sphereL[i]->Fire(spawn, target - spawn, 900.0f);

					//HB_sphereL[i]->Fire(Vector2(HB_Head->GetWorldPos().x - 50.0f, HB_Head->GetWorldPos().y), UP, 100.0f);
					break;
				}
			}

		}

	}
	if (state == STATE::ATTACK3)
	{
		damage = 5.0f;
		Vector2 spawn;
		if (HB_laser->GetIsTurn())
		{
			Img_leftHand->SetWorldPosY(player->GetWorldPos().y);
			spawn = Vector2(0.0f, Img_leftHand->GetWorldPos().y);
		}
		else
		{
			Img_rightHand->SetWorldPosY(player->GetWorldPos().y);
			spawn = Vector2(0.0f, Img_rightHand->GetWorldPos().y);
		}
		if (TIMER->GetTick(delayST, 1.0f))
		{
			HB_laser->Fire(spawn);
		}
	}
}


void Dun_Boss::Update()
{
	if (hp <= 0) state = STATE::DEATH;
	if (state != STATE::NONE and state != STATE::DEATH)
	{
		HB_Head->Update();
		idle->Update();
		Img_rightHand->Update();
		Img_leftHand->Update();
		HB_laser->Update();
		for (int i = 0; i < SWORDMAX; i++)
		{
			HB_sword[i]->Update();
		}
		for (int i = 0; i < SPHEREMAX; i++)
		{
			HB_sphereT[i]->Update();
			HB_sphereB[i]->Update();
			HB_sphereR[i]->Update();
			HB_sphereL[i]->Update();
		}
	}
}

void Dun_Boss::Render()
{
	if (hp <= 0) state = STATE::DEATH;
	if (state != STATE::NONE and state != STATE::DEATH)
	{
		
		HB_Head->Render();
		idle->Render();
		Img_rightHand->Render();
		Img_leftHand->Render();
		HB_laser->Render();
		for (int i = 0; i < SWORDMAX; i++)
		{
			HB_sword[i]->Render();
		}
		for (int i = 0; i < SPHEREMAX; i++)
		{
			HB_sphereT[i]->Render();
			HB_sphereB[i]->Render();
			HB_sphereR[i]->Render();
			HB_sphereL[i]->Render();
		}
	}
}


void Dun_Boss::Change_State(STATE ps)
{
	if (state != ps)
	{
		state = ps;
		//if (state == STATE::NONE)
		//{
		//	HB_Head->isVisible = false;
		//	idle->isVisible = false;
		//	Im_rightHand->isVisible = false;
		//	Im_leftHand->isVisible = false;
		//	for (int i = 0; i < SWORDMAX; i++)
		//	{
		//		HB_sword[i]->isVisible = false;
		//	}
		//}
		//else if (state != STATE::NONE)
		//{
		//	HB_Head->isVisible = true;
		//	idle->isVisible = true;
		//	Im_rightHand->isVisible = true;
		//	Im_leftHand->isVisible = true;
		//	for (int i = 0; i < SWORDMAX; i++)
		//	{
		//		HB_sword[i]->isVisible = true;
		//	}
		//}
		if (state == STATE::IDLE)
		{

		}
		if (state == STATE::ATTACK1)		// 검 공격
		{
			for (int i = 0; i < SWORDMAX; i++)
			{
				HB_sword[i]->isVisible = true;
			}
		}
		else
		{
			for (int i = 0; i < SWORDMAX; i++)
			{
				HB_sword[i]->isVisible = false;
			}
		}
		if (state == STATE::ATTACK2)		// 구체 공격
		{

		}
		if (state == STATE::ATTACK3)		// 레이저 공격
		{

		}
		if (state == STATE::DEATH)
		{

		}
	}
}
