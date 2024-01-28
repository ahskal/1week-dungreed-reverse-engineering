#pragma once
class Grenade : public Bullet
{
private:

	bool isFire;

public:
	Bullet* bullet[36];
	Grenade();
	~Grenade();
	void Explosion(Vector2 pos, int Length, float speed);
	void Update();

	void Render();
	void Release() { isFire = false; }
};

