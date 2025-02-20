/*===================================
//
//	UI
//
===================================*/

//�C���N���[�h
#include "BG.h"
#include "manager.h"
#include "renderer.h"
#include "player.x.h"

//�ÓI�����o������
CBG* CBG::m_BG = nullptr;
int CBG::BGNum = NULL;

/*=========================
//�R���X�g���N�^�E�f�X�g���N�^
=========================*/
CBG::CBG() : CB_board(m_Priority = 3)
{
	B_Type = NULL;
	/*IsGame = false;*/
	BGNum++;
}

CBG::~CBG()
{
	BGNum--;
}

/*============================
//������
=============================*/
HRESULT CBG::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (B_Type == BG_GAME)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\seamless_19.png",
			&m_ptex);
	}

	else if (B_Type == BG_TITLE)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Title_test.png",
			&m_ptex);
	}

	else if (B_Type == BG_RESULT)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\seamless_19.png",
			&m_ptex);
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	if (B_Type == BG_GAME)
	{
		pVtx[0].pos = D3DXVECTOR3(0 - (500), 0 + (500), 100);
		pVtx[1].pos = D3DXVECTOR3(0 + (500), 0 + (500), 100);
		pVtx[2].pos = D3DXVECTOR3(0 - (500), 0 - (500), 100);
		pVtx[3].pos = D3DXVECTOR3(0 + (500), 0 - (500), 100);
	}

	else
	{
		pVtx[0].pos = D3DXVECTOR3(0 - (170), 0 + (170), 30);
		pVtx[1].pos = D3DXVECTOR3(0 + (170), 0 + (170), 30);
		pVtx[2].pos = D3DXVECTOR3(0 - (170), 0 - (170), 30);
		pVtx[3].pos = D3DXVECTOR3(0 + (170), 0 - (170), 30);
	}

	////�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

/*==========================
//�j��
==========================*/
void CBG::Uninit()
{
	CB_board::Uninit();
	Release();
}

/*=========================
//�X�V
==========================*/
void CBG::Update()
{
	if (IsUse == false)
	{
	CBG::Uninit();
	}

	else
	{
		if (B_Type == BG_GAME)
		{
			CPlayerX* player = player->GetPlayer();
			m_pos.x = player->m_pos.x;
			m_pos.y = player->m_pos.y;
		}
	}
}

/*============================
//�`��
============================*/
void CBG::Draw()
{
	if (IsUse == true)
	{
		//�f�o�C�X�擾
		CRenderer* pRenderer = CManager::GetRenderer();

		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//���[���h�ϊ��s��̍쐬

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_rot.y, m_rot.x, m_rot.z);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x, m_pos.y, m_pos.z);

		pDevice->GetTransform(D3DTS_VIEW, &B_View);
		D3DXMatrixInverse(&B_View, nullptr, &B_View);
		B_View._11 = 1.0f;
		B_View._12 = 0.0f;
		B_View._13 = 0.0f;
		B_View._41 = 0.0f;
		B_View._42 = 0.0f;
		B_View._43 = 0.0f;

		//���[���h�ϊ��s��̐ݒ�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &B_View);

		D3DXMatrixMultiply(&m_mtxWorld, &B_View, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���֐ݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_ptex);

		//�|���S���̕`��
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

/*===========================
//�e��擾
===========================*/
CBG* CBG::GetBG()
{
	return m_BG;
}

int CBG::GetBGNum()
{
	return BGNum;
}

/*============================
//����
=============================*/

CBG* CBG::Create(BG_Type type/*, bool Game*/)
{
	int UI_Num = CBG::GetBGNum();

	if (m_BG != nullptr)
	{
		m_BG = nullptr;
		m_BG = new CBG();
		m_BG->B_Type = type;
		//m_BG->IsGame = Game;
		m_BG->IsUse = true;
		m_BG->Init();
	}

	else if (m_BG == nullptr/* && UI_Num < 2*/)
	{
		m_BG = new CBG();
		m_BG->B_Type = type;
		//m_BG->IsGame = Game;
		m_BG->IsUse = true;
		m_BG->Init();
	}
	return m_BG;
}