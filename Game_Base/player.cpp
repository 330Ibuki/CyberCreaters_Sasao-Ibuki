/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"



//�ÓI�����o������
CPlayer* CPlayer::m_pPlayer = nullptr;

/*=======================
//�R���X�g���N�^�E�f�X�g���N�^
=======================*/

CPlayer::CPlayer(int nPriotity) : CObject2D()
{
	m_AnimChang = 0;
	m_AnimCnt = 0;
	m_AnimPat = 0;
	m_MAnimPat = 0;
	m_bUse = false;
	m_fHeight = 0;
	m_fWidth = 0;
	m_pVtxBuff = nullptr;
	m_pPLtex = nullptr;
}

CPlayer::~CPlayer()
{

}

/*=======================
//������
=======================*/

HRESULT CPlayer::Init()
{
	m_bUse = true;
	m_AnimPat = 0;
	m_MAnimPat = 8;
	m_AnimCnt = 0;
	m_AnimChang = 5;
	m_fWidth = 100.0f;
	m_fHeight = 100.0f;
	m_pos = SENTER;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_2D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\runningman000.png",
		&m_pPLtex);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

/*=======================
//�I��
=======================*/

void CPlayer::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pPLtex != nullptr)
	{
		m_pPLtex->Release();
		m_pPLtex = nullptr;
	}
}

/*=======================
//�X�V
=======================*/

void CPlayer::Update()
{
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_AnimCnt++;

	if (m_AnimCnt % m_AnimChang == 0)
	{
		m_AnimPat++;

		if (m_AnimPat >= m_MAnimPat)
		{
			m_AnimPat = 0;
		}
	}

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	/*pVtx[0].tex = D3DXVECTOR2(0.18f * (float)(m_AnimPat), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.18f + 0.18f * (float)(m_AnimPat), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.18f * (float)(m_AnimPat), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.18f + 0.18f * (float)(m_AnimPat), 1.0f);*/

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

/*=======================
//�`��
=======================*/

void CPlayer::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = pRenderer->GetDevice();
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, m_pPLtex);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

/*=======================
//�I��
=======================*/

CPlayer* CPlayer::Create()
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer();
		m_pPlayer->Init();
	}

	return m_pPlayer;
}