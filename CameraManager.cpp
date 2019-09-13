#include "DXUT.h"
#include "CameraManager.h"
#include "Transform.h"


CameraManager::CameraManager()
	:vCameraPos(0.f, 500.5f, -10.f), vViewPos(0.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), lerpObj(nullptr)
{

	//10.5f, -5.f
	//D3DXMatrixIdentity(&matView);
	//D3DXMatrixIdentity(&matProj);
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), float(WINSIZEX) / float(WINSIZEY), 1, 10000.0f);
	//D3DX_PI / 3.f  /4.f

	NowMouse = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	//RECT r;
	//SetRect(&r, GetScreenPos().x, GetScreenPos().y, GetScreenPos().x + WINSIZEX, GetScreenPos().y + WINSIZEY);
	//ClipCursor(&r);

	SetCursorPos(GetScreenPos().x + WINSIZEX / 2, GetScreenPos().y + WINSIZEY / 2);
}


CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
	//if (!lerpObj)
	//	return;
	//
	//OldMouse = NowMouse;
	//NowMouse = GetMousePos();
	//
	//
	//if (OldMouse != NowMouse)
	//{
	//	float x_rot = NowMouse.x - OldMouse.x;
	//	float y_rot = NowMouse.y - OldMouse.y;
	//
	//	DEBUG_LOG(x_rot);
	//	DEBUG_LOG(y_rot);
	//
	//	f_Rot.x += x_rot;
	//	f_Rot.y += y_rot;
	//
	//	Matrix XMat, YMat, XYMat;
	//	D3DXMatrixRotationX(&XMat, D3DXToRadian(f_Rot.y));
	//	D3DXMatrixRotationY(&YMat, D3DXToRadian(f_Rot.x));
	//
	//	XYMat = XMat * YMat;
	//
	//	Vector3 temp = Vector3(0.0f, 10.5f, -5.f);
	//	
	//	D3DXVec3TransformCoord(&(vCameraPos), &(temp), &XYMat);
	//
	//	//SetCursorPos(GetScreenPos().x + WINSIZEX / 2, GetScreenPos().y + WINSIZEY / 2);
	//}
	//

	POINT cur;
	GetCursorPos(&cur);
	NowMouse = Vector2(cur.x, cur.y);
	
	if (NowMouse != GetScreenPos() + Vector2(WINSIZEX / 2, WINSIZEY / 2))
	{
		if (NowMouse.x > GetScreenPos().x + WINSIZEX / 2)
		{
			f_Rot.x += 200.f * DeltaTime;
			if (f_Rot.x > 360.f)
				f_Rot.x -= 360.f;
		}
		if (NowMouse.x < GetScreenPos().x + WINSIZEX / 2)
		{
			f_Rot.x -= 200.f * DeltaTime;
			if (f_Rot.x < 0.f)
				f_Rot.x += 360.f;
		}
		if (NowMouse.y > GetScreenPos().y + WINSIZEY / 2)
		{
			f_Rot.y += 200.f * DeltaTime;
			if (f_Rot.y > 360.f)
				f_Rot.y -= 360.f;
		}
		if (NowMouse.y < GetScreenPos().y + WINSIZEY / 2)
		{
			f_Rot.y -= 200.f * DeltaTime;
			if (f_Rot.y < 0.f)
				f_Rot.y += 360;
		}

		//DEBUG_LOG(f_Rot.x << " X");
		//DEBUG_LOG(f_Rot.y << " Y");

		Matrix XMat, YMat, XYMat;
		D3DXMatrixRotationX(&XMat, D3DXToRadian(f_Rot.y));
		D3DXMatrixRotationY(&YMat, D3DXToRadian(f_Rot.x));

		XYMat = XMat * YMat;

		Vector3 temp = Vector3(0.0f, 10.5f, -10.f);

		D3DXVec3TransformCoord(&(vCameraPos), &(temp), &XYMat);

		if (lerpObj)
		{
			Vector3 distance = vCameraPos - vViewPos;

			//if(D3DXVec3Length(&distance) >= 25.f)
			vViewPos = lerpObj->GetTransform()->GetPos();
			
		}

		vCameraPos += vViewPos;
	}
	SetCursorPos(GetScreenPos().x + WINSIZEX / 2, GetScreenPos().y + WINSIZEY / 2);
}

void CameraManager::SetTransform()
{
	D3DXMatrixLookAtLH(&matView, &vCameraPos, &vViewPos, &vUp);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), (float)WINSIZEX / (float)WINSIZEY, 1.f, 1000.f);

	g_device->SetTransform(D3DTS_VIEW, &matView);
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

/*
void cCameraManager::Update()
{
	if (shakeFrame > 0)
	{
		eye.x += RandNum(-20, 20) * 0.1f;
		eye.y += RandNum(-20, 20) * 0.1f;
		eye.z += RandNum(-20, 20) * 0.1f;
		shakeFrame -= DeltaTime;
	}

	float moveSpeed = 0.1f;
	float rotSpeed = 2.f;

	//if (INPUT->KeyPress('W')) // 'W' key, front move
	//{
	//   D3DXVECTOR3 Direction;
	//   D3DXVec3Normalize(&Direction, &(at - eye));
	//   eye += Direction * moveSpeed;
	//   at += Direction * moveSpeed;
	//}
	//
	//if (INPUT->KeyPress('S')) // 'S' key, back move
	//{
	//   D3DXVECTOR3 Direction;
	//   D3DXVec3Normalize(&Direction, &(at - eye));
	//   eye -=  Direction * moveSpeed;
	//   at -= Direction * moveSpeed;
	//}
	//
	//if (INPUT->KeyPress('A')) // 'A' key, left move
	//{
	//   D3DXVECTOR3 UpNormal, ForwardNormal, Direction;
	//   D3DXVec3Normalize(&UpNormal, &up);
	//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
	//   D3DXVec3Cross(&Direction, &ForwardNormal, &UpNormal);
	//   D3DXVec3Normalize(&Direction, &Direction);
	//   eye += Direction * moveSpeed;
	//   at += Direction * moveSpeed;
	//}
	//
	//if (INPUT->KeyPress('D')) // 'D' key, right move
	//{
	//   D3DXVECTOR3 UpNormal, ForwardNormal, Direction;
	//   D3DXVec3Normalize(&UpNormal, &up);
	//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
	//   D3DXVec3Cross(&Direction, &ForwardNormal, &UpNormal);
	//   D3DXVec3Normalize(&Direction, &Direction);
	//   eye -= Direction * moveSpeed;
	//   at -= Direction * moveSpeed;
	//}

	//if (INPUT->KeyPress(VK_SPACE)) // 'Q' key, up move
	//{
	//   eye.y += moveSpeed;
	//   at.y += moveSpeed;
	//}
	//if (INPUT->KeyPress(VK_SHIFT)) // 'E' key, down move
	//{
	//   eye.y -= moveSpeed;
	//   at.y -= moveSpeed;
	//}

	POINT vCur;
	GetCursorPos(&vCur);
	float angle, angle_y;
	if (isClip)
	{
		POINT vCenter = { WINSIZEX / 2 , WINSIZEY / 2 };
		ClientToScreen(DXUTGetHWND(), &vCenter);
		SetCursorPos(vCenter.x, vCenter.y);

		//if (vCur.y < vCenter.y) // mouse up look
		//{
		//   D3DXVECTOR3 UpNormal;
		//   D3DXVec3Normalize(&UpNormal, &up);
		//   at += UpNormal * rotSpeed;
		//}
		//
		//if (vCur.y > vCenter.y) // mouse down look
		//{
		//   D3DXVECTOR3 UpNormal;
		//   D3DXVec3Normalize(&UpNormal, &up);
		//   at -= UpNormal * rotSpeed;
		//}

		//if (vCur.x < vCenter.x) // mouse left look
		//{
		//   D3DXVECTOR3 UpNormal, ForwardNormal, Left;
		//   D3DXVec3Normalize(&UpNormal, &up);
		//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
		//   D3DXVec3Cross(&Left, &ForwardNormal, &UpNormal);
		//   D3DXVec3Normalize(&Left, &Left);
		//   at +=  Left * rotSpeed; 
		//}
		//
		//if (vCur.x > vCenter.x) // mouse right look
		//{
		//   D3DXVECTOR3 UpNormal, ForwardNormal, Right;
		//   D3DXVec3Normalize(&UpNormal, &up);
		//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
		//   D3DXVec3Cross(&Right, &ForwardNormal, &UpNormal);
		//   D3DXVec3Normalize(&Right, &Right);
		//   at -=  Right * rotSpeed;
		//}

		Vector3 Dir = Vector3(0.f, 3.f, -5.f);
		Vector3 OriginalDir = Vector3(0.f, 3.f, -5.f);

		if (vCur.x < vCenter.x)
		{
			angle -= rotSpeed;
			if (angle < -360)
				angle += 360;
		}

		if (vCur.x > vCenter.x)
		{
			angle += rotSpeed;
			if (angle > 360)
				angle -= 360;
		}

		if (vCur.y < vCenter.y - 30)
		{
			angle_y -= rotSpeed;
			if (angle_y < -360)
				angle_y += 360;
		}

		if (vCur.y > vCenter.y + 30)
		{
			angle_y += rotSpeed;
			if (angle_y > 360)
				angle_y -= 360;
		}

		D3DXMATRIX matRotation_x, matRotation_y, matR;
		D3DXMatrixRotationY(&matRotation_y, D3DXToRadian(angle));
		D3DXMatrixRotationX(&matRotation_x, D3DXToRadian(angle_y));
		matR = matRotation_x * matRotation_y;
		D3DXVec3TransformNormal(&Dir, &OriginalDir, &matR);

		eye = at + Dir * 10.f;
	}
}
*/