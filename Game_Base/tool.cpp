/*=================================
#
# GameTool_StageCrafter
# Author: Sasao Ibuki
#
=================================*/

//インクルード
#include "tool.h"
#include "input.h"

//静的メンバ初期化
CToolPlace* CToolPlace::TP = {};

/*=========================
コンストラクタ・デストラクタ
===========================*/

CToolPlace::CToolPlace()
{
	B_Num = NULL;
	B_x = NULL;
	B_y = NULL;
	B_z = NULL;
}

CToolPlace::~CToolPlace()
{

}

/*=========================
初期化
===========================*/

void CToolPlace::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	B_Num = 0;
	B_x = 0;
	B_y = 0;
	B_z = 0;
}

/*=========================
終了
===========================*/

void CToolPlace::Uninit()
{

}

/*=========================
更新
===========================*/

void CToolPlace::Update()
{
	CInputKeyboard* pKeyBoard = CManager::GetKeyboard();
	CBlock* pBlock[MOBJ] = {};

	for (int i = 0; i < MOBJ; i++)
	{
		pBlock[i] = pBlock[i]->GetBlock(i);
	}

	if (pBlock[B_Num] != nullptr)
	{
		if (pKeyBoard->GetPress(DIK_W) == true) //up
		{
			pBlock[B_Num]->m_pos.y += 1;

			if (pKeyBoard->GetPress(DIK_A) == true) //left
			{
				pBlock[B_Num]->m_pos.x -= 1;
			}

			else if (pKeyBoard->GetPress(DIK_D) == true) //right
			{
				pBlock[B_Num]->m_pos.x += 1;
			}
		}

		else if (pKeyBoard->GetPress(DIK_S) == true) //down
		{
			pBlock[B_Num]->m_pos.y += -1;

			if (pKeyBoard->GetPress(DIK_A) == true) //left
			{
				pBlock[B_Num]->m_pos.x -= 1;
			}

			else if (pKeyBoard->GetPress(DIK_D) == true) //right
			{
				pBlock[B_Num]->m_pos.x += 1;
			}
		}



		if (pKeyBoard->GetPress(DIK_RETURN) == true) //Place
		{
			pBlock[B_Num]->m_pos.x = B_x;
			pBlock[B_Num]->m_pos.y = B_y;
			pBlock[B_Num]->m_pos.z = B_z;
			//CBlock::Create(D3DXVECTOR3(B_x, B_y, B_z), false);
			B_Num++;
		}

		if (pKeyBoard->GetPress(DIK_BACKSPACE) == true) //Delete
		{
			B_Num++;
		}
	}

}

//CToolPlace* CToolPlace::ToolActive()
//{
//	TP->B_Num = 0;
//	TP->B_x = 0;
//	TP->B_y = 0;
//	TP->B_z = 0;
//	return TP;
//}