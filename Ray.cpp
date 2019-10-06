#include "DXUT.h"
#include "Ray.h"
#include "Collider.h"


Ray::Ray()
{
}


Ray::~Ray()
{
}


Ray Ray::RayAtViewSpace(int x, int y)
{
	D3DVIEWPORT9 Viewport;
	g_device->GetViewport(&Viewport);

	Matrix matProj;
	g_device->GetTransform(D3DTS_PROJECTION, &matProj);

	Ray ray;
	ray.vDirection.x = ((2 * x) / Viewport.Width - 1) / matProj._11;
	ray.vDirection.y = ((-2 * y) / Viewport.Height - 1) / matProj._22;
	ray.vDirection.z = 1;
	ray.RaySpace = R_VIEW;

	return ray;
}

Ray Ray::RayAtWorldSpace(int x, int y)
{
	Ray ray = Ray::RayAtViewSpace(x, y);

	Matrix matView;
	g_device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOriginal, &ray.vOriginal, &matView);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matView);
	D3DXVec3Normalize(&vDirection, &vDirection);

	ray.RaySpace = R_WORLD;

	return ray;
}


bool Ray::IntersectTriangle(Vector3& v1, Vector3 PickPosition)
{
	float u, v, t;

	list<Collider*> list = COLLISION->GetColliderList();
	
	for (auto iter : list)
	{
		if ((*iter).GetColliderType() == ColliderType::MeshSphere)
		{
			continue;
		}

		Vector3 center = (*iter).GetCenter();
		float length = (*iter).getlength();

		if (D3DXVec3Length(&(center - v1)) < length)
		{
			// 충돌처리 코드 나중에 생각해boza

			PickPosition = vOriginal + (t * vDirection);
			return true;
		}
	}

	//bool b = D3DXIntersectTri(&v1, &v1, &v1, &vOriginal,
	//	&vDirection, &u, &v, &t);


	return false;
}