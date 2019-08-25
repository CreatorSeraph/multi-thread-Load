#pragma once
#include "singleton.h"
#include "Renderer.h"
#include "CGameObject.h"


class ObjectManager :
	public singleton<ObjectManager>
{
private:
	list<CGameObject*> l_Obj;
	list<Renderer*> l_Ren;
public:
	ObjectManager();
	virtual ~ObjectManager();

	CGameObject* Instance()
	{
		CGameObject* obj = new CGameObject;
		l_Obj.emplace_back(obj);
		return obj;
	}

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


	void Update();
	void Render();

	void ResetComponents();

};

#define OBJMANAGER ObjectManager::GetInstance()