#include "DXUT.h"
#include "Component.h"
#include "Actor.h"


Component::Component()
	: b_Enable(true), b_Delete(false)
{
}


Component::~Component()
{
}

Transform * Component::GetTransform()
{
	return actor->transform;
}

Renderer * Component::GetRenderer()
{
	return actor->renderer;
}

Collider * Component::GetCollider()
{
	return actor->collider;
}

Rigidbody * Component::GetRigidbody()
{
	return actor->rigidbody;
}
