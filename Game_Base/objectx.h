#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//インクルード
#include "main.h"
#include "object.h"

//オブジェクトX
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 2);
	~CObjectX() override;
	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	//static CObjectX* Create(D3DXVECTOR3 pos);
	static CObjectX* Getobj(int B_Num);
	//static HRESULT Load();
	//static void Unload();

	bool OnCol;
	bool m_bDeath;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 m_posOld;

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_ptex;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	int m_Priority;
	int m_Flame_Count;
	int OBJ_ID;

private:
	static CObjectX* m_apObjectX[MOBJ];
};

#endif // !_OBJECTX_H_
