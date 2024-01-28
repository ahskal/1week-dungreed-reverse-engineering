#pragma once
class Bullet : public ObRect
{
private:
	// ½î´Â ¹æÇâ
	// ½î´Â Èû
	Vector2  gravityDir;
	float    gravityForce;


	//========================================


	Vector2   Distance;
	Vector2   fireDir;
	
	float     pressPower;
	//float	  lifeTime;
	
	bool      hasImage;
	bool      isFire;
	bool      isGravite;





public:
	ObImage* img;

	Bullet();
	Bullet(wstring imgAddr);
	virtual ~Bullet();

	void Fire(Vector2 pos, Vector2 dir, float pressPower);
	void Fire(Vector2 pos, Vector2 pos2, Vector2 scale, float pressPower, bool gravite = false);

	void Drop(Vector2 pos, Vector2 scale, float pressPower, bool gravite = false);

	//void Fire(GameObject* shooter,float pressPower);
	//void Fire(Vector2 pos,Vector2 dir,float pressPower);
	//void Drop(Vector2 pos);
	void Update() override;
	void Render() override;
	bool Touch(GameObject* target);

	bool GetIsFire() { return isFire; }
	void Release() { isFire = false; }

	void ChangeImg(wstring file);

	void ReflectionY() 
	{ 
		fireDir.x = -fireDir.x; 
		/*Vector2 dir =
			Vector2(cosf(rotation.z), sinf(rotation.z));
		rotation.z = atan2f(dir.y, -dir.x);*/
		pressPower *= 0.7f;
	    gravityForce *= 0.7f;
	}
	void ReflectionX() 
	{ 
		fireDir.y = -fireDir.y; 
		gravityForce = -gravityForce;
		//Vector2 dir =
		//	Vector2(cosf(rotation.z), sinf(rotation.z));
		//rotation.z = atan2f(-dir.y, dir.x);
		pressPower *= 0.7f;
		gravityForce *= 0.7f;
	}
};

