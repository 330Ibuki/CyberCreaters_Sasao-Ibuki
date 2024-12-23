#ifndef _BULLET_H_
#define _BULLET_H_

//インクルード
#include "main.h"
#include "billboard.h"

//マクロ定義
#define MBULLET	(1024)

//弾
class CBullet : public CB_board
{
public:
	CBullet();
	~CBullet() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CBullet* Create(D3DXVECTOR3 PLpos,D3DXVECTOR3 Dest, D3DXVECTOR3 Move,bool IsPlayer, bool IsChased);
	static CBullet* GetBullet(int Num);
	static int GetBulletNum();
	bool IsPlayer;
	//bool IsUse;
	
private:
	static CBullet* m_pBullets[MBULLET];

	static int BulletNum;
	D3DXVECTOR3 move;
	D3DXVECTOR3 Dest;
	int Life;
	bool IsChase;
};

//static std::list<CBullet> bullet;

#endif // !_BULLET_H_
