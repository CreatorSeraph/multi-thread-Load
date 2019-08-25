#include "DXUT.h"
#include "CTitle.h"
#include "Transform.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}

void CTitle::Init()
{
	player = OBJMANAGER->Instance();
	player->AddComponent<Renderer>(RenderType::vecmesh, L"player", L"./Image/obj/thief%df.obj", 5);// ->AddVecMesh(L"player", L"./Image/obj/thief%df.obj", 5);
	//player->AddComponent<Renderer>()->AddVecMesh(L"player", L"./Image/Soldier/walk%d.obj", 5);
	CAMERA->SetGameObject(player);
	//player->transform->GetSize() - Vector3(0.99f, 0.99f, 0.99f);
	player->transform->SetSize(Vector3(0.5f, 0.5f, 0.5f));
	player->renderer->Getframe().SetFrame(0, 5, 30);

	player->GetComponent<Renderer>();
}

void CTitle::Update()
{
	player->renderer->Getframe()();
}

void CTitle::Render()
{
}

void CTitle::Destroy()
{
}
