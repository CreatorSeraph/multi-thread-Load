#include "DXUT.h"
#include "terrain.h"
#include <fstream>
#include <cmath>

const DWORD Terrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

Terrain::Terrain(IDirect3DDevice9* device,//����̽� ��ü
	std::string heightmapFileName,//�����̸�
	int numVertsPerRow,//��
	int numVertsPerCol,//��
	int cellSpacing,//�� ���� ���� 
	float heightScale)//���� ������ �����ϴ� ��
{
	_device = device;//��ġ
	_numVertsPerRow = numVertsPerRow;//
	_numVertsPerCol = numVertsPerCol;//
	_cellSpacing = cellSpacing;//���� ����

	_numCellsPerRow = _numVertsPerRow - 1;
	_numCellsPerCol = _numVertsPerCol - 1;

	_width = _numCellsPerRow * _cellSpacing;
	_depth = _numCellsPerCol * _cellSpacing;

	_numVertices = _numVertsPerRow * _numVertsPerCol;
	_numTriangles = _numCellsPerRow * _numCellsPerCol * 2;

	_heightScale = heightScale;

	// load heightmap
	if (!readRawFile(heightmapFileName))//raw������ �д´�.
	{
		::MessageBox(0, L"readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// scale heights
	for (int i = 0; i < _heightmap.size(); i++)//����..
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

int Terrain::getHeightmapEntry(int row, int col)//���̸� ���� �׸� ����
{
	return _heightmap[row * _numVertsPerRow + col];
}

void Terrain::setHeightmapEntry(int row, int col, int value)//���̸� ���� �׸��� ����.
{
	_heightmap[row * _numVertsPerRow + col] = value;
}

//���������� ���ؽ��� ������
bool Terrain::computeVertices()
{
	HRESULT hr = 0;

	hr = _device->CreateVertexBuffer(
		_numVertices * sizeof(TerrainVertex),//���ؽ��� ����, �� ���ؽ�.
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if (FAILED(hr))
		return false;

	//���ؽ������� ������ ��ǥ..
	//�߰��� �������� ���� ������ �쿡�� �����Ѵ�.
	int startX = -_width / 2;
	int startZ = _depth / 2;

	//���ؽ������� ����ĥ ��ǥ..
	//�߰��� �������� ���� ������ �Ʒ����� ������.
	int endX = _width / 2;
	int endZ = -_depth / 2;

	//�ϳ��� ���ؽ� ���� ������ ���ؽ��� ������ �ؽ�ó�� ��ǥ�� ���.
	float uCoordIncrementSize = 1.0f / (float)_numCellsPerRow;
	//������ �ؽ�ó�� ������ 1 �̹Ƿ� ��ü�� 1�� ���� ���� �ϳ��� ���� �������� ������ �ȴ�.
	float vCoordIncrementSize = 1.0f / (float)_numCellsPerCol;

	TerrainVertex* v = 0;//��ġ�� �ؽ�ó�� �մ� ���ؽ� ����.Terrain...Ŭ���� �ȿ� �����Ѵ�.
	_vb->Lock(0, 0, (void**)&v, 0);//���ؽ���.���D����.

	int i = 0;
	for (int z = startZ; z >= endZ; z -= _cellSpacing)
	{//ó�� ���ؽ� ���� ������ ���ؽ����� ���ǰ����� ���鼭..
		//z�� -������ ���̹Ƿ�..
		int j = 0;
		for (int x = startX; x <= endX; x += _cellSpacing)
		{
			//��ø�� ���� ���� ��ġ�� ���� ���ؽ� ���ۿ� ���̸������� �ùٸ�
			//�ε����� ����Ѵ�...x���̹Ƿ�..���ذ��鼭..
			int index = i * _numVertsPerRow + j;
			//�������� �ε����� numBertsPerRow�� �����Ŀ� ���� ���� �ε����� ���Ѵ�.

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

//�ε����� ���.
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

	WORD* indices = 0;//�ε��� ��������.
	_ib->Lock(0, 0, (void**)&indices, 0);

	//6���� �ε����� �ϳ��� �簢���� �����ϴ� �ΰ��� �ﰢ���� ��Ÿ���� ���� �ε��� �׷��� ������
	// index to start of a group of 6 indices that describe the
	// two triangles that make up a quad
	int baseIndex = 0;

	// loop through and compute the triangles of each quad
	//�� �簢���� �ﰢ���� ����ϴ� ����
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

//�ؽ�ó��
bool Terrain::loadTexture(const wstring& fileName)
{
	HRESULT hr = 0;
	//�̸������� �ؽ�ó ������ �о���̰� �̸� �̿��ϴ� ���....
	hr = D3DXCreateTextureFromFile(
		g_device,
		fileName.c_str(),//�����н�
		&_tex);//�ؽ�ó�� ������
	//_tex������ ����� �ؽ�ó ������ �о���δ�.

	if (FAILED(hr))
		return false;

	return true;
}

//�Ǵ� ���������� �ؽ�ó�� ����Ѵ�.
//�� �ؽ�ó�� ����� �̸� ���ǵ� ���ڸ� �������� �ڵ忡�� �� �ؼ��� 
//�÷��� ����ϴ� ���̴�.
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
	//�켱�� �ϳ��� �� �ؽ�ó�� �����.

	if (FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc; //�ؽ�ó�� ���ۿ� �����Ͽ� ���� �а� ������ �� �ְ�.
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code 
	// that fills the texture is hard coded to a 32 bit pixel depth.
	if (textureDesc.Format != D3DFMT_X8R8G8B8)//�ùٸ� �����ΰ�?
		return false;

	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(0/*�ֻ��� ������ ��ٴ�.*/, &lockedRect,
		0 /* lock entire tex*/, 0/*flags*/);

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < texHeight; i++)
	{
		for (int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			// get height of upper left vertex of quad.
			float height = (float)getHeightmapEntry(i, j) / _heightScale;
			//���̿� ���� ������ �ٸ��� �����Ѵ�.
			if ((height) < 42.5f) 		 c = D3DCOLOR_XRGB(255, 249, 157); // beach sand;
			else if ((height) < 85.0f)	 c = D3DCOLOR_XRGB(124, 197, 118); // light yellow green;
			else if ((height) < 127.5f) c = D3DCOLOR_XRGB(0, 166, 81); //PUREGREEN;
			else if ((height) < 170.0f) c = D3DCOLOR_XRGB(25, 123, 48); //DARK_YELLOW_GREEN;
			else if ((height) < 212.5f) c = D3DCOLOR_XRGB(115, 100, 87); // DARKBROWN;
			else	                     c = D3DCOLOR_XRGB(255, 255, 255); //WHITE;

			// fill locked data, note we divide the pitch by four because the
			// pitch is given in bytes and there are 4 bytes per DWORD.
			//��� �����͸� ä���. ��ġ�� 4�� ���������� ��ġ�� ����Ʈ����
			//dword�� 4����Ʈ �̹Ƿ�..
			imageData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);//�������

	if (!lightTerrain(directionToLight))//������ ������.
	{
		::MessageBox(0, L"lightTerrain() - FAILED", 0, 0);
		return false;
	}

	hr = D3DXFilterTexture(
		_tex,//�Ӹʷ����� ä�� �ؽ�ó
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
			// ���缿�� ���� ��´�.
			D3DXCOLOR c(imageData[index]);

			// shade current quad
			//���� ������ �����Ѵ�.
			c *= computeShade(i, j, directionToLight);;

			// save shaded color
			//������ ���� �÷��� �����Ѵ�.
			imageData[index] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	return true;
}

float Terrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight)
{
	// get heights of three vertices on the quad
	// �簢���� �� ���ؽ� ���̸� ���Ѵ�.
	float heightA = getHeightmapEntry(cellRow, cellCol);
	float heightB = getHeightmapEntry(cellRow, cellCol + 1);
	float heightC = getHeightmapEntry(cellRow + 1, cellCol);

	// build two vectors on the quad
	//�簢���� �� ���͸� �����Ѵ�.
	D3DXVECTOR3 u(_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -_cellSpacing);

	// find the normal by taking the cross product of two
	// vectors on the quad.
	//�簢���� �� ���� ������ �̿��� ������ ã�Ƴ���.
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	//��Į�� s�� [-1,1]�������� ��ġ�Ͽ��� [-1,0)���� s�� ����
	//���� ���� ���ϴ� 90�� �̻��� �����Ϳ� �簢�� ǥ�� �������� ������ �����ǹǷ�
	//[-1,0)�� ��쿡�� 0���� �������ѹ�����.
	float cosine = D3DXVec3Dot(&n, directionToLight);
	//����..�ڻ��� ������ ���Ѵ�.

	if (cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}

bool Terrain::readRawFile(std::string fileName)
{

	//raw������ ������ �Ϸ��� ���ӵ� ����Ʈ ��Ͽ� �Ұ��ϴ�.
	std::vector<BYTE> in(_numVertices);//�� ���͸� ���� ����.

	std::ifstream inFile(fileName.c_str(), std::ios_base::binary);

	if (!inFile)
		return false;

	inFile.read(
		(char*)&in[0], // ����
		in.size());// ���۷� �о� ���� ����Ʈ�� 

	inFile.close();//�ݱ�.

	//BYTE ���͸� int ���ͷ� �����Ѵ�.
	_heightmap.resize(_numVertices);

	for (int i = 0; i < in.size(); i++)
		_heightmap[i] = in[i];

	return true;
}

//�������� �ȴ°� ���� ������ �ֱ� ���ؼ��� ������ ���̿� ����
//ī�޶��� ��ġ�� �����ϸ� �� ���̴�.
float Terrain::getHeight(float x, float z)
{
	// Translate on xz-plane by the transformation that takes
	// the terrain START point to the origin.
	x = ((float)_width / 2.0f) + x;//������ �������� �������� �̵��ϴ� ��ȯ���� 
	z = ((float)_depth / 2.0f) - z;//xz-���󿡼� �̵��Ѵ�.

	// Scale down by the transformation that makes the 
	// cellspacing equal to one.  This is given by 
	// 1 / cellspacing since; cellspacing * 1 / cellspacing = 1.
	///�������� 1�� ����� ��ȣ������ ��ȯ�� ������ �����.
	x /= (float)_cellSpacing;
	z /= (float)_cellSpacing;

	// From now on, we will interpret our positive z-axis as
	// going in the 'down' direction, rather than the 'up' direction.
	// This allows to extract the row and column simply by 'flooring'
	// x and z:

	float col = ::floorf(x);//�� ���� ������ �������� ������ �����Ѵ�.
	float row = ::floorf(z);

	// get the heights of the quad we're in:
	// 
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D

	float A = getHeightmapEntry(row, col);//���� �����ϴ� �� ���ؽ��� ����
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
	float dx = x - col;//�츮�� ���� � �ﰢ���� �ִ����� �˱� ���ؼ�
	float dz = z - row;//���� ����� ���ؽ��� ������ ������ ������ ���� �̵�..

	// Note the below compuations of u and v are unneccessary, we really
	// only need the height, but we compute the entire vector to emphasis
	// the books discussion.
	//���� �ﰢ��
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
	//�Ʒ��� �ﰢ��
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

