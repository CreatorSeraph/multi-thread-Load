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

	// 새 엑터를 생성합니다.
	// DEFAULT_COMPONENT 메크로 옵션을 통해 기본으로 엑터에 내장할 컴포넌트를
	// 지정할 수 있습니다.
	Actor* Create(int tag = -1, bool isVisible = true, bool isActive = true);

	// 새 빈 엑터를 생성합니다.
	Actor* CreateEmpty(int tag = -1, bool isVisible = true, bool isActive = true);

	void Update();
	void Reset();
};

#define ACTOR ActorManager::GetInstance()