#ifndef VECTOR3D_H
#define VECTOR3D_H

template<class T>
struct Vector2d
{
	float x;
	float y;

	Vector2d(T _x = 0, T _y = 0)
	{
		x = _x;
		y = _y;
	}
};

typedef Vector2d<int> Vector2di;
typedef Vector2d<float> Vector2df;

template<class T>
struct Vector3d
{
	T x;
	T y;
	T z;

	Vector3d(T _x = 0, T _y = 0, T _z = 0)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

typedef Vector3d<int> Vector3di;
typedef Vector3d<float> Vector3df;
typedef Vector3d<float> Rotation;

template<class T>
struct BBox3d
{
	T l;
	T h;
	T w;

	BBox3d(T _l = 0, T _h = 0, T _w = 0)
	{
		l = _l;
		h = _h;
		w = _w;
	}
};

typedef BBox3d<float> BBox3df;

#endif // VECTOR3D_H
