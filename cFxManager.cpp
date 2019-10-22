#include "DXUT.h"
#include "cFxManager.h"


cFxManager::cFxManager()
{
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

	LPD3DXBUFFER errBuffer;

	if (FAILED(D3DXCreateEffectFromFile(g_device, L"./resorce/Test.fx", NULL, NULL, dwShaderFlags,

		NULL, &m_pEffect, &errBuffer)))

	{

		MessageBoxA(DXUTGetHWND(), (LPCSTR)errBuffer->GetBufferPointer(), "ERROR", MB_OK);

		SAFE_RELEASE(errBuffer);

	}

}


cFxManager::~cFxManager()
{
	SAFE_RELEASE(m_pEffect);
}
