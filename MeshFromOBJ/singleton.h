#pragma once
template <class T>
class singleton
{
private:
	static T* p;
public:
	singleton() {}
	virtual ~singleton() {}

	static T* GetInstance()
	{
		if (!p)
			p = new T;
		return p;
	}
	static void DestroyInstance()
	{
		if (p)
			SAFE_DELETE(p);
		p = nullptr;
	}
};

template <class T>
T* singleton<T>::p = nullptr;