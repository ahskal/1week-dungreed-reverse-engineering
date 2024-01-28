#pragma once
class Camera : public Singleton<Camera>
{
private:
    Matrix              V, P, VP, S;     

public:
    //ī�޶���ġ
    Viewport            viewport;  
    Vector3             position;
    //Vector2             position;
    Vector2             scale;

public:
    Camera();
    void          Set();
    void          ResizeScreen();
    const Matrix& GetP() { return P; };
    const Matrix& GetVP() { return VP; };
};