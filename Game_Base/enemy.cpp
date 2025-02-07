/*=====================================
//
// enemy
//
=====================================*/

//�C���N���[�h
#include "enemy.h"
#include "player.x.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "bullet.h"

//�ÓI�����o������
CEnemy* CEnemy::m_apEnemy[ENM_MAX] = {};
int CEnemy::EnemyNum = NULL;

/*================================
//�R���X�g���N�^�E�f�X�g���N�^
=================================*/
CEnemy::CEnemy() : CObjectX(m_Priority = 1)
{
	move = {};
	E_Score = NULL;
	EType = NULL;
	RF_OverHeat = false;
	RF_Count = NULL;
	E_HP = NULL;
	EnemyNum++;
}

CEnemy::~CEnemy()
{
	EnemyNum--;
}

/*================================
//������
=================================*/
HRESULT CEnemy::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);
	//move = D3DXVECTOR3(0, 0, 0.1);

	//�}�e���A���f�[�^�̃|�C���^�擾
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (DWORD i = 0; i < m_dwNumMat; i++)
	{
		if (mat[i].pTextureFilename != NULL)
		{
			char* TexName = mat[i].pTextureFilename;
			D3DXCreateTextureFromFileA(pDevice,
				TexName,
				&m_ptex);
		}

		else
		{
			m_ptex = nullptr;
		}
	}

	return S_OK;
}

/*================================
//�j��
=================================*/
void CEnemy::Uninit()
{
	CObjectX::Uninit();

}

/*================================
//�X�V
=================================*/
void CEnemy::Update()
{
	if (m_bDeath == false)
	{
		m_Flame_Count++;



			CPlayerX* pPlayer = pPlayer->GetPlayer();
			if (EType == E_Normal)
			{
				if (m_Flame_Count % 60 == 0)
				{
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 5, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(0, 0, 0), false, true);
				}
			}
			
			else if (EType == E_RapidFire)
			{
				if (m_Flame_Count % 20 == 0 && RF_OverHeat == false)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 5, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(-5, -5, 0), false, true);
					RF_Count++;
				}

				else if (m_Flame_Count % 90 == 0 && RF_OverHeat == true)
				{
					RF_OverHeat = false;
				}

				if (RF_Count >= 15)
				{
					RF_Count = 0;
					RF_OverHeat = true;
				}
			}
		
			else if (EType == E_Speed)
			{
				if (m_Flame_Count % 120 == 0 )
				{
						CBullet::Create(D3DXVECTOR3(m_pos.x - 15, m_pos.y + 4.1, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(-3, 0, 0), false, false);
				}
			}

			else 
			{
				if (m_Flame_Count % 60 == 0)
				{
					if (EType == E_3Way_Down)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x - 6, m_pos.y - 8, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(-1.5, -1.5, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 8, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(0, -2.5, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x + 9, m_pos.y - 8, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(1.5, -1.5, 0), false, false);
					}

					else if (EType == E_3Way_Up)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x - 6, m_pos.y + 8, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(-1.5, 1.5, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 8, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(0, 2.5, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x + 9, m_pos.y + 8, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(1.5, 1.5, 0), false, false);
					}

					else if (EType == E_3Way_Left)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x + 8, m_pos.y + 6, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(1.5, 0.5, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x + 8, m_pos.y, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(2.5, 0, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x + 8, m_pos.y - 9, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(1.5, -0.5, 0), false, false);
					}

					else if (EType == E_3Way_Right)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x + 8, m_pos.y + 6, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(-1.5, 0.5, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x + 8, m_pos.y, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(-2.5, 0, 0), false, false);
						CBullet::Create(D3DXVECTOR3(m_pos.x + 8, m_pos.y - 9, m_pos.z), pPlayer->m_pos, D3DXVECTOR3(-1.5, -0.5, 0), false, false);
					}
				}
			}
	}

	else
	{
		IsUse = false;
		CN_Score::SetScore(E_Score);
		//Uninit();
	}
	
}

/*================================
//�`��
=================================*/
void CEnemy::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}

/*================================
//�擾
=================================*/
CEnemy* CEnemy::GetEnmey(int Num)
{
	return m_apEnemy[Num];
}

/*================================
//�擾(����)
=================================*/
int CEnemy::GetE_Num()
{
	return EnemyNum;
}

/*================================
//����
=================================*/
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, E_TYPE E_Type)
{
	int E_Num = CEnemy::GetE_Num();
	if (m_apEnemy[E_Num] != nullptr)
	{
		m_apEnemy[E_Num] = nullptr;
	}

	if (m_apEnemy[E_Num] == nullptr)
	{	
		
		switch (E_Type)
		{
		case E_Normal:
			m_apEnemy[E_Num] = new CE_Normal();
			m_apEnemy[E_Num]->m_pos.x = pos.x;
			m_apEnemy[E_Num]->m_pos.y = pos.y;
			m_apEnemy[E_Num]->m_pos.z = pos.z - 10;
			m_apEnemy[E_Num]->move.z = 2.5;
			m_apEnemy[E_Num]->EType = E_Type;
			m_apEnemy[E_Num]->IsUse = true;
			m_apEnemy[E_Num]->OBJ_ID = E_Num;
			m_apEnemy[E_Num]->Init();
			break;

		case E_RapidFire:
			m_apEnemy[E_Num] = new CE_Rapid();
			m_apEnemy[E_Num]->m_pos.x = pos.x;
			m_apEnemy[E_Num]->m_pos.y = pos.y;
			m_apEnemy[E_Num]->m_pos.z = pos.z - 10;
			m_apEnemy[E_Num]->EType = E_Type;
			m_apEnemy[E_Num]->IsUse = true;
			m_apEnemy[E_Num]->OBJ_ID = E_Num;
			m_apEnemy[E_Num]->Init();
			break;

		case E_Speed:
			m_apEnemy[E_Num] = new CE_Speed();
			m_apEnemy[E_Num]->m_pos.x = pos.x;
			m_apEnemy[E_Num]->m_pos.y = pos.y;
			m_apEnemy[E_Num]->m_pos.z = pos.z - 10;
			m_apEnemy[E_Num]->EType = E_Type;
			m_apEnemy[E_Num]->IsUse = true;
			m_apEnemy[E_Num]->OBJ_ID = E_Num;
			m_apEnemy[E_Num]->Init();
			break;

		case E_3Way_Up:
			m_apEnemy[E_Num] = new CE_3Way_Up();
			m_apEnemy[E_Num]->m_pos.x = pos.x;
			m_apEnemy[E_Num]->m_pos.y = pos.y;
			m_apEnemy[E_Num]->m_pos.z = pos.z - 10;
			m_apEnemy[E_Num]->EType = E_Type;
			m_apEnemy[E_Num]->IsUse = true;
			m_apEnemy[E_Num]->OBJ_ID = E_Num;
			m_apEnemy[E_Num]->Init();
			break;

		case E_3Way_Down:
			m_apEnemy[E_Num] = new CE_3Way_Down();
			m_apEnemy[E_Num]->m_pos.x = pos.x;
			m_apEnemy[E_Num]->m_pos.y = pos.y;
			m_apEnemy[E_Num]->m_pos.z = pos.z - 10;
			m_apEnemy[E_Num]->EType = E_Type;
			m_apEnemy[E_Num]->IsUse = true;
			m_apEnemy[E_Num]->OBJ_ID = E_Num;
			m_apEnemy[E_Num]->Init();
			break;

		case E_3Way_Left:
			m_apEnemy[E_Num] = new CE_3Way_Left();
			m_apEnemy[E_Num]->m_pos.x = pos.x;
			m_apEnemy[E_Num]->m_pos.y = pos.y;
			m_apEnemy[E_Num]->m_pos.z = pos.z - 10;
			m_apEnemy[E_Num]->EType = E_Type;
			m_apEnemy[E_Num]->IsUse = true;
			m_apEnemy[E_Num]->OBJ_ID = E_Num;
			m_apEnemy[E_Num]->Init();
			break;

		case E_3Way_Right:
			m_apEnemy[E_Num] = new CE_3Way_Right();
			m_apEnemy[E_Num]->m_pos.x = pos.x;
			m_apEnemy[E_Num]->m_pos.y = pos.y;
			m_apEnemy[E_Num]->m_pos.z = pos.z - 10;
			m_apEnemy[E_Num]->EType = E_Type;
			m_apEnemy[E_Num]->IsUse = true;
			m_apEnemy[E_Num]->OBJ_ID = E_Num;
			m_apEnemy[E_Num]->Init();
			break;
		}

	}
	return m_apEnemy[E_Num];
}

/*======================
//�G�i�ʏ�j
======================*/
/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/
CE_Normal::CE_Normal() : CEnemy()
{
	M_Switch = true;
	flame_move = NULL;
	flame_switch = NULL;
}
CE_Normal::~CE_Normal()
{

}

/*=============================
//������
=============================*/
HRESULT CE_Normal::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(
		"data\\MODEL\\EV2_Normal.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	E_HP = 3;
	CEnemy::Init();


	return S_OK;
}

/*=============================
//�j��
=============================*/
void CE_Normal::Uninit()
{
	CEnemy::Uninit(); 
	Release();
}

/*=============================
//�X�V
=============================*/
void CE_Normal::Update()
{


	if (m_bDeath == true)
	{
		Uninit();
	}

	if (E_HP > 0)
	{
		flame_switch++;

		if (flame_switch % 60 == 0)
		{
			M_Switch = !M_Switch;
		}

		if (M_Switch == true)
		{
			flame_move++;
			if (flame_move % 20 == 0)
			{
				move.z = move.z * (-1);
			}
			m_pos.z = m_pos.z + move.z;
		}
		
		CEnemy::Update();
	}

	if (E_HP <= 0)
	{
		CN_Score::SetScore(E_Score);
		m_bDeath = true;
	}
}

/*=============================
//�`��
=============================*/
void CE_Normal::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}

/*======================
//�G�i�A�ˁj
======================*/
/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/
CE_Rapid::CE_Rapid() : CEnemy()
{

}
CE_Rapid::~CE_Rapid()
{

}

/*=============================
//������
=============================*/
HRESULT CE_Rapid::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(
		"data\\MODEL\\E_Rapid.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	E_HP = 8;
	CEnemy::Init();

	return S_OK;
}

/*=============================
//�j��
=============================*/
void CE_Rapid::Uninit()
{
	CEnemy::Uninit();
	Release();
}

/*=============================
//�X�V
=============================*/
void CE_Rapid::Update()
{
	if (m_bDeath == true)
	{
		Uninit();
	}

	if (E_HP > 0)
	{
		CEnemy::Update();
	}

	if (E_HP <= 0)
	{
		CN_Score::SetScore(E_Score);
		m_bDeath = true;
	}
}

/*=============================
//�`��
=============================*/
void CE_Rapid::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}


/*======================
//�G�i�����j
======================*/
/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/
CE_Speed::CE_Speed() : CEnemy()
{

}
CE_Speed::~CE_Speed()
{

}

/*=============================
//������
=============================*/
HRESULT CE_Speed::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(
		"data\\MODEL\\E_Speed.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	E_HP = 5;
	CEnemy::Init();

	return S_OK;
}

/*=============================
//�j��
=============================*/
void CE_Speed::Uninit()
{
	CEnemy::Uninit();
	Release();
}

/*=============================
//�X�V
=============================*/
void CE_Speed::Update()
{
	if (m_bDeath == true)
	{
		Uninit();
	}

	if (E_HP > 0)
	{
		CEnemy::Update();
	}

	if (E_HP <= 0)
	{
		CN_Score::SetScore(E_Score);
		m_bDeath = true;
	}
}

/*=============================
//�`��
=============================*/
void CE_Speed::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}

/*======================
//�G�i3����[��]�j
======================*/
/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/
CE_3Way_Up::CE_3Way_Up() : CEnemy()
{

}
CE_3Way_Up::~CE_3Way_Up()
{

}

/*=============================
//������
=============================*/
HRESULT CE_3Way_Up::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(
		"data\\MODEL\\E_3WayUp.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	E_HP = 3;
	CEnemy::Init();

	return S_OK;
}

/*=============================
//�j��
=============================*/
void CE_3Way_Up::Uninit()
{
	CEnemy::Uninit();
	Release();
}

/*=============================
//�X�V
=============================*/
void CE_3Way_Up::Update()
{
	if (m_bDeath == true)
	{
		Uninit();
	}

	if (E_HP > 0)
	{
		CEnemy::Update();
	}

	if (E_HP <= 0)
	{
		CN_Score::SetScore(E_Score);
		m_bDeath = true;
	}
}

/*=============================
//�`��
=============================*/
void CE_3Way_Up::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}

/*======================
//�G�i3����[��]�j
======================*/
/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/
CE_3Way_Down::CE_3Way_Down() : CEnemy()
{

}
CE_3Way_Down::~CE_3Way_Down()
{

}

/*=============================
//������
=============================*/
HRESULT CE_3Way_Down::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(
		"data\\MODEL\\E_3WayDown.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	E_HP = 3;
	CEnemy::Init();

	return S_OK;
}

/*=============================
//�j��
=============================*/
void CE_3Way_Down::Uninit()
{
	CEnemy::Uninit();
	Release();
}

/*=============================
//�X�V
=============================*/
void CE_3Way_Down::Update()
{
	if (m_bDeath == true)
	{
		Uninit();
	}

	if (E_HP > 0)
	{
		CEnemy::Update();
	}

	if (E_HP <= 0)
	{
		CN_Score::SetScore(E_Score);
		m_bDeath = true;
	}
}

/*=============================
//�`��
=============================*/
void CE_3Way_Down::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}

/*======================
//�G�i3����[��]�j
======================*/
/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/
CE_3Way_Left::CE_3Way_Left() : CEnemy()
{

}
CE_3Way_Left::~CE_3Way_Left()
{

}

/*=============================
//������
=============================*/
HRESULT CE_3Way_Left::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(
		"data\\MODEL\\E_3WayLeft.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	E_HP = 3;
	CEnemy::Init();

	return S_OK;
}

/*=============================
//�j��
=============================*/
void CE_3Way_Left::Uninit()
{
	CEnemy::Uninit();
	Release();
}

/*=============================
//�X�V
=============================*/
void CE_3Way_Left::Update()
{
	if (m_bDeath == true)
	{
		Uninit();
	}

	if (E_HP > 0)
	{
		CEnemy::Update();
	}

	if (E_HP <= 0)
	{
		CN_Score::SetScore(E_Score);
		m_bDeath = true;
	}
}

/*=============================
//�`��
=============================*/
void CE_3Way_Left::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}

/*======================
//�G�i3����[�E]�j
======================*/
/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/
CE_3Way_Right::CE_3Way_Right() : CEnemy()
{

}
CE_3Way_Right::~CE_3Way_Right()
{

}

/*=============================
//������
=============================*/
HRESULT CE_3Way_Right::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(
		"data\\MODEL\\E_3WayRight.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	E_HP = 3;
	CEnemy::Init();

	return S_OK;
}

/*=============================
//�j��
=============================*/
void CE_3Way_Right::Uninit()
{
	CEnemy::Uninit(); 
	Release();
}

/*=============================
//�X�V
=============================*/
void CE_3Way_Right::Update()
{
	if (m_bDeath == true)
	{
		Uninit();
	}

	if (E_HP > 0)
	{
		CEnemy::Update();
	}

	if (E_HP <= 0)
	{
		CN_Score::SetScore(E_Score);
		m_bDeath = true;
	}
}

/*=============================
//�`��
=============================*/
void CE_3Way_Right::Draw()
{
	if (m_bDeath == false)
	{
		CObjectX::Draw();
	}
}
