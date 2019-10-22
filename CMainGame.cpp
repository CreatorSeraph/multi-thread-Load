#include "DXUT.h"
#include "CMainGame.h"
#include "CTitle.h"
#include "TestScene.h"
#include "CLoadScene.h"
#include "ClockScene.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{
	g_device->SetRenderState(D3DRS_LIGHTING, false);

	SCENE->ADDSCENE(L"Load", new CLoadScene());
	SCENE->ADDSCENE(L"Test", new TestScene());
	SCENE->ADDSCENE(L"Title", new CTitle());
	SCENE->ADDSCENE(L"Clock", new ClockScene());

	SCENE->CHANGESCENE(L"Test");
}

void CMainGame::Update()
{
	INPUT->Update();
	CAMERA->Update();
	ACTOR->Update();
	SCENE->Update();
}

void CMainGame::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(false);
	SCENE->Render();
	IMAGE->End();

	IMAGE->Begin(true);

	TCHAR FPS_MSG[200];
	swprintf(FPS_MSG, L"FPS : %.f", DXUTGetFPS());
	IMAGE->PrintText(FPS_MSG, Vector3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	IMAGE->End();

}

void CMainGame::Destroy()
{
	ImageManager::DestroyInstance();
	SceneManager::DestroyInstance();
	ObjectManager::DestroyInstance();
	CameraManager::DestroyInstance();
	InputManager::DestroyInstance();
	CollisionManager::DestroyInstance();
	ActorManager::DestroyInstance();
}

void CMainGame::LostDevice()
{
	IMAGE->RESETDEVICE();
}

void CMainGame::ResetDevice()
{
	IMAGE->LOSTDEVICE();
}
