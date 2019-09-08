#pragma once
#include "Component.h"

class Rigidbody :
	public Component
{
private:

	Vector3 m_vVelocity;
	Vector3 m_vForce;

	float m_fFriction = 0.8f;

	bool m_bIsPhysicalTreatment = false;

public:
	// Component을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;
	virtual void OnCollision(Collider* other) override;

	void AddForce(const Vector3& force);
	void AddForce(const Vector2& force);
	void AddForce(float x, float y, float z);
	void AddForce(float x, float y);

	void MovePosition(const Vector3& position);

public:

	Vector3 GetVelocity() { return m_vVelocity; }
	void SetVelocity(const Vector3& value) { m_vVelocity = value; }

	float GetFriction() { return m_fFriction; }
	void SetFriction(float value) { m_fFriction = value; }

	bool GetPhysicalTreatment() { return m_bIsPhysicalTreatment; }
	void SetPhysicalTreatment(bool value) { m_bIsPhysicalTreatment = value; }

	PropertyGS(GetVelocity, SetVelocity) Vector3 Velocity;
	PropertyGS(GetFriction, SetFriction) float Friction;
	PropertyGS(GetPhysicalTreatment, SetPhysicalTreatment) bool PhysicalTreatment;
};

