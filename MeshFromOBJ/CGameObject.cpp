#include "DXUT.h"
#include "CGameObject.h"
#include "Component.h"
#include "Transform.h"


CGameObject::CGameObject()
{
	transform = new Transform();
	transform->SetTransform(transform);
	transform->SetGameObject(this);
	l_com.emplace_back(transform);
}


CGameObject::~CGameObject()
{
}

void CGameObject::ComDestroy()
{
	for (auto Iter : l_com)
	{
		Iter->Destroy();
		SAFE_DELETE(Iter);
	}

	l_com.clear();
}

void CGameObject::ComUpdate()
{
	for (auto iter = l_com.begin(); iter != l_com.end();)
	{
		if ((*iter)->GetDelete())
		{
			(*iter)->Destroy();
			SAFE_DELETE(*iter);

			iter = l_com.erase(iter);
		}
		else if((*iter)->GetEnable())
		{
			(*iter)->Update();
			++iter;
		}
	}
}
