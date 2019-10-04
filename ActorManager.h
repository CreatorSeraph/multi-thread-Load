#pragma once
#include "singleton.h"

class Actor;
static class TagType
{
public:
	enum : char
	{
		BACKGROUND,
		PLAYER,
		END,
	};
};

class ActorManager :
	public singleton<ActorManager>
{
private:
	std::list< Actor* > m_listActors;

public:
	ActorManager() {}
	virtual ~ActorManager() { Reset(); }

	// �� ���͸� �����մϴ�.
	// DEFAULT_COMPONENT ��ũ�� �ɼ��� ���� �⺻���� ���Ϳ� ������ ������Ʈ��
	// ������ �� �ֽ��ϴ�.
	Actor* Create(int tag = -1, bool isVisible = true, bool isActive = true);

	// �� �� ���͸� �����մϴ�.
	Actor* CreateEmpty(int tag = -1, bool isVisible = true, bool isActive = true);

	void Update();
	void Reset();
};

#define ACTOR ActorManager::GetInstance()