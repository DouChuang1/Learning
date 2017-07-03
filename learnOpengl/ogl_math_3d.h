
#include<math.h>
#define M_PI 3.1415926535
#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x)*180.0)/M_PI)

struct PersProjInfo
{
	float FOV;
	float WindowWidth;
	float WindowHeight;
	float zNear;
	float zFar;
};

struct Vector2f
{
	float x;
	float y;
	Vector2f() {}
	Vector2f(float _x, float _y) {
		x = _x; y = _y;
	}
};

struct Vector3f
{
	float x;
	float y;
	float z;
	Vector3f() {}
	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Vector3f(const float* pFloat)
	{
		x = pFloat[0];
		y = pFloat[1];
		z = pFloat[2];
	}

	const Vector3f& Normalize();
	Vector3f Cross(const Vector3f& v)const;
	void Rotate(float Angle, const Vector3f& Axe);
	Vector3f operator *(float f);
	Vector3f& operator +=(const Vector3f& v);
	Vector3f& operator -=(const Vector3f& v);
	Vector3f& operator *=(float f);
};

struct Vector4f
{
	float x;
	float y;
	float z;
	float w;
	Vector4f() {}
	Vector4f(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};

class Matrix4f
{
public:
	float m[4][4];
	Matrix4f() {}
	void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
	void Matrix4f::InitRotateTransform(float RotateX, float RotateY, float RotateZ);
	void Matrix4f::InitTranslationTransform(float x, float y, float z);

	void InitPersProjTransform(const PersProjInfo& p);
	void InitCameraTransform(const Vector3f& Target, const Vector3f& Up);


	inline Matrix4f operator*(const Matrix4f& r)
	{
		Matrix4f res;
		for (int i = 0; i<4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				res.m[i][j] = m[i][0] * r.m[0][j] +
					m[i][1] * r.m[1][j] +
					m[i][2] * r.m[2][j] +
					m[i][3] * r.m[3][j];
			}
		return res;
	}

};

struct Vector2i
{
	int x;
	int y;
};

struct Quaternion
{
	float x, y, z, w;
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(const Vector3f& V);
	void Normalize();
	Quaternion Conjugate();
	Vector3f ToDegrees();
	//Quaternion operator*(const Quaternion& RightQ);
	//Quaternion operator*(const Vector3f& RightV);

};

//用非成员变量的时候，还是要声明一下
Quaternion operator*(const Quaternion& l, const Quaternion& r);
Quaternion operator*(const Quaternion& q, const Vector3f& v);
Vector3f operator-(const Vector3f& v1, const Vector3f& v2);
