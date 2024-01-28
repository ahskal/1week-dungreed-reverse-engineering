#pragma once
#define SWORDMAX 7
#define SPHEREMAX 30

enum class STATE {
	NONE,
	IDLE,
	RUN,
	JUMP,
	FALL,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	Hit,
	DEATH
};

/**
우선 첫번째 보스만 구현
두번째 보스 구현하게 되면 Boss_Dungreed를 각 보스가 상속 받는 형식으로 변경
*/
class Dun_Boss : public GameObject
{
private:
	SYSTEMTIME	time;
	STATE		state;							// 보스 상태
	bool		isdead;							// 죽은 상태인지
	float		attackCoolT;					// 공격 쿨타임 5초
	float		delayST;						// 검 공격 딜레이 타임
	int			random;							// random값으로 공격 패턴 결정
	int			rem;							// 다음 random값이 정해지기 전까지 가지고있을 변수

	int			damage;							// 보스 데미지
	ObImage* idle;							// 기본 상태 이미지
	ObImage* Img_rightHand;					// 오른손 이미지
	ObImage* Img_leftHand;					// 왼손 이미지

	/**HitBox*/
	ObCircle* HB_Head;						// 머리 히트박스
	ObRect* rightHand;						// 오른손 히트박스
	ObRect* leftHand;						// 왼손 히트박스
	class Dun_Sword* HB_sword[SWORDMAX];		// 보스 검 히트박스 + 이미지
	class Dun_Sphere* HB_sphereT[SPHEREMAX];	// 위로 나가는 구체 히트박스 + 이미지
	class Dun_Sphere* HB_sphereB[SPHEREMAX];	// 아래로 나가는 구체 히트박스 + 이미지
	class Dun_Sphere* HB_sphereR[SPHEREMAX];	// 우측으로 나가는 구체 히트박스 + 이미지
	class Dun_Sphere* HB_sphereL[SPHEREMAX];	// 좌측으로 나가는 구체 히트박스 + 이미지
	class Dun_Laser* HB_laser;				// 레이저 히트박스 + 이미지

public:
	int			hp;				// 보스 체력
	bool		ishit_B;						// 피격 됬는지

public:
	Dun_Boss();								// 생성자 함수
	virtual ~Dun_Boss();									// 소멸자 함수
	void	Init(Vector2 spawn);		// 초기화 함수
	void	Action(class GameObject* player, int time);			// 보스 행동
	void	Attack(class GameObject* player);					// 공격시 (보스 -> 플레이어)
	//void	Hit(class GameObject* player);						// 피격시 (보스 <- 플레이어)
	void	Update();											// 업데이트
	void	Render();											// 랜더링
	void	Change_State(STATE ps);

	int			GetHp() { return hp; }
	int			GetDamage() { return damage; }

	STATE		GetState() { return state; }

	ObCircle* GetBoss() { return HB_Head; }
	Dun_Sword* GetSword(int i) { return HB_sword[i]; }
	Dun_Sphere* GetSphereT(int i) { return HB_sphereT[i]; }
	Dun_Sphere* GetSphereB(int i) { return HB_sphereB[i]; }
	Dun_Sphere* GetSphereR(int i) { return HB_sphereR[i]; }
	Dun_Sphere* GetSphereL(int i) { return HB_sphereL[i]; }
	Dun_Laser* GetLaser() { return HB_laser; }
};

