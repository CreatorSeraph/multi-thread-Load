#include "DXUT.h"
#include "ImageManager.h"
#include "MeshLoader.h"


ImageManager::ImageManager()
	:mSprite(nullptr)
{
	D3DXCreateSprite(g_device, &mSprite);
	D3DXCreateFontW(g_device, 40, 0, 0, 1,
		FALSE, HANGUL_CHARSET, 0, 0, 0, L"���� ���� Bold", &font);
}

ImageManager::~ImageManager()
{
	for (auto iter : mTexture)
	{
		SAFE_RELEASE(iter.second->texturePtr);
		SAFE_DELETE(iter.second);
	}
	mTexture.clear();

	for (auto iter : mMesh) {
		SAFE_DELETE(iter.second);
	}


	mMesh.clear();
	SAFE_RELEASE(mSprite);
	SAFE_RELEASE(font);
}

texture* ImageManager::GetTexture(const wstring & key, const wstring & path)
{
	if (auto iter = mTexture.find(key); iter != mTexture.end())
		return iter->second;

	LPDIRECT3DTEXTURE9 lptexture;
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(path.c_str(), &info);
	if (D3DXCreateTextureFromFileEx(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, info.MipLevels, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &info, nullptr, &lptexture) == S_OK)
	{
		texture* tex = new texture(lptexture, info);
		mTexture.insert(make_pair(key, tex));
		return tex;
	}
	
	return nullptr;
}

vector<texture*> ImageManager::GetVecTexture(const wstring & key, const wstring & path, int count)
{
	vector<texture*> result;
	for (int i = 1; i <= count; ++i)
	{
		LPDIRECT3DTEXTURE9 lptexture;
		D3DXIMAGE_INFO info;

		wstring newKey = key + L"__" + to_wstring(i);

		wchar_t ch[256];
		wsprintf(ch, path.c_str(), i);

		result.push_back(GetTexture(newKey, ch));
	}
	return result;
}

CMeshLoader * ImageManager::GetMesh(const wstring & key, const wstring & path, bool bFirst)
{
	if (auto iter = mMesh.find(key); iter != mMesh.end())
		return iter->second;

	CMeshLoader* lpMesh = new CMeshLoader();
	lpMesh->bFirst = bFirst;
	lpMesh->Create(g_device, path);

	if (lpMesh)
	{
		mMesh.insert(make_pair(key, lpMesh));
		return lpMesh;
	}
	DEBUG_LOGW(" getmesh failed : " << path);

	return nullptr;
}

vector<CMeshLoader*> ImageManager::GetVecMesh(const wstring & key, const wstring & path, int count)
{
	vector<CMeshLoader*> result;

	for (int i = 0; i <= count; ++i)
	{
		wstring newKey = key + L"__" + to_wstring(i);
		wchar_t ch[256];
		wsprintf(ch, path.c_str(), i);
		result.push_back(GetMesh(newKey, ch, (i == 0)));
	}

	return result;
}

void ImageManager::PrintText(const wstring & text, Vector3 pos, D3DCOLOR color)
{
	Matrix mat;

	D3DXMatrixTranslation(&mat, 10, 10, 0);

	mSprite->SetTransform(&mat);
	font->DrawTextW(mSprite, text.c_str(), text.size(), NULL, DT_CENTER, color);
}

void ImageManager::Begin(bool isInterface)
{
	if (!isInterface)
		mSprite->Begin(D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_ALPHABLEND);

	// is object
	else
		mSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//is ui
}

void ImageManager::End()
{
	mSprite->End();
}

void ImageManager::RESETDEVICE()
{
	mSprite->OnResetDevice();
}

void ImageManager::LOSTDEVICE()
{
	mSprite->OnLostDevice();
}

