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
	//terrain = new Terrain(IMAGE->GetTexture(L"height", L"./Image/HeightMap.png"), IMAGE->GetTexture(L"heightmap", L"./Image/maping.png"), 3, 3, 1.f);
	Actor* player = ACTOR->Create(TagType::BACKGROUND, false);
	player->AddComponent<Player>();
	player->AddComponent<Transform>();
	player->AddComponent<Rigidbody>();
	player->AddComponent<Renderer>();
	player->AddComponent<Collider>();
}

void CTitle::Update()
{
	//terrain->getHeight(player->transform->GetPos().x, player->transform->GetPos().z);
	ACTOR->Update();

}

void CTitle::Render()
{
	//terrain->Render();
}

void CTitle::Destroy()
{
	//terrain->Destroy();
	
	//delete terrain;
}
