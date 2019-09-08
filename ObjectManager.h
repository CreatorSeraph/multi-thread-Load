#pragma once
#include "singleton.h"
#include "Renderer.h"
#include "CGameObject.h"


class ObjectManager :
	public singleton<ObjectManager>
{
private:
	list<Renderer*> l_Ren;
public:
	ObjectManager();
	virtual ~ObjectManager();

	Renderer* AddRenderer(Renderer* _render)
	{
		if (!_render)
			return nullptr;
		l_Ren.emplace_back(_render);
		return _render;
	}

	void DeleteRenderer(Renderer* _render)
	{
		l_Ren.remove(_render);
	}


	void Render();
	void Destroy();


};

#define OBJMANAGER ObjectManager::GetInstance()