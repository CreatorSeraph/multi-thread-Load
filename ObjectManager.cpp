#include "DXUT.h"
#include "ObjectManager.h"
#include "Transform.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Render()
{
	for (auto iter : l_Ren)
	{
		iter->Render();
	}
}

void ObjectManager::Destroy()
{
	for (auto iter : l_Ren)
	{
		SAFE_DELETE(iter);
	}

	l_Ren.clear();
}


