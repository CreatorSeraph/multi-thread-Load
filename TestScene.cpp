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
	for (int i = 0; i < 10; ++i)
	{
		//m_tp.AddFunc([i]() {
		//	cout << i << endl;
		//});

		auto func = [](int val) {
			cout << val << endl;
		};

		m_tp.AddFunc(func, i);
	}

	m_tp.AddFunc([&]() { IMAGE->GetVecMesh(L"Player_Idle", L"./Image/obj/thief%df.obj", 40); });


}

void TestScene::Update()
{
	if (m_tp.isEmpty())
		SCENE->CHANGESCENE(L"Title");
}

void TestScene::Render()
{
}

void TestScene::Destroy()
{
}
