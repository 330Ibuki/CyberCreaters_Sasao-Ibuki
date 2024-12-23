#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include <Windows.h>
#include "d3dx9.h"
#include "object.h"

//ÇQDÉ|ÉäÉSÉìä«óù
class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 5);
	virtual ~CObject2D() override;
	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	static CObject2D* Create(); 

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	D3DXVECTOR3& GetPos() { return m_pos; }

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTex;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	float m_fWidth;
	float m_fHeight;
	int m_Priority;
	int m_AnimPat;
	int m_AnimCnt;
	int m_MAnimPat;
	int m_AnimChang;
	bool m_bUse;
	static CObject2D* m_apObject2D;                 
};
#endif // !_OBJECT2D_H_

