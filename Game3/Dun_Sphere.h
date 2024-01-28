#pragma once
class Dun_Sphere : public ObCircle
{
private:
	ObImage* Img_sphere;

	bool      isFire;
	float	  lifeTime;

	// ½î´Â ¹æÇâ
	Vector2   fireDir;
	// ½î´Â Èû
	float     pressPower;

public:
	Dun_Sphere();
	virtual ~Dun_Sphere();
	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Update() override;
	void Render() override;
	bool Touch(GameObject* target);

	bool GetIsFire() { return isFire; }
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

