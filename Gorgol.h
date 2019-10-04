#pragma once
#include "Component.h"
class Gorgol :
	public Component
{
public:
	Gorgol();
	virtual ~Gorgol();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* other);

	void Update2();
};

