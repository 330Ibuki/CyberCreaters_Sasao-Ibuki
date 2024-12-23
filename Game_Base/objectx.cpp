/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include "objectx.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"

//�ÓI�����o������
CObjectX* CObjectX::m_apObjectX[MOBJ] = {};

/*=====================================
//�R���X�g���N�^�E�f�X�g���N�^
=====================================*/

CObjectX::CObjectX(int nPriority) : CObject(m_Priority)
{
	m_pos = {};
	m_posOld = {};
	m_rot = {};
	m_pVtxBuff = nullptr;
	m_ptex = nullptr;
	m_dwNumMat = {};
	m_pBuffMat = {};
	m_pMesh = {};
	OnCol = false;
	m_bDeath = false;
	m_Priority = nPriority;
	m_Flame_Count = NULL;
	OBJ_ID = NULL;
}

CObjectX::~CObjectX()
{

}

/*====================================
//�����ݒ�
====================================*/

HRESULT CObjectX::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL,NULL,NULL);

	//X�ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\box_test.x",
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

/*====================================
//�j��
====================================*/

void CObjectX::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	if (m_ptex != nullptr)
	{
		m_ptex->Release();
		m_ptex = nullptr;
	}

	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	this->Release();
}

/*====================================
//�X�V
====================================*/

void CObjectX::Update()
{

}

/*====================================
//�`��
====================================*/

void CObjectX::Draw()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//�}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

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

	//�}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();


	for (int i = 0; i < (int)m_dwNumMat; i++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, m_ptex);

		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//���f���`��
		m_pMesh->DrawSubset(i);

		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

/*====================================
//����
====================================*/

//CObjectX* CObjectX::Create(D3DXVECTOR3 pos)
//{
//	int BCnt = CObjectX::GetNumBlock();
//
//	if (m_apObjectX[BCnt] == nullptr)
//	{
//		m_apObjectX[BCnt] = new CObjectX();
//		m_apObjectX[BCnt]->m_pos = pos;
//		m_apObjectX[BCnt]->Init();
//	}
//
//	return m_apObjectX[BCnt];
//}

/*====================================
//�擾
====================================*/



CObjectX* CObjectX::Getobj(int B_Num)
{
	
	return m_apObjectX[B_Num];
}

/*====================================
//
====================================*/



/*====================================
//
====================================*/