#pragma once
class CMainGame
{
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

