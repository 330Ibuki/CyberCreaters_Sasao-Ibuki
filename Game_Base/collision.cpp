/*==================================
//
// Collision
// Author : Sasao Ibuki
//
==================================*/

//インクルード
#include "collision.h"
#include "player.x.h"
#include "enemy.h"
#include "block.h"
#include "bullet.h"
#include "gimic.h"
#include "item.h"
#include "camera.h"
#include "number.h"
#include "manager.h"

/*===================================
//コンストラクタ・デストラクタ
===================================*/

CCollision::CCollision(int C_pri,int obj)
{

}

CCollision::~CCollision()
{

}

/*===================================
//初期化
===================================*/

HRESULT CCollision::Init()
{
	return S_OK;
}

/*===================================
//破棄
===================================*/

void CCollision::Uninit()
{

}

/*===================================
//更新（当たり判定あれこれ）
===================================*/

void CCollision::Update()
{
	CPlayerX* pPlayerX = pPlayerX->GetPlayer();
	CEnemy* pEnemy[ENM_MAX] = {};
	CGimic* pGimic[MGIMC] = {};
	CBullet* pBullet[MBULLET] = {};
	CBlock* pBlock[MOBJ] = {};
	CFloorRoof* pFRoof[FROOF] = {};
	CFloorWall* pFWall[FROOF] = {};
	CPlatform* pPlat[PLAT] = {};
	CGround* pGround[GROUND] = {};
	CSG* pSG[MSG] = {};
	CItem* pItem[INUM_MAX] = {};


	for (int i = 0; i < FROOF; i++)
	{
		pFRoof[i] = pFRoof[i]->GetFloor(i);
		pFWall[i] = pFWall[i]->GetWall(i);
		pPlat[i] = pPlat[i]->GetPlat(i);
	}

	for (int i = 0; i < GROUND; i++)
	{
		pGround[i] = pGround[i]->GetGround(i);
	}

	for (int i = 0; i < MOBJ; i++)
	{
		pBlock[i] = pBlock[i]->GetBlock(i);
	}

	for (int i = 0; i < MGIMC; i++)
	{
		pGimic[i] = pGimic[i]->GetGimic(i);

	}

	for (int i = 0; i < ENM_MAX; i++)
	{
		pEnemy[i] = pEnemy[i]->GetEnmey(i);
	}

	for (int i = 0; i < MBULLET; i++)
	{
		pBullet[i] = pBullet[i]->GetBullet(i);
	}

	for (int i = 0; i < MSG; i++)
	{
		pSG[i] = pSG[i]->GetSG(i);
	}

	for (int i = 0; i < INUM_MAX; i++)
	{
		pItem[i] = pItem[i]->GetItem(i);
	}

	for (int i = 0; i < M_COL; i++)
	{
		if (pBlock[i] != nullptr && pBlock[i]->IsUse != false)
		{

			//プレイヤーとブロックの当たり判定(Z軸の当たり判定なし)
			//当たり判定　左
			if (pPlayerX->m_pos.x + 5 > pBlock[i]->m_pos.x - 5 &&
				pPlayerX->m_posOld.x < pBlock[i]->m_pos.x - 5 &&
				pPlayerX->m_pos.z + 5 > pBlock[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pBlock[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y < pBlock[i]->m_pos.y + 15 &&
				pPlayerX->m_pos.y >= pBlock[i]->m_pos.y)
			{
				pPlayerX->m_pos.x = pBlock[i]->m_pos.x - 10;
			}

			//当たり判定　右
			else if (pPlayerX->m_pos.x - 5 < pBlock[i]->m_pos.x + 5 &&
				pPlayerX->m_posOld.x > pBlock[i]->m_pos.x + 5 &&
				pPlayerX->m_pos.z + 5 > pBlock[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pBlock[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y < pBlock[i]->m_pos.y + 15 &&
				pPlayerX->m_pos.y >= pBlock[i]->m_pos.y)
			{
				pPlayerX->m_pos.x = pBlock[i]->m_pos.x + 10;
			}



			//当たり判定　上
			else if (pPlayerX->m_pos.x + 5 > pBlock[i]->m_pos.x - 5 &&
				pPlayerX->m_pos.x - 5 < pBlock[i]->m_pos.x + 5 &&
				pPlayerX->m_pos.z + 5 > pBlock[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pBlock[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y < pBlock[i]->m_pos.y + 18 &&
				pPlayerX->m_pos.y > pBlock[i]->m_pos.y + 9)/*&&
				pPlayerX->m_posOld.y > pBlock[i]->m_pos.y + 20*/
			{
				pBlock[i]->OnCol = true;
				pPlayerX->m_pos.y = pBlock[i]->m_pos.y + 18;
				pPlayerX->m_Land = true;

			}

			//当たり判定　下
			else if (pPlayerX->m_pos.x + 5 > pBlock[i]->m_pos.x - 5 &&
				pPlayerX->m_pos.x - 5 < pBlock[i]->m_pos.x + 5 &&
				pPlayerX->m_pos.z + 5 > pBlock[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pBlock[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y > pBlock[i]->m_pos.y &&
				pPlayerX->m_pos.y < pBlock[i]->m_pos.y + 9)
			{
				pPlayerX->move.y = 0;
				pPlayerX->m_Grav = 0.75;
				pPlayerX->m_pos.y = pBlock[i]->m_pos.y - 5;
			}

			if (pBlock[i]->OnCol == true &&
				pPlayerX->m_pos.x + 5 < pBlock[i]->m_pos.x - 5)
			{
				pBlock[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}

			else if (pBlock[i]->OnCol == true &&
				pPlayerX->m_pos.x - 5 > pBlock[i]->m_pos.x + 5)
			{
				pBlock[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}

		}
		//ここまでブロック当たり判定
	}

	for (int i = 0; i < FROOF; i++)
	{
		//天井
		if (pFRoof[i] != nullptr && pFRoof[i]->IsUse != false)
		{	//下
			if (pPlayerX->m_pos.x + 5 > pFRoof[i]->m_pos.x - 119 &&
				pPlayerX->m_pos.x - 5 < pFRoof[i]->m_pos.x + 119 &&
				pPlayerX->m_pos.z + 5 > pFRoof[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pFRoof[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y > pFRoof[i]->m_pos.y &&
				pPlayerX->m_pos.y < pFRoof[i]->m_pos.y + 5)
			{
				pPlayerX->move.y = 0;
				pPlayerX->m_Grav = 0.75;
				pPlayerX->m_pos.y = pFRoof[i]->m_pos.y - 5;

			}

			//左
			else if (pPlayerX->m_pos.x + 5 > pFRoof[i]->m_pos.x - 120 &&
				pPlayerX->m_posOld.x < pFRoof[i]->m_pos.x - 120 &&
				pPlayerX->m_pos.z + 5 > pFRoof[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pFRoof[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y < pFRoof[i]->m_pos.y + 5 &&
				pPlayerX->m_pos.y >= pFRoof[i]->m_pos.y)
			{
				pPlayerX->m_pos.x = pFRoof[i]->m_pos.x - 126;
			}

			//右
			else if (pPlayerX->m_pos.x - 5 < pFRoof[i]->m_pos.x + 120 &&
				pPlayerX->m_posOld.x > pFRoof[i]->m_pos.x + 120 &&
				pPlayerX->m_pos.z + 5 > pFRoof[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pFRoof[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y < pFRoof[i]->m_pos.y + 5 &&
				pPlayerX->m_pos.y >= pFRoof[i]->m_pos.y)
			{
				pPlayerX->m_pos.x = pFRoof[i]->m_pos.x + 126;
			}

			if (pFRoof[i]->OnCol == true &&
				pPlayerX->m_pos.x - 5 > pFRoof[i]->m_pos.x + 120)
			{
				pFRoof[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}

			else if (pFRoof[i]->OnCol == true &&
				pPlayerX->m_pos.x + 5 < pFRoof[i]->m_pos.x - 120)
			{
				pFRoof[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}
		}

		//壁の当たり判定
		if (pFWall[i] != nullptr && pFWall[i]->IsUse != false)
		{
			//左の当たり判定
			if (pPlayerX->m_pos.x + 5 > pFWall[i]->m_pos.x - 10 &&
				pPlayerX->m_posOld.x < pFWall[i]->m_pos.x - 10 &&
				pPlayerX->m_pos.y <= pFWall[i]->m_pos.y + 100 &&
				pPlayerX->m_pos.y >= pFWall[i]->m_pos.y &&
				pPlayerX->m_pos.z + 5 > pFWall[i]->m_pos.z - 90 &&
				pPlayerX->m_pos.z - 5 < pFWall[i]->m_pos.z + 90)
			{
				pPlayerX->m_pos.x = pFWall[i]->m_pos.x - 15;
			}

			//右の当たり判定
			else if (pPlayerX->m_pos.x - 5 < pFWall[i]->m_pos.x + 10 &&
				pPlayerX->m_posOld.x > pFWall[i]->m_pos.x + 10 &&
				pPlayerX->m_pos.y <= pFWall[i]->m_pos.y + 100 &&
				pPlayerX->m_pos.y >= pFWall[i]->m_pos.y &&
				pPlayerX->m_pos.z + 5 > pFWall[i]->m_pos.z - 90 &&
				pPlayerX->m_pos.z - 5 < pFWall[i]->m_pos.z + 90)
			{
				pPlayerX->m_pos.x = pFWall[i]->m_pos.x + 15;
			}

			else if (pPlayerX->m_pos.x + 5 > pFWall[i]->m_pos.x - 10 &&
				pPlayerX->m_pos.x - 5 < pFWall[i]->m_pos.x + 10 &&
				pPlayerX->m_pos.y <= pFWall[i]->m_pos.y + 115 &&
				pPlayerX->m_pos.y > pFWall[i]->m_pos.y &&
				pPlayerX->m_pos.z + 5 > pFWall[i]->m_pos.z - 90 &&
				pPlayerX->m_pos.z - 5 < pFWall[i]->m_pos.z + 90)
			{
				pPlayerX->m_Land = true;
				pPlayerX->m_pos.y = pFWall[i]->m_pos.y + 115;
				pFWall[i]->OnCol = true;
			}

			if (pFWall[i]->OnCol == true &&
				pPlayerX->m_pos.x - 5 > pFWall[i]->m_pos.x + 10)
			{
				pFWall[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}

			else if (pFWall[i]->OnCol == true &&
				pPlayerX->m_pos.x + 5 < pFWall[i]->m_pos.x - 10)
			{
				pFWall[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}
		}
		//プラットフォーム
		if (pPlat[i] != nullptr && pPlat[i]->IsUse != false)
		{
			//上のみ
			if (pPlayerX->m_pos.x + 5 > pPlat[i]->m_pos.x - 21 &&
				pPlayerX->m_pos.x - 5 < pPlat[i]->m_pos.x + 21 &&
				pPlayerX->m_pos.z + 5 > pPlat[i]->m_pos.z - 5 &&
				pPlayerX->m_pos.z - 5 < pPlat[i]->m_pos.z + 5 &&
				pPlayerX->m_pos.y < pPlat[i]->m_pos.y + 10 &&
				pPlayerX->m_pos.y > pPlat[i]->m_pos.y + 7)
			{
				pPlat[i]->OnCol = true;
				pPlayerX->m_Land = true;
				pPlayerX->m_pos.y = pPlat[i]->m_pos.y + 10;
			}

			if (pPlat[i]->OnCol == true &&
				pPlayerX->m_pos.x - 5 > pPlat[i]->m_pos.x + 21)
			{
				pPlat[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}

			else if (pPlat[i]->OnCol == true &&
				pPlayerX->m_pos.x + 5 < pPlat[i]->m_pos.x - 21)
			{
				pPlat[i]->OnCol = false;
				pPlayerX->m_Land = false;
			}
		}
	}
	//地面
	for (int i = 0; i < GROUND; i++)
	{
		if (pGround[i] != nullptr && pGround[i]->IsUse != false)
		{//地面（大）
			if (pGround[i]->G_type == CGround::GType::BIG)
			{
				//上
				if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 119 &&
					pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 119 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y > pGround[i]->m_pos.y + 25)
				{
					pGround[i]->OnCol = true;
					pPlayerX->m_Land = true;
					pPlayerX->m_pos.y = pGround[i]->m_pos.y + 53;

				}
				//下
				else if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 119 &&
					pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 119 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y > pGround[i]->m_pos.y &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 25)
				{
					pPlayerX->move.y = 0;
					pPlayerX->m_Grav = 0.75;
					pPlayerX->m_pos.y = pGround[i]->m_pos.y - 5;

				}

				//左
				else if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 120 &&
					pPlayerX->m_posOld.x < pGround[i]->m_pos.x - 120 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y >= pGround[i]->m_pos.y)
				{
					pPlayerX->m_pos.x = pGround[i]->m_pos.x - 126;
				}

				//右
				else if (pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 120 &&
					pPlayerX->m_posOld.x > pGround[i]->m_pos.x + 120 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y >= pGround[i]->m_pos.y)
				{
					pPlayerX->m_pos.x = pGround[i]->m_pos.x + 126;
				}

				if (pGround[i]->OnCol == true &&
					pPlayerX->m_pos.x - 5 > pGround[i]->m_pos.x + 120)
				{
					pGround[i]->OnCol = false;
					pPlayerX->m_Land = false;
				}

				else if (pGround[i]->OnCol == true &&
					pPlayerX->m_pos.x + 5 < pGround[i]->m_pos.x - 120)
				{
					pGround[i]->OnCol = false;
					pPlayerX->m_Land = false;
				}
			}

			else if (pGround[i]->G_type == CGround::GType::MIDDLE)
			{//地面（中）
				//上
				if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 80 &&
					pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 80 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y > pGround[i]->m_pos.y + 25)
				{
					pGround[i]->OnCol = true;
					pPlayerX->m_Land = true;
					pPlayerX->m_pos.y = pGround[i]->m_pos.y + 53;

				}
				//下
				else if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 80 &&
					pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 80 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y > pGround[i]->m_pos.y &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 25)
				{
					pPlayerX->move.y = 0;
					pPlayerX->m_Grav = 0.75;
					pPlayerX->m_pos.y = pGround[i]->m_pos.y - 5;

				}

				//左
				else if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 85 &&
					pPlayerX->m_posOld.x < pGround[i]->m_pos.x - 85 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y >= pGround[i]->m_pos.y)
				{
					pPlayerX->m_pos.x = pGround[i]->m_pos.x - 90;
				}

				//右
				else if (pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 85 &&
					pPlayerX->m_posOld.x > pGround[i]->m_pos.x + 85 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y >= pGround[i]->m_pos.y)
				{
					pPlayerX->m_pos.x = pGround[i]->m_pos.x + 90;
				}

				if (pGround[i]->OnCol == true &&
					pPlayerX->m_pos.x - 5 > pGround[i]->m_pos.x + 85)
				{
					pGround[i]->OnCol = false;
					pPlayerX->m_Land = false;
				}

				else if (pGround[i]->OnCol == true &&
					pPlayerX->m_pos.x + 5 < pGround[i]->m_pos.x - 85)
				{
					pGround[i]->OnCol = false;
					pPlayerX->m_Land = false;
				}
			}

			else if (pGround[i]->G_type == CGround::GType::SMALL)
			{//地面（小）
			//上
				if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 45 &&
					pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 45 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y > pGround[i]->m_pos.y + 25)
				{
					pGround[i]->OnCol = true;
					pPlayerX->m_Land = true;
					pPlayerX->m_pos.y = pGround[i]->m_pos.y + 53;

				}
				//下
				else if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 45 &&
					pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 45 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y > pGround[i]->m_pos.y &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 25)
				{
					pPlayerX->move.y = 0;
					pPlayerX->m_Grav = 0.75;
					pPlayerX->m_pos.y = pGround[i]->m_pos.y - 5;

				}

				//左
				else if (pPlayerX->m_pos.x + 5 > pGround[i]->m_pos.x - 50 &&
					pPlayerX->m_posOld.x < pGround[i]->m_pos.x - 50 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y >= pGround[i]->m_pos.y)
				{
					pPlayerX->m_pos.x = pGround[i]->m_pos.x - 55;
				}

				//右
				else if (pPlayerX->m_pos.x - 5 < pGround[i]->m_pos.x + 50 &&
					pPlayerX->m_posOld.x > pGround[i]->m_pos.x + 50 &&
					pPlayerX->m_pos.z + 5 > pGround[i]->m_pos.z - 5 &&
					pPlayerX->m_pos.z - 5 < pGround[i]->m_pos.z + 5 &&
					pPlayerX->m_pos.y < pGround[i]->m_pos.y + 53 &&
					pPlayerX->m_pos.y >= pGround[i]->m_pos.y)
				{
					pPlayerX->m_pos.x = pGround[i]->m_pos.x + 55;
				}

				if (pGround[i]->OnCol == true &&
					pPlayerX->m_pos.x - 5 > pGround[i]->m_pos.x + 50)
				{
					pGround[i]->OnCol = false;
					pPlayerX->m_Land = false;
				}

				else if (pGround[i]->OnCol == true &&
					pPlayerX->m_pos.x + 5 < pGround[i]->m_pos.x - 50)
				{
					pGround[i]->OnCol = false;
					pPlayerX->m_Land = false;
				}
			}
		}
	}
	//敵
	for (int i = 0; i < ENM_MAX; i++)
	{
		if (pEnemy[i] != nullptr && pEnemy[i]->m_bDeath == false && pEnemy[i]->IsUse != false)
		{
			if (pPlayerX->m_pos.x - 5 <= pEnemy[i]->m_pos.x + 10 &&
				pPlayerX->m_pos.x + 5 >= pEnemy[i]->m_pos.x - 10 &&
				pPlayerX->m_pos.y + 10 <= pEnemy[i]->m_pos.y + 20 &&
				pPlayerX->m_pos.y >= pEnemy[i]->m_pos.y)
			{
				pPlayerX->m_pos.x -= 30;
				CN_Stock::SetStock(1, true);
			}
		}
	}

	//たま
	for (int i = 0; i < MBULLET; i++)
	{
		if (pBullet[i] != nullptr && pBullet[i]->IsUse != false)
		{
			if (pBullet[i]->IsPlayer == true)	//敵用当たり判定
			{
				for (int enemy = 0; enemy < ENM_MAX; enemy++)
				{

					if (pEnemy[enemy] != nullptr && pEnemy[enemy]->m_bDeath == false && pBullet[i]->IsUse == true)
					{
						if (pBullet[i]->m_pos.x - 5 <= pEnemy[enemy]->m_pos.x + 5 &&
							pBullet[i]->m_pos.x + 5 >= pEnemy[enemy]->m_pos.x - 5 &&
							pBullet[i]->m_pos.y <= pEnemy[enemy]->m_pos.y + 20 &&
							pBullet[i]->m_pos.y >= pEnemy[enemy]->m_pos.y &&
							pBullet[i]->m_pos.z >= pEnemy[enemy]->m_pos.z - 5 &&
							pBullet[i]->m_pos.z <= pEnemy[enemy]->m_pos.z + 5 )
						{
							pBullet[i]->IsUse = false;
							pEnemy[enemy]->E_HP--;
						}
					}

				}
			}

			else if (pBullet[i]->IsPlayer == false && pBullet[i]->IsUse == true)//プレイヤー用当たり判定
			{
				if (pPlayerX->m_pos.x - 5 <= pBullet[i]->m_pos.x + 5 &&
					pPlayerX->m_pos.x + 5 >= pBullet[i]->m_pos.x - 5 &&
					pPlayerX->m_pos.y <= pBullet[i]->m_pos.y + 5 &&
					pPlayerX->m_pos.y >= pBullet[i]->m_pos.y - 5)
				{
					//pPlayerX->m_pos = pPlayerX->StartPos;
					CN_Stock::SetStock(1, true);
					pBullet[i]->IsUse = false;
				}
			}

			for (int Floor = 0; Floor < FROOF; Floor++)
			{
				if (pFRoof[Floor] != nullptr && pFRoof[Floor]->IsUse == true)
				{
					if (pBullet[i]->m_pos.x + 5 >= pFRoof[Floor]->m_pos.x - 5 &&
						pBullet[i]->m_pos.x - 5 <= pFRoof[Floor]->m_pos.x + 5 &&
						pBullet[i]->m_pos.y <= pFRoof[Floor]->m_pos.y + 5 &&
						pBullet[i]->m_pos.y >= pFRoof[Floor]->m_pos.y)
					{
						pBullet[i]->IsUse = false;
					}
				}

				else if (pFWall[Floor] != nullptr && pFWall[Floor]->IsUse == true)
				{
					if (pBullet[i]->m_pos.x + 5 >= pFWall[Floor]->m_pos.x - 5 &&
						pBullet[i]->m_pos.x - 5 <= pFWall[Floor]->m_pos.x + 5 &&
						pBullet[i]->m_pos.y <= pFWall[Floor]->m_pos.y + 100 &&
						pBullet[i]->m_pos.y >= pFWall[Floor]->m_pos.y)
					{
						pBullet[i]->IsUse = false;
					}
				}
			}

			for (int Block = 0; Block < MOBJ; Block++)
			{
				if (pBlock[Block] != nullptr && pBlock[Block]->IsUse == true)
				{
					if (pBullet[i]->m_pos.x + 5 >= pBlock[Block]->m_pos.x - 5 &&
						pBullet[i]->m_pos.x - 5 <= pBlock[Block]->m_pos.x + 5 &&
						pBullet[i]->m_pos.y <= pBlock[Block]->m_pos.y + 18 &&
						pBullet[i]->m_pos.y >= pBlock[Block]->m_pos.y)
					{
						pBullet[i]->IsUse = false;
					}
				}
			}
		}
	}
	//スタートゴール
	for (int i = 0; i < MSG; i++)
	{
		if (pSG[i] != nullptr && pSG[i]->IsUse != false)
		{
			if (pSG[i]->IsStart == true)
			{//スタートの当たり判定
				if (pPlayerX->m_pos.x - 5 <= pSG[i]->m_pos.x + 10 &&
					pPlayerX->m_pos.x + 5 >= pSG[i]->m_pos.x - 10 &&
					pPlayerX->m_pos.y + 10 <= pSG[i]->m_pos.y + 30 &&
					pPlayerX->m_pos.y >= pSG[i]->m_pos.y)
				{
					pPlayerX->StartPos.x = pSG[i]->m_pos.x;
					pPlayerX->StartPos.y = pSG[i]->m_pos.y;
				}
			}

			else
			{//ゴールの当たり判定
				if (pPlayerX->m_pos.x - 5 <= pSG[i]->m_pos.x + 10 &&
					pPlayerX->m_pos.x + 5 >= pSG[i]->m_pos.x - 10 &&
					pPlayerX->m_pos.y + 10 <= pSG[i]->m_pos.y + 30 &&
					pPlayerX->m_pos.y >= pSG[i]->m_pos.y)
				{
					pPlayerX->m_pos.x = pPlayerX->StartPos.x;
					pPlayerX->m_pos.y = pPlayerX->StartPos.y;
				}
			}
		}
	}
	//アイテム
	for (int i = 0; i < INUM_MAX; i++)
	{
		if (pItem[i] != nullptr)
		{
			if (pPlayerX->m_pos.x - 5 <= pItem[i]->m_pos.x + 10 &&
				pPlayerX->m_pos.x + 5 >= pItem[i]->m_pos.x - 10 &&
				pPlayerX->m_pos.y + 10 <= pItem[i]->m_pos.y + 20 &&
				pPlayerX->m_pos.y >= pItem[i]->m_pos.y)
			{
				pItem[i]->IsUse = false;

				if (pItem[i]->Item_type == CItem::ITEM::I_SCORE)
				{
					CN_Score::SetScore(1000);
				}

				else if (pItem[i]->Item_type == CItem::ITEM::I_EXTEND)
				{
					CN_Stock::SetStock(1, false);
				}


			}

		}
	}
}


