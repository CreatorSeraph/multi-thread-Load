#pragma once

class Ray
{
public:
	Ray();
	virtual ~Ray();

	enum RaySpace
	{
		R_NONE,
		R_VIEW,
		R_WORLD,
		E_LOCALm,
	};

protected:
	Vector3 vOriginal;
	Vector3 vDirection;
	RaySpace RaySpace;

	//x�� y�� ���콺 ��ǥ
	Ray RayAtViewSpace(int x, int y);
	Ray RayAtWorldSpace(int x, int y);
	bool IntersectTriangle(Vector3& v1, Vector3 PickPosition);
};

