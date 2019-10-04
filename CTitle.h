#pragma once

#include "CScene.h"

class Terrain;
class CTitle :
	public CScene

{
private:
	Actor* player;
	Actor* gorgol;

	Transform* p_transform;
	Renderer* p_renderer;

	Vector3 vec = Vector3(0.f, 0.f, 0.f);

	Terrain* terrain;
public:
	CTitle();
	virtual ~CTitle();


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

