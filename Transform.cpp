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


void Transform::Update()
{
	Matrix S, R, P;

	D3DXMatrixScaling(&S, vSize.x, vSize.y, vSize.z);

	Matrix rX, rY, rZ;
	D3DXMatrixRotationX(&rX, D3DXToRadian(vRotation.x));
	D3DXMatrixRotationY(&rY, D3DXToRadian(vRotation.y));
	D3DXMatrixRotationZ(&rZ, D3DXToRadian(vRotation.z));

	D3DXMatrixTranslation(&P, v_pos.x, v_pos.y, v_pos.z);

	R = rX * rY * rZ;
	matWorld = (S * R * P);
}

void Transform::Init()
{
	GetActor()->transform = this;
}
