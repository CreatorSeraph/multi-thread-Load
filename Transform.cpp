#include "DXUT.h"
#include "Transform.h"
#include "Actor.h"

Transform::Transform()
{
	D3DXMatrixIdentity(&matWorld);
}


Transform::~Transform()
{
}


void Transform::TransformUpdate()
{
	Matrix S, R, P;

	D3DXMatrixScaling(&S, vSize.x, vSize.y, vSize.z);

	D3DXMatrixRotationX(&R, D3DXToRadian(vRotation.x));
	D3DXMatrixRotationY(&R, D3DXToRadian(vRotation.y));
	D3DXMatrixRotationZ(&R, D3DXToRadian(vRotation.z));

	D3DXMatrixTranslation(&P, v_pos.x, v_pos.y, v_pos.z);

	matWorld = (S * R * P);
}

void Transform::Init()
{
	GetActor()->transform = this;
}
