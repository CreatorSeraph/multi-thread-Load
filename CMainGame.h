#pragma once
class CMainGame
{
private:
	DWORD frameCount = 0;
	float timeElapsed = 0.0f;
	DWORD lastTime = timeGetTime();

	DWORD curTime = timeGetTime();
	float timeDelta;
	float Fps = 0;
public:
	CMainGame();
	virtual ~CMainGame();

	void Init();
	void Update();
	void Render();
	void Destroy();

	void LostDevice();
	void ResetDevice();
};

