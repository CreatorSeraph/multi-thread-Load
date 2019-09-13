#include "DXUT.h"
#include "CTitle.h"
#include "Transform.h"
#include "Terrain.h"
#include "Actor.h"
#include "Player.h"


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

	player = ACTOR->Create(TagType::BACKGROUND);
	player->AddComponent<Player>();
	//player->AddComponent<Transform>();
	player->AddComponent<Rigidbody>();
	player->AddComponent<Renderer>(RenderType::vecmesh , L"player", L"./Image/obj/thief%df.obj", 1);
	player->AddComponent<Collider>();
	CAMERA->SetObjPos(player->GetComponent<Transform>());
}


void CTitle::Update()
{

	Vector3 pos = Vector3(player->GetTransform()->GetPos().x,
		terrain->getHeight(player->GetTransform()->GetPos().x, player->GetTransform()->GetPos().z),
		player->GetTransform()->GetPos().z);


	player->GetTransform()->SetPos(pos);
	
	ACTOR->Update();

}


void CTitle::Render()
{
	terrain->Render();
}


void CTitle::Destroy()
{
	ACTOR->Reset();
	terrain->Destroy();
	delete terrain;
}
