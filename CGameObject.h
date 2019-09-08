#pragma once
#include "Component.h"

class CGameObject
	: public Component
{
private:
	friend class ObjectManager;


	bool b_Active = true;
	bool b_DeleteTag = false;

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual void Destroy() {};

	bool GetbActive() { return b_Active; }
	bool GetbDeleteTag() { return b_DeleteTag; }

};

