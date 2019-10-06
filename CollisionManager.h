#pragma once
#include "singleton.h"
class Collider;

class CollisionManager :
	public singleton<CollisionManager>
{

private:
	texture* map;
	float Scale = 10.f;

	list<Collider*> l_Collider;

public:
	CollisionManager();
	virtual ~CollisionManager();

	bool PixelCollider(Vector3* pos, CGameObject* target, int mW, int mH, int CellSpacingX, int CellSpacingZ);

	void MapChange(texture* _map)
	{
		map = _map;
	}

	void AddCollider(Collider* col);
	void RemoveCollider(Collider* col);
	list<Collider*> GetColliderList()
	{
		return l_Collider;
	}

	void Update();

};

#define COLLISION CollisionManager::GetInstance()