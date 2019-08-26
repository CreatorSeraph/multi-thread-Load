#pragma once
#include "CScene.h"

enum class LoadType : char
{
	meshType,
	textureType,
};

class CLoadScene :
	public CScene
{
private:
	int CurLoad = 0;
	int MaxLoad = 0;


	vector<thread> m_thread;

	struct Pass
	{
		wstring key;
		wstring path;
		LoadType type;
		int count;
		Pass(const wstring& key, const wstring& path, int count, LoadType type)
			:key(key), path(path), count(count), type(type)
		{
		}
	};

	vector<Pass> m_Load;
	void Load(const wstring& key, const wstring& path, int count, LoadType type)
	{
		m_Load.emplace_back(key, path, count, type);
	}
	void StartLoad(int threadCount = 4);
public:
	CLoadScene();
	virtual ~CLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void LoadResource(const Pass& pass);

};

