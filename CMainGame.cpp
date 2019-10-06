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

	SCENE->CHANGESCENE(L"Clock");
}

void CMainGame::Update()
{
	timeDelta = (curTime - lastTime) * 0.0001f;
	timeElapsed += timeDelta;
	CAMERA->Update();
	INPUT->Update();
	SCENE->Update();
	frameCount++;
	if (timeElapsed >= 1.0f)
	{
		Fps = (float)frameCount / timeElapsed;
		frameCount = 0;
		timeElapsed = 0;
	}
	lastTime = curTime;
}

void CMainGame::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(false);
	SCENE->Render();
	IMAGE->Begin(true);
	IMAGE->PrintText(L"Fps: ", Vector3(CAMERA->GetScreenPos().x, CAMERA->GetScreenPos().y, 0)
		, D3DCOLOR_ARGB(255, 0, 0, 0), 10, false);

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
