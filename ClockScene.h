#pragma once
#include "CScene.h"

class ClockScene :
	public CScene
{
private:
	LPD3DXMESH sphereMesh[10];
	Vector3 pos[10];
	Matrix mat[10];

	float angle[10] = {0,};

	system_clock::time_point timepoint[10];
public:
	ClockScene();
	~ClockScene();

	virtual void Update() override;
	virtual void Init() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

