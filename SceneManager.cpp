#include "DXUT.h"
#include "SceneManager.h"
#include "CScene.h"


SceneManager::SceneManager()
	:NowScene(nullptr), NextScene(nullptr)
{
}


SceneManager::~SceneManager()
{
	Destroy();
}

CScene * SceneManager::ADDSCENE(const wstring & key, CScene * scenePtr)
{
	if (auto iter = SCENES.find(key); iter == SCENES.end())
	{
		SCENES.insert(make_pair(key, scenePtr));
		return scenePtr;
	}
	else
	{
		return iter->second;
	}

	
	return nullptr;
}

CScene * SceneManager::CHANGESCENE(const wstring & key)
{
	if (auto iter = SCENES.find(key); iter == SCENES.end())
		return nullptr;
	else
		NextScene = iter->second;

	return NextScene;
}

void SceneManager::Update()
{
	if (NextScene)
	{
		if (NowScene)
		{
			NowScene->Destroy();
			//OBJMANAGER->ResetComponents();
		}
		NextScene->Init();
		NowScene = NextScene;
		NextScene = nullptr;
	}
	else if (NowScene)
	{
		NowScene->Update();
		//OBJMANAGER->Update();
	}
}

void SceneManager::Render()
{
	if (NowScene)
	{
		OBJMANAGER->Render();
		NowScene->Render();
	}
}

void SceneManager::Destroy()
{
	if (NowScene)
	{
		NowScene->Destroy();
		//OBJMANAGER->ResetComponents();
		//SAFE_DELETE(NowScene);
	}

	for (auto iter : SCENES)
	{
		SAFE_DELETE(iter.second);
	}
	SCENES.clear();
}
