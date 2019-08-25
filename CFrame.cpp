#include "DXUT.h"
#include "CFrame.h"


CFrame::CFrame()
{
}


CFrame::~CFrame()
{
}

void CFrame::SetFrame(int min, int max, DWORD delay)
{
	CurF = StartF = min;
	EndF = max;
	DWskip = timeGetTime();
	DWdelay = delay;
}

bool CFrame::Frame()
{
	if (DWskip + DWdelay < timeGetTime())
	{
		DWskip = timeGetTime();
		if(++CurF > EndF)
		{
			CurF = StartF;
			DWskip = timeGetTime();
			return true;
		}
	}
	return false;
}
