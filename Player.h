#pragma once
#include "Component.h"
class Player :
	public Component
{
private:
	Renderer* renderer;
public:
	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* other);

	void Update2();
};

