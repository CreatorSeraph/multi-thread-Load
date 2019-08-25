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

	CFrame frame;

public:
	Renderer(RenderType type, const wstring& key, const wstring& path, int count = 0);
	virtual ~Renderer();

	CFrame& Getframe() { return frame; }

	virtual void Init() override;

	virtual void Render();

	virtual void Destroy() override;

	
};

