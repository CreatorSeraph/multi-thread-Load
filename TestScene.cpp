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
	//m_tp.AddFunc([&]() {IMAGE->GetVecMesh(L"Palyer_Run", L"./Image/obj/thief_run%df.obj", 24); });
	//m_tp.AddFunc([&]() {IMAGE->GetVecMesh(L"player", L"./Image/obj/thief%df.obj", 40); });
	//for (int i = 0; i < 24; ++i)
	//{
	//	//m_tp.AddFunc([i]() {IMAGE->GetVecMesh(L"Plyaer_Run", L"./Image/obj/thief_run%df", i); });
	//	
	//	
	//	//m_tp.AddFunc([i]() {IMAGE->GetMesh(L"Player_Idle", L"./Image/obj/thief%df.obj", i); });
	//
	//
	//	//m_tp.AddFunc([i]() {
	//	//	cout << i << endl;
	//	//});
	//	//
	//	//auto func1 = [](int val) {
	//	//	cout << val << endl;
	//	//	return val + 1;
	//	//};
	//	//
	//	//auto func2 = [](int val) {
	//	//	cout << val << endl;
	//	//};
	//	//
	//	//m_result[i] = m_tp.AddFunc(func1, i);
	//	//m_tp.AddFunc(func2, i);
	//}
	//for (int i = 0; i < 41; ++i)
	//{
	//	//m_tp.AddFunc([i]() {IMAGE->GetVecMesh(L"player", L"./Image/obj/thief%df.obj", i); });
	//}
}

void TestScene::Update()
{
	if (m_tp.isEmpty())
	{
		//for (auto& iter : m_result)
		//	cout << "hi" << iter.get() << endl;
		SCENE->CHANGESCENE(L"Title");
	}
}

void TestScene::Render()
{
}

void TestScene::Destroy()
{
}
