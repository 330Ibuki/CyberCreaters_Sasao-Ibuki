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
						if (value == "1")	//��(���j�ق��̏��Ɓi5 +�i�ق��̏��̔��a�̃Z���j)���������@��F���{�� = (5+8)�Z������
						{
							CGround::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -40.0f - (Lvrow * 10), 0.0f), CGround::GType::SMALL);
						}

						else if (value == "2")	//��(���j�ق��̏��Ɓi8 +�i�ق��̏��̔��a�̃Z���j)��������
						{
							CGround::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -40.0f - (Lvrow * 10), 0.0f), CGround::GType::MIDDLE);
						}

						else if (value == "3")	//��(��j�ق��̏��Ɓi12 +�i�ق��̏��̔��a�̃Z���j)��������
						{
							CGround::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -40.0f - (Lvrow * 10), 0.0f), CGround::GType::BIG);
						}

						else if (value == "4")	//�V��@�����z�u����Ȃ�O��24�A5�Z���Ԋu���Ƃ�
						{
							CFloorRoof::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), 0.0f, 0.0f));
						}

						else if (value == "5")	//��
						{
							CFloorWall::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f));
						}

						else if (value == "6")	//�u���b�N
						{
							CBlock::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f));
						}

						else if (value == "7")	//���蔲����(��)
						{
							CPlatform::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CPlatform::PType::SMALL);
						}

						else if (value == "8")	//���蔲����(���j
						{
							CPlatform::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CPlatform::PType::MIDDLE);
						}

						//else if (value == "9")	//���蔲����(��j
						//{
						//	CPlatform::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CPlatform::PType::MIDDLE);
						//}

						else if (value == "10")	//�A�C�e��_�X�R�A
						{
							CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_SCORE);
						}

						//else if (value == "10.1")	//�A�C�e��_���x
						//{
						//	CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_SPD);
						//}

						//else if (value == "10.2")	//�A�C�e��_�З�
						//{
						//	CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_POW);
						//}

						else if (value == "10.3")	//�A�C�e��_�c�@
						{
							CItem::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 0.0f), CItem::ITEM::I_EXTEND);
						}

						else if (value == "11")	//�X�^�[�g
						{
							CSG::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), true);
							CPlayerX::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), 0.0f - (Lvrow * 10), 0.0f));
						}

						else if (value == "12")	//�S�[��
						{
							CSG::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), false);
						}

						else if (value == "13")	//�G_�ʏ�
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_Normal);
						}

						else if (value == "13.1")	//�G_����
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_RapidFire);
						}

						else if (value == "13.2")	//�G_�����e
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_Speed);
						}

						else if (value == "13.3")	//�G_�O������
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_3Way_Up);
						}

						else if (value == "13.4")	//�G_�O������
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_3Way_Down);
						}

						else if (value == "13.5")	//�G_�O�������i�E�����ɔ��ˁj
						{
							CEnemy::Create(D3DXVECTOR3(0.0f + (Lvcol * 10), -0.0f - (Lvrow * 10), 20.0f), CEnemy::E_TYPE::E_3Way_Left);
						}

						else if (value == "13.6")	//�G_�O�����E�i�������ɔ��ˁj
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