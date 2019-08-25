#pragma once
#include "CScene.h"
class CTitle :
	public CScene
{
private:
	CGameObject* player;
public:
	CTitle();
	virtual ~CTitle();


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

