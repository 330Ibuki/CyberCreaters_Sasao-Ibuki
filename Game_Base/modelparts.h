#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_
//include
#include "main.h"
#include "object.h"

//macro
#define FILENAME	(40)
#define PARTLIM		(120)

//モデルパーツ読み込み
class CModelParts
{
public:
	CModelParts();
	~CModelParts();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CModelParts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,char* PartsName,int PartsNum);
	static int GetPartsNum();
	void SetParent(CModelParts* pParent);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_ptex;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	CModelParts* m_pParent;
	static CModelParts* m_pModelParts[PARTLIM];
	static int PartNum;
	int P_Num;
	char PartsName[FILENAME];
};
#endif // !_MODELPARTS_H_
