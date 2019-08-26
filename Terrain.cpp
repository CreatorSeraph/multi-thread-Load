#include "DXUT.h"
#include "terrain.h"
#include <fstream>
#include <cmath>

const DWORD Terrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

Terrain::Terrain(IDirect3DDevice9* device,//디바이스 객체
	std::string heightmapFileName,//파일이름
	int numVertsPerRow,//행
	int numVertsPerCol,//열
	int cellSpacing,//셀 간의 간격 
	float heightScale)//높이 배율을 조정하는 값
{
	_device = device;//장치
	_numVertsPerRow = numVertsPerRow;//
	_numVertsPerCol = numVertsPerCol;//
	_cellSpacing = cellSpacing;//셀의 공간

	_numCellsPerRow = _numVertsPerRow - 1;
	_numCellsPerCol = _numVertsPerCol - 1;

	_width = _numCellsPerRow * _cellSpacing;
	_depth = _numCellsPerCol * _cellSpacing;

	_numVertices = _numVertsPerRow * _numVertsPerCol;
	_numTriangles = _numCellsPerRow * _numCellsPerCol * 2;

	_heightScale = heightScale;

	// load heightmap
	if (!readRawFile(heightmapFileName))//raw파일을 읽는다.
	{
		::MessageBox(0, L"readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// scale heights
	for (int i = 0; i < _heightmap.size(); i++)//높이..
		_heightmap[i] *= heightScale;

	// compute the vertices
	if (!computeVertices())
	{
		::MessageBox(0, L"computeVertices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// compute the indices
	if (!computeIndices())
	{
		::MessageBox(0, L"computeIndices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
}

Terrain::~Terrain()
{
	_vb->Release();
	_ib->Release();
	_tex->Release();
}

int Terrain::getHeightmapEntry(int row, int col)//높이맵 내의 항목에 접근
{
	return _heightmap[row * _numVertsPerRow + col];
}

void Terrain::setHeightmapEntry(int row, int col, int value)//높이맵 내의 항목을 수정.
{
	_heightmap[row * _numVertsPerRow + col] = value;
}

//최종적으로 버텍스를 생성함
bool Terrain::computeVertices()
{
	HRESULT hr = 0;

	hr = _device->CreateVertexBuffer(
		_numVertices * sizeof(TerrainVertex),//버텍스의 갯수, 한 버텍스.
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if (FAILED(hr))
		return false;

	//버텍스생성을 시작할 좌표..
	//중간을 기준으로 가장 왼쪽의 우에서 시작한다.
	int startX = -_width / 2;
	int startZ = _depth / 2;

	//버텍스생성을 끝마칠 좌표..
	//중간을 기준으로 가장 오른쪽 아래에서 끝난다.
	int endX = _width / 2;
	int endZ = -_depth / 2;

	//하나의 버텍스 에서 다음의 버텍스로 증가할 텍스처의 좌표를 계산.
	float uCoordIncrementSize = 1.0f / (float)_numCellsPerRow;
	//어차피 텍스처의 범위는 1 이므로 전체를 1로 잡은 다음 하나의 셀의 공간으로 나누면 된다.
	float vCoordIncrementSize = 1.0f / (float)_numCellsPerCol;

	TerrainVertex* v = 0;//위치와 텍스처만 잇는 버텍스 구조.Terrain...클래스 안에 존재한다.
	_vb->Lock(0, 0, (void**)&v, 0);//버텍스에.접귾ㄴ다.

	int i = 0;
	for (int z = startZ; z >= endZ; z -= _cellSpacing)
	{//처음 버텍스 부터 마지막 버텍스까지 셀의공간씩 띄우면서..
		//z는 -방향이 양이므로..
		int j = 0;
		for (int x = startX; x <= endX; x += _cellSpacing)
		{
			//중첩된 루프 내의 위치에 따라 버텍스 버퍼와 높이맵으로의 올바른
			//인덱스를 계산한다...x축이므로..더해가면서..
			int index = i * _numVertsPerRow + j;
			//현재행의 인덱스에 numBertsPerRow을 곱한후에 해재 열의 인덱스를 더한다.

			v[index] = TerrainVertex(
				(float)x,
				(float)_heightmap[index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}

	_vb->Unlock();

	return true;
}

//인덱스를 계산.
bool Terrain::computeIndices()
{
	HRESULT hr = 0;

	hr = _device->CreateIndexBuffer(
		_numTriangles * 3 * sizeof(WORD), // 3 index per trangle 
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);

	if (FAILED(hr))
		return false;

	WORD* indices = 0;//인덱스 버퍼접근.
	_ib->Lock(0, 0, (void**)&indices, 0);

	//6개의 인덱스로 하나의 사각형을 구성하는 두개의 삼각형을 나타내기 위한 인덱스 그룹의 시작점
	// index to start of a group of 6 indices that describe the
	// two triangles that make up a quad
	int baseIndex = 0;

	// loop through and compute the triangles of each quad
	//각 사각형의 삼각형을 계산하는 루프
	for (int i = 0; i < _numCellsPerCol; i++)
	{
		for (int j = 0; j < _numCellsPerRow; j++)
		{
			indices[baseIndex] = i * _numVertsPerRow + j;
			indices[baseIndex + 1] = i * _numVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i + 1) * _numVertsPerRow + j;

			indices[baseIndex + 3] = (i + 1) * _numVertsPerRow + j;
			indices[baseIndex + 4] = i * _numVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i + 1) * _numVertsPerRow + j + 1;

			// next quad
			baseIndex += 6;
		}
	}

	_ib->Unlock();

	return true;
}

//텍스처링
bool Terrain::loadTexture(const wstring& fileName)
{
	HRESULT hr = 0;
	//미리만들어둔 텍스처 파일을 읽어들이고 이를 이용하는 방법....
	hr = D3DXCreateTextureFromFile(
		g_device,
		fileName.c_str(),//파일패스
		&_tex);//텍스처의 포인터
	//_tex데이터 멤버로 텍스처 파일을 읽어들인다.

	if (FAILED(hr))
		return false;

	return true;
}

//또는 절차적으로 텍스처를 계산한다.
//빈 텍스처를 만들고 미리 정의된 인자를 바탕으로 코드에서 각 텍셀의 
//컬러를 계산하는 것이다.
bool Terrain::genTexture(D3DXVECTOR3* directionToLight)
{
	// Method fills the top surface of a texture procedurally.  Then
	// lights the top surface.  Finally, it fills the other mipmap
	// surfaces based on the top surface data using D3DXFilterTexture.

	HRESULT hr = 0;

	// texel for each quad cell
	int texWidth = _numCellsPerRow;
	int texHeight = _numCellsPerCol;

	// create an empty texture
	hr = D3DXCreateTexture(
		_device,
		texWidth, texHeight,
		0, // create a complete mipmap chain
		0, // usage
		D3DFMT_X8R8G8B8,// 32 bit XRGB format
		D3DPOOL_MANAGED, &_tex);
	//우선은 하나의 빈 텍스처를 만든다.

	if (FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc; //텍스처의 버퍼에 접근하여 값을 읽고 수정할 수 있게.
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code 
	// that fills the texture is hard coded to a 32 bit pixel depth.
	if (textureDesc.Format != D3DFMT_X8R8G8B8)//올바른 포멧인가?
		return false;

	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(0/*최상위 레벨을 잠근다.*/, &lockedRect,
		0 /* lock entire tex*/, 0/*flags*/);

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < texHeight; i++)
	{
		for (int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			// get height of upper left vertex of quad.
			float height = (float)getHeightmapEntry(i, j) / _heightScale;
			//높이에 따른 색상을 다르게 지정한다.
			if ((height) < 42.5f) 		 c = D3DCOLOR_XRGB(255, 249, 157); // beach sand;
			else if ((height) < 85.0f)	 c = D3DCOLOR_XRGB(124, 197, 118); // light yellow green;
			else if ((height) < 127.5f) c = D3DCOLOR_XRGB(0, 166, 81); //PUREGREEN;
			else if ((height) < 170.0f) c = D3DCOLOR_XRGB(25, 123, 48); //DARK_YELLOW_GREEN;
			else if ((height) < 212.5f) c = D3DCOLOR_XRGB(115, 100, 87); // DARKBROWN;
			else	                     c = D3DCOLOR_XRGB(255, 255, 255); //WHITE;

			// fill locked data, note we divide the pitch by four because the
			// pitch is given in bytes and there are 4 bytes per DWORD.
			//잠근 데이터를 채운다. 피치를 4로 나눈이유는 피치는 바이트지만
			//dword는 4바이트 이므로..
			imageData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);//잠금해제

	if (!lightTerrain(directionToLight))//지형을 밝힌다.
	{
		::MessageBox(0, L"lightTerrain() - FAILED", 0, 0);
		return false;
	}

	hr = D3DXFilterTexture(
		_tex,//밉맵레벨을 채울 텍스처
		0, // default palette
		0, // use top level as source level
		D3DX_DEFAULT); // default filter

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXFilterTexture() - FAILED", 0, 0);
		return false;
	}

	return true;
}

bool Terrain::lightTerrain(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	D3DSURFACE_DESC textureDesc;
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code that fills the
	// texture is hard coded to a 32 bit pixel depth.
	if (textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(
		0,          // lock top surface level in mipmap chain
		&lockedRect,// pointer to receive locked data
		0,          // lock entire texture image
		0);         // no lock flags specified

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < textureDesc.Height; i++)
	{
		for (int j = 0; j < textureDesc.Width; j++)
		{
			// index into texture, note we use the pitch and divide by 
			// four since the pitch is given in bytes and there are 
			// 4 bytes per DWORD.
			int index = i * lockedRect.Pitch / 4 + j;

			// get current color of quad
			// 현재셀의 색을 얻는다.
			D3DXCOLOR c(imageData[index]);

			// shade current quad
			//셀에 음영을 적용한다.
			c *= computeShade(i, j, directionToLight);;

			// save shaded color
			//음영을 입힌 컬러를 저장한다.
			imageData[index] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	return true;
}

float Terrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight)
{
	// get heights of three vertices on the quad
	// 사각형의 세 버텍스 높이를 구한다.
	float heightA = getHeightmapEntry(cellRow, cellCol);
	float heightB = getHeightmapEntry(cellRow, cellCol + 1);
	float heightC = getHeightmapEntry(cellRow + 1, cellCol);

	// build two vectors on the quad
	//사각형의 두 벡터를 구성한다.
	D3DXVECTOR3 u(_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -_cellSpacing);

	// find the normal by taking the cross product of two
	// vectors on the quad.
	//사각형의 두 벡터 외적을 이용해 법선을 찾아낸다.
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	//스칼라 s는 [-1,1]범위내에 위치하여서 [-1,0)내의 s의 값은
	//빛을 받지 못하는 90도 이상의 빛벡터와 사각형 표면 법선간의 각도에 대응되므로
	//[-1,0)일 경우에는 0으로 고정시켜버린다.
	float cosine = D3DXVec3Dot(&n, directionToLight);
	//내적..코사인 각도를 구한다.

	if (cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}

bool Terrain::readRawFile(std::string fileName)
{

	//raw파일은 어차피 일련의 연속된 바이트 블록에 불과하다.
	std::vector<BYTE> in(_numVertices);//각 벡터를 위한 높이.

	std::ifstream inFile(fileName.c_str(), std::ios_base::binary);

	if (!inFile)
		return false;

	inFile.read(
		(char*)&in[0], // 버퍼
		in.size());// 버퍼로 읽어 들일 바이트수 

	inFile.close();//닫기.

	//BYTE 벡터를 int 벡터로 복사한다.
	_heightmap.resize(_numVertices);

	for (int i = 0; i < in.size(); i++)
		_heightmap[i] = in[i];

	return true;
}

//지형위를 걷는것 같은 느낌을 주기 위해서는 지형의 높이에 따라
//카메라의 위치를 조정하면 될 것이다.
float Terrain::getHeight(float x, float z)
{
	// Translate on xz-plane by the transformation that takes
	// the terrain START point to the origin.
	x = ((float)_width / 2.0f) + x;//지형의 시작점을 원점으로 이동하는 변환으로 
	z = ((float)_depth / 2.0f) - z;//xz-평면상에서 이동한다.

	// Scale down by the transformation that makes the 
	// cellspacing equal to one.  This is given by 
	// 1 / cellspacing since; cellspacing * 1 / cellspacing = 1.
	///셀간격을 1로 만드는 변호나으로 변환의 배율을 낮춘다.
	x /= (float)_cellSpacing;
	z /= (float)_cellSpacing;

	// From now on, we will interpret our positive z-axis as
	// going in the 'down' direction, rather than the 'up' direction.
	// This allows to extract the row and column simply by 'flooring'
	// x and z:

	float col = ::floorf(x);//셀 간격 변수의 반전으로 배율을 변경한다.
	float row = ::floorf(z);

	// get the heights of the quad we're in:
	// 
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D

	float A = getHeightmapEntry(row, col);//셀을 구성하는 네 버텍스의 높이
	float B = getHeightmapEntry(row, col + 1);
	float C = getHeightmapEntry(row + 1, col);
	float D = getHeightmapEntry(row + 1, col + 1);

	//
	// Find the triangle we are in:
	//

	// Translate by the transformation that takes the upper-left
	// corner of the cell we are in to the origin.  Recall that our 
	// cellspacing was nomalized to 1.  Thus we have a unit square
	// at the origin of our +x -> 'right' and +z -> 'down' system.
	float dx = x - col;//우리가 셀의 어떤 삼각형에 있는지르 알기 위해서
	float dz = z - row;//왼쪽 상단의 버텍스가 원점에 오도록 현재의 셀을 이동..

	// Note the below compuations of u and v are unneccessary, we really
	// only need the height, but we compute the entire vector to emphasis
	// the books discussion.
	//위쪽 삼각형
	float height = 0.0f;
	if (dz < 1.0f - dx)  // upper triangle ABC
	{
		float uy = B - A; // A->B
		float vy = C - A; // A->C

		// Linearly interpolate on each vector.  The height is the vertex
		// height the vectors u and v originate from {A}, plus the heights
		// found by interpolating on each vector u and v.
		height = A + Lerp(0.0f, uy, dx) + Lerp(0.0f, vy, dz);
	}
	//아래쪽 삼각형
	else // lower triangle DCB
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B

		// Linearly interpolate on each vector.  The height is the vertex
		// height the vectors u and v originate from {D}, plus the heights
		// found by interpolating on each vector u and v.
		height = D + Lerp(0.0f, uy, 1.0f - dx) + Lerp(0.0f, vy, 1.0f - dz);

	}

	return height;
}

bool Terrain::draw(D3DXMATRIX* world, bool drawTris)
{
	HRESULT hr = 0;

	if (_device)
	{
		_device->SetTransform(D3DTS_WORLD, world);

		_device->SetStreamSource(0, _vb, 0, sizeof(TerrainVertex));
		_device->SetFVF(TerrainVertex::FVF);
		_device->SetIndices(_ib);

		_device->SetTexture(0, _tex);

		// turn off lighting since we're lighting it ourselves
		_device->SetRenderState(D3DRS_LIGHTING, false);

		hr = _device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			_numVertices,
			0,
			_numTriangles);

		_device->SetRenderState(D3DRS_LIGHTING, true);

		if (drawTris)
		{
			_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			hr = _device->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				0,
				_numVertices,
				0,
				_numTriangles);

			_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		if (FAILED(hr))
			return false;
	}

	return true;
}

