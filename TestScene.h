#pragma once
#include "CScene.h"
#include "ThreadPool.h"

class TestScene :
	public CScene
{
private:
	static constexpr int loopCount = 10;

	ThreadPool m_tp;
	std::future<int> m_result[loopCount];
public:
	TestScene();
	virtual ~TestScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

