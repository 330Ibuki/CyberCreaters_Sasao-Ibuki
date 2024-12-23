#ifndef _COLLISION_H_
#define _COLLISION_H_

//インクルード
#include "main.h"

//マクロ定義
#define M_COL	(1024)
#define C_PRI	(6)

//当たり判定の定義
class CCollision
{
public:
	/*
	* ０ブロック
	* １プレイヤー
	* ２敵
	* ３ダメージがないギミック
	* ４ダメージが発生するギミック
	* ５取得できるもの
	*/
	typedef enum
	{
		NONE = 0,
		PLAYER,
		ENEMY,
		GIMIC,
		TRAP,
		ITEM,
		C_MAX
	}C_TYPE;

	CCollision(int C_pri = 0,int C_ID = 0);
	~CCollision();
	HRESULT Init();
	void Uninit();
	void Update();

private:
};

#endif // !_COLLISION_H_
