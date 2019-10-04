#include "DXUT.h"
#include "CameraManager.h"
#include "Transform.h"


CameraManager::CameraManager()
	:vCameraPos(0.f, 700.5f, -20.f), vAt(0.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), lerpObj(nullptr)
{
	//500.5

	//10.5f, -5.f
	//D3DXMatrixIdentity(&matView);
	//D3DXMatrixIdentity(&matProj);
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), float(WINSIZEX) / float(WINSIZEY), 1, 10000.0f);
	//D3DX_PI / 3.f  /4.f

	NowMouse = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	//RECT r;
	//SetRect(&r, GetScreenPos().x, GetScreenPos().y, GetScreenPos().x + WINSIZEX, GetScreenPos().y + WINSIZEY);
	//ClipCursor(&r);

	SetCursorPos(GetScreenWheelPos().x + WINSIZEX / 2, GetScreenWheelPos().y + WINSIZEY / 2);
}


CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
	//DEBUG_LOG(vUp.y);
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
	
	if (NowMouse != GetScreenWheelPos() + Vector2(WINSIZEX / 2, WINSIZEY / 2))
	{
		if (NowMouse.x > GetScreenWheelPos().x + WINSIZEX / 2)
		{
			f_Rot.x += 200.f * DeltaTime;
			if (f_Rot.x > 360.f)
				f_Rot.x -= 360.f;
		}
		if (NowMouse.x < GetScreenWheelPos().x + WINSIZEX / 2)
		{
			f_Rot.x -= 200.f * DeltaTime;
			if (f_Rot.x < 0.f)
				f_Rot.x += 360.f;
		}
		if (NowMouse.y > GetScreenWheelPos().y + WINSIZEY / 2)
		{
			f_Rot.y += 100.f * DeltaTime;
			if (f_Rot.y > 360.f)
				f_Rot.y -= 360.f;
		}
		if (NowMouse.y < GetScreenWheelPos().y + WINSIZEY / 2)
		{
			f_Rot.y -= 100.f * DeltaTime;
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
			//D3DXVec3TransformCoord(&(lerpObj->transform->GetPos()), &Vector3(0.0f, 0.f, 0.f), &XYMat);
			Vector3 distance = vCameraPos - vAt;

			//if(D3DXVec3Length(&distance) >= 25.f)
			vAt = lerpObj->GetTransform()->GetPos();
			
		}

		vCameraPos += vAt;
	}
	SetCursorPos(GetScreenWheelPos().x + WINSIZEX / 2, GetScreenWheelPos().y + WINSIZEY / 2);
}

void CameraManager::SetTransform()
{
	D3DXMatrixLookAtLH(&matView, &vCameraPos, &vAt, &vUp);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), (float)WINSIZEX / (float)WINSIZEY, 1.f, 1000.f);

	g_device->SetTransform(D3DTS_VIEW, &matView);
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CameraManager::RayCast()
{
	D3DVIEWPORT9 vp;
	POINT ptCursor;
	Vector3 v;
	g_device->GetViewport(&vp);
	g_device->GetTransform(D3DTS_PROJECTION, &matProj);
	GetCursorPos(&ptCursor); 
	ScreenToClient(DXUTGetHWND(), &ptCursor);
	v.x = (((((ptCursor.x - vp.X)*2.0f / vp.Width) - 1.0f)) - matProj._31) / matProj._11;
	v.y = ((-(((ptCursor.y - vp.Y)*2.0f / vp.Height) - 1.0f)) - matProj._32) / matProj._22;
	v.z = 1.0f;

	Matrix InverseM;
	Vector3 vPickRayDir;
	Vector3 vPickRayOrig;
	g_device->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&InverseM, NULL, &matView);
	vPickRayDir.x = v.x*InverseM._11 + v.y*InverseM._21 + v.z*InverseM._31;
	vPickRayDir.y = v.x*InverseM._12 + v.y*InverseM._22 + v.z*InverseM._32;
	vPickRayDir.z = v.x*InverseM._13 + v.y*InverseM._23 + v.z*InverseM._33;

	vPickRayOrig.x = InverseM._41; 
	vPickRayOrig.y = InverseM._42;
	vPickRayOrig.z = InverseM._43;

	//BOOL CMyD3DApplication::IntersectTriangle(vPickRayOrig, vPickRayDir, );



	/*
	D3DVIEWPORT9 vp;
	g_device->GetViewport ( &vp );

	POINT mouse;
	g_device->GetTransform(D3DTS_PROJECTION, &matProj);

	GetCursorPos(&mouse);
	ScreenToClient(DXUTGetHWND(), &mouse);

	//Note: 마우스 좌표에 투영행렬을 역으로 적용하여 공간좌표를 만든다 (=카메라 좌표계)
	D3DXVECTOR3 v, vPickRayDir, vPickRayOrig;
	v.x = (((((mouse.x - vp.X)*2.0f / vp.Width) - 1.0f)) - matProj._31) / matProj._11;
	v.y = ((-(((mouse.y - vp.Y)*2.0f / vp.Height) - 1.0f)) - matProj._32) / matProj._22;
	v.z = 1.0f;

	// Get the inverse view matrix
	D3DXMATRIXA16 matView, m;
	g_device->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&m, NULL, &matView);

	//두점을 빼주면 RayDir 이 만들어진다.(RayDir = Mouse - RayOrig)
	//vPickRayDir : 카메라 방향 벡터 vPickRayOrig: 카메라 위치벡터
	//얻어진 Ray를 가지고 피킹을 수행한다.
	//==>(2) 반직선과 교차하는 폴리곤중 가장 가까운것을 택한다. ( picking )

	vPickRayDir.x = v.x*m._11 + v.y*m._21 + v.z*m._31;
	vPickRayDir.y = v.x*m._12 + v.y*m._22 + v.z*m._32;
	vPickRayDir.z = v.x*m._13 + v.y*m._23 + v.z*m._33;
	vPickRayOrig.x = m._41;
	vPickRayOrig.y = m._42;
	vPickRayOrig.z = m._43;

	//삼각형의 세부분을 알아야 한다. x 파일을 Mesh로 불러들이기 때문에
	//Mesh의 그려주는 삼각형을 알려면 GetLocalMesh()함수 이용
	//LPD3DXBASEMESH pMesh = m_pMesh->GetLocalMesh();

	BOOL bHit;      //충돌 값 True = 충돌!!
	DWORD dwFace;     //pHit 가 TRUE 의 경우, 레이의 시점에 가장 가까운 면의 인덱스값의 포인터
	float fBary1, fBary2;   //중심 히트 좌표 U 의 포인터(=fBary1), 중심 히트 좌표 V 의 포인터(=fBary2)
	float fDist = 100.f;     //fDist: 레이의 시점에서 교점까지의 거리의 포인터.
			//NULL : D3DXINTERSECTINFO 구조체의 배열을 저장 하는 ID3DXBuffer 개체의 포인터.
			//NULL : ppAllHits 배열내의 엔트리수를 저장 하는 DWORD 의 포인터.

	//Intersect은 구한 반직선이 삼각형에 교차하는지 검사하기 위해 쓰는 함수
	//D3DXIntersect(pMesh, &vPickRayOrig, &vPickRayDir, &bHit, &dwFace, &fBary1, &fBary2, &fDist,
	//	NULL, NULL);

	// 3D마우스 좌표 = vPickRayOrig + vPickRayDir * t ;
	D3DXVECTOR3 vPos = vPickRayOrig + vPickRayDir * fDist;
	*/
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