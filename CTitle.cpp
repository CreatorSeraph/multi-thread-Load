#include "DXUT.h"
#include "CTitle.h"
#include "Transform.h"
#include "Terrain.h"
#include "Actor.h"
#include "Player.h"
#include "Gorgol.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}    

void CTitle::Init()
{
	terrain = new Terrain(IMAGE->GetTexture(L"height", L"./Image/HeightMap.png"), 
	IMAGE->GetTexture(L"heightmap", L"./Image/maping.png"), 3, 3, 1.f);

	//IMAGE->GetVecMesh(L"Plyaer_Run", L"./Image/obj/thief_run%df", 24);

	player = ACTOR->Create(TagType::BACKGROUND);
	player->AddComponent<Player>();
	player->AddComponent<Rigidbody>();
	player->AddComponent<Renderer>(RenderType::vecmesh , L"player", L"./Image/obj/thief%df.obj", 1);
	//player->AddComponent<Renderer>(RenderType::vecmesh, L"clud", L"./Image/dx_cloud_cha/Character%df.obj", 15);
	player->AddComponent<Collider>(ColliderType::MeshSphere, 10.f);

	//gorgol = ACTOR->Create(TagType::BACKGROUND);
	//gorgol->AddComponent<Gorgol>();
	//
	//
	//gorgol->AddComponent<Rigidbody>();
	//gorgol->AddComponent<Renderer>(RenderType::vecmesh, L"gorgol", L"./Image/gorgol/idle/gorgol_Idle%df.obj", 1);
	//gorgol->AddComponent<Collider>(ColliderType::MeshSphere, 10.f);

	p_renderer = player->GetComponent<Renderer>();
	p_renderer->Getframe()->SetFrame(0, 1, 50);
	p_renderer->SetFrame();

	//player->GetTransform()->SetSize(Vector3(0.02, 0.02, 0.02));
	p_transform = player->GetComponent<Transform>();
	p_transform->SetSize(Vector3(1, 1, 1));

	CAMERA->SetObjPos(player);

}


void CTitle::Update()
{

	Vector3 pos = Vector3(p_transform->GetPos().x,
		terrain->getHeight(p_transform->GetPos().x, p_transform->GetPos().z),
		p_transform->GetPos().z);

	//Vector3 gpos = Vector3(gorgol->GetTransform()->GetPos().x,
	//	terrain->getHeight(gorgol->GetTransform()->GetPos().x, gorgol->GetTransform()->GetPos().z),
	//	gorgol->GetTransform()->GetPos().z);


	p_transform->SetPos(pos);
	//gorgol->GetTransform()->SetPos(gpos);

}


void CTitle::Render()
{
	terrain->Render();
}


void CTitle::Destroy()
{
	terrain->Destroy();
	delete terrain;
}
