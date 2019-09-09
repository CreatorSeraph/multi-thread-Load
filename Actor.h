#pragma once

class Component;

class Actor final
{
	friend class ActorManager;
	friend class CollisionManager;

	friend class Transform;
	friend class Renderer;
	friend class Collider;
	friend class Rigidbody;
private:
	bool	m_bLive			= true;
	bool	m_bVisible		= true;
	bool	m_bActive		= true;

	Tag		m_Tag			= -1;

	std::map< std::string, Component* > m_mapComponents;

private:

	Transform* m_pTransform = nullptr;
	Renderer* m_pRenderer = nullptr;
	Collider* m_pCollider = nullptr;
	Rigidbody* m_pRigidbody = nullptr;

public:

	inline Transform* GetTransform() { return m_pTransform; }
	inline Renderer* GetRenderer() { return m_pRenderer; }
	inline Collider* GetCollider() { return m_pCollider; }
	inline Rigidbody* GetRigidbody() { return m_pRigidbody; }

	inline void SetTransform(Transform* value) { m_pTransform = value; }
	inline void SetRenderer(Renderer* value) { m_pRenderer = value; }
	inline void SetCollider(Collider* value) { m_pCollider = value; }
	inline void SetRigidbody(Rigidbody* value) { m_pRigidbody = value; }

	PropertyGS(GetTransform, SetTransform) Transform* transform;
	PropertyGS(GetRenderer, SetRenderer) Renderer* renderer;
	PropertyGS(GetCollider, SetCollider) Collider* collider;
	PropertyGS(GetRigidbody, SetRigidbody) Rigidbody* rigidbody;

private:
	Actor() {}

	Actor(Tag tag)
		: m_Tag(tag) {}

	Actor(bool isVisible, bool isActive) 
		: m_bVisible(isVisible), m_bActive(isActive) {}

	Actor(Tag tag, bool isVisible, bool isActive)
		: m_Tag(tag), m_bVisible(isVisible), m_bActive(isActive) {}

	~Actor() {}

	void Initialize();
	void Update();
	void Release();

	void OnVisible();
	void OnUnvisible();
	void OnEnable();
	void OnDisable();
	void OnDestroy();

	void OnCollision(Collider* other);

public:

	void SetIsLive		(bool value);
	void SetIsVisible	(bool value);
	void SetIsActive	(bool value);

	bool GetIsLive		()		{ return m_bLive;		}
	bool GetIsVisible	()		{ return m_bVisible;	}
	bool GetIsActive	()		{ return m_bActive;		}

	PropertyGS(GetIsLive, SetIsLive)			bool IsLive;
	PropertyGS(GetIsVisible, SetIsVisible)		bool IsVisible;
	PropertyGS(GetIsActive, SetIsActive)		bool IsActive;

public:

	template <class COM, class ..._Ty>
	COM* AddComponent(_Ty&&..._ty);

	template <class COM>
	COM* GetComponent();
};

#include "Actor.hpp"