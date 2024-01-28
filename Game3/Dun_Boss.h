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
�켱 ù��° ������ ����
�ι�° ���� �����ϰ� �Ǹ� Boss_Dungreed�� �� ������ ��� �޴� �������� ����
*/
class Dun_Boss : public GameObject
{
private:
	SYSTEMTIME	time;
	STATE		state;							// ���� ����
	bool		isdead;							// ���� ��������
	float		attackCoolT;					// ���� ��Ÿ�� 5��
	float		delayST;						// �� ���� ������ Ÿ��
	int			random;							// random������ ���� ���� ����
	int			rem;							// ���� random���� �������� ������ ���������� ����

	int			damage;							// ���� ������
	ObImage* idle;							// �⺻ ���� �̹���
	ObImage* Img_rightHand;					// ������ �̹���
	ObImage* Img_leftHand;					// �޼� �̹���

	/**HitBox*/
	ObCircle* HB_Head;						// �Ӹ� ��Ʈ�ڽ�
	ObRect* rightHand;						// ������ ��Ʈ�ڽ�
	ObRect* leftHand;						// �޼� ��Ʈ�ڽ�
	class Dun_Sword* HB_sword[SWORDMAX];		// ���� �� ��Ʈ�ڽ� + �̹���
	class Dun_Sphere* HB_sphereT[SPHEREMAX];	// ���� ������ ��ü ��Ʈ�ڽ� + �̹���
	class Dun_Sphere* HB_sphereB[SPHEREMAX];	// �Ʒ��� ������ ��ü ��Ʈ�ڽ� + �̹���
	class Dun_Sphere* HB_sphereR[SPHEREMAX];	// �������� ������ ��ü ��Ʈ�ڽ� + �̹���
	class Dun_Sphere* HB_sphereL[SPHEREMAX];	// �������� ������ ��ü ��Ʈ�ڽ� + �̹���
	class Dun_Laser* HB_laser;				// ������ ��Ʈ�ڽ� + �̹���

public:
	int			hp;				// ���� ü��
	bool		ishit_B;						// �ǰ� �����

public:
	Dun_Boss();								// ������ �Լ�
	virtual ~Dun_Boss();									// �Ҹ��� �Լ�
	void	Init(Vector2 spawn);		// �ʱ�ȭ �Լ�
	void	Action(class GameObject* player, int time);			// ���� �ൿ
	void	Attack(class GameObject* player);					// ���ݽ� (���� -> �÷��̾�)
	//void	Hit(class GameObject* player);						// �ǰݽ� (���� <- �÷��̾�)
	void	Update();											// ������Ʈ
	void	Render();											// ������
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

