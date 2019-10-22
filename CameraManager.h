#pragma once
#include "singleton.h"
#include "Transform.h"
#include "Actor.h"

class CGameObject;
class CameraManager :
	public singleton<CameraManager>
{
private:
	Vector3 vCameraPos;
	Vector3 vRotCameraPos;
	Vector3 vAt;
	Vector3 vUp;

	Matrix matView;
	Matrix matProj;
	Matrix matProjOrtho;

	Vector2 NowMouse;
	Vector2 OldMouse;
	Vector2 f_Rot = Vector2(0.f, 0.f);

	float LimitDistance = 25.f;

	Actor* lerpObj;
public:
	CameraManager();
	virtual ~CameraManager();

	void Update();
	void Update2();
	void SetTransform();
	void SetCameraPos(Vector3 pos) { vCameraPos = pos; }
	void SetAtPos(Vector3 at) { vAt = at; }

	Vector2 GetRot() { return f_Rot; }
	Vector3 CameraPos() { return vCameraPos; }
	Vector3 AtPos() { return vAt; }

	Matrix GetMatView() { return matView; }
	Matrix GetMatProj() { return matProj; }



	Vector2 SetRot(const Vector2& _rot) { return f_Rot = _rot; }
	void SetObjPos(Actor* obj)
	{
		lerpObj = obj;
	}

	Vector2& GetScroll() { return Vector2(WINSIZEX / 2 - vCameraPos.x, WINSIZEY / 2 - vCameraPos.y); }

	//ui
	//ScreenToClient 전체 창에서 mousepos를 프로그램 내의 mousepos로 변경
	Vector2& GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(DXUTGetHWND(), &point);
		Vector2 v_mousepos(point.x, point.y);
		return v_mousepos;
	}
	//obj
	Vector2& GetScreenPos()
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(DXUTGetHWND(), &point);
		Vector2 v_mousepos(point.x, point.y);
		v_mousepos -= GetScroll();
		return v_mousepos;
	}

	Vector2& GetScreenWheelPos()
	{
		POINT point = { 0,0 };
		ClientToScreen(DXUTGetHWND(), &point);
		Vector2 v_mousepos(point.x, point.y);
		return v_mousepos;
	}

};

#define CAMERA CameraManager::GetInstance()