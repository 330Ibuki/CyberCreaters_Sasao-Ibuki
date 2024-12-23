/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include "object3d.h"
#include "renderer.h"
#include "manager.h"

//�ÓI�����o������
CObject3D* CObject3D::m_apObject3D = nullptr;

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CObject3D::CObject3D() : CObject(2)
{
	m_ptex = nullptr;
	m_pos = D3DXVECTOR3(NULL, NULL, NULL);
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);
	m_pVtxBuff = nullptr;
}

CObject3D::~CObject3D()
{

}

/*==============================
//�����ݒ�
==============================*/

HRESULT CObject3D::Init()
{
	//�f�o�C�X�擾
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//�e�N�X�`��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\seamless_55.png",
		&m_ptex);

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

	//�@���x�N�g��
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

/*==============================
//�j��
==============================*/

void CObject3D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_ptex != nullptr)
	{
		m_ptex->Release();
		m_ptex = nullptr;
	}
}

/*==============================
//�X�V
==============================*/

void CObject3D::Update()
{

}

/*==============================
//�`��
==============================*/

void CObject3D::Draw()
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

	//���[���h�ϊ��s��̐ݒ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���֐ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_ptex);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/*==============================
//���[�h
==============================*/



/*==============================
//�A�����[�h
==============================*/



/*==============================
//����
==============================*/

CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	if (m_apObject3D == nullptr)
	{
		m_apObject3D = new CObject3D();
		m_apObject3D->m_pos = pos;
		m_apObject3D->Init();
	}

	return m_apObject3D;
}