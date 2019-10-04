#pragma once
#include "Component.h"
#include "CFrame.h"

#include <variant>

enum RenderType : char
{
	mesh,
	vecmesh,
	img,
	vecimg
};

class Renderer :
	public Component
{
private:
	RenderType renderType;

	variant<CMeshLoader*, vector<CMeshLoader*>, texture*, vector<texture*>> resource;

	CFrame* frame;

	bool IsFrame = false;

public:
	Renderer(RenderType type, const wstring& key, const wstring& path, int count = 0);
	Renderer();
	virtual ~Renderer();

	void ChangeMesh(const wstring& key, const wstring& path, int count = 0);

	CFrame* Getframe() { return frame; }
	void SetFrame() { IsFrame = !IsFrame; }

	virtual void Init() override;

	virtual void Render();

	virtual void Destroy() override;

	//virtual void OnCollisionEnter(CObject * _pObject) PURE;
	//virtual void OnCollisionStay(CObject * _pObject) PURE;
	//virtual void OnCollisionExit(CObject * _pObject) PURE;

	
};

