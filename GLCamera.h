#ifndef GLCamera_H
#define GLCamera_H

#include <math.h>

class Point3
{
public:
	float x,y,z;
	void set(float dx,float dy,float dz)
	{
		x=dx; y=dy; z=dz;
	}
	void set(Point3& p)
	{
		x=p.x; y=p.y; z=p.z;
	}
	Point3(float xx,float yy,float zz)
	{
		x=xx; y=yy; z=zz;
	}
	Point3()
	{
		x=y=z=0;
	}
	void build4tuple(float v[])
	{
		v[0]=x; v[1]=y; v[2]=z; v[3]=1.0f;
	}
};

class Vector3
{
public:
	float x,y,z;
	void set(float dx,float dy,float dz)
	{
		x=dx; y=dy; z=dz;
	}
	void set(Vector3& v)
	{
		x=v.x; y=v.y; z=v.z;
	}
	void flip()
	{
		x=-x; y=-y; z=-z;
	}
	void setDiff(Point3& a,Point3& b)
	{
		x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;
	}
	void normalize()
	{
		float base=pow(x,2)+pow(y,2)+pow(z,2);
		x=x/pow(base,0.5f);
		y=y/pow(base,0.5f);
		z=z/pow(base,0.5f);
	}
	Vector3(float xx, float yy, float zz)
	{
		x=xx; y=yy; z=zz;
	}
	Vector3(Vector3 &v)
	{
		x=v.x; y=v.y; z=v.z;
	}
	Vector3()
	{
		x=0; y=0; z=0;
	}

	Vector3 cross(Vector3 b)
	{
		float x1,y1,z1;
		x1=y*b.z-z*b.y;
		y1=z*b.x-x*b.z;
		z1=x*b.y-y*b.x;
		Vector3 c(x1,y1,z1);
		return c;
	}

	float dot(Vector3 b)
	{
		float d=x*b.x+y*b.y+z*b.z;
		return d;
	}
};

class GLCamera
{
public:
	/* ���캯������������ */
	GLCamera();
	~GLCamera();

	/* �����������λ��, �۲����������� */
	void setCamera( float eyeX, float eyeY, float eyeZ,
		float lookX, float lookY, float lookZ,
		float upX, float upY, float upZ);
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	void slide(float du, float dv, float dn);
	float getDist();
	void setShape(float viewAngle,float aspect,float Near,float Far);


private:
	/* ��������� */
	Point3         eye,look,up;
	Vector3        u,v,n;
	float          viewAngle, aspect, nearDist, farDist;
	void           setModelViewMatrix();

};

#endif //__GLCamera_H__
