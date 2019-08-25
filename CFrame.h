#pragma once
class CFrame
{
public:
	int CurF = 0;
	int StartF = 0;
	int EndF = 0;

	DWORD DWskip = 0;
	DWORD DWdelay = 0;
public:
	CFrame();
	virtual ~CFrame();

	void SetFrame(int min, int max, DWORD delay);
	bool Frame();
	void operator()()
	{
		Frame();
	}
};

