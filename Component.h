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

	// ��ü�� ���̰� �Ǿ��� �� ȣ��˴ϴ�.
	virtual void OnVisible() {}
	// ��ü�� ������ �ʰ� �Ǿ��� �� ȣ��˴ϴ�.
	virtual void OnUnvisible() {}
	// ��ü�� Ȱ��ȭ �Ǿ��� �� ȣ��˴ϴ�.
	virtual void OnEnable() {}
	// ��ü�� ��Ȱ��ȭ �Ǿ��� �� ȣ��˴ϴ�.
	virtual void OnDisable() {}
	// ��ü�� �ı��� �� ȣ��˴ϴ�. < Destroy( Actor* ) �Լ��� ���� ȣ��˴ϴ�. >
	virtual void OnDestroy() {}
	// ��ü�� �浹�� �� ȣ��˴ϴ�. Collider* ������Ʈ�� �߰��Ǿ� �ִ� ���¿����� ȣ��˴ϴ�.
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
