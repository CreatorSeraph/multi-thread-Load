#pragma once
#include "CScene.h"
#include "ThreadPool.h"

class TestScene :
	public CScene
{
private:
	ThreadPool m_tp;
public:
	TestScene();
	virtual ~TestScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

