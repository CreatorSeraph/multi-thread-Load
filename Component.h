#pragma once
class CGameObject;
class Transform;

class Component
{
private:
	CGameObject* gameObj;
	Transform* transform;

	bool b_Enable;
	bool b_Delete;
public:
	Component();
	virtual ~Component();

	virtual void Init() {};
	virtual void Update() {};

	virtual void Destroy() {};

	CGameObject* GetGameObject() { return gameObj; }
	Transform* GetTransform() { return transform; }
	bool GetEnable() { return b_Enable; }
	bool GetDelete() { return b_Delete; }

	void SetGameObject(CGameObject* obj) { gameObj = obj; }
	void SetTransform(Transform* trans) { transform = trans; }

};

