#pragma once

//헤이트맵전용 버텍스데이터

struct TERRAINVERTEX
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TexCoord;

	TERRAINVERTEX(Vector3 Pos, Vector3 _Normal, Vector2 Tex)
	{
		Position = Pos;
		Normal = _Normal;
		TexCoord = Tex;
	}
};

//이건알거고 모르면 Hangang
#define D3DFVF_TERRAINVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 ) 

class Terrain
{
private:
	//헤이트맵 텍스쳐 객체 (니가 쓰고있는 스프라이트 객체랑 똑같은거일거임)
	texture* m_Spr; //m_pTex는 LPDIRECT3DTEXTURE9, m_Info는 D3DXIMAGE_INFO 자료형임
	texture* maping;
	string WallMeshKey; //이거 들어가있는거 무시 (우리 지방기능대회때 헤이트맵을 둘러싸는벽 렌더하는거였음)

	LPDIRECT3DVERTEXBUFFER9 m_pVB; //헤이트맵의 버텍스버퍼
	LPDIRECT3DINDEXBUFFER9 m_pIB; //헤이트맵의 인덱스버퍼

	vector<int> m_HeightMap; //헤이트맵의 높이를 저장하는 벡터

	int numVertX, numVertZ; //버텍스 X길이, Z길이 (예를 들어서 헤이트맵이미지의 크기가 256 x 256이면 둘이 256이 되는거), Z가 이미지의 Y
	int XScale; //버텍스간의 X간격 (예를 들어서 3으로 하면 X축으로 버텍스가 3씩 멀어질거임)
	int ZScale; //버텍스간의 Z간격 (똑같음)

	int numCellX, numCellZ; //X, Z의 인덱스수 numVertX, numVertZ에서 -1을하여서 구한다.
	int Width, Depth; //헤이트맵 이미지로 뽑아낸 3D물체의 X , Z 최종길이 

	int numVertices, numTriangles; //총 버텍스의 개수, 총 삼각형의 개수
	float heightScale; //높이 스케일 (이거 높이면 헤이트맵의 높이가 늘어남, 근데 간단하게 한거라 너무 높이면 단조롭게 높여짐)

	float Lerp(float a, float b, float t) //평면의 방정식에서 필요한 보간 ( 나중에 헤이트맵의 높이를 구할때 사용 )
	{
		return  a - (a*t) + (b*t);
	}

	void ReadHeight(); //높이 읽어오는 함수
	void VertexSetting(); //버텍스 세팅
	void IndexSetting(); //인덱스 세팅
public:
	Terrain(texture* _Spr,texture* _map, int CellSpacingX, int CellSpacingZ, float _heightScale);
	~Terrain();

	int getHeightmapEntry(int row, int col); //높이정보를 저장하고 있는 벡터에서 높이값 추출
	float getHeight(float x, float z); // 오브젝트의 포지션에서 헤이트맵의 높이 추출

	void Render(); //헤이트맵 출력

	void Destroy();
};