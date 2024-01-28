#pragma once
#define StarMax 100

class Main : public Scene
{
private:
	class Player* pl[2];
	int turn;
	int damage = 0;
	float damageTime = 0.0f;
	int releasebullet;

	ObStar* bg[StarMax];
	Vector2 Campos;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
