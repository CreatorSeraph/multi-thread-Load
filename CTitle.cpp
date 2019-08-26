#include "DXUT.h"
#include "CTitle.h"
#include "Transform.h"
#include "Terrain.h"

CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}    

void CTitle::Init()
{

	

	player = OBJMANAGER->Instance();
	//player->AddComponent<Renderer>()->AddVecMesh(L"player", L"./Image/obj2/thief%df.obj", 40);
	//player->AddComponent<Renderer>()->AddVecMesh(L"player", L"./Image/Soldier/walk%d.obj", 5);
	player->AddComponent<Renderer>(RenderType::vecmesh, L"Player_Idle", L"./Image/obj/thief%df.obj", 40);
	//p_renderer = player->GetComponent<Renderer>();
	CAMERA->SetGameObject(player);
	//player->transform->GetSize() - Vector3(0.99f, 0.99f, 0.99f);
	player->transform->SetSize(Vector3(1.f, 1.f, 1.f));
	player->renderer->Getframe().SetFrame(0, 40, 30);

	//heightmap = new Terrain(g_device, );
}

void CTitle::Update()
{
	player->renderer->Getframe()();


	Vector3 camerapos = CAMERA->CameraPos() - player->transform->GetPos() ;

	D3DXVec3Normalize(&camerapos, &camerapos);

	float rot = atan2f(camerapos.y, camerapos.x);

 	player->transform->SetRotation(Vector3(0.f, D3DXToRadian(rot), 0.f));


	//float a = atan2f(CAMERA->GetRot().y, CAMERA->GetRot().x);
	//player->transform->SetRotation(Vector3(0.f, a, 0.f));

	

	if (KEYDOWN('W'))
		player->transform->SetPos(player->transform->GetPos() + Vector3(0.f, 0.f, 10.f * DeltaTime));

	

	//if (KEYDOWN('U'))
	//	player->transform->SetRotation(Vector3(0.f, 0.f, 0.f));
	//if (KEYDOWN('I'))
	//	player->transform->SetRotation(Vector3(0.f, CAMERA->GetRot().y, 0.f));


}

void CTitle::Render()
{
}

void CTitle::Destroy()
{
}
