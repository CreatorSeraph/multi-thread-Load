#include "DXUT.h"
#include "ActorManager.h"

#include "Actor.h"
#include "Transform.h"


#define COMPONENTTYPE_TRANSFORM (1 << 1)
#define COMPONENTTYPE_RENDERER  (1 << 2)

// TODO: Setting default component modules.
#define DEFAULT_COMPONENT	COMPONENTTYPE_TRANSFORM | COMPONENTTYPE_RENDERER


Actor* ActorManager::Create(int tag, bool isVisible, bool isActive)
{
	Actor* A = new Actor(tag, isVisible, isActive);

#if (DEFAULT_COMPONENT & COMPONENTTYPE_TRANSFORM)
	A->AddComponent<Transform>();
#endif

//#if (DEFAULT_COMPONENT & COMPONENTTYPE_RENDERER)
//	A->AddComponent<Renderer>();
//#endif

	m_listActors.push_back(A);

	return A;
}

Actor* ActorManager::CreateEmpty(int tag, bool isVisible, bool isActive)
{
	Actor* A = new Actor(tag, isVisible, isActive);

	m_listActors.push_back(A);

	return A;
}

void ActorManager::Update()
{
	for (auto iter : m_listActors)
	{
		if (iter->IsLive == true)
		{
			if (iter->IsActive)
			{
				iter->Update();
			}
		}
	}
}

void ActorManager::Reset()
{
	for(auto iter : m_listActors)
	{
		iter->Release();
		
		SAFE_DELETE(iter);
	}

	m_listActors.clear();
}
