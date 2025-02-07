/*==========================
#
# UI_Scope
#
==========================*/

//�C���N���[�h
#include "scope.h"
#include "player.x.h"
#include "tool.h"

//�ÓI�����o������

CScope* CScope::m_scope = nullptr;

/*=============================
// �R���X�g���N�^�E�f�X�g���N�^
==============================*/

CScope::CScope() :CB_board(m_Priority = 4)
{

}

CScope::~CScope()
{

}

/*=============================
// ������
==============================*/

HRESULT CScope::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Scope.png",
		&m_ptex);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, 0);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, 0);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, 0);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, 0);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}

/*=============================
// �I��
==============================*/

void CScope::Uninit()
{
	CB_board::Uninit();
}

/*=============================
// �X�V
==============================*/

void CScope::Update()
{
	CInputKeyboard* pKeyBoard = CManager::GetKeyboard();
	CPlayerX* pPlayerX = pPlayerX->GetPlayer();
	if (pPlayerX != nullptr)
	{
		if (pPlayerX->SwitchStat == true)
		{
			if (pKeyBoard->GetPress(DIK_W) == true)
			{
				m_pos.y += 2.5;
			}

			if (pKeyBoard->GetPress(DIK_S) == true)
			{
				m_pos.y += -2.5;
			}

			if (pKeyBoard->GetPress(DIK_A) == true)
			{
				m_pos.x += -2.5;
			}

			if (pKeyBoard->GetPress(DIK_D) == true)
			{
				m_pos.x += 2.5;
			}
		}

		else
		{
			m_pos.x = pPlayerX->m_pos.x;
			m_pos.y = pPlayerX->m_pos.y + 40;
		}
	}

	else
	{
		CB_board::Update();
	}

	m_posOld = m_pos;
}

/*=============================
// �`��
==============================*/

void CScope::Draw()
{
	CB_board::Draw();
}

/*=============================
// �擾�E����
==============================*/

CScope* CScope::GetScope()
{
	return m_scope;
}

CScope* CScope::Create(D3DXVECTOR3 pos)
{
	if (m_scope != nullptr)
	{
		/*delete m_scope;*/
		m_scope = nullptr;
	}

	if (m_scope == nullptr)
	{
		m_scope = new CScope();

		m_scope->IsUse = true;
		m_scope->B_Height = 10.0f;
		m_scope->B_Width = 10.0f;
		m_scope->m_pos = pos;

		m_scope->Init();
	}

	return m_scope;
}