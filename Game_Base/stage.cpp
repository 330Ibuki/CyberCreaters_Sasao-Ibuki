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

	int AllNum = 0, TypeNum = 0;
	float PosX = 0, PosY = 0, PosZ = 0;
	if (Lv == 1)
	{
		ifstream SaveData("data\\TOOL\\STAGE\\Stage_XX.txt");
		if (SaveData.is_open())
		{
			getline(SaveData, line);
			AllNum = stoi(line);

			for (int i = 0; i < AllNum; i++)
			{
				getline(SaveData, line);
				TypeNum = stoi(line);

				getline(SaveData, line);
				PosX = stof(line);

				getline(SaveData, line);
				PosY = stof(line);

				getline(SaveData, line);
				PosZ = stof(line);

				switch (TypeNum)
				{
				case 1:
					CGround::Create(D3DXVECTOR3(PosX,PosY,PosZ),CGround::GType::SMALL);	//床（小）
					break;

				case 2:
					CGround::Create(D3DXVECTOR3(PosX, PosY, PosZ), CGround::GType::MIDDLE);	//床（中）
					break;

				case 3:
					CGround::Create(D3DXVECTOR3(PosX, PosY, PosZ), CGround::GType::BIG);	//床（大）
					break;

				case 4:
					CFloorRoof::Create(D3DXVECTOR3(PosX, PosY, PosZ));	//天井
					break;

				case 5:
					CFloorWall::Create(D3DXVECTOR3(PosX, PosY, PosZ));	//壁
					break;

				case 6:
					CBlock::Create(D3DXVECTOR3(PosX, PosY, PosZ));	//ブロック
					break;

				case 7:
					CPlatform::Create(D3DXVECTOR3(PosX, PosY, PosZ),CPlatform::PType::SMALL);	//すりぬけ（小）
					break;

				case 8:
					CPlatform::Create(D3DXVECTOR3(PosX, PosY, PosZ),CPlatform::PType::MIDDLE);	//すりぬけ（中）
					break;

				case 9:
					CItem::Create(D3DXVECTOR3(PosX, PosY, PosZ),CItem::ITEM::I_SCORE);	//スコアアイテム
					break;

				case 10:
					CItem::Create(D3DXVECTOR3(PosX, PosY, PosZ), CItem::ITEM::I_EXTEND);	//残機アイテム
					break;

				case 11:
					CSG::Create(D3DXVECTOR3(PosX, PosY, PosZ), true);	//スタート
					CPlayerX::Create(D3DXVECTOR3(PosX, PosY, PosZ));
					break;

				case 12:
					CSG::Create(D3DXVECTOR3(PosX, PosY, PosZ), false);	//ゴール
					break;

				case 13:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_Normal);	//敵_Normal
					break;

				case 14:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_RapidFire);	//敵_Rapid
					break;

				case 15:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_Speed);	//敵_Sniper
					break;

				case 16:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Up);	//敵_3W_up
					break;

				case 17:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Down);	//敵_3W_Down
					break;

				case 18:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Left);	//敵_3W_Left
					break;

				case 19:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Right);	//敵_3W_Right
					break;
				}
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