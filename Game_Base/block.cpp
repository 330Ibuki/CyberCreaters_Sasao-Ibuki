/*==========================================
*
* 3D(2D)ACTSTG_Block
* Author: Sasao Ibuki
*
===========================================*/

//�C���N���[�h
#include"block.h"
#include"object.h"
#include"collision.h"
#include "tool.h"
#include"renderer.h"
#include"manager.h"

//�ÓI�����o������
int CBlock::BlockNum = NULL;
int CFloorRoof::FRNum = NULL;
int CFloorWall::FWNum = NULL;
int CPlatform::Plat = NULL;
int CGround::Ground = NULL;
int CSG::SGNum = NULL;
CBlock* CBlock::m_apBlock[MOBJ] = {};
CFloorRoof* CFloorRoof::m_apFRoof[FROOF] = {};
CFloorWall* CFloorWall::m_apFWall[FROOF] = {};
CPlatform* CPlatform::m_apPlat[PLAT] = {};
CGround* CGround::m_apGround[GROUND] = {};
CSG* CSG::m_apSG[MSG] = {};

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CBlock::CBlock():CObjectX(m_Priority = 2)
{
	BlockNum++;
}

CBlock::~CBlock()
{
	BlockNum--;
}

/*============================
//������
============================*/

HRESULT CBlock::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���  data\\MODEL\\bullet_test
	D3DXLoadMeshFromX(
		"data\\MODEL\\BoxV4.x",
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

/*============================
//�I��
============================*/

void CBlock::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//�X�V
============================*/

void CBlock::Update()
{
	if (IsUse == true)
	{
		CObjectX::Update();
	}

	else
	{
		CBlock::Uninit();
	}
}

/*============================
//�`��
============================*/

void CBlock::Draw()
{
	if (IsUse == true)
	{
		CObjectX::Draw();
	}
}

/*============================
//�擾
============================*/

CBlock* CBlock::GetBlock(int Num)
{
	return m_apBlock[Num];
}

int CBlock::GetNumBlock()
{
	return BlockNum;
}

/*============================
//����
============================*/

CBlock* CBlock::Create(D3DXVECTOR3 pos)
{
	int Num = CBlock::GetNumBlock();

	if (m_apBlock[Num] != nullptr)
	{
		m_apBlock[Num] = nullptr;
	}

	if (m_apBlock[Num] == nullptr)
	{
		m_apBlock[Num] = new CBlock();
		m_apBlock[Num]->m_pos = pos;
		m_apBlock[Num]->IsUse = true;
		m_apBlock[Num]->Init();
	}

	return m_apBlock[Num];
}

/*=======================
//
//�K�w�V��+��
//
========================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CFloorRoof::CFloorRoof() : CBlock()
{
	FRNum++;
}

CFloorRoof::~CFloorRoof()
{
	FRNum--;
}

/*============================
//������
============================*/

HRESULT CFloorRoof::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\RoofV1.x",
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

/*============================
//�I��
============================*/

void CFloorRoof::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//�X�V
============================*/

void CFloorRoof::Update()
{
	if (IsUse == true)
	{
		CObjectX::Update();
	}

	else
	{
		CFloorRoof::Uninit();
	}
}

/*============================
//�`��
============================*/

void CFloorRoof::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//�擾
============================*/

CFloorRoof* CFloorRoof::GetFloor(int Num)
{
	return m_apFRoof[Num];
}

int CFloorRoof::GetFRNum()
{
	return FRNum;
}

/*============================
//����
============================*/

CFloorRoof* CFloorRoof::Create(D3DXVECTOR3 pos)
{
	int Num = CFloorRoof::GetFRNum();

	if (m_apFRoof[Num] != nullptr)
	{
		m_apFRoof[Num] = nullptr;
	}

	if (m_apFRoof[Num] == nullptr)
	{
		m_apFRoof[Num] = new CFloorRoof();
		m_apFRoof[Num]->m_pos = pos;
		m_apFRoof[Num]->IsUse = true;
		m_apFRoof[Num]->Init();

	}

	return m_apFRoof[Num];
}

/*=======================
//
//�K�w ��
//
========================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CFloorWall::CFloorWall() : CBlock()
{
	FWNum++;
}

CFloorWall::~CFloorWall()
{
	FWNum--;
}

/*============================
//������
============================*/

HRESULT CFloorWall::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\WallV3.x",
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

/*============================
//�I��
============================*/

void CFloorWall::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//�X�V
============================*/

void CFloorWall::Update()
{
	if (IsUse == true)
	{
		CObjectX::Update();
	}

	else
	{
		CFloorWall::Uninit();
	}
}

/*============================
//�`��
============================*/

void CFloorWall::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//�擾
============================*/

CFloorWall* CFloorWall::GetWall(int Num)
{
	return m_apFWall[Num];
}

int CFloorWall::GetFWNum()
{
	return FWNum;
}

/*============================
//����
============================*/

CFloorWall* CFloorWall::Create(D3DXVECTOR3 pos)
{
	int Num = CFloorWall::GetFWNum();

	if (m_apFWall[Num] != nullptr)
	{
		m_apFWall[Num] = nullptr;
	}

	if (m_apFWall[Num] == nullptr)
	{
		m_apFWall[Num] = new CFloorWall();
		m_apFWall[Num]->m_pos = pos;
		m_apFWall[Num]->IsUse = true;
		m_apFWall[Num]->Init();
		
	}

	return m_apFWall[Num];
}

/*=======================
//
//�v���b�g�t�H�[��
//
========================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CPlatform::CPlatform() : CBlock()
{
	P_type = SMALL;
	Plat++;
}

CPlatform::~CPlatform()
{
	Plat--;
}

/*============================
//������
============================*/

HRESULT CPlatform::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���
	if (P_type == CPlatform::PType::SMALL)
	{
		D3DXLoadMeshFromX(
			"data\\MODEL\\platformV2_short.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

	else if (P_type == CPlatform::PType::MIDDLE)
	{
		D3DXLoadMeshFromX(
			"data\\MODEL\\platform_middle.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}



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

/*============================
//�I��
============================*/

void CPlatform::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//�X�V
============================*/

void CPlatform::Update()
{
	if (IsUse == true)
	{
		CObjectX::Update();
	}

	else
	{
		CPlatform::Uninit();
	}
}

/*============================
//�`��
============================*/

void CPlatform::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//�擾
============================*/

CPlatform* CPlatform::GetPlat(int Num)
{
	return m_apPlat[Num];
}

int CPlatform::GetPlatNum()
{
	return Plat;
}

/*============================
//����
============================*/

CPlatform* CPlatform::Create(D3DXVECTOR3 pos,PType type)
{
	int Num = CPlatform::GetPlatNum();
	if (m_apPlat[Num] != nullptr)
	{
		m_apPlat[Num] = nullptr;
	}

	if (m_apPlat[Num] == nullptr)
	{
		m_apPlat[Num] = new CPlatform();
		m_apPlat[Num]->m_pos = pos;
		m_apPlat[Num]->P_type = type;
		m_apPlat[Num]->IsUse = true;
		m_apPlat[Num]->Init();
		
	}
	return m_apPlat[Num];
}

/*=======================
//
//�n��
//
========================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CGround::CGround() : CBlock()
{
	G_type = NULL;
	Ground++;
}

CGround::~CGround()
{
	Ground--;
}

/*============================
//������
============================*/

HRESULT CGround::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���
	if (G_type == CGround::GType::SMALL)
	{
		D3DXLoadMeshFromX(
			"data\\MODEL\\GroundV2_short.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

	else if (G_type == CGround::GType::MIDDLE)
	{
		D3DXLoadMeshFromX(
			"data\\MODEL\\GroundV2_middle.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

	else if (G_type == CGround::GType::BIG)
	{
		D3DXLoadMeshFromX(
			"data\\MODEL\\GroundV2_big.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

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

/*============================
//�I��
============================*/

void CGround::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//�X�V
============================*/

void CGround::Update()
{
	if (IsUse == true)
	{
		CObjectX::Update();
	}

	else
	{
		CGround::Uninit();
	}
}

/*============================
//�`��
============================*/

void CGround::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//�擾
============================*/

CGround* CGround::GetGround(int Num)
{
	return m_apGround[Num];
}

int CGround::GetPlatNum()
{
	return Ground;
}

/*============================
//����
============================*/

CGround* CGround::Create(D3DXVECTOR3 pos, GType G_type)
{
	int Num = CGround::GetPlatNum();

	if (m_apGround[Num] != nullptr)
	{
		m_apGround[Num] = nullptr;
	}

	if (m_apGround[Num] == nullptr)
	{
		m_apGround[Num] = new CGround();
		m_apGround[Num]->m_pos = pos;
		m_apGround[Num]->G_type = G_type;
		m_apGround[Num]->IsUse = true;
		m_apGround[Num]->Init();
		
	}

	return m_apGround[Num];
}

/*==============================================
//�X�^�[�g�E�S�[��
==============================================*/

/*==============================
//�R���X�g���N�^�E�f�X�g���N�^
==============================*/

CSG::CSG()
{
	IsStart = true;
	SGNum++;
}

CSG::~CSG()
{
	SGNum--;
}

/*==============================
//������
==============================*/
HRESULT CSG::Init()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�p�����[�^�̏����ݒ�
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X�ǂݍ���
	if (IsStart == true)
	{
		D3DXLoadMeshFromX(
			"data\\MODEL\\Start.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

	else if (IsStart == false)
	{//�S�[��
		D3DXLoadMeshFromX(
			"data\\MODEL\\Goal.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}

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

/*==============================
//�j��
==============================*/
void CSG::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*==============================
//�X�V
==============================*/
void CSG::Update()
{
	if (IsUse == true)
	{
		CObjectX::Update();
	}

	else
	{
		CSG::Uninit();
	}
}

/*==============================
//�`��
==============================*/
void CSG::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*==============================
//�擾
==============================*/
CSG* CSG::GetSG(int Num)
{
	return m_apSG[Num];
}

int CSG::GetSGNum()
{
	return SGNum;
}
/*==============================
//����
==============================*/
CSG* CSG::Create(D3DXVECTOR3 pos, bool IsStart)
{
	int SGNum = CSG::GetSGNum();

	if (m_apSG[SGNum] != nullptr)
	{
		m_apSG[SGNum] = nullptr;
	}

	if (m_apSG[SGNum] == nullptr)
	{
		m_apSG[SGNum] = new CSG();
		m_apSG[SGNum]->m_pos = pos;
		m_apSG[SGNum]->IsStart = IsStart;
		m_apSG[SGNum]->IsUse = true;
		m_apSG[SGNum]->Init();
	}

	return m_apSG[SGNum];
}