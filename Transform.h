#pragma once
#include "Component.h"

class Transform :
	public Component
{
public:
	Vector3 v_pos = Vector3(0.f, 0.f, 0.f);
	Vector3 vRotation = Vector3(0.f, 0.f, 0.f);
	Vector3 vSize = VecOne;
	Matrix matWorld;

public:
	Transform();
	virtual ~Transform();

	Vector3 GetPos() { return v_pos; }
	Vector3 GetRotation() { return vRotation; }
	Vector3 GetSize() { return vSize; }
	Matrix GetWorldMatrix() { return matWorld; }

	void SetSize(const Vector3& sizz) { vSize = sizz;}
	void SetPos(const Vector3& pos) { v_pos = pos; }
	void SetRotation(const Vector3& rotation) { vRotation = rotation; }

	Vector3 GetWorldPos() { return Vector3(matWorld._41, matWorld._42, matWorld._43); }

	virtual void Init() override;
	void TransformUpdate();

};

