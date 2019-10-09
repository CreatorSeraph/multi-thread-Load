#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <variant>

using namespace std;
using namespace chrono;

ID3DXEffect* LIGHTFXEFT;
ID3DXEffect* g_pEffect;
ID3DXBaseEffect* LIGHTFX;

#define DeltaTime DXUTGetElapsedTime()
#define GetNowTime system_clock::now()
#define g_device DXUTGetD3D9Device()
#define VecOne Vector3(1.f,1.f,1.f);
#define CCOLOR D3DCOLOR_ARGB(255,255,255,255)

#define PropertyG(G) __declspec(property(get = G))
#define PropertyS(S) __declspec(property(put = S))
#define PropertyGS(G, S) __declspec(property(get = G, put = S))

#define WHITE (D3DCOLOR_XRGB(255, 255, 255));
#define BLACK (D3DCOLOR_XRGB(0, 0, 0));
#define RED (D3DCOLOR_XRGB(255, 0, 0));
#define GREEN (D3DCOLOR_XRGB(0, 255, 0));
#define BLUE (D3DCOLOR_XRGB(0, 0, 255));
#define YELLOW (D3DCOLOR_XRGB(255, 255, 0));
#define CYAN (D3DCOLOR_XRGB(0, 255, 255));
#define MAGENTA (D3DCOLOR_XRGB(255, 0, 255));

#define DESERT_SAND (D3DCOLOR_XRGB(250, 205, 135));
#define BEACH_SAND (D3DCOLOR_XRGB(255, 249, 157));

#define LIGHTGREEN (D3DCOLOR_XRGB(60, 184, 120));
#define PUREGREEN (D3DCOLOR_XRGB(0, 166, 81));
#define DARKGREEN (D3DCOLOR_XRGB(0, 114, 54));

#define LIGHT_YELLOW_GREEN (D3DCOLOR_XRGB(124, 197, 118));
#define PURE_YELLOW_GREEN (D3DCOLOR_XRGB(57, 181, 74));
#define DARK_YELLOW_GREEN (D3DCOLOR_XRGB(25, 123, 48));

#define LIGHTBROWN (D3DCOLOR_XRGB(198, 156, 109));
#define DARKBROWN (D3DCOLOR_XRGB(115, 100, 87));

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#define DEBUG_LOGW(log) wcout << log << endl;
#else
#define DEBUG_LOG(log) 
#define DEBUG_LOGW(log)
#endif


using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Vector4 = D3DXVECTOR4;
using Matrix = D3DXMATRIX;
using Quaternion = D3DXQUATERNION;
using Tag = int;


const int WINSIZEX = 1280;
const int WINSIZEY = 720;

template <class T>
void Lerp(T* target, const T& start, const T& end, float speed)
{
	*target = start + (end - start) * speed * DeltaTime;
}

static float lerp(float a, float b, float t)
{
	return a - (a*t) + (b*t);
}

#pragma comment (linker , "/entry:wWinMainCRTStartup /subsystem:console")

#include "ImageManager.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ActorManager.h"
#include "CFrame.h"