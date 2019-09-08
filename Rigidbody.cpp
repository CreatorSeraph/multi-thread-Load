#include "DXUT.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Collider.h"
#include "Actor.h"

void Rigidbody::Init()
{
	GetActor()->rigidbody = this;
}

void Rigidbody::Update()
{
	m_vVelocity += m_vForce;
	m_vForce = Vector3(0.f, 0.f, 0.f);

		GetTransform()->v_pos += m_vVelocity;

	m_vVelocity *= m_fFriction;
}

void Rigidbody::Destroy()
{
	if (GetActor()->rigidbody == this)
		GetActor()->rigidbody = nullptr;
}

void Rigidbody::OnCollision(Collider* other)
{
	if (m_bIsPhysicalTreatment == true)
	{
		Vector3 EndPosition = GetTransform()->v_pos;
		Vector3 TargetPosition = other->GetTransform()->v_pos;

		Vector3 Direction = EndPosition - TargetPosition;

		float Length = D3DXVec3Length(&Direction);

		D3DXVec3Normalize(&Direction, &Direction);

		AddForce(Direction * Length * DeltaTime);
	}
}

void Rigidbody::AddForce(const Vector3& force)
{
	m_vForce += force;
}

void Rigidbody::AddForce(const Vector2& force)
{
	m_vForce += Vector3(force.x, force.y, 0);
}

void Rigidbody::AddForce(float x, float y, float z)
{
	m_vForce += Vector3(x, y, z);
}

void Rigidbody::AddForce(float x, float y)
{
	m_vForce += Vector3(x, y, 0);
}

void Rigidbody::MovePosition(const Vector3& position)
{
	GetTransform()->v_pos = position;
}
