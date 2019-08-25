#include "DXUT.h"
#include "ObjectManager.h"
#include "Transform.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	ResetComponents();
}

void ObjectManager::Update()
{
	for (auto iter = l_Obj.begin(); iter != l_Obj.end();)
	{
		if ((*iter)->GetbDeleteTag())
		{
			(*iter)->ComDestroy();
			SAFE_DELETE(*iter);
			iter = l_Obj.erase(iter);
		}
		else if((*iter)->GetbActive())
		{
			(*iter)->ComUpdate();
			(*iter)->transform->TransformUpdate();
			++iter;
		}
	}
}

void ObjectManager::Render()
{
	for (auto iter : l_Ren)
	{
		iter->Render();
	}
}

void ObjectManager::ResetComponents()
{
	for (auto iter : l_Obj)
	{
		iter->ComDestroy();

		SAFE_DELETE(iter);
	}
	l_Obj.clear();
}
