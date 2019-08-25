#pragma once
#include "Component.h"
class Transform :
	public Component
{
private:
	Vector3 v_pos = Vector3(0.f, 0.f, 0.f);
	Vector3 vRotation = Vector3(0.f, 0.f, 0.f);
	Vector3 vSize = VecOne;

	Matrix matWorld;

public:
	Transform();
	virtual ~Transform();

	void TransformUpdate();

	const Vector3& GetPos() { return v_pos; }
	const Vector3& GetRotation() { return vRotation; }
	const  Vector3& GetSize() { return vSize; }
	const Matrix& GetWorldMatrix() { return matWorld; }

	void SetSize(const Vector3& sizz) { vSize = sizz;}

	Vector3 GetEulerRot() { Vector3 eularAngle; }
	Vector3 GetWorldPos() { return Vector3(matWorld._41, matWorld._42, matWorld._43); }

	virtual void Init() override;

};

