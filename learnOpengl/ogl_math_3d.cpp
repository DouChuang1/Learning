#include "stdafx.h"
#include "ogl_math_3d.h"

void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
{
	m[0][0] = ScaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
	m[1][0] = 0.0f;   m[1][1] = ScaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
	m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = ScaleZ; m[2][3] = 0.0f;
	m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void Matrix4f::InitRotateTransform(float RotateX, float RotateY, float RotateZ)
{
	Matrix4f rx, ry, rz;

	const float x = ToRadian(RotateX);
	const float y = ToRadian(RotateY);
	const float z = ToRadian(RotateZ);

	rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f; rx.m[0][2] = 0.0f; rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x); rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f; rx.m[3][2] = 0.0f; rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f; ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y); ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f; ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z); rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f; rz.m[2][1] = 0.0f; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f; rz.m[3][1] = 0.0f; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

	*this = rz * ry * rx;
}

void Matrix4f::InitTranslationTransform(float x, float y, float z)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}


void Matrix4f::InitPersProjTransform(const PersProjInfo& p)
{
	const float ar = (float)p.WindowWidth / p.WindowHeight;
	//const float TanHalfA = tanf(p.FOV / 2.0f);
	//没有转化为弧度制，这个bug藏得有多深！！！
	const float TanHalfA = tanf(ToRadian(p.FOV / 2.0f));
	float zn = p.zNear;
	float zf = p.zFar;
	m[0][0] = 1 / (ar * TanHalfA); m[0][1] = 0.0f;          m[0][2] = 0.0f;                   m[0][3] = 0.0f;
	m[1][0] = 0.0f;               m[1][1] = 1 / TanHalfA;  m[1][2] = 0.0f;                   m[1][3] = 0.0f;
	m[2][0] = 0.0f;               m[2][1] = 0.0f;          m[2][2] = (-zn - zf) / (zn - zf); m[2][3] = (2 * zn*zf) / (zn - zf);
	m[3][0] = 0.0f;               m[3][1] = 0.0f;          m[3][2] = 1.0f;                   m[3][3] = 0.0f;
}

void Matrix4f::InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
{
	Vector3f N = Target;
	N.Normalize();
	Vector3f U = Up;
	U.Normalize();
	U = U.Cross(N);

	Vector3f V = N.Cross(U);

	m[0][0] = U.x;  m[0][1] = U.y;  m[0][2] = U.z;  m[0][3] = 0.0f;
	m[1][0] = V.x;  m[1][1] = V.y;  m[1][2] = V.z;  m[1][3] = 0.0f;
	m[2][0] = N.x;  m[2][1] = N.y;  m[2][2] = N.z;  m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

const Vector3f& Vector3f::Normalize()
{
	float module = (float)sqrt(x*x + y*y + z*z);
	x /= module;
	y /= module;
	z /= module;
	return *this;
}

Vector3f Vector3f::Cross(const Vector3f& v)const
{
	Vector3f res;
	res.x = y*v.z - z*v.y;
	res.y = z*v.x - x*v.z;
	res.z = x*v.y - y*v.x;
	return res;
}

Vector3f Vector3f::operator*(float f)
{
	Vector3f res;
	res.x = x*f;
	res.y = y*f;
	res.z = z*f;

	return res;
}

Vector3f&  Vector3f::operator +=(const Vector3f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3f& Vector3f::operator -=(const Vector3f& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3f& Vector3f::operator *=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

void Vector3f::Rotate(float Angle, const Vector3f& Axe)
{
	Vector3f IAxe = Axe;
	//IAxe.Normalize();
	const float SinHalfAngle = (float)sinf(ToRadian(Angle / 2));
	const float CosHalfAngle = (float)cosf(ToRadian(Angle / 2));
	const float Rx = IAxe.x * SinHalfAngle;
	const float Ry = IAxe.y * SinHalfAngle;
	const float Rz = IAxe.z * SinHalfAngle;
	const float Rw = CosHalfAngle;

	Quaternion RotationQ(Rx, Ry, Rz, Rw);
	Quaternion ConjugateQ = RotationQ.Conjugate();
	//RotationQ.Normalize();
	Vector3f V = *this;
	Quaternion W = RotationQ * V * ConjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void Quaternion::Normalize()
{
	float l = (float)sqrt(x*x + y*y + z*z + w*w);
	x /= l;
	y /= l;
	z /= l;
	w /= l;
}

Quaternion Quaternion::Conjugate()
{
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

Vector3f Quaternion::ToDegrees()
{
	float f[3];
	f[0] = (float)atan2(x*z + y*w, x*w - y*z);
	f[1] = (float)acos(-x*x - y*y - z*z - w*w);
	f[2] = (float)atan2(x*z - y*w, x*w + y*z);

	f[0] = ToDegree(f[0]);
	f[1] = ToDegree(f[1]);
	f[2] = ToDegree(f[2]);

	return Vector3f(f);
}

//Quaternion Quaternion:: operator*(const Quaternion& RightQ)
//{
//	Quaternion temp = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
//	temp.x = y*RightQ.z - z*RightQ.y + x*RightQ.w + w*RightQ.x;
//	temp.y = z*RightQ.x - x*RightQ.z + y*RightQ.w + w*RightQ.y;
//	temp.z = x*RightQ.y - y*RightQ.x + z*RightQ.w + w*RightQ.z;
//	temp.w = -x*RightQ.x - y*RightQ.y - z*RightQ.z + w*RightQ.w;
//	return temp;
//}
//
Quaternion::Quaternion(const Vector3f& V)
{
	Quaternion(V.x, V.y, V.z, 0);
}
//
////其实没有必要，真正乘向量的时候先用构造函数把向量转化为四元数就好了
//Quaternion Quaternion::operator* (const Vector3f& RightV)
//{
//	Quaternion temp = Quaternion(RightV);
//	Quaternion res = (*this) * temp;
//	return res;
//}


Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
	const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
	const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
	const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
	const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

	Quaternion ret(x, y, z, w);

	return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
	const float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	Quaternion ret(x, y, z, w);

	return ret;
}


Vector3f operator-(const Vector3f& v1, const Vector3f& v2)
{
	Vector3f res;
	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return res;
}