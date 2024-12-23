#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//�C���N���[�h
#include "main.h"
#include "object.h"

//�I�u�W�F�N�g3D�N���X�̒�`�i���N���X�FCObject�j
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
