#include "DXUT.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

bool CollisionManager::PixelCollider(Vector3 * pos, CGameObject * target, 
	int mW, int mH, int CellSpacingX, int CellSpacingZ)
{
	if(!target)
	{
		DEBUG_LOG("Find failed target(collisionManager)");
		return false;
	}
	if (!map)
	{
		DEBUG_LOG("Find failed map(collisionManager)");
		return false;
	}


	Vector3 CheckPos = (*pos) / Scale;
	D3DLOCKED_RECT lockRect;
	bool ret;

	map->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lockRect.pBits);


	int posX = (int)CheckPos.x / CellSpacingX;
	int posY = (int)CheckPos.y;
	int posZ = (int)CheckPos.z / CellSpacingZ;

	int tW = (map->info.Width);
	int tH = (map->info.Height);

	//if (posX < 0 || posX > tW || posZ > tH || posZ < 0)
	//{
	//	map->texturePtr->UnlockRect(0);
	//	return true;
	//}

	D3DXCOLOR color = dwColor[posZ + (map->info.Height / 2) * tW +
		posX + (map->info.Width /2)];


	int checkx = posZ + (map->info.Height / 2);
	int checkz = posX + (map->info.Width / 2);


	DEBUG_LOG(checkx << " X");
	DEBUG_LOG(checkz << " Z");


	//D3DCOLORVALUE value = GetColor(color);

	if (color.r > -posY)
	{
		map->texturePtr->UnlockRect(0);
		return true;
	}


	map->texturePtr->UnlockRect(0);
	return false;
}

void CollisionManager::AddCollider(Collider * col)
{
	l_Collider.emplace_back(col);
}

void CollisionManager::RemoveCollider(Collider * col)
{
	l_Collider.remove(col);
}

void CollisionManager::Update()
{
	if (l_Collider.size() < 2)
		return;

	for (auto iter : l_Collider)
	{
		for (auto Iter : l_Collider)
		{
			if (Iter == iter)
				continue;

			if (Iter->GetActor()->collider->GetColliderType() !=
				iter->GetActor()->collider->GetColliderType())
				continue;


			if ((Iter->GetActor()->collider->GetColliderType() ==
				iter->GetActor()->collider->GetColliderType())
				== ColliderType::spriteBox)
			{
				RECT out;
				if (IntersectRect(&out, &Iter->GetWorldRange(), &iter->GetWorldRange()))
				{
					Iter->GetActor()->OnCollision(iter);
					iter->GetActor()->OnCollision(Iter);
				}
			}
			else if ((Iter->GetActor()->collider->GetColliderType() ==
				iter->GetActor()->collider->GetColliderType())
				== ColliderType::MeshSphere)
			{
				float centerLength = D3DXVec3Length(&(Iter->GetActor()->collider->GetCenter() -
					iter->GetActor()->collider->GetCenter()));

				float radiusLength = Iter->GetActor()->collider->getlength() + 
					iter->GetActor()->collider->getlength();

				if (radiusLength >= centerLength)
				{
					Iter->GetActor()->OnCollision(iter);
					iter->GetActor()->OnCollision(Iter);
				}
			}

			
		}
	}
}
