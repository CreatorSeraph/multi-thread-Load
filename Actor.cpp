#include "DXUT.h"
#include "Actor.h"

#include "Component.h"

#include "Renderer.h"
#include "Transform.h"

#define ComponentsAction( DO ) \
for (auto &iter: m_mapComponents) \
{ \
	(iter.second)->DO; \
}

void Actor::Initialize()
{

}

void Actor::Update()
{
	ComponentsAction(Update());
}

void Actor::Release()
{
	for (auto iter : m_mapComponents)
	{
		iter.second->Destroy();
		SAFE_DELETE(iter.second);
	}

	m_mapComponents.clear();
}

void Actor::OnVisible()
{
	ComponentsAction(OnVisible());
}

void Actor::OnUnvisible()
{
	ComponentsAction(OnUnvisible());
}

void Actor::OnEnable()
{
	ComponentsAction(OnEnable());
}

void Actor::OnDisable()
{
	ComponentsAction(OnDisable());
}

void Actor::OnDestroy()
{
	ComponentsAction(OnDestroy());
}

void Actor::OnCollision(Collider* other)
{
	ComponentsAction(OnCollision(other));
}

void Actor::SetIsLive(bool value)
{
	if (m_bLive == value)
		return;

	m_bLive = value;

	if (m_bLive == false)
	{
		OnDestroy();
	}
}

void Actor::SetIsVisible(bool value)
{
	if (m_bVisible == value)
		return;

	m_bVisible = value;

	if (m_bVisible == true)
	{
		OnVisible();
	}
	else
	{
		OnUnvisible();
	}
}

void Actor::SetIsActive(bool value)
{
	if (m_bActive == value)
		return;

	m_bActive = value;

	if (m_bActive == true)
	{
		OnEnable();
	}
	else
	{
		OnDisable();
	}
}
