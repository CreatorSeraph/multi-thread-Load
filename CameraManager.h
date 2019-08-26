#pragma once
#include "singleton.h"

class CGameObject;
class CameraManager :
	public singleton<CameraManager>
{
private:
	Vector3 vCameraPos;
	Vector3 vViewPos;
	Vector3 vUp;

	Matrix matView;
	Matrix matProj;

	Vector2 NowMouse;
	Vector2 OldMouse;
	Vector2 f_Rot = Vector2(0.f, 0.f);

	CGameObject* lerpObj;
public:
	CameraManager();
	virtual ~CameraManager();

	void Update();

	void CalculatorViewMatrix();
	void CalculatorProjMatrix();

	void SetTransform();

	const Vector2& GetRot() { return f_Rot; }
	const Vector3& CameraPos() { return vCameraPos; }
	const Vector3& ViewPos() { return vViewPos; }

	void SetGameObject(CGameObject* obj)
	{
		lerpObj = obj;
	}
	Vector2& GetScroll() { return Vector2(WINSIZEX / 2 - vCameraPos.x, WINSIZEY / 2 - vCameraPos.y); }

	Vector2& GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(DXUTGetHWND(), &point);
		Vector2 Cur (point.x, point.y);
		return Cur;
	}

	Vector2& GetScreenPos()
	{
		POINT point = {0,0};
		ClientToScreen(DXUTGetHWND(), &point);
		Vector2 v_mousepos(point.x, point.y);
		return v_mousepos;
	}

};

#define CAMERA CameraManager::GetInstance()