#pragma once

class Transform;
class Renderer;
class Collider;
class Rigidbody;

class Actor;


class Component
{
	friend class Actor;
private:
	Actor* actor;

	bool b_Enable = true;
	bool b_Delete = false;
public:
	Component();
	virtual ~Component();

	virtual void Init() {};
	virtual void Update() {};
	virtual void Destroy() {};

	virtual Actor* GetActor() { return actor; }
	virtual void SetActor(Actor* ac) { actor = ac; }

	virtual bool GetEnable() { return b_Enable; }
	virtual bool GetDelete() { return b_Delete; }

	Transform* GetTransform();
	Renderer* GetRenderer();
	Collider* GetCollider();
	Rigidbody* GetRigidbody();

	// 객체가 보이게 되었을 때 호출됩니다.
	virtual void OnVisible() {}
	// 객체가 보이지 않게 되었을 때 호출됩니다.
	virtual void OnUnvisible() {}
	// 객체가 활성화 되었을 때 호출됩니다.
	virtual void OnEnable() {}
	// 객체가 비활성화 되었을 때 호출됩니다.
	virtual void OnDisable() {}
	// 객체가 파괴될 때 호출됩니다. < Destroy( Actor* ) 함수로 인해 호출됩니다. >
	virtual void OnDestroy() {}
	// 객체가 충돌될 때 호출됩니다. Collider* 컴포넌트가 추가되어 있는 상태에서만 호출됩니다.
	virtual void OnCollision(Collider* other) {}

	//template<class com, class ..._Ty>
	//com* AddComponent(_Ty&&..._ty)
	//{
	//	com* com = new com(forward<_Ty>(_ty)...);
	//	com->Init();
	//	
	//	return com;
	//}
	template<class com, class ..._Ty>
	com* AddComponent(_Ty&&..._ty);

	template<class com>
	com* GetComponent();


};

template<class com, class ..._Ty>
inline com * Component::AddComponent(_Ty&&..._ty)
{
	return actor->AddComponent<com>(forward<_Ty>(_ty)...);
}

template<class com>
inline com * Component::GetComponent()
{
	return actor->GetComponent<com>();
}
