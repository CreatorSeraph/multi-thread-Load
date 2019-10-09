#pragma once
class CMainGame
{
private:
	int Fps = 0;
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

