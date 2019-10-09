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
	CAMERA->Update();
	INPUT->Update();
	SCENE->Update();
}

void CMainGame::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(false);
	SCENE->Render();
	IMAGE->End();

	static DWORD frameCount = 0;            //������ ī��Ʈ��
	static float timeElapsed = 0.0f;            //�帥 �ð�
	static DWORD lastTime = timeGetTime();   //������ �ð�(temp����)

	DWORD curTime = timeGetTime();      //���� �ð�
	float timeDelta = (curTime - lastTime)*0.001f;        //timeDelta(1�������� �帥 �ð�) 1�ʴ����� �ٲ��ش�.

	timeElapsed += timeDelta;

	frameCount++;

	if (timeElapsed >= 1.0f)         //�帥�ð��� 1���̻��̸� ���� �ϰ������ ó��
	{
		int fps = (float)frameCount / timeElapsed;
		IMAGE->Begin(true);
		
		IMAGE->PrintText(L"FPS : " + to_wstring(fps), Vector3(CAMERA->GetScreenPos().x, CAMERA->GetScreenPos().y, 0)
			, D3DCOLOR_ARGB(255, 0, 0, 0), 30, false);
		
		IMAGE->End();

		Fps = fps;
		frameCount = 0;
		timeElapsed = 0.0f;
	}
	else
	{
		IMAGE->Begin(true);

		IMAGE->PrintText(L"FPS : " + to_wstring(Fps), Vector3(CAMERA->GetScreenPos().x, CAMERA->GetScreenPos().y, 0)
			, D3DCOLOR_ARGB(255, 0, 0, 0), 30, false);

		IMAGE->End();
	}
	lastTime = curTime;

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
