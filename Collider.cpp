#include "DXUT.h"
#include "Actor.h"
#include "Collider.h"
#include "Transform.h"
#include "Actor.h"

/*
void Collider::Init()
{
	GetActor()->collider = this;

	COLLISION->AddCollider(this);
}

void Collider::Update()
{
	if (sphereData)
		sphereData->Translation(GetActor()->transform->v_pos);
	if (aabbData)
		aabbData->Translation(GetActor()->transform->v_pos);
}

void Collider::Destroy()
{
	if (GetActor()->collider == this)
		GetActor()->collider = nullptr;

	type = None;

	COLLISION->RemoveCollider(this);

	SAFE_DELETE(sphereData);
	SAFE_DELETE(aabbData);
}

void Collider::SetAsSphere(float radius)
{
	if (sphereData)
	{
		SAFE_DELETE(sphereData);
	}

	sphereData = new SphereData(radius);

	sphereData->center = GetActor()->transform->GetPos();

	type = Sphere;
}

void Collider::SetAsBox(float x, float y, float z)
{
	if (aabbData)
	{
		SAFE_DELETE(aabbData);
	}

	aabbData = new AABBData(x, y, z);

	aabbData->center = GetActor()->transform->GetPos();

	type = Box;
}

bool Collider::IsCollision(const Collider* col1, const Collider* col2)
{
	if (col1->type == None)
		return false;

	if (col2->type == None)
		return false;

	if (col1->type == Sphere &&
		col2->type == Sphere)
		return SphereData::IsCollision(col1->sphereData, col2->sphereData);

	if (col1->type == Box &&
		col2->type == Box)
		return AABBData::IsCollision(col1->aabbData, col2->aabbData);

	if (col1->type == Box &&
		col2->type == Sphere)
		return MixData::IsCollision(col1->aabbData, col2->sphereData);

	if (col1->type == Sphere &&
		col2->type == Box)
		return MixData::IsCollision(col1->sphereData, col2->aabbData);

	return false;
}

bool Collider::SphereData::IsCollision(const SphereData* a, const SphereData* b)
{
	Vector3 diff = b->center - a->center;
	float distance = D3DXVec3Length(&diff);

	if (distance <= (a->length + b->length))
	{
		return true;
	}

	return false;
}

void Collider::SphereData::Translation(const Vector3& center)
{
	this->center = center;
}

bool Collider::AABBData::IsCollision(const AABBData* a, const AABBData* b)
{
	Vector3 amax = a->GetMax();
	Vector3 bmax = b->GetMax();

	Vector3 amin = a->GetMin();
	Vector3 bmin = b->GetMin();

	if (amax.x < bmin.x || amin.x > bmax.x) return 0;
	if (amax.y < bmin.y || amin.y > bmax.y) return 0;
	if (amax.z < bmin.z || amin.z > bmax.z) return 0;
	return 1;

	return false;
}

void Collider::AABBData::Translation(const Vector3& center)
{
	this->center = center;
}

bool Collider::MixData::IsCollision(const AABBData* a, const SphereData* b)
{
	Vector3 min = a->GetMin();
	Vector3 max = a->GetMax();

	Vector3 sphereC = b->center;
	float radius = b->length;

	if (max.x < (sphereC.x - radius) || min.x >(sphereC.x + radius)) return false;
	if (max.y < (sphereC.y - radius) || min.y >(sphereC.y + radius)) return false;
	if (max.z < (sphereC.z - radius) || min.z >(sphereC.z + radius)) return false;

	return true;
}

bool Collider::MixData::IsCollision(const SphereData* a, const AABBData* b)
{
	return IsCollision(b, a);
}
*/

Collider::Collider(ColliderType _type, float width, float height)
	:c_sphere(nullptr)
{
	type = ColliderType::spriteBox;
	RECT* r;
	SetRect(&(*r), -width / 2, -height / 2, width / 2, height / 2);

	c_rect = r;
}

Collider::Collider(ColliderType _type, float radius)
	:c_rect(nullptr)
{
	type = ColliderType::MeshSphere;

	Sphere* empty = new Sphere(radius);

	c_sphere = empty;
}

Collider::Collider()
{
}

Collider::~Collider()
{
	if (c_sphere)
		delete (c_sphere);

	if (c_rect)
		delete (c_rect);
}

void Collider::Init()
{
	GetActor()->collider = this;
	if(type == ColliderType::MeshSphere)
		c_sphere->center = GetActor()->transform->GetPos();
}

void Collider::Update()
{
}

void Collider::Destroy()
{
}

RECT Collider::GetWorldRange()
{
	RECT ret;

	ret.left = c_rect->left + GetActor()->GetTransform()->GetPos().x;
	ret.right = c_rect->right + GetActor()->GetTransform()->GetPos().x;
	ret.top = c_rect->top + GetActor()->GetTransform()->GetPos().y;
	ret.bottom = c_rect->bottom + GetActor()->GetTransform()->GetPos().y;

	return ret;
}