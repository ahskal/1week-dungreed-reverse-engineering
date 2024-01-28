#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Main.h"

Main::Main()
{
	pl[0] = new Player;
	pl[1] = new Player;
    for (int i = 0; i < StarMax; i++)
    {
        bg[i] = new ObStar();
        bg[i]->SetWorldPosX(RANDOM->Float(-800.0f, 800.0f));
        bg[i]->SetWorldPosY(RANDOM->Float(-600.0f, 600.0f));
        bg[i]->scale.x = 15.0f;
        bg[i]->scale.y = 15.0f;
        bg[i]->color = Color(0, 1, 1)* RANDOM->Float();
        //bg[i]->space = SPACE::SCREEN;
    }
    
    
}

Main::~Main()
{
}

void Main::Init()
{

	pl[0]->Init(Vector2(0, -240), false);
    pl[0]->isFilled = false;
    pl[0]->color = Color(0.5, 0, 0);
	pl[1]->Init(Vector2(340, -240), true);
    pl[1]->color = Color(0, 0, 1);
	turn = 0;
    Campos = CAM->position;
}

void Main::Release()
{
   
}

void Main::Update()
{
    ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());
    /*if (INPUT->KeyPress(VK_UP))
    {
       CAM->position += UP*100.0f* DELTA;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        CAM->position += DOWN * 100.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        CAM->position += LEFT * 100.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        CAM->position += RIGHT * 100.0f * DELTA;;
    }*/

	pl[turn]->Control();

	pl[0]->Update();
	pl[1]->Update();

    Campos = (pl[0]->GetWorldPos() + INPUT->GetWorldMousePos() ) * 0.5f;

    CAM->position = Campos + Vector2(RANDOM->Float(-5, 5), RANDOM->Float(-5, 5));

    //Cam과 플레이어의 차이값 벡터
   /* Vector2 minus = pl[0]->GetWorldPos() - CAM->position;

    CAM->position += minus  *DELTA;*/

    for (int i = 0; i < StarMax; i++)
    {
        bg[i]->Update();
    }

    CAM->position.x = Utility::Saturate(CAM->position.x, -400.0f, 400.0f);
    /*if (CAM->position.x < -400.0f)
    {
        CAM->position.x = 400.0f;
    }*/

}

void Main::LateUpdate()
{
    for (int i = 0; i < 30; i++)
    {

        if (not pl[turn]->GetBullet(i)->GetIsFire())continue;

        if (pl[turn]->GetBullet(i)->GetWorldPos().x < -400.0f + 10.0f)
        {
            pl[turn]->GetBullet(i)->SetWorldPosX(-400.0f + 10.0f);
            pl[turn]->GetBullet(i)->ReflectionY();
            pl[turn]->GetBullet(i)->Update();
        }
        else if (pl[turn]->GetBullet(i)->GetWorldPos().x > 400.0f - 10.0f)
        {
            pl[turn]->GetBullet(i)->SetWorldPosX(400.0f - 10.0f);
            pl[turn]->GetBullet(i)->ReflectionY();
            pl[turn]->GetBullet(i)->Update();
        }
        if (pl[turn]->GetBullet(i)->GetWorldPos().y < -300.0f - 10.0f)
        {
            pl[turn]->GetBullet(i)->Release();
            turn = not turn;
            damage = 0;
            damageTime = 0.0f;
        }

        if (pl[turn]->GetBullet(i)->Touch(pl[not turn]))
        {
            //pl[not turn]->
            //pl[not turn]->Damage(10.0f);
            //pl[turn]->GetBullet(i)->Release();
            //turn = not turn;
            damage = 1;
            releasebullet = i;
        }
    }

    if (damage)
    {
        if (TIMER->GetTick(damageTime, 0.02f))
        {
            pl[not turn]->Damage(5.0f);
            damage++;
        }

        if (damage >= 5)
        {
            pl[turn]->GetBullet(releasebullet)->Release();
            turn = not turn;
            damage = 0;
            damageTime = 0.0f;
        }
    }

}

void Main::Render()
{
    for (int i = 0; i < StarMax; i++)
    {
        bg[i]->Render();
    }

    pl[0]->Render();
    pl[1]->Render();


}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(800.0f,600.0f);
    app.background = Color(0, 0, 0);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}