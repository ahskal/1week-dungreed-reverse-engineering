#pragma once
class Dun_Laser : public ObRect
{
private:
	ObImage*	Img_laserFirst;		// ¾ÕºÎºÐ
	ObImage*	Img_laserSecond;		// Áß°£
	ObImage*	Img_laserThird;		// µÞºÎºÐ

	bool		isFire;
	bool		isturn;				// false = ¿À¸¥¼Õ true = ¿Þ¼Õ
	float		lifeTime;
	float		delayTime;

	// ½î´Â ¹æÇâ
	Vector2		fireDir;
	// ½î´Â Èû
	float		pressPower;

public:
	Dun_Laser();
	virtual ~Dun_Laser();
	void Fire(Vector2 pos);
	void Update() override;
	void Render() override;
	bool Touch(GameObject* target);

	bool GetIsFire() { return isFire; }
	bool GetIsTurn() { return isturn; }
	void Release() { isFire = false; }

	//void ReflectionY()
	//{
	//	fireDir.x = -fireDir.x;
	//	/*Vector2 dir =
	//		Vector2(cosf(rotation.z), sinf(rotation.z));
	//	rotation.z = atan2f(dir.y, -dir.x);*/
	//	pressPower *= 0.7f;
	//	gravityForce *= 0.7f;
	//}
	//void ReflectionX()
	//{
	//	fireDir.y = -fireDir.y;
	//	gravityForce = -gravityForce;
	//	//Vector2 dir =
	//	//	Vector2(cosf(rotation.z), sinf(rotation.z));
	//	//rotation.z = atan2f(-dir.y, dir.x);
	//	pressPower *= 0.7f;
	//	gravityForce *= 0.7f;
	//}
};

