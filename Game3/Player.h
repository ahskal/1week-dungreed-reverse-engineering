#pragma once

#define  DeshMaxGauge 5 //´ë½Ã Ç® °ÔÀÌÁö ¾ç

#define BULLETMAX1 15
#define BULLETMAX2 30
#define BULLETMAX3 10


class Player : public ObRect
{

	ObImage* Img;

	/** ÃÑ¾Ë ¹× ÃÑ ±¸Çö*/
	class Bullet** bullets;
	int				BulletType = 0;

	float* bulletAS;

	ObRect* weapon;
	ObRect* weapon2;
	ObRect* gauge;
	ObRect* gauge2;
	float			pressPower = 1000.0f;
	ObRect* guard[4];
	/** ÃÑ, ÃÑ¾Ë, °¡µå ±¸Çö*/

	int				dash = 200;
	float			GuardCoolTime = 200.0f;
	bool			hasGuard = false;

	bool			isColliding = false;
	bool			isDash = false;

	Vector2			JumpDir;
	Vector2			JumpGravityDir;
	float			JumpPower = 800.0f;


	float			spawnTime;

	int				dashStacks = 5;
	float			dashRecoverTime = 0.0f;

	bool			isJump = false;
	bool			isDownJump = false;
	bool			dashComplete = false;

	bool			isWeaponType1 = false;
	bool			isWeaponType2 = false;
public:
	ObRect* touchOb[4];

	float			JumpGravityForce = 500.0f;
	bool			ishit = false;
	int				hp = 100;
	int				damage = 0;

public:
	Player();
	virtual ~Player();

	void Init(Vector2 spawn);
	void Control();
	void Jump(Vector2 pos, Vector2 dir, float Power);
	void Jump(GameObject* Player, Vector2 dir, float Power);
	void downJump(float Power);
	void Dash(GameObject* Player, Vector2 dir);
	void recoverDash();
	void Collision(class Dun_Boss* boss);

	bool GetIsJump() { return isJump; }


	void Update() override;
	void Render() override;
	float GetHp() { return gauge2->scale.x; }
	//Bullet2* GetBullet2(int i) const { return bullet2[i]; }
	void Damage(float dmg) { gauge2->scale.x -= dmg; }
	//const Bullet** GetBullet() { return bullet; }
};

