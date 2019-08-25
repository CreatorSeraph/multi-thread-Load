#pragma once
#include "singleton.h"
class InputManager :
	public singleton<InputManager>
{
private:
	bool NowKey[256] = { false, };
	bool OldKey[256] = { false, };


public:
	InputManager();
	virtual ~InputManager();

	bool KeyDown(int i)  { return NowKey[i] && !OldKey[i]; }
	bool KeyPress(int i) { return NowKey[i] && OldKey[i]; }
	bool KeyUp(int i)    { return !NowKey[i] && OldKey[i]; }

	void Update();
};

#define INPUT InputManager::GetInstance()
#define KEYDOWN(i) INPUT->KeyDown(i)
#define KEYPRESS(i) INPUT->KeyPress(i)
#define KEYUP(i) INPUT->KeyUp(i)