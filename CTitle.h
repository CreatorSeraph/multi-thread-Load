#pragma once
#include "CScene.h"

class Terrain;
class CTitle :
	public CScene
{
private:
	CGameObject* player;
	Renderer* p_renderer;

	Terrain* heightmap;
public:
	CTitle();
	virtual ~CTitle();


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

