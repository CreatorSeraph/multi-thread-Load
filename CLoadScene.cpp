#include "DXUT.h"
#include "CLoadScene.h"


CLoadScene::CLoadScene()
{
}


CLoadScene::~CLoadScene()
{
}

void CLoadScene::Init()
{
	//Load(L"player", L"./Image/obj/thief%df.obj", 40, LoadType::meshType);

	MaxLoad = m_Load.size();

	StartLoad();
}

void CLoadScene::StartLoad(int threadCount)
{
	CurLoad = 0;
	auto loadFunc = [&](int startIdx, int endIdx) {
		for (int i = startIdx; i < endIdx; ++i)
		{
			if (i >= MaxLoad) continue;

			auto loadData = m_Load[i];
			switch (loadData.type)
			{
			case LoadType::meshType:
			{
				if (loadData.count == 0)
					IMAGE->GetMesh(loadData.key, loadData.path);
				else
					IMAGE->GetVecMesh(loadData.key, loadData.path, loadData.count);
			}
				break;
			case LoadType::textureType:
			{
				if (loadData.count == 0)
					IMAGE->GetTexture(loadData.key, loadData.path);
				else
					IMAGE->GetVecTexture(loadData.key, loadData.path, loadData.count);
			}
				break;
			default:
				break;
			}
			++CurLoad;
		}
	};

	for (int i = 0; i < MaxLoad; i += MaxLoad / threadCount + 1)
	{
		auto t = thread(loadFunc, i, i + MaxLoad / threadCount + 1);
		t.detach();
	}
}

void CLoadScene::Update()
{
	SCENE->CHANGESCENE(L"Title");
	if (CurLoad == MaxLoad)
	{
		SCENE->CHANGESCENE(L"Title");
	}
	else
	{

	}
}

void CLoadScene::Render()
{
}

void CLoadScene::Destroy()
{
}

void CLoadScene::LoadResource(const Pass& pass)
{
	IMAGE->GetVecMesh(pass.key, pass.path, pass.count);
}
