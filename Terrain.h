#pragma once

//����Ʈ������ ���ؽ�������

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

//�̰Ǿ˰Ű� �𸣸� Hangang
#define D3DFVF_TERRAINVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 ) 

class Terrain
{
private:
	//����Ʈ�� �ؽ��� ��ü (�ϰ� �����ִ� ��������Ʈ ��ü�� �Ȱ������ϰ���)
	texture* m_Spr; //m_pTex�� LPDIRECT3DTEXTURE9, m_Info�� D3DXIMAGE_INFO �ڷ�����
	texture* maping;
	string WallMeshKey; //�̰� ���ִ°� ���� (�츮 �����ɴ�ȸ�� ����Ʈ���� �ѷ��δº� �����ϴ°ſ���)

	LPDIRECT3DVERTEXBUFFER9 m_pVB; //����Ʈ���� ���ؽ�����
	LPDIRECT3DINDEXBUFFER9 m_pIB; //����Ʈ���� �ε�������

	vector<int> m_HeightMap; //����Ʈ���� ���̸� �����ϴ� ����

	int numVertX, numVertZ; //���ؽ� X����, Z���� (���� �� ����Ʈ���̹����� ũ�Ⱑ 256 x 256�̸� ���� 256�� �Ǵ°�), Z�� �̹����� Y
	int XScale; //���ؽ����� X���� (���� �� 3���� �ϸ� X������ ���ؽ��� 3�� �־�������)
	int ZScale; //���ؽ����� Z���� (�Ȱ���)

	int numCellX, numCellZ; //X, Z�� �ε����� numVertX, numVertZ���� -1���Ͽ��� ���Ѵ�.
	int Width, Depth; //����Ʈ�� �̹����� �̾Ƴ� 3D��ü�� X , Z �������� 

	int numVertices, numTriangles; //�� ���ؽ��� ����, �� �ﰢ���� ����
	float heightScale; //���� ������ (�̰� ���̸� ����Ʈ���� ���̰� �þ, �ٵ� �����ϰ� �ѰŶ� �ʹ� ���̸� �����Ӱ� ������)

	float Lerp(float a, float b, float t) //����� �����Ŀ��� �ʿ��� ���� ( ���߿� ����Ʈ���� ���̸� ���Ҷ� ��� )
	{
		return  a - (a*t) + (b*t);
	}

	void ReadHeight(); //���� �о���� �Լ�
	void VertexSetting(); //���ؽ� ����
	void IndexSetting(); //�ε��� ����
public:
	Terrain(texture* _Spr,texture* _map, int CellSpacingX, int CellSpacingZ, float _heightScale);
	~Terrain();

	int getHeightmapEntry(int row, int col); //���������� �����ϰ� �ִ� ���Ϳ��� ���̰� ����
	float getHeight(float x, float z); // ������Ʈ�� �����ǿ��� ����Ʈ���� ���� ����

	void Render(); //����Ʈ�� ���

	void Destroy();
};