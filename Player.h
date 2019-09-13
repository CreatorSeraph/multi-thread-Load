#pragma once
#include "Component.h"
class Player :
	public Component
{
private:

public:
	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;
};

