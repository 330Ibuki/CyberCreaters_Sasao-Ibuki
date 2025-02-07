/*==========================================
*
* 3D(2D)ACTSTG_Block
* Author: Sasao Ibuki
*
===========================================*/

//インクルード
#include"block.h"
#include"object.h"
#include"collision.h"
#include "tool.h"
#include"renderer.h"
#include"manager.h"

//静的メンバ初期化
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
//コンストラクタ・デストラクタ
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
//初期化
============================*/

HRESULT CBlock::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X読み込み  data\\MODEL\\bullet_test
	D3DXLoadMeshFromX(
		"data\\MODEL\\BoxV4.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//マテリアルデータのポインタ取得
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
//終了
============================*/

void CBlock::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//更新
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
//描画
============================*/

void CBlock::Draw()
{
	if (IsUse == true)
	{
		CObjectX::Draw();
	}
}

/*============================
//取得
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
//生成
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
//階層天井+床
//
========================*/

/*============================
//コンストラクタ・デストラクタ
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
//初期化
============================*/

HRESULT CFloorRoof::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\RoofV1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//マテリアルデータのポインタ取得
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
//終了
============================*/

void CFloorRoof::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//更新
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
//描画
============================*/

void CFloorRoof::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//取得
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
//生成
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
//階層 壁
//
========================*/

/*============================
//コンストラクタ・デストラクタ
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
//初期化
============================*/

HRESULT CFloorWall::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\WallV3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//マテリアルデータのポインタ取得
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
//終了
============================*/

void CFloorWall::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//更新
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
//描画
============================*/

void CFloorWall::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//取得
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
//生成
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
//プラットフォーム
//
========================*/

/*============================
//コンストラクタ・デストラクタ
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
//初期化
============================*/

HRESULT CPlatform::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X読み込み
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



	//マテリアルデータのポインタ取得
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
//終了
============================*/

void CPlatform::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//更新
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
//描画
============================*/

void CPlatform::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//取得
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
//生成
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
//地面
//
========================*/

/*============================
//コンストラクタ・デストラクタ
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
//初期化
============================*/

HRESULT CGround::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X読み込み
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

	//マテリアルデータのポインタ取得
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
//終了
============================*/

void CGround::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*============================
//更新
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
//描画
============================*/

void CGround::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*============================
//取得
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
//生成
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
//スタート・ゴール
==============================================*/

/*==============================
//コンストラクタ・デストラクタ
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
//初期化
==============================*/
HRESULT CSG::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X読み込み
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
	{//ゴール
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

	//マテリアルデータのポインタ取得
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
//破棄
==============================*/
void CSG::Uninit()
{
	CObjectX::Uninit();
	Release();
}

/*==============================
//更新
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
//描画
==============================*/
void CSG::Draw()
{
	if (IsUse == true)
	{
		CBlock::Draw();
	}
}

/*==============================
//取得
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
//生成
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