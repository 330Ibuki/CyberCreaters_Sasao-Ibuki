/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/
 
/*=======================
//�C���N���[�h
=======================*/

#include "main.h"
#include "object2d.h"
#include "renderer.h"
#include "player.h"
#include "manager.h"

/*=======================
//�ÓI�����o������
=======================*/

CObject2D* CObject2D::m_apObject2D = nullptr;

/*=======================
//�R���X�g���N�^�E�f�X�g���N�^
=======================*/

CObject2D::CObject2D(int nPriority) : CObject(m_Priority = 0)
{
	m_AnimChang = 0;
	m_AnimCnt = 0;
	m_AnimPat = 0;
	m_MAnimPat = 0;
	m_bUse = false;
	m_fHeight = 0;
	m_fWidth = 0;
	m_pVtxBuff = nullptr;
	m_pTex = nullptr;
}

CObject2D::~CObject2D()
{
	
}

/*=======================
//������
=======================*/

HRESULT CObject2D::Init()
{
	m_bUse = true;          
	m_fWidth = 20.0f;       
	m_fHeight = 20.0f;      
	m_pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f);
	//m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	VERTEX_2D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\img_005.png",
		&m_pTex);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, m_pos.z);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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

void CObject2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTex != nullptr)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}
}

/*=======================
//�X�V
=======================*/

void CObject2D::Update()
{
	//VERTEX_2D* pVtx;

	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	////rhw�̐ݒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f,1.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f,1.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f,0.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f,0.0f);

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();
}

/*=======================
//�`��
=======================*/

void CObject2D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, m_pTex);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/*=======================
//����
=======================*/

CObject2D* CObject2D::Create()
{
	if (m_apObject2D == nullptr)
	{
		m_apObject2D = new CObject2D();
		m_apObject2D->Init();
	}

	return m_apObject2D;
}


/*========================
//�e�N�X�`���ݒ�
========================*/

void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}