#pragma once
class Dun_Sword : public ObRect
{
//private:
//	ObImage*	Im_sword;
//
//	bool		isFire;
//	Vector2		fireDir;
//	float		lifeTime;
//
//
//public:
//	Bullet_Dun();
//	virtual ~Bullet_Dun();
//	void Init(GameObject* player, int i);
//	void Fire(GameObject* player, int i);
//	void Move(GameObject* player, int i);
//
//	void Update() override;
//	void Render() override;
//
//	bool Touch(GameObject* target);
//
//	bool GetIsFire() { return isFire; }
//	void Release() { isFire = false; }

private:
	ObImage* Img_sword;

	bool      isFire;
	float	  lifeTime;

	// ½î´Â ¹æÇâ
	Vector2   fireDir;
	// ½î´Â Èû
	float     pressPower;

public:
	Dun_Sword();
	virtual ~Dun_Sword();
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update() override;
	void Render() override;
	bool Touch(GameObject* target);

	bool GetIsFire() { return isFire; }
	void Release() { isFire = false; }



//	void ReflectionY()
//	{
//		fireDir.x = -fireDir.x;
//		/*Vector2 dir =
//			Vector2(cosf(rotation.z), sinf(rotation.z));
//		rotation.z = atan2f(dir.y, -dir.x);*/
//		pressPower *= 0.7f;
//		gravityForce *= 0.7f;
//	}
//	void ReflectionX()
//	{
//		fireDir.y = -fireDir.y;
//		gravityForce = -gravityForce;
//		//Vector2 dir =
//		//	Vector2(cosf(rotation.z), sinf(rotation.z));
//		//rotation.z = atan2f(-dir.y, dir.x);
//		pressPower *= 0.7f;
//		gravityForce *= 0.7f;
//	}
};

