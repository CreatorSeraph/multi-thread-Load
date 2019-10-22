#pragma once
#include "singleton.h"
class cFxManager : public singleton<cFxManager>
{
private:
	LPD3DXEFFECT m_pEffect;

public:
	cFxManager();
	virtual ~cFxManager();

	LPD3DXEFFECT GetEffect() { return m_pEffect; }
};
#define FX cFxManager::GetInstance()->GetEffect()
