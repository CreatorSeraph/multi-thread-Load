#pragma once
class Component;
class Transform;
class Renderer;

class CGameObject
{
public:
	Transform* transform;
	Renderer* renderer;

private:
	friend class ObjectManager;


	list<Component*> l_com;

	bool b_Active = true;
	bool b_DeleteTag = false;

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual void Destroy() {};

	

	bool GetbActive() { return b_Active; }
	bool GetbDeleteTag() { return b_DeleteTag; }

	void ComDestroy();
	void ComUpdate();

	template<class T, class ..._Ty>
	T* AddComponent(_Ty&&... _ty)
	{
		T* com = new T(std::forward<_Ty>(_ty)...);
		com->SetGameObject(this);
		com->SetTransform(transform);
		com->Init();
		l_com.emplace_back(com);

		return com;
	}

	template<class T>
	T* GetComponent()
	{
		T* com = nullptr;
		for (auto iter : l_com)
		{
			com = dynamic_cast<T*>(iter);
			if (com)
				return com;
		}
		return nullptr;
	}

	template<class T>
	T* DeleteComponent()
	{
		T* com = nullptr;

		for (auto Iter = liComponents.begin(); Iter != liComponents.end();)
		{
			com = dynamic_cast<T*>((*Iter));

			if (com)
			{ 
				(*Iter)->SetDelete(true);
				break;
			}
			else
				++Iter;
		}
	}
};

