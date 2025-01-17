#pragma once
#include "singleton.h"
class CMeshLoader;
struct texture
{
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 texturePtr, const D3DXIMAGE_INFO& info, int count = 0)
		:texturePtr(texturePtr), info(info)
	{
	}
};

class ImageManager :
	public singleton<ImageManager>
{
private:
	LPD3DXSPRITE mSprite;
	LPD3DXFONT font;
	map<wstring, texture*> mTexture;
	map<wstring, CMeshLoader*> mMesh;

	wstring mtlKey;

public:
	ImageManager();
	virtual ~ImageManager();
	
	texture* GetTexture(const wstring& key, const wstring& path);
	vector<texture*> GetVecTexture(const wstring& key, const wstring& path, int count);

	CMeshLoader* GetMesh(const wstring& key, const wstring& path, bool bFirst = false);
	vector<CMeshLoader*> GetVecMesh(const wstring& key, const wstring& path, int count);

	void PrintText(const wstring& text, Vector3 pos, D3DCOLOR color);

	wstring GetMtlPath() { return mtlKey; }

	LPD3DXSPRITE GetSprite() { return mSprite; }



	void Begin(bool isInterface);
	void End();

	void RESETDEVICE();
	void LOSTDEVICE();
};

#define IMAGE ImageManager::GetInstance()
