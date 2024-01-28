#pragma once
class Bullet : public ObRect
{
private:
	bool      isFire;
	float	  lifeTime;

	// ��� ����
	Vector2   fireDir;
	// ��� ��
	float     pressPower;

	Vector2  gravityDir;
	float    gravityForce;

public:
	Bullet();
	virtual ~Bullet();
	void Fire(GameObject* shooter,float pressPower);
	void Fire(Vector2 pos,Vector2 dir,float pressPower);
	void Drop(Vector2 pos);
	void Update() override;
	void Render() override;
	bool Touch(GameObject* target);

	bool GetIsFire() { return isFire; }
	void Release() { isFire = false; }

};

