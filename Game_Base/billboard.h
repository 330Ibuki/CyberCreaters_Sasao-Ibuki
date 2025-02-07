/*==========================
#
# Item FrameWork
#
#
============================*/
#ifndef _BILL_H_
#define _BILL_H_

#include "main.h"
#include "objectx.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "player.x.h"

#define MITEM	(1024)

class CB_board : public CObjectX
{
public:

	//typedef enum
	//{
	//	I_SCORE = 0,	//スコア
	//	I_EXTEND,		//残機
	//	I_SPD,			//速度
	//	I_POW,			//威力
	//	I_INV,			//無敵化（未定）
	//	I_MAX
	//}ITEM;

	CB_board(int nPriority = 1);
	virtual ~CB_board() override;
	virtual HRESULT Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	//static CB_board* Create(D3DXVECTOR3 pos);	//引数（位置,アイテムタイプ）
	static CB_board* GetItem(int I_Num);
	static int GetItemAll();
	//bool IsUse;		//使用判断

protected:

	//int V_Time;		//消失までの時間
	//int I_Type;		//アイテムタイプ
	float B_Width;	//幅
	float B_Height;	//高さ				
	D3DXMATRIX B_View;

private:
	static CB_board* ItemBase[MITEM];
	static int ItemAll;
};

#endif // !_ITEM_H_
