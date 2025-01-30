///*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
//==============================================*/

//�C���N���[�h
#include "player.x.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "collision.h"
#include "bullet.h"
#include "scope.h"
#include "tool.h"
#include "number.h"

//�ÓI�����o������
CPlayerX* CPlayerX::m_apPlayerX = nullptr;
CModelParts* CPlayerX::m_apModel[PARTS] = {};

/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/

CPlayerX::CPlayerX() : CObject(m_Priority = 1)
{
	StartPos = {};
	m_rot = {};
	m_PJump = 2;
	m_Grav = 0.0f;
	m_Jump = true;
	m_Land = true;
	m_life = 0;
	SwitchStat = false;
	Dodge = true;
	m_WallLand = false;
	m_bDeath = false;
	m_Ammo = 5;
	m_CoolDown = 60;
	//for (int i = 0; i < PARTS; i++)
	//{
	//	m_apModel[i] = new CModelParts();
	//}
}

CPlayerX::~CPlayerX()
{

}

/*=============================
//������
=============================*/

HRESULT CPlayerX::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);
	move = D3DXVECTOR3(1.5f, 0.0f, 0.0f);
	m_life = 10;
	
	m_apModel[0] = CModelParts::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), (char*)"data\\MODEL\\body_00.x",0);
	//m_apModel[1] = CModelParts::Create(D3DXVECTOR3(0, 10, 0), D3DXVECTOR3(0, 0, 0), (char*)"data\\MODEL\\body_01.x",1);
	//m_apModel[1]->SetParent(m_apModel[0]);
	return S_OK;
}

/*=============================
//�I��
=============================*/

void CPlayerX::Uninit()
{
	for (int i = 0; i < PARTS; i++)
	{
		if (m_apModel[i] != nullptr)
		{
			m_apModel[i]->Uninit();
			//delete m_apModel[i];
			m_apModel[i] = nullptr;
		}
	}
}

/*====================l=========
//�X�V
=============================*/

void CPlayerX::Update()
{
	if (m_bDeath != true)
	{
		CInputKeyboard* pKeyBoard = CManager::GetKeyboard();
		CCamera* pCamera = CManager::GetCamera();
		CScope* pScope = CScope::GetScope();
		//CToolPlace* pTP = CToolPlace::ToolActive();
		if (SwitchStat == false)
		{
			if (pKeyBoard->GetTrigger(DIK_LSHIFT) == true)
			{
				SwitchStat = true;
			}
		}

		else if (SwitchStat == true)
		{
				if (pKeyBoard->GetTrigger(DIK_LSHIFT) == true)
				{
					SwitchStat = false;
				}
		}


		if (SwitchStat == false)
		{
			/*==================�ړ�==================*/
			if (pKeyBoard->GetPress(DIK_D) == true)
			{
				m_pos.x += move.x;

			}

			if (pKeyBoard->GetPress(DIK_A) == true)
			{
				m_pos.x -= move.x;

			}
			/*=========================================*/

			/*================�W�����v==================*/
			if (pKeyBoard->GetTrigger(DIK_SPACE) == true)
			{
			if (m_PJump >= 1)
				{
					m_Land = false;
					move.y += 1.5;
					m_PJump--;
					m_Land = false;
					
					if (m_PJump <= 0)
					{
						move.y += 0.1;
						m_Grav = 0.75;
						m_Jump = false;
					}
				}
			}
			/*=========================================*/

			if (m_Land == false)
			{
				m_pos.y +=  move.y - m_Grav;
				m_Grav += .075;
			}

			else
			{
				m_Land = true;
				m_Jump = true;
				m_Grav = 0.0f;
				move.y = .0f;
				m_PJump = 2;
			}
		}

		if (SwitchStat == true)
		{
			if (m_Land == false)
			{
				m_pos.y += move.y - m_Grav;
				m_Grav += .075;
			}
			else
			{
				m_Land = true;
				m_Jump = true;
				m_Grav = 0.0f;
				move.y = .0f;
				m_PJump = 2;
			}
			if (m_Ammo > 0)
			{
				if (pKeyBoard->GetTrigger(DIK_SPACE) == true)
				{
					CBullet::Create(m_pos, pScope->m_pos, D3DXVECTOR3(0, 0, 0), true, true);
					m_Ammo--;
				}
			}

			else
			{
				if (m_CoolDown > 0)
				{
					m_CoolDown--;
				}

				else
				{
					m_CoolDown = 60;
					m_Ammo = 5;
				}
			}

		}

		m_posOld = m_pos;
		if (m_pos.y < -500)
		{
			m_pos = StartPos;
		}
	}

	else
	{
		Uninit();
	}
}

/*=============================
//�`��
=============================*/

void CPlayerX::Draw()
{
	if (m_bDeath != true && IsUse == true)
	{
		//�f�o�C�X�擾
		CRenderer* pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
		D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
		//D3DMATERIAL9 matDef;			//�}�e���A���ۑ��p
		//D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

		pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		//���[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&m_mtxWorld);

		//���[���h�ϊ��s��̍쐬

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_rot.y, m_rot.x, m_rot.z);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x, m_pos.y, m_pos.z);

		//���[���h�ϊ��s��̐ݒ�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//for (int i = 0; i < PARTS; i++)
		//{
		//	if (m_apModel[i] != nullptr)
		//	{
				m_apModel[0]->Draw();
		//	}
		//}
	}
}

/*=============================
//�_���[�W����
=============================*/

void CPlayerX::Damage(int DMG)
{
	if (DMG < 0)
	{
		DMG = DMG * (-1);
		CN_Stock::SetStock(DMG, false);
	}
	else
	{
		CN_Stock::SetStock(DMG, true);
	}
}


/*=============================
//����
=============================*/

CPlayerX* CPlayerX::Create(D3DXVECTOR3 pos)
{
	if (m_apPlayerX != nullptr)
	{
		m_apPlayerX = nullptr;
	}

	if (m_apPlayerX  == nullptr)
	{
		m_apPlayerX = new CPlayerX();
		m_apPlayerX->m_pos = pos;
		m_apPlayerX->IsUse = true;
		m_apPlayerX->Init();
	}

	return m_apPlayerX;
}

/*==============================
//�擾
==============================*/

CPlayerX* CPlayerX::GetPlayer()
{
	return m_apPlayerX;
}