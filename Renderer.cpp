#include "DXUT.h"
#include "CGameObject.h"
#include "Actor.h"
#include "Component.h"
#include "Transform.h"
#include "Renderer.h"
#include "MeshLoader.h"
#include "CFrame.h"

//http://occamsrazr.net/tt/323 variant�� �����ΰ�?
//https://www.kudryavka.me/?p=267 variant�� �̿��� visit������ ����, visit�� ��� ����ϴ°�

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...)->overload<Ts...>;//��! ���ø�!

Renderer::Renderer(RenderType type, const wstring& key, const wstring& path, int count)
	:renderType(type), frame(nullptr)
{
	switch (type)
	{
	case mesh:
		resource = IMAGE->GetMesh(key, path);
		break;
	case vecmesh:
		resource = IMAGE->GetVecMesh(key, path, count);
		frame = new CFrame();
		break;
	case img:
		resource = IMAGE->GetTexture(key, path);
		break;
	case vecimg:
		resource = IMAGE->GetVecTexture(key, path, count);
		frame = new CFrame();
		break;
	default:
		break;
	}
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	if(frame)
		delete frame;
}

void Renderer::ChangeMesh(const wstring & key, const wstring & path, int count)
{
	switch (renderType)
	{
	case mesh:
		resource = IMAGE->GetMesh(key, path);
		break;
	case vecmesh:
		resource = IMAGE->GetVecMesh(key, path, count);
		break;
	case img:
		resource = IMAGE->GetTexture(key, path);
		break;
	case vecimg:
		resource = IMAGE->GetVecTexture(key, path, count);
		break;
	default:
		break;
	}
}

void Renderer::Init()
{
	GetActor()->renderer = this;
	OBJMANAGER->AddRenderer(this);
}

void Renderer::Render()
{
	if (frame)
		if(IsFrame)
			frame->Frame();

	std::visit(overload{
		[&](CMeshLoader* Mesh3d) {
			g_device->SetTransform(D3DTS_WORLD, &GetActor()->transform->GetWorldMatrix());
			g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			for (int i = 0; i < Mesh3d->GetNumMaterials(); ++i)
			{
				g_device->SetTexture(0, Mesh3d->GetMaterial(i)->pTexture);
				Mesh3d->GetMesh()->DrawSubset(i);
			}
		},
		[&](vector<CMeshLoader*> VecMesh3d) {
			g_device->SetTransform(D3DTS_WORLD, &GetActor()->transform->GetWorldMatrix());
			g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			for (int i = 0; i < VecMesh3d[frame->CurF]->GetNumMaterials(); ++i)
			{
				g_device->SetTexture(0, VecMesh3d[frame->CurF]->GetMaterial(i)->pTexture);
				VecMesh3d[frame->CurF]->GetMesh()->DrawSubset(i);
			}
		},
		[&](texture* Img) {
			IMAGE->Begin(IsBegin);
			IMAGE->GetSprite()->SetTransform(&GetActor()->transform->GetWorldMatrix());
			IMAGE->GetSprite()->Draw(Img->texturePtr, nullptr, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255,255,255,255));
			IMAGE->End();
		},
		[&](vector<texture*> VecImg) {
			IMAGE->Begin(IsBegin);
			IMAGE->GetSprite()->SetTransform(&GetActor()->transform->GetWorldMatrix());
			IMAGE->GetSprite()->Draw(VecImg[frame->CurF]->texturePtr, nullptr, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			IMAGE->End();
		}
		}, resource);
}


void Renderer::Destroy()
{
	OBJMANAGER->DeleteRenderer(this);
	if (GetActor()->renderer == this)
		GetActor()->renderer = nullptr;
}
