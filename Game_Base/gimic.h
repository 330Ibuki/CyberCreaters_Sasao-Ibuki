#ifndef _GIMIC_H_
#define _GIMIC_H_

//インクルード
#include "main.h"
#include "objectx.h"

//マクロ定義
#define MGIMC	(1024)

//ステージ構成用ブロッククラス（基底クラス：CObjectX）
class CGimic : public CObjectX
{
public:
	typedef enum
	{
		NORMAL = 0,	//左右往復
		REVERSE,	//左右往復（反転）
		G_MAX
	}G_TYPE;

	CGimic();
	~CGimic();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CGimic* Create(D3DXVECTOR3 pos, D3DXVECTOR3 mov, G_TYPE type);
	static CGimic* GetGimic(int Num);
	static int GetGimNum();

	G_TYPE m_Rift;
	D3DXVECTOR3 m_move;
private:
	static CGimic* m_apGimic[MGIMC];
	static int GimNum;
	int m_Rift_timer;
	int m_Rift_Set;
	int m_Rift_Count;
	int m_Rift_BCount;

};
#endif // !_BLOCK_H_
