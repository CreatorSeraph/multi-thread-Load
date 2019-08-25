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

using namespace std;
using namespace chrono;

#define DeltaTime DXUTGetElapsedTime()
#define GetNowTime system_clock::now()
#define g_device DXUTGetD3D9Device()
#define VecOne Vector3(1.f,1.f,1.f);
#define CCOLOR D3DCOLOR_ARGB(255,255,255,255)

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

const int WINSIZEX = 1280;
const int WINSIZEY = 720;

template <class T>
void Lerp(T* target, const T& start, const T& end, float speed)
{
	*target += start + (end - start) * speed * DeltaTime;
}


#include "ImageManager.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CFrame.h"