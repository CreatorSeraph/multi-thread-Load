#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(&OldKey, NowKey, sizeof(bool) * 256);
	memset(&NowKey, false, sizeof(bool) * 256);

	for (int i = 0; i < 256; ++i)
		NowKey[i] = GetAsyncKeyState(i);
}
