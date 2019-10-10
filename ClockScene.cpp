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
	CAMERA->SetCameraPos(Vector3(0.f, 0.f, 1000.f));
	CAMERA->SetAtPos(Vector3(0.f, 0.f, 0.f));


	D3DXCreateSphere(g_device, 10.0f, 30, 15, &(*sphereMesh)[0], NULL);
	D3DXCreateSphere(g_device, 11.0f, 33, 16.f, &(*sphereMesh)[1], NULL);

	D3DXMatrixIdentity(&mat[0]);
	D3DXMatrixIdentity(&mat[1]);

	pos[0] = Vector3(0.f, 0.f, 0.f);
	pos[1] = Vector3(0.f, 0.f, 0.f);
}

void ClockScene::Update()
{
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

	(*sphereMesh)[0]->DrawSubset(0);

	g_device->SetTransform(D3DTS_WORLD, &mat[1]);

	(*sphereMesh)[1]->DrawSubset(0);

	
	g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
}

void ClockScene::Destroy()
{
	if(*sphereMesh[0])
		SAFE_RELEASE(*sphereMesh[0]);
	if (*sphereMesh[1])
		SAFE_RELEASE(*sphereMesh[1]);
}
