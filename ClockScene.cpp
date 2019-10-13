#include "DXUT.h"
#include "ClockScene.h"


ClockScene::ClockScene()
{
}


ClockScene::~ClockScene()
{
	//Destroy();
}

void ClockScene::Init()
{
	auto actor = ACTOR->Create(TagType::BACKGROUND);
	auto actor2 = ACTOR->Create(TagType::BACKGROUND);

	actor->AddComponent<Renderer>(RenderType::mesh, L"clock", L"./IMAGE/Clock/Character0f.obj", 0);
	actor->GetComponent<Transform>()->GetTransform()->SetPos(Vector3(0, 0, -50.f));
	actor->GetComponent<Transform>()->GetTransform()->SetSize(Vector3(-0.5, -0.5, -0.5));
	actor->GetComponent<Transform>()->GetTransform()->SetRotation(Vector3(-90, 0, 0));


	actor2->AddComponent<Renderer>(RenderType::mesh, L"clocks", L"./IMAGE/ClockSpire/Character0f.obj", 0);
	actor2->GetComponent<Transform>()->GetTransform()->SetPos(Vector3(0, 0, -30.f));
	actor2->GetComponent<Transform>()->GetTransform()->SetSize(Vector3(-0.5, -0.5, -0.5));
	actor2->GetComponent<Transform>()->GetTransform()->SetRotation(Vector3(90, 0, 0));

	CAMERA->SetCameraPos(Vector3(0.f, 0.f, 1000.f));
	CAMERA->SetAtPos(Vector3(0.f, 0.f, 0.f));


	D3DXCreateSphere(g_device, 3.0f, 30, 15, &(sphereMesh)[0], NULL);
	D3DXCreateSphere(g_device, 4.0f, 33, 16.f, &(sphereMesh)[1], NULL);

	D3DXMatrixIdentity(&mat[0]);
	D3DXMatrixIdentity(&mat[1]);

	pos[0] = Vector3(0.f, 0.f, 0.f);
	pos[1] = Vector3(0.f, 0.f, 0.f);
}

void ClockScene::Update()
{
	//Vector3 temp = Vector3(0.0f, 0.f, 100.f);
	//CAMERA->SetCameraPos(temp);
	duration<float> sec = GetNowTime - timepoint[0];



	if (sec.count() >= 1.f)
	{
		angle[0]++;
		if (angle[0] >= 360) 
		{
			angle[0] -= 360;
		}
		timepoint[0] = GetNowTime;
	}


	pos[0].x = 10 * cosf(D3DXToRadian(angle[0]));
	pos[0].y = 10 * sinf(D3DXToRadian(angle[0]));
	pos[1].x = 40 * cosf(D3DXToRadian(angle[0]));
	pos[1].y = 40 * sinf(D3DXToRadian(angle[0]));

}

void ClockScene::Render()
{

	g_device->SetRenderState(D3DRS_LIGHTING, false);
	g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	D3DXMatrixTranslation(&mat[0], pos[0].x, pos[0].y, 0.f);
	D3DXMatrixTranslation(&mat[1], pos[1].x, pos[1].y, 0.f);

	g_device->SetTransform(D3DTS_WORLD, &mat[0]);

	g_device->SetTexture(NULL, (IMAGE->GetTexture(L"maping", L"./Image/maping.png")->texturePtr));

	(sphereMesh)[0]->DrawSubset(0);

	g_device->SetTransform(D3DTS_WORLD, &mat[1]);

	(sphereMesh)[1]->DrawSubset(0);

	
	g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
}

void ClockScene::Destroy()
{
		SAFE_RELEASE(sphereMesh[0]);
		SAFE_RELEASE(sphereMesh[1]);
}
