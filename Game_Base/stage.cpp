/*==========================
//
// stage
//
=========================*/

//�C���N���[�h
#include "stage.h"
#include "player.x.h"
#include "enemy.h"
#include "item.h"

//�ÓI�����o������
CStage* CStage::m_Stage = {};

/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
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
//������
=============================*/

HRESULT CStage::Init()
{
	//�f�o�C�X�擾
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
					CGround::Create(D3DXVECTOR3(PosX,PosY,PosZ),CGround::GType::SMALL);	//���i���j
					break;

				case 2:
					CGround::Create(D3DXVECTOR3(PosX, PosY, PosZ), CGround::GType::MIDDLE);	//���i���j
					break;

				case 3:
					CGround::Create(D3DXVECTOR3(PosX, PosY, PosZ), CGround::GType::BIG);	//���i��j
					break;

				case 4:
					CFloorRoof::Create(D3DXVECTOR3(PosX, PosY, PosZ));	//�V��
					break;

				case 5:
					CFloorWall::Create(D3DXVECTOR3(PosX, PosY, PosZ));	//��
					break;

				case 6:
					CBlock::Create(D3DXVECTOR3(PosX, PosY, PosZ));	//�u���b�N
					break;

				case 7:
					CPlatform::Create(D3DXVECTOR3(PosX, PosY, PosZ),CPlatform::PType::SMALL);	//����ʂ��i���j
					break;

				case 8:
					CPlatform::Create(D3DXVECTOR3(PosX, PosY, PosZ),CPlatform::PType::MIDDLE);	//����ʂ��i���j
					break;

				case 9:
					CItem::Create(D3DXVECTOR3(PosX, PosY, PosZ),CItem::ITEM::I_SCORE);	//�X�R�A�A�C�e��
					break;

				case 10:
					CItem::Create(D3DXVECTOR3(PosX, PosY, PosZ), CItem::ITEM::I_EXTEND);	//�c�@�A�C�e��
					break;

				case 11:
					CSG::Create(D3DXVECTOR3(PosX, PosY, PosZ), true);	//�X�^�[�g
					CPlayerX::Create(D3DXVECTOR3(PosX, PosY, PosZ));
					break;

				case 12:
					CSG::Create(D3DXVECTOR3(PosX, PosY, PosZ), false);	//�S�[��
					break;

				case 13:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_Normal);	//�G_Normal
					break;

				case 14:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_RapidFire);	//�G_Rapid
					break;

				case 15:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_Speed);	//�G_Sniper
					break;

				case 16:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Up);	//�G_3W_up
					break;

				case 17:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Down);	//�G_3W_Down
					break;

				case 18:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Left);	//�G_3W_Left
					break;

				case 19:
					CEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CEnemy::E_TYPE::E_3Way_Right);	//�G_3W_Right
					break;
				}
			}

		}
	}

	return S_OK;
}

/*=============================
//�I��
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
//�X�V
=============================*/

void CStage::Update()
{

}

/*=============================
//�ǂݍ���
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