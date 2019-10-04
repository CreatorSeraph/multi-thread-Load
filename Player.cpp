#include "DXUT.h"
#include "Player.h"
#include "Actor.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	//renderer = GetActor()->GetRenderer();
}

void Player::Update()
{
	//Vector3 camera = CAMERA->CameraPos();
	//Vector3 view = CAMERA->ViewPos();
	//D3DXVec3Normalize(&camera, &camera);
	//D3DXVec3Normalize(&view, &view);
	//
	//Vector3 test = CAMERA->ViewPos() - CAMERA->CameraPos();
	//test.y = 0.f;
	//D3DXVec3Normalize(&test, &test);
	//
	//float rot = acosf(test.x);

	Update2();

//
//
//	Vector3 p_Rot = this->GetTransform()->GetRotation();
//
//	if (KEYPRESS('W'))
//	{
//		Vector3 direction = CAMERA->AtPos() - CAMERA->CameraPos();
//		D3DXVec3Normalize(&direction, &direction);
//
//		Vector2 c_rot = Vector2(CAMERA->GetRot().x, CAMERA->GetRot().y);
//
//		GetActor()->GetTransform()->Translate(direction * 10);
//		this->GetTransform()->SetRotation(Vector3(p_Rot.x, (c_rot.x + 180.f), p_Rot.z));
//	}
//	if (KEYPRESS('S'))
//	{
//		Vector2 c_rot = Vector2(CAMERA->GetRot().x + 180.f, CAMERA->GetRot().y);
//		//c_rot = 카메라 각도
//
//		Matrix matR; 
//		Vector3 camPos = CAMERA->CameraPos(), nowPos = GetTransform()->v_pos;
//		nowPos.y = 0;
//		camPos.y = 0;
//		
//		Vector3 r = Vector3(0, 0, 0);
//		D3DXVec3TransformNormal(&r, &r, &matR);
///*
//		D3DXQUATERNION 
//
//		D3DXQuaternionRotationYawPitchRoll(r.y, r.x, r.z);
//*/
//		D3DXMatrixLookAtLH(&matR, &nowPos, &camPos, &Vector3(0, 1, 0));
//		GetTransform()->SetRotation(r);
//
//		Vector3 temp = Vector3(0.0f, 10.5f, -10.f);
//
//		Vector3 direction = CAMERA->CameraPos() - GetTransform()->v_pos;
//
//		D3DXVec3Normalize(&direction, &direction);
//
//		GetActor()->GetTransform()->Translate(direction * 10);
//		this->GetTransform()->SetRotation(Vector3(p_Rot.x, (c_rot.x + 180.f), p_Rot.z));
//	}
//	if (KEYPRESS('A'))
//	{
//		Vector2 c_rot = Vector2(CAMERA->GetRot().x + 270.f, CAMERA->GetRot().y);
//		// camRot, vCameraRotation, camRot c_rot
//
//		Matrix matR;
//		Vector3 camPos = CAMERA->CameraPos(), nowPos = GetTransform()->v_pos;
//		nowPos.y = 0;
//		camPos.y = 0;
//
//		Vector3 r = Vector3(0, 0, 0);
//		D3DXVec3TransformNormal(&r, &r, &matR);
//
//		Vector3 direction = Vector3(0, 0, 0);
//		direction.x = sin(D3DXToRadian(CAMERA->GetRot().x + 270.f));
//		direction.y = cos(D3DXToRadian(CAMERA->GetRot().y));
//
//		D3DXVec3Normalize(&direction, &direction);
//
//		GetActor()->GetTransform()->Translate(direction * 10);
//		this->GetTransform()->SetRotation(Vector3(p_Rot.x, (c_rot.x + 180.f), p_Rot.z));
//	}
//	if (KEYPRESS('D'))
//	{
//		Vector2 c_rot = Vector2(CAMERA->GetRot().x + 90.f, CAMERA->GetRot().y);
//
//		Matrix x, y, world;
//		D3DXMatrixRotationX(&x, D3DXToRadian(c_rot.y));
//		D3DXMatrixRotationY(&y, D3DXToRadian(c_rot.x));
//
//		world = x * y;
//
//		Vector3 temp = Vector3(0.0f, 10.5f, -10.f);
//		D3DXVec3TransformCoord(&temp, &temp, &world);
//
//		Vector3 direction = CAMERA->AtPos() - temp;
//		D3DXVec3Normalize(&direction, &direction);
//
//		GetActor()->GetTransform()->Translate(direction * 10);
//		this->GetTransform()->SetRotation(Vector3(p_Rot.x, (c_rot.x + 180.f), p_Rot.z));
//	}
//
//

	//Matrix billmat;
	//D3DXMatrixIdentity(&billmat);
	//
	//Matrix view;
	//view = CAMERA->GetMatView();
	//billmat._11 = view._11;
	//billmat._13 = view._13;
	//billmat._31 = view._31;
	//billmat._33 = view._33;
	//D3DXMatrixInverse(&billmat,
	//	NULL, &billmat);
	//billmat._41 = GetActor()->transform->GetWorldMatrix()._41;
	//billmat._42 = GetActor()->transform->GetWorldMatrix()._42;
	//billmat._43 = GetActor()->transform->GetWorldMatrix()._43;
	//
	//GetActor()->transform->matWorld = billmat;

}

void Player::Destroy()
{
}

void Player::OnCollision(Collider * other)
{
}

void Player::Update2()
{
	float moveSpeed = 10.0f;

	Vector3 direction = Vector3(0, 0, 0);
	bool check = false;

	if (KEYPRESS('W')) { direction.z++; check = true; }
	if (KEYPRESS('A')) { direction.x--; check = true; }
	if (KEYPRESS('S')) { direction.z--; check = true; }
	if (KEYPRESS('D')) { direction.x++; check = true; }
	if (KEYPRESS(VK_SHIFT)) { moveSpeed += 5.f; }

	if (!check)
		return;
	//Renderer* renderer = GetActor()->GetRenderer();
	//if (check == false) {
	//	renderer->ChangeMesh( L"player", L"./Image/obj/thief%df.obj", 40);
	//	renderer->Getframe()->SetFrame(0, 40, 50);
	//
	//	return;
	//}
	//else
	//{
	//	renderer->ChangeMesh(L"Palyer_Run", L"./Image/obj/thief_run%df.obj", 24);
	//	renderer->Getframe()->SetFrame(0, 24, 50);
	//}
		




	float angle = CAMERA->GetRot().x;

	Matrix matWorld;
	Vector3 rotationDirection = direction;

	D3DXMatrixRotationY(&matWorld, D3DXToRadian(angle));

	D3DXVec3Normalize(&direction, &direction);
	D3DXVec3TransformNormal(&direction, &direction, &matWorld);



	//D3DXMatrixRotationY(&matWorld, D3DXToRadian(angle + 180.f));
	D3DXMatrixRotationY(&matWorld, D3DXToRadian(angle));

	D3DXVec3Normalize(&rotationDirection, &rotationDirection);
	D3DXVec3TransformNormal(&rotationDirection, &rotationDirection, &matWorld);



	Transform* transform = GetActor()->GetTransform();



	float rotationValue = D3DXToDegree(atan2f(rotationDirection.x, rotationDirection.z));
	
	float rotY = transform->GetRotation().y;

	

	if(rotationValue < 0)
		rotationValue += 360.f;

	Matrix mat;
	D3DXMatrixRotationY(&matWorld, D3DXToRadian(rotY));


	D3DXQUATERNION quater;
	D3DXQUATERNION pQuater;

	D3DXQuaternionRotationMatrix(&quater, &matWorld);
	D3DXQuaternionSlerp(&pQuater, &pQuater, &quater, 0.1f);
	D3DXMATRIX mRQ;
	D3DXMatrixRotationQuaternion(&mRQ, &pQuater);



	Lerp(&rotY, rotY, rotationValue, 5.f);

	transform->SetRotation(Vector3(transform->GetRotation().x, rotY, transform->GetRotation().z));


	if(rotY <= rotationValue-1.f || 
		rotY >= rotationValue - 1.f ||
			rotY >= rotationValue + 1.f ||
			rotY <= rotationValue + 1.f)
		transform->Translate(direction * moveSpeed);
	
}

