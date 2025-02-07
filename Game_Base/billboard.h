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
	//	I_SCORE = 0,	//�X�R�A
	//	I_EXTEND,		//�c�@
	//	I_SPD,			//���x
	//	I_POW,			//�З�
	//	I_INV,			//���G���i����j
	//	I_MAX
	//}ITEM;

	CB_board(int nPriority = 1);
	virtual ~CB_board() override;
	virtual HRESULT Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	//static CB_board* Create(D3DXVECTOR3 pos);	//�����i�ʒu,�A�C�e���^�C�v�j
	static CB_board* GetItem(int I_Num);
	static int GetItemAll();
	//bool IsUse;		//�g�p���f

protected:

	//int V_Time;		//�����܂ł̎���
	//int I_Type;		//�A�C�e���^�C�v
	float B_Width;	//��
	float B_Height;	//����				
	D3DXMATRIX B_View;

private:
	static CB_board* ItemBase[MITEM];
	static int ItemAll;
};

#endif // !_ITEM_H_
