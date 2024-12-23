#ifndef _PLAYERX_H_
#define _PLAYERX_H_

//インクルード
#include "objectx.h"
#include "modelparts.h"


#define PARTS	(1)

//プレイヤー（3D）クラスの定義
class CPlayerX : public CObject
{
public:
	CPlayerX();
	~CPlayerX();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Damage(int DMG);
	static CPlayerX* Create(D3DXVECTOR3 pos);
	static CPlayerX* GetPlayer();
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 move;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 StartPos;
	bool m_bDeath;
	bool m_Land;
	bool m_WallLand;
	bool SwitchStat;
	float m_Grav;
	int m_Priority;

private:
	static CPlayerX* m_apPlayerX;
	D3DXMATRIX m_mtxWorld;
	int m_PJump;
	bool m_Jump;
	int m_life;
	bool Dodge;
	static CModelParts* m_apModel[PARTS];
};

#endif // !_PLAYERX_H_
