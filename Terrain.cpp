#include "DXUT.h"
#include "Terrain.h"

Terrain::Terrain(texture* _Spr, texture* _map, int CellSpacingX, int CellSpacingZ, float _heightScale)
{
	m_Spr = _Spr;
	maping = _map;

	XScale = CellSpacingX;
	ZScale = CellSpacingZ;
	heightScale = _heightScale;

	D3DSURFACE_DESC ddsd;
	m_Spr->texturePtr->GetLevelDesc(0, &ddsd);
	numVertX = ddsd.Width;
	numVertZ = ddsd.Height;

	numCellX = numVertX - 1;
	numCellZ = numVertZ - 1;

	Width = numCellX * XScale;
	Depth = numCellZ * ZScale;

	numVertices = numVertX * numVertZ;
	numTriangles = numCellX * numCellZ * 2;

	ReadHeight();

	VertexSetting();
	IndexSetting();

	WallMeshKey = "MAPWALL1";
}

Terrain::~Terrain()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
}

void Terrain::ReadHeight()
{
	m_HeightMap.resize(numVertices);

	D3DLOCKED_RECT d3drc;
	m_Spr->texturePtr->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);
	DWORD* pColor = (DWORD*)d3drc.pBits;

	for (int i = 0; i < numVertices; i++)
	{
		D3DXCOLOR xClr = pColor[i];
		m_HeightMap[i] = xClr.r * 10 + xClr.g * 10 + xClr.b * 10;
	}

	m_Spr->texturePtr->UnlockRect(0);

	for (int i = 0; i < m_HeightMap.size(); i++)
	{
		m_HeightMap[i] *= heightScale;
	}
}

void Terrain::VertexSetting()
{
	g_device->CreateVertexBuffer(numVertices * sizeof(TERRAINVERTEX), D3DUSAGE_WRITEONLY,
		D3DFVF_TERRAINVERTEX, D3DPOOL_MANAGED, &m_pVB, 0);

	int StartX = -Width / 2;
	int StartZ = Depth / 2;

	int EndX = Width / 2;
	int EndZ = -Depth / 2;

	float uUnit = 1.0f / (float)numCellX;
	float vUnit = 1.0f / (float)numCellZ;

	TERRAINVERTEX* v = nullptr;
	m_pVB->Lock(0, 0, (void**)&v, 0);
	int i = 0;
	for (int z = StartZ; z >= EndZ; z -= ZScale)
	{
		int j = 0;
		for (int x = StartX; x <= EndX; x += XScale)
		{
			int Index = i * numVertX + j;

			Vector3 Pos = Vector3((float)x, (float)m_HeightMap[Index], (float)z);
			Vector3 Normal = Pos;
			D3DXVec3Normalize(&Normal, &Normal);
			Vector2 texCoord = Vector2((float)j * uUnit, (float)i * vUnit);
			v[Index] = TERRAINVERTEX(
				Pos,
				Normal,
				texCoord
			);
			++j;
		}
		++i;
	}
	m_pVB->Unlock();
}

void Terrain::IndexSetting()
{
	g_device->CreateIndexBuffer(numTriangles * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, 0);
	
	WORD* Indices = 0;
	m_pIB->Lock(0, 0, (void**)&Indices, 0);

	int baseIndex = 0;

	for (int i = 0; i < numCellZ; i++)
	{
		for (int j = 0; j < numCellX; j++)
		{
			Indices[baseIndex] = i * numVertX + j;
			Indices[baseIndex + 1] = i * numVertX + j + 1;
			Indices[baseIndex + 2] = (i + 1) * numVertX + j;

			Indices[baseIndex + 3] = (i + 1) * numVertX + j;
			Indices[baseIndex + 4] = i * numVertX + j + 1;
			Indices[baseIndex + 5] = (i + 1) * numVertX + j + 1;

			baseIndex += 6;
		}
	}

	m_pIB->Unlock();
}

void Terrain::Render()
{
	UINT iPass, cPasses;
	
	g_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	g_device->SetTransform(D3DTS_WORLD, &mat);

	g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_device->SetStreamSource(0, m_pVB, 0, sizeof(TERRAINVERTEX));
	g_device->SetFVF(D3DFVF_TERRAINVERTEX);
	g_device->SetIndices(m_pIB);
	
	g_device->SetTexture(0, maping->texturePtr);
	g_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0, 0,
		numVertices,
		0, numTriangles);
		
	g_device->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Terrain::Destroy()
{
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pVB);
}

int Terrain::getHeightmapEntry(int row, int col)
{
	//return m_HeightMap[row+ (m_Spr->info.Height/2) * numVertX + col + (m_Spr->info.Width / 2)];
	return m_HeightMap[row * numVertX + col ];
}

float Terrain::getHeight(float x, float z)
{
	x = ((float)Width / 2.0f) + x;
	z = ((float)Depth / 2.0f) - z;

	x /= XScale;
	z /= ZScale;

	float col = floorf(x);
	float row = floorf(z);

	float A = getHeightmapEntry(row, col);
	float B = getHeightmapEntry(row, col + 1);
	float C = getHeightmapEntry(row + 1, col);
	float D = getHeightmapEntry(row + 1, col + 1);

	float dx = x - col;
	float dz = z - row;

	float height = 0.0f;

	if (dz < 1.0f - dx)
	{
		float uy = B - A;
		float vy = C - A;

		height = A + Lerp(0.0f, uy, dx) + Lerp(0.0f, vy, dz);
	}

	else
	{
		float uy = C - D;
		float vy = B - D;

		height = D + Lerp(0.0f, uy, 1.0f - dx) + Lerp(0.0f, vy, 1.0f - dz);
	}

	return height;
}