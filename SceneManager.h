#pragma once
#include "singleton.h"

class CScene;
class SceneManager :
	public singleton<SceneManager>
{
private:
	CScene* NowScene;
	CScene* NextScene;
	map<wstring, CScene*> SCENES;
public:
	SceneManager();
	virtual ~SceneManager();

	CScene* ADDSCENE(const wstring& key, CScene* scenePtr);
	CScene* CHANGESCENE(const wstring& key);

	void Update();
	void Render();
	void Destroy();

};

#define SCENE SceneManager::GetInstance()

