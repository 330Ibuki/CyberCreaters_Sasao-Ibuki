/*==========================
//
// stage
//
=========================*/

//インクルード
#include "stage.h"
#include "player.x.h"
#include "enemy.h"
#include "item.h"

//静的メンバ初期化
CStage* CStage::m_Stage = {};

/*=============================
//コンストラクタ・デストラクタ
=============================*/

CStage::CStage()
{
	Lv = NULL;
	Lvcol = NULL;
	Lvrow = NULL;
	ColReset = false;
}

CStage::~CStage()
{

}

/*=============================
//初期化
=============================*/

HRESULT CStage::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (Lv == 1)
	{
		StageData = { "data\\STAGE\\Stage_large.csv" };
		for (const auto& SData : StageData)
		{
			std::ifstream file(SData);

			if (file.is_open())
			{
				while (getline(file, line))
				{
					std::stringstream ss(line);
					while (getline(ss, value, ','))
					{
						if (value == "1")	//床(小）ほかの床と（5 +（ほかの床の半径のセル）)だけ離す　例：小＋中 = (5+8)セル離す
						{
							CGround::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -40.0f - (Lvrow * 10), 0.0f), CGround::GType::SMALL);
						}

						else if (value == "2")	//床(中）ほかの床と（8 +（ほかの床の半径のセル）)だけ離す
						{
							CGround::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -40.0f - (Lvrow * 10), 0.0f), CGround::GType::MIDDLE);
						}

						else if (value == "3")	//床(大）ほかの床と（12 +（ほかの床の半径のセル）)だけ離す
						{
							CGround::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -40.0f - (Lvrow * 10), 0.0f), CGround::GType::BIG);
						}

						else if (value == "4")	//天井　複数配置するなら前後24、5セル間隔をとる
						{
							CFloorRoof::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), 0.0f, 0.0f));
						}

						else if (value == "5")	//壁
						{
							CFloorWall::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f));
						}

						else if (value == "6")	//ブロック
						{
							CBlock::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f));
						}

						else if (value == "7")	//すり抜け床(小)
						{
							CPlatform::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CPlatform::PType::SMALL);
						}

						else if (value == "8")	//すり抜け床(中）
						{
							CPlatform::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CPlatform::PType::MIDDLE);
						}

						//else if (value == "9")	//すり抜け床(大）
						//{
						//	CPlatform::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CPlatform::PType::MIDDLE);
						//}

						else if (value == "10")	//アイテム_スコア
						{
							CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_SCORE);
						}

						//else if (value == "10.1")	//アイテム_速度
						//{
						//	CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_SPD);
						//}

						//else if (value == "10.2")	//アイテム_威力
						//{
						//	CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_POW);
						//}

						else if (value == "10.3")	//アイテム_残機
						{
							CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_EXTEND);
						}

						else if (value == "11")	//スタート
						{
							CSG::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), true);
							CPlayerX::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), 0.0f - (Lvrow * 10), 0.0f));
						}

						else if (value == "12")	//ゴール
						{
							CSG::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), false);
						}

						else if (value == "13")	//敵_通常
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_Normal);
						}

						else if (value == "13.1")	//敵_速射
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_RapidFire);
						}

						else if (value == "13.2")	//敵_高速弾
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_Speed);
						}

						else if (value == "13.3")	//敵_三方向上
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_3Way_Up);
						}

						else if (value == "13.4")	//敵_三方向下
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_3Way_Down);
						}

						else if (value == "13.5")	//敵_三方向左（右方向に発射）
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_3Way_Left);
						}

						else if (value == "13.6")	//敵_三方向右（左方向に発射）
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_3Way_Right);
						}

						Lvcol++;
					}
					Lvcol = 0;
					Lvrow++;
				}
				file.close();
				Lvcol = 0;
				Lvrow = 0;
				Lv++;
			}

		}
	}

	return S_OK;
}

/*=============================
//終了
=============================*/

void CStage::Uninit()
{
	if (m_Stage != nullptr)
	{
		delete m_Stage;
		m_Stage = nullptr;
	}
}

/*=============================
//更新
=============================*/

void CStage::Update()
{

}

/*=============================
//読み込み
=============================*/

CStage* CStage::LoadStage(int StgNum)
{
	if (m_Stage != nullptr)
	{
		m_Stage->Uninit();
		m_Stage = new CStage();
		m_Stage->Lv = StgNum;
		m_Stage->Init();
	}

	else if (m_Stage == nullptr)
	{
		m_Stage = new CStage();
		m_Stage->Lv = StgNum;
		m_Stage->Init();
	}

	return m_Stage;
}