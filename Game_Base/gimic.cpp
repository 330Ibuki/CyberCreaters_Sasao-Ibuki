/*==========================================
*
* 3D(2D)ACTSTG_Gimic
* Author: Sasao Ibuki
*
===========================================*/

//�C���N���[�h
#include"gimic.h"
#include"object.h"
#include"collision.h"
#include"renderer.h"
#include"manager.h"

//�ÓI�����o������
CGimic* CGimic::m_apGimic[MGIMC] = {};
int CGimic::GimNum = 0;

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CGimic::CGimic() :CObjectX(m_Priority = 3)
{
	m_move = {};
	m_Rift_Set = 0;
	m_Rift_timer = 0;
	m_Rift_Count = 0;
	m_Rift_BCount = 0;
	m_Rift = {};
}

CGimic::~CGimic()
{

}

/*============================
//������
============================*/

HRESULT CGimic::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\gimic_test.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);


	//�}�e���A���f�[�^�̃|�C���^�擾


	return S_OK;
}

/*============================
//�I��
============================*/

void CGimic::Uninit()
{
	CObjectX::Uninit();
}

/*============================
//�X�V
============================*/

void CGimic::Update()
{
	m_Flame_Count++;
	for (int i = 0; i < MGIMC; i++)
	{
		if (m_apGimic[i] != nullptr)
		{
			/*===============���E����================*/
			if (m_Rift == NORMAL)
			{
				if (m_apGimic[i]->m_Rift_Count == 5)
				{
					m_apGimic[i]->m_move.x= m_move.x * -1;
					m_apGimic[i]->m_Rift_Count = 0;
				}
				m_apGimic[i]->m_pos.x += m_move.x;

			}
			/*=======================================*/

			/*============���E�����i���]�j===========*/
			if (m_Rift == REVERSE)
			{
				if (m_apGimic[i]->m_Rift_Count == 5)
				{
					m_apGimic[i]->m_move.x = m_move.x * -1;
					m_apGimic[i]->m_Rift_Count = 0;
				}
				m_apGimic[i]->m_pos.x += m_move.x * -1;
			}
			/*=======================================*/

		}
	}

	if (m_Flame_Count % 60 == 0)
	{
		for (int i = 0; i < MGIMC; i++)
		{
			if (m_apGimic[i] != nullptr)
			{
				m_apGimic[i]->m_Rift_Count++;
			}
		}
		m_Flame_Count = 0;
	}
}

/*============================
//�`��
============================*/

void CGimic::Draw()
{
	CObjectX::Draw();
}

/*============================
//�擾
============================*/

CGimic* CGimic::GetGimic(int Num)
{
	return m_apGimic[Num];
}

int CGimic::GetGimNum()
{
	return GimNum;
}

/*============================
//����
============================*/

CGimic* CGimic::Create(D3DXVECTOR3 pos, D3DXVECTOR3 mov, G_TYPE type)
{
	int Num = CGimic::GetGimNum();

	if (m_apGimic[Num] == nullptr)
	{
		m_apGimic[Num] = new CGimic();
		m_apGimic[Num]->m_pos = pos;
		m_apGimic[Num]->m_move = mov;
		m_apGimic[Num]->m_Rift = type;
		m_apGimic[Num]->Init();
		GimNum++;
	}

	return m_apGimic[Num];
}