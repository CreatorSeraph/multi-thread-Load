#include "DXUT.h"
#include "CameraManager.h"
#include "Transform.h"


CameraManager::CameraManager()
	:vCameraPos(0.f, 10.5, -5.f), vViewPos(0.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f),lerpObj(nullptr)
{
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);

	CalculatorViewMatrix();
	CalculatorProjMatrix();

	SetTransform();
	NowMouse = Vector2(WINSIZEX / 2, WINSIZEY / 2);
}


CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
	OldMouse = NowMouse;
	NowMouse = GetMousePos();

	SetCursorPos(GetScreenPos().x + WINSIZEX / 2, GetScreenPos().y + WINSIZEY / 2);
	if (OldMouse != NowMouse)
	{
		float x_rot = NowMouse.x - OldMouse.x;
		float y_rot = NowMouse.y - OldMouse.y;

		f_Rot.x += x_rot;
		f_Rot.y += y_rot;

		Vector3 direction = vCameraPos - vViewPos;

		Matrix XMat, YMat, XYMat;
		D3DXMatrixRotationX(&XMat, D3DXToRadian(f_Rot.y));
		D3DXMatrixRotationY(&YMat, D3DXToRadian(f_Rot.x));

		XYMat = XMat * YMat;

		//vCameraPos = Vector3(0, 0, 5);

		D3DXVec3TransformNormal(&vCameraPos, &vCameraPos, &XYMat);
	}

}

void CameraManager::CalculatorViewMatrix()
{
	D3DXMatrixLookAtLH(&matView, &vCameraPos, &vViewPos, &vUp);
}

void CameraManager::CalculatorProjMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 500.f);
	//D3DX_PI / 3.f
}

void CameraManager::SetTransform()
{
	g_device->SetTransform(D3DTS_VIEW, &matView);
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

//void cCameraManager::Update()
//{
//	if (shakeFrame > 0)
//	{
//		eye.x += RandNum(-20, 20) * 0.1f;
//		eye.y += RandNum(-20, 20) * 0.1f;
//		eye.z += RandNum(-20, 20) * 0.1f;
//		shakeFrame -= DeltaTime;
//	}
//
//	float moveSpeed = 0.1f;
//	float rotSpeed = 2.f;
//
//	//if (INPUT->KeyPress('W')) // 'W' key, front move
//	//{
//	//   D3DXVECTOR3 Direction;
//	//   D3DXVec3Normalize(&Direction, &(at - eye));
//	//   eye += Direction * moveSpeed;
//	//   at += Direction * moveSpeed;
//	//}
//	//
//	//if (INPUT->KeyPress('S')) // 'S' key, back move
//	//{
//	//   D3DXVECTOR3 Direction;
//	//   D3DXVec3Normalize(&Direction, &(at - eye));
//	//   eye -=  Direction * moveSpeed;
//	//   at -= Direction * moveSpeed;
//	//}
//	//
//	//if (INPUT->KeyPress('A')) // 'A' key, left move
//	//{
//	//   D3DXVECTOR3 UpNormal, ForwardNormal, Direction;
//	//   D3DXVec3Normalize(&UpNormal, &up);
//	//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
//	//   D3DXVec3Cross(&Direction, &ForwardNormal, &UpNormal);
//	//   D3DXVec3Normalize(&Direction, &Direction);
//	//   eye += Direction * moveSpeed;
//	//   at += Direction * moveSpeed;
//	//}
//	//
//	//if (INPUT->KeyPress('D')) // 'D' key, right move
//	//{
//	//   D3DXVECTOR3 UpNormal, ForwardNormal, Direction;
//	//   D3DXVec3Normalize(&UpNormal, &up);
//	//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
//	//   D3DXVec3Cross(&Direction, &ForwardNormal, &UpNormal);
//	//   D3DXVec3Normalize(&Direction, &Direction);
//	//   eye -= Direction * moveSpeed;
//	//   at -= Direction * moveSpeed;
//	//}
//
//	//if (INPUT->KeyPress(VK_SPACE)) // 'Q' key, up move
//	//{
//	//   eye.y += moveSpeed;
//	//   at.y += moveSpeed;
//	//}
//	//if (INPUT->KeyPress(VK_SHIFT)) // 'E' key, down move
//	//{
//	//   eye.y -= moveSpeed;
//	//   at.y -= moveSpeed;
//	//}
//
//	POINT vCur;
//	GetCursorPos(&vCur);
//
//	if (isClip)
//	{
//		POINT vCenter = { WINSIZEX / 2 , WINSIZEY / 2 };
//		ClientToScreen(DXUTGetHWND(), &vCenter);
//		SetCursorPos(vCenter.x, vCenter.y);
//
//		//if (vCur.y < vCenter.y) // mouse up look
//		//{
//		//   D3DXVECTOR3 UpNormal;
//		//   D3DXVec3Normalize(&UpNormal, &up);
//		//   at += UpNormal * rotSpeed;
//		//}
//		//
//		//if (vCur.y > vCenter.y) // mouse down look
//		//{
//		//   D3DXVECTOR3 UpNormal;
//		//   D3DXVec3Normalize(&UpNormal, &up);
//		//   at -= UpNormal * rotSpeed;
//		//}
//
//		//if (vCur.x < vCenter.x) // mouse left look
//		//{
//		//   D3DXVECTOR3 UpNormal, ForwardNormal, Left;
//		//   D3DXVec3Normalize(&UpNormal, &up);
//		//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
//		//   D3DXVec3Cross(&Left, &ForwardNormal, &UpNormal);
//		//   D3DXVec3Normalize(&Left, &Left);
//		//   at +=  Left * rotSpeed; 
//		//}
//		//
//		//if (vCur.x > vCenter.x) // mouse right look
//		//{
//		//   D3DXVECTOR3 UpNormal, ForwardNormal, Right;
//		//   D3DXVec3Normalize(&UpNormal, &up);
//		//   D3DXVec3Normalize(&ForwardNormal, &(at - eye));
//		//   D3DXVec3Cross(&Right, &ForwardNormal, &UpNormal);
//		//   D3DXVec3Normalize(&Right, &Right);
//		//   at -=  Right * rotSpeed;
//		//}
//
//		Vec3 Dir = Vec3(0.f, 3.f, -5.f);
//		Vec3 OriginalDir = Vec3(0.f, 3.f, -5.f);
//
//		if (vCur.x < vCenter.x)
//		{
//			angle -= rotSpeed;
//			if (angle < -360)
//				angle += 360;
//		}
//
//		if (vCur.x > vCenter.x)
//		{
//			angle += rotSpeed;
//			if (angle > 360)
//				angle -= 360;
//		}
//
//		if (vCur.y < vCenter.y - 30)
//		{
//			angle_y -= rotSpeed;
//			if (angle_y < -360)
//				angle_y += 360;
//		}
//
//		if (vCur.y > vCenter.y + 30)
//		{
//			angle_y += rotSpeed;
//			if (angle_y > 360)
//				angle_y -= 360;
//		}
//
//		D3DXMATRIX matRotation_x, matRotation_y, matR;
//		D3DXMatrixRotationY(&matRotation_y, D3DXToRadian(angle));
//		D3DXMatrixRotationX(&matRotation_x, D3DXToRadian(angle_y));
//		matR = matRotation_x * matRotation_y;
//		D3DXVec3TransformNormal(&Dir, &OriginalDir, &matR);
//
//		eye = at + Dir * 10.f;
//	}
//}
