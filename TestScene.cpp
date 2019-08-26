#include "DXUT.h"
#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	for (int i = 0; i < loopCount; ++i)
	{
		m_tp.AddFunc([i]() {
			cout << i << endl;
		});

		auto func1 = [](int val) {
			cout << val << endl;
			return val + 1;
		};

		auto func2 = [](int val) {
			cout << val << endl;
		};

		m_result[i] = m_tp.AddFunc(func1, i);
		m_tp.AddFunc(func2, i);
	}

	//m_tp.AddFunc([&]() { IMAGE->GetVecMesh(L"Player_Idle", L"./Image/obj/thief%df.obj", 40); });
}

void TestScene::Update()
{
	if (m_tp.isEmpty())
	{
		for (auto& iter : m_result)
			cout << "hi" << iter.get() << endl;
		SCENE->CHANGESCENE(L"Title");
	}
}

void TestScene::Render()
{
}

void TestScene::Destroy()
{
}
