/*
Item
*/
#ifndef _ITEM_H_
#define _ITEM_H_

//Include
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

#define INUM_MAX	(150)

//class
class CItem : public CB_board
{
public:
	typedef enum
	{
		I_SCORE = 0,	//スコア
		I_EXTEND,		//残機
		I_SPD,			//PL速度
		I_POW,			//威力
		I_INV,			//無敵化（未定）
		ITEM_MAX
	}ITEM;

	CItem();
	~CItem()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CItem* Create(D3DXVECTOR3 pos, ITEM type);
	static CItem* GetItem(int num);
	static int GetItemNum();
	int Item_type;

private:
	static CItem* m_Item[INUM_MAX];
	static int ItemNum;

};

#endif // !_ITEM_H_