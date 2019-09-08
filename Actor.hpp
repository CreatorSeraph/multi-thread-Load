#pragma once

#include "Transform.h"
#include "Renderer.h"
#include "Actor.h"

template<class COM>
inline COM* Actor::AddComponent()
{
	string typeID = typeid(COM).name();

	if (auto find = m_mapComponents.find(typeID); find == m_mapComponents.end())
	{
		COM* component = new COM();

		// TODO: initialize variable 'component'

		component->SetActor(this);
		component->Init();

		m_mapComponents.insert(std::make_pair(typeID, component));

		return component;
	}

	return nullptr;
}

template<class COM>
inline COM* Actor::GetComponent()
{
	string typeID = typeid(COM).name();

	if (auto find = m_mapComponents.find(typeID); find != m_mapComponents.end())
	{
		return static_cast<COM*>(find->second);
	}

	return nullptr;
}