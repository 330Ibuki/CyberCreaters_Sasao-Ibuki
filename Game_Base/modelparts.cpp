/*=======================
//ModelParts
=======================*/

//include
#include"modelparts.h"
#include "renderer.h"
#include "manager.h"

CModelParts* CModelParts::m_pModelParts[PARTLIM] = {};
int CModelParts::PartNum = NULL;

/*========================
//�R���X�g���N�^�E�f�X�g���N�^
========================*/
CModelParts::CModelParts()
{
	m_pos = {};
	/*m_posOld = {};*/
	m_rot = {};
	m_pVtxBuff = nullptr;
	m_ptex = nullptr;
	m_dwNumMat = {};
	m_pBuffMat = {};
	m_pMesh = {};
	m_pParent = nullptr;
	PartsName[FILENAME] = {};
	PartNum++;
	P_Num = NULL;
}

CModelParts::~CModelParts()
{
	PartNum--;
}

/*==========================
//������
===========================*/
HRESULT CModelParts::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���
	D3DXLoadMeshFromX(
		(char*)PartsName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

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

/*==========================
//�j��
==========================*/
void CModelParts::Uninit()
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

	
}

/*==========================
//�X�V
==========================*/
void CModelParts::Update()
{

}

/*==========================
//�`��
==========================*/
void CModelParts::Draw()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//�}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

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

	if (m_pParent != nullptr)
	{//�e�̍s����擾
		mtxParent = m_pParent->m_mtxWorld;
	}

	else
	{//�ŐV�̃��[���h�s����擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
		m_pModelParts[P_Num]->m_pMesh->DrawSubset(i);

		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

/*==========================
//�擾�E����
==========================*/
int CModelParts::GetPartsNum()
{
	return PartNum;
}

CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,char* PartsName,int PartsNum)
{
	int Parts = GetPartsNum();

	if (m_pModelParts[Parts] == nullptr)
	{
		m_pModelParts[Parts] = new CModelParts();
		m_pModelParts[Parts]->m_pos = pos;
		m_pModelParts[Parts]->m_rot = rot;
		m_pModelParts[Parts]->m_pBuffMat = nullptr;
		m_pModelParts[Parts]->m_pMesh = nullptr;
		m_pModelParts[Parts]->m_ptex = nullptr;
		m_pModelParts[Parts]->m_pVtxBuff = nullptr;
		m_pModelParts[Parts]->m_pParent = nullptr;
		m_pModelParts[Parts]->P_Num = PartsNum;
		strcpy(m_pModelParts[Parts]->PartsName, (char*)PartsName);
		m_pModelParts[Parts]->Init();
	}

	return m_pModelParts[Parts];
}

/*==========================
//�e�̐ݒ�
==========================*/
void CModelParts::SetParent(CModelParts* pParent)
{
	m_pParent = pParent;
}