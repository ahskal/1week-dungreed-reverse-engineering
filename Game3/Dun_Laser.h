#pragma once
class Dun_Laser : public ObRect
{
private:
	ObImage*	Img_laserFirst;		// �պκ�
	ObImage*	Img_laserSecond;		// �߰�
	ObImage*	Img_laserThird;		// �޺κ�

	bool		isFire;
	bool		isturn;				// false = ������ true = �޼�
	float		lifeTime;
	float		delayTime;

	// ��� ����
	Vector2		fireDir;
	// ��� ��
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

