#include "DXUT.h"
#include "CMainGame.h"
#include "CTitle.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{
	g_device->SetRenderState(D3DRS_LIGHTING, false);

	SCENE->ADDSCENE(L"Title", new CTitle());

	SCENE->CHANGESCENE(L"Title");
}

void CMainGame::Update()
{
	CAMERA->Update();
	INPUT->Update();
	SCENE->Update();
}

void CMainGame::Render()
{
	CAMERA->CalculatorProjMatrix();
	CAMERA->CalculatorViewMatrix();
	CAMERA->SetTransform();

	IMAGE->Begin(false);
	SCENE->Render();
	IMAGE->End();
}

void CMainGame::Destroy()
{
	ImageManager::DestroyInstance();
	SceneManager::DestroyInstance();
	ObjectManager::DestroyInstance();
	CameraManager::DestroyInstance();
	InputManager::DestroyInstance();
	
}

void CMainGame::LostDevice()
{
	IMAGE->RESETDEVICE();
}

void CMainGame::ResetDevice()
{
	IMAGE->LOSTDEVICE();
}
