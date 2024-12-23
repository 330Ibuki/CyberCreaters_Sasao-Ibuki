#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//インクルード
#include "main.h"
#include "object.h"

//オブジェクト3Dクラスの定義（基底クラス：CObject）
class CObject3D : public CObject
{
public:
	CObject3D();
	~CObject3D() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CObject3D* Create(D3DXVECTOR3 pos);
	//static HRESULT Load();
	//static void Unload();

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_ptex;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;

	static CObject3D* m_apObject3D;
};

#endif // !_OBJECT3D_H_
